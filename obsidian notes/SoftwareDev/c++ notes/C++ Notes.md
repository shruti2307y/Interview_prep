

### Abstraction
```c
#include <iostream>
using namespace std;

// Abstract base class
class Shape {
public:
    // Pure virtual function
    virtual void draw() = 0;  
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Drawing Rectangle" << endl;
    }
};

int main() {
    Shape* shape1 = new Circle();
    Shape* shape2 = new Rectangle();

    shape1->draw();
    shape2->draw();

    delete shape1;
    delete shape2;
    return 0;
}

```

### Runtime Polymorphism
```c
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {  // Virtual function
        cout << "Base class show function called." << endl;
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived class show function called." << endl;
    }
};

int main() {
    Base* basePtr;
    Derived derivedObj;

    basePtr = &derivedObj;

    // Run-time Polymorphism
    basePtr->show();  // Calls Derived's show function
    return 0;
}

```

### Strategy Design Pattern
```cpp
#include <iostream>
#include <string>
using namespace std;

// Strategy interface (PaymentStrategy)
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;  // Pure virtual function
    virtual ~PaymentStrategy() = default;  // Virtual destructor for polymorphism
};

// Concrete strategy 1 (CreditCardPayment)
class CreditCardPayment : public PaymentStrategy {
private:
    string cardNumber;
    string cardHolderName;
    string cvv;
    string expirationDate;

public:
    CreditCardPayment(const string& number, const string& name, const string& cvv, const string& expDate)
        : cardNumber(number), cardHolderName(name), cvv(cvv), expirationDate(expDate) {}

    void pay(int amount) override {
        cout << "Paid " << amount << " using Credit Card. Card Number: " << cardNumber << endl;
    }
};

// Concrete strategy 2 (PayPalPayment)
class PayPalPayment : public PaymentStrategy {
private:
    string email;

public:
    PayPalPayment(const string& email) : email(email) {}

    void pay(int amount) override {
        cout << "Paid " << amount << " using PayPal. PayPal Email: " << email << endl;
    }
};

// Context (PaymentContext)
class PaymentContext {
private:
    PaymentStrategy* strategy;  // Reference to a strategy object

public:
    // Constructor that accepts a strategy
    PaymentContext(PaymentStrategy* strategy) : strategy(strategy) {}

    // Change the strategy at runtime
    void setStrategy(PaymentStrategy* strategy) {
        this->strategy = strategy;
    }

    // Method to process payment
    void processPayment(int amount) {
        strategy->pay(amount);  // Delegate the payment to the strategy
    }

    // Destructor to clean up strategy
    ~PaymentContext() {
        delete strategy;  // Clean up strategy object
    }
};

// Main function
int main() {
    // Using Credit Card payment strategy
    PaymentContext* payment = new PaymentContext(new CreditCardPayment("1234-5678-9876-5432", "John Doe", "123", "12/24"));
    payment->processPayment(500);  // Output: Paid 500 using Credit Card. Card Number: 1234-5678-9876-5432

    // Switch to PayPal payment strategy
    payment->setStrategy(new PayPalPayment("john.doe@example.com"));
    payment->processPayment(300);  // Output: Paid 300 using PayPal. PayPal Email: john.doe@example.com

    delete payment;  // Clean up context and strategy
    return 0;
}

```

### Basic Exception Handling
```c

try{
	if( condition )
		throw "Some error";
	if( some condition)
		throw 10;
		
}
catch(const char* e)
{
	cout<<"Error happened: "<< e <<endl;
}
catch( const int e)
{
	cout<< "Error "<< e <<endl;
}
catch(...)
{
	cout<<"Catching all exception "<<endl;
}
```

### Custom Exception 
```cpp

class MyException: public exception{
string message;
public:
	MyException(string _message): message(_message) {}
	const char* what() const noexcept override{
		return 
	}
};

try{

	if(condition)
		throw MyException("Some Error");
}
catch(const MyException& e){
	cout<<"Error: "<<e.what()<<endl;
}

```

### Priority Queue with custom logic

#### Using Struct
```cpp
class Task {
public:
    int id;        // Unique identifier for the task
    int priority;  // Priority of the task (higher means more urgent)

    Task(int i, int p) : id(i), priority(p) {}  // Constructor

    // For debugging purposes
    friend std::ostream& operator<<(std::ostream& os, const Task& task) {
        os << "Task ID: " << task.id << ", Priority: " << task.priority;
        return os;
    }
};

// Custom comparator for the priority queue
struct CompareTask {
    bool operator()(const Task& t1, const Task& t2) {
        return t1.priority < t2.priority;
    }
};

int main() {
    // Define a priority queue with custom comparator
    std::priority_queue<Task, std::vector<Task>, CompareTask> pq;
    return 0;
}
```
#### Using Lambda
```cpp

auto compare = [](const Task& t1, const Task& t2){
	return t1.priority < t2.priority;
}
std::priority_queue<Task, std::vector<Task>, decltype(compare)> pq(compare);
```

### Using overloading of comparator class
```cpp
#include <iostream>
#include <queue>
#include <vector>

class Task {
public:
    int id;
    int priority;

    Task(int i, int p) : id(i), priority(p) {}

	bool operator<(const Task& other) const{
		return priority < other.priority;
	}
	bool operator>(const Task& other) const { return priority > other.priority; // For max-heap behavior }
};

int main() {
    // Priority queue using default less-than operator for Task
    std::priority_queue<Task> pq;
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> pq2;

    pq.push(Task(1, 5));
    pq.push(Task(2, 3));
    pq.push(Task(3, 8));
    pq.push(Task(4, 1));

    while (!pq.empty()) {
        Task t = pq.top();
        pq.pop();
        std::cout << t << std::endl;
    }

    return 0;
}

```

### Threads and Locks

#### Making threads
```c++

void task(int a, int b)
{
	some task
}

int main(){

	thread t1(task,1,2);

	t1.join();

	return 0;
}
```

#### with locks
* The `std::mutex` class is a mutual exclusion primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. A `std::lock_guard` is a convenient RAII-style mechanism for owning a `std::mutex` for the duration of a scoped block.
```c++
#include <thread> 
#include <mutex>

std:: mutex mtx;

void task(){

	std::lock_guard<std::mutex> lock(mtx);

	some code

}

```

* `std::unique_lock` is more flexible than `std::lock_guard`. It allows you to lock and unlock the mutex manually, which is useful when you need more control over the lock's lifetime.
```c++
std:: mutex mtx;

void task(){

	std::unique_lock<std::mutex> lock(mtx);

	some code

	lock.unlock();

}
```

* **Condition variables** are a key synchronization primitive used to block one or more threads until a certain condition is met. They are typically used in conjunction with a **mutex** to protect shared data.

- **`std::condition_variable`**: Used to block a thread until notified by another thread that a specific condition is true.
- **`std::mutex`**: Used to protect shared data.
```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

// Shared data and synchronization primitives
std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;
bool done = false;  // Flag to indicate if production is finished

// Function to produce data
void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate work

        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex
        dataQueue.push(i);  // Produce data
        std::cout << "Produced: " << i << std::endl;

        lock.unlock();  // Unlock before notifying
        cv.notify_one();  // Notify one waiting thread
    }

    // Indicate that production is finished
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_all();  // Notify all waiting threads
}

// Function to consume data
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex

        // Wait for data or completion signal
        cv.wait(lock, [] { return !dataQueue.empty() || done; });

        if (!dataQueue.empty()) {
            int data = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << data << std::endl;
        } else if (done) {
            break;  // Exit if done
        }

        // Mutex is automatically unlocked here when `lock` goes out of scope
    }

    std::cout << "Consumer finished." << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

```

#### Promises 

```c++
#include <iostream>
#include <thread>
#include <future>

// Function that sets a promise
void setPromiseValue(std::promise<int>& prom) {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate some work
    prom.set_value(42);  // Set the result
}

int main() {
    std::promise<int> prom;  // Create a promise
    std::future<int> fut = prom.get_future();  // Get a future associated with the promise

    // Create a thread that will set the promise value
    std::thread t(setPromiseValue, std::ref(prom));

    std::cout << "Waiting for the result..." << std::endl;
    int result = fut.get();  // Wait for the promise to be fulfilled
    std::cout << "Result received: " << result << std::endl;

    t.join();
    return 0;
}

```