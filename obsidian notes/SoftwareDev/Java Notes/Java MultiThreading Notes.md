

## Simple Thread creation

```java
public class myTask implements Runnable{

	@Override
	public void run(){
	// your task or code
	}
}

public static void main(String args[])
{

	Thread thread = new Thread(new myTask());
	thread.start();
}


```

### Producer Consumer problem

```java

public class Buffer{

	private List<Integer> buffer = new ArrayList<>();
	private Boolean done = false;
	
	public void syncronized addIntoBuffer(value){
		buffer.add(value);
		notify();
	}

	public void syncronized markDone(){

		this.done = true;
	}

	public void syncronized consumeItem(){

		while(true)
		{
			if(!done && buffer.empty())
				wait();
			else if(done)
				break;
			else
			{
				System.out.println("Consuming "+ buffer.pop());
			}
		}
	}


}


public static void main(String args[])
{

	Buffer sharedResource = new Buffer();
	
	Thread producer = new Thread(()->{

		for(int i=0;i<10;i++)
		{
			sharedResource.addIntoBuffer();
			thread.sleep(2000);
		}
		markDone();
	})

	Thread consumer = new Thread(()->{
		sharedResource.consumeItem()
	})
}

```


#### Thread join
* When join method is invoked on a thread object, current thread will be blocked and waits for the specific thread to finish.

#### Thread priority
* Ranges from 1 to 10.
* Its just an suggestion not a mandate.

#### Daemon thread
* th.setDaemon(true);
* If all user thread stops working then only Daemon thread will stop.


## Locks 

#### ReentrantLock
* Reentrancy: If a thread already holds the lock and calls a method that also requires the lock, the thread can re-enter and acquire the lock again without being blocked.
```java
import java.util.concurrent.locks.ReentrantLock;

class BankAccount {
    private double balance;
    private final ReentrantLock sharedLock;  // Shared lock across both accounts

    public BankAccount(double initialBalance, ReentrantLock sharedLock) {
        this.balance = initialBalance;
        this.sharedLock = sharedLock;  // Shared lock passed in
    }

    // Method to deposit money to the account
    public void deposit(double amount) {
        sharedLock.lock();  // Lock shared between two accounts
        try {
            balance += amount;
            System.out.println(Thread.currentThread().getName() + " deposited $" + amount + ", new balance: $" + balance);
        } finally {
            sharedLock.unlock();  // Always unlock in the 'finally' block to avoid deadlocks
        }
    }

    // Method to withdraw money from the account
    public void withdraw(double amount) {
        sharedLock.lock();  // Lock shared between two accounts
        try {
            if (balance >= amount) {
                balance -= amount;
                System.out.println(Thread.currentThread().getName() + " withdrew $" + amount + ", new balance: $" + balance);
            } else {
                System.out.println(Thread.currentThread().getName() + " attempted to withdraw $" + amount + " but has insufficient funds.");
            }
        } finally {
            sharedLock.unlock();  // Always unlock to avoid deadlocks
        }
    }

    // Method to transfer money between accounts
    public void transfer(BankAccount target, double amount) {
        sharedLock.lock();  // Locking shared across both accounts
        try {
            if (this.balance >= amount) {
                this.withdraw(amount);
                target.deposit(amount);
                System.out.println(Thread.currentThread().getName() + " transferred $" + amount + " from " + this + " to " + target);
            } else {
                System.out.println(Thread.currentThread().getName() + " has insufficient balance to transfer $" + amount);
            }
        } finally {
            sharedLock.unlock();  // Unlocking shared lock
        }
    }

    @Override
    public String toString() {
        return "Account@" + Integer.toHexString(hashCode()) + " with balance $" + balance;
    }
}

public class SharedLockExample {
    public static void main(String[] args) throws InterruptedException {
        ReentrantLock sharedLock = new ReentrantLock();  // Single lock shared between two accounts

        BankAccount account1 = new BankAccount(1000, sharedLock);
        BankAccount account2 = new BankAccount(1000, sharedLock);

        Thread t1 = new Thread(() -> {
            account1.transfer(account2, 500);
        }, "Thread-1");

        Thread t2 = new Thread(() -> {
            account2.transfer(account1, 300);
        }, "Thread-2");

        t1.start();
        t2.start();

        t1.join();
        t2.join();
    }
}

```

#### ReadWriteLock
```java
import java.util.concurrent.locks.ReentrantReadWriteLock;

class BankAccount {
    private double balance;
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();  // ReadWriteLock instance

    public BankAccount(double initialBalance) {
        this.balance = initialBalance;
    }

    // Method to read the balance
    public double getBalance() {
        lock.readLock().lock();  // Acquire the read lock
        try {
            System.out.println(Thread.currentThread().getName() + " read balance: $" + balance);
            return balance;
        } finally {
            lock.readLock().unlock();  // Release the read lock
        }
    }

    // Method to deposit money
    public void deposit(double amount) {
        lock.writeLock().lock();  // Acquire the write lock
        try {
            balance += amount;
            System.out.println(Thread.currentThread().getName() + " deposited $" + amount + ", new balance: $" + balance);
        } finally {
            lock.writeLock().unlock();  // Release the write lock
        }
    }

    // Method to withdraw money
    public void withdraw(double amount) {
        lock.writeLock().lock();  // Acquire the write lock
        try {
            if (balance >= amount) {
                balance -= amount;
                System.out.println(Thread.currentThread().getName() + " withdrew $" + amount + ", new balance: $" + balance);
            } else {
                System.out.println(Thread.currentThread().getName() + " attempted to withdraw $" + amount + " but has insufficient funds.");
            }
        } finally {
            lock.writeLock().unlock();  // Release the write lock
        }
    }
}
```

#### Stamped lock
```java
import java.util.concurrent.locks.StampedLock;

class BankAccount {
    private double balance;
    private final StampedLock lock = new StampedLock();  // StampedLock instance

    public BankAccount(double initialBalance) {
        this.balance = initialBalance;
    }

    // Method to get the balance with optimistic read
    public double getBalance() {
        long stamp = lock.tryOptimisticRead();  // Optimistic read lock
        double currentBalance = balance;  // Read the balance
        // Check if the stamp is still valid (i.e., no write occurred during the read)
        if (!lock.validate(stamp)) {
            stamp = lock.readLock();  // Fall back to read lock if optimistic read was invalid
            try {
                currentBalance = balance;  // Read again under a read lock
            } finally {
                lock.unlockRead(stamp);  // Release the read lock
            }
        }
        System.out.println(Thread.currentThread().getName() + " read balance: $" + currentBalance);
        return currentBalance;
    }

    // Method to deposit money
    public void deposit(double amount) {
        long stamp = lock.writeLock();  // Acquire write lock
        try {
            balance += amount;
            System.out.println(Thread.currentThread().getName() + " deposited $" + amount + ", new balance: $" + balance);
        } finally {
            lock.unlockWrite(stamp);  // Release the write lock
        }
    }

    // Method to withdraw money
    public void withdraw(double amount) {
        long stamp = lock.writeLock();  // Acquire write lock
        try {
            if (balance >= amount) {
                balance -= amount;
                System.out.println(Thread.currentThread().getName() + " withdrew $" + amount + ", new balance: $" + balance);
            } else {
                System.out.println(Thread.currentThread().getName() + " attempted to withdraw $" + amount + " but has insufficient funds.");
            }
        } finally {
            lock.unlockWrite(stamp);  // Release the write lock
        }
    }
}
```

### signal and await

If you are using above locks you need to use signal() for notify() and await() for wait().

```java
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class Buffer {
    private final Queue<Integer> queue = new LinkedList<>();
    private final int capacity;
    private final ReentrantLock lock = new ReentrantLock();
    private final Condition notFull = lock.newCondition();  // Condition for producer
    private final Condition notEmpty = lock.newCondition(); // Condition for consumer

    public Buffer(int capacity) {
        this.capacity = capacity;
    }

    // Producer adds items to the buffer
    public void produce(int item) throws InterruptedException {
        lock.lock();
        try {
            while (queue.size() == capacity) {
                System.out.println(Thread.currentThread().getName() + ": Buffer is full, waiting...");
                notFull.await();  // Wait until there's space in the buffer
            }

            queue.offer(item);
            System.out.println(Thread.currentThread().getName() + ": Produced " + item);
            notEmpty.signal();  // Signal the consumer that the buffer is not empty
        } finally {
            lock.unlock();
        }
    }

    // Consumer removes items from the buffer
    public int consume() throws InterruptedException {
        lock.lock();
        try {
            while (queue.isEmpty()) {
                System.out.println(Thread.currentThread().getName() + ": Buffer is empty, waiting...");
                notEmpty.await();  // Wait until there's an item to consume
            }

            int item = queue.poll();
            System.out.println(Thread.currentThread().getName() + ": Consumed " + item);
            notFull.signal();  // Signal the producer that the buffer is not full
            return item;
        } finally {
            lock.unlock();
        }
    }
}

class Producer implements Runnable {
    private final Buffer buffer;

    public Producer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        int item = 0;
        while (true) {
            try {
                buffer.produce(item++);
                Thread.sleep(500);  // Simulate time taken to produce
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}

class Consumer implements Runnable {
    private final Buffer buffer;

    public Consumer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            try {
                buffer.consume();
                Thread.sleep(1000);  // Simulate time taken to consume
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }
        }
    }
}

public class ProducerConsumerWithReentrantLock {
    public static void main(String[] args) {
        Buffer buffer = new Buffer(5);  // Buffer with a capacity of 5 items

        Thread producerThread = new Thread(new Producer(buffer), "Producer");
        Thread consumerThread = new Thread(new Consumer(buffer), "Consumer");

        producerThread.start();
        consumerThread.start();
    }
}

```


## Atomic Variables
- `AtomicInteger` is used to store and manipulate an integer value in a thread-safe manner.
- The `incrementAndGet()` method atomically increments the integer by one and returns the updated value.
- The `get()` method retrieves the current value atomically.
```java
    private final AtomicInteger count = new AtomicInteger(0);  // AtomicInteger instanc
```

## Concurrent Collections
```java

ConcurrentHashMap<String, Integer> map = new ConcurrentHashMap<>();

CopyOnWriteArrayList<String> list = new CopyOnWriteArrayList<>();

ConcurrentLinkedQueue<Integer> queue = new ConcurrentLinkedQueue<>();

BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(3); // Fixed capacity of 3
```

- **`ConcurrentHashMap`**: Best suited for scenarios where many threads need to read and write concurrently with minimal contention.
- **`CopyOnWriteArrayList`**: Ideal for situations where reads are frequent and writes are rare, such as managing a list of listeners in an event system.
- **`ConcurrentLinkedQueue`**: Non-blocking, lock-free queue suitable for lightweight concurrent access where the order of items matters.
- **`BlockingQueue`**: Useful for producer-consumer scenarios where threads may need to block until the queue becomes available.


## Thread Pools

### Thread Pool Executor

`ThreadPoolExecutor` is a class in Java that provides a flexible, scalable thread pool framework for managing multiple threads efficiently. It allows you to create and control a pool of threads, set the number of core and maximum threads, and manage the lifecycle of tasks executed in the pool.
```java
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

class Task implements Runnable {
    private final String name;

    public Task(String name) {
        this.name = name;
    }

    @Override
    public void run() {
        try {
            System.out.println(Thread.currentThread().getName() + " is executing task " + name);
            Thread.sleep(2000);  // Simulate task execution time
            System.out.println(Thread.currentThread().getName() + " has completed task " + name);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class ThreadPoolExecutorExample {
    public static void main(String[] args) {
        // Create a ThreadPoolExecutor with corePoolSize=2, maxPoolSize=4, queueSize=2
        ThreadPoolExecutor executor = new ThreadPoolExecutor(
                2,                                      // Core pool size
                4,                                      // Maximum pool size
                60,                                     // Keep-alive time for idle threads
                TimeUnit.SECONDS,                       // Keep-alive time unit
                new LinkedBlockingQueue<>(2),           // Work queue with a capacity of 2
                Executors.defaultThreadFactory(),       // Thread factory
                new ThreadPoolExecutor.CallerRunsPolicy()  // Rejected task handler
        );

        // Submit 6 tasks to the executor
        for (int i = 1; i <= 6; i++) {
            Task task = new Task("Task-" + i);
            System.out.println("Submitting " + task.name);
            executor.execute(task);
        }

        // Shut down the executor once all tasks are submitted
        executor.shutdown();
        try {
            if (!executor.awaitTermination(10, TimeUnit.SECONDS)) {
                executor.shutdownNow();  // Forcefully shut down if tasks are not completed
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
        }
    }
}

```


## Future and Callable
```java
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

class Task implements Callable<String> {
    private final String name;

    public Task(String name) {
        this.name = name;
    }

    @Override
    public String call() throws Exception {
        System.out.println(Thread.currentThread().getName() + " is executing " + name);
        Thread.sleep(2000);  // Simulate a task taking some time
        return "Result of " + name;
    }
}

public class CallableFutureExample {
    public static void main(String[] args) throws Exception {
        ExecutorService executor = Executors.newFixedThreadPool(3);

        // Submit Callable tasks and get Future objects
        Future<String> future1 = executor.submit(new Task("Task-1"));
        Future<String> future2 = executor.submit(new Task("Task-2"));
        Future<String> future3 = executor.submit(new Task("Task-3"));

        // Get the results from Future objects
        System.out.println(future1.get());  // Blocks until the task is done
        System.out.println(future2.get());
        System.out.println(future3.get());

        executor.shutdown();  // Shut down the executor
    }
}

```


## @Async with spring boot

we can use @Async like this
```java
import org.springframework.scheduling.annotation.Async;
import org.springframework.stereotype.Service;

import java.util.concurrent.CompletableFuture;

@Service
public class AsyncService {

    @Async  // Run this method asynchronously
    @Async("taskExecutor") // Specify custom executor
    public CompletableFuture<String> asyncMethod() throws InterruptedException {
        System.out.println("Executing method asynchronously - " + Thread.currentThread().getName());
        Thread.sleep(2000);  // Simulate a long-running task
        return CompletableFuture.completedFuture("Task Completed");
    }
}


import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.scheduling.annotation.AsyncConfigurer;
import org.springframework.scheduling.concurrent.ThreadPoolTaskExecutor;

import java.util.concurrent.Executor;

@Configuration
public class AsyncConfig implements AsyncConfigurer {

    @Bean(name = "taskExecutor")  // Bean name "taskExecutor" to match the default
    public Executor taskExecutor() {
        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();
        executor.setCorePoolSize(5);  // Minimum number of threads to keep alive
        executor.setMaxPoolSize(10);  // Maximum number of threads in the pool
        executor.setQueueCapacity(25);  // Capacity of the queue for tasks
        executor.setThreadNamePrefix("AsyncThread-");  // Naming pattern for threads
        executor.initialize();
        return executor;
    }
}


```