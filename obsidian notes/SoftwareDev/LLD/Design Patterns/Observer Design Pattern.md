
**Observer** is a [[Behavioural Design Patterns]] that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

### Problem

This pattern is useful when you want to implement an messaging, notification service.

### Uses

Use the Observer pattern when changes to the state of one object may require changing other objects, and the actual set of objects is unknown beforehand or changes dynamically.

Use the pattern when some objects in your app must observe others, but only for a limited time or in specific cases.

### Implementation

1. Look over your business logic and try to break it down into two parts: the core functionality, independent from other code, will act as the publisher; the rest will turn into a set of subscriber classes.
    
2. Declare the subscriber interface. At a bare minimum, it should declare a single `update` method.
    
3. Declare the publisher interface and describe a pair of methods for adding a subscriber object to and removing it from the list. Remember that publishers must work with subscribers only via the subscriber interface.
    
4. Decide where to put the actual subscription list and the implementation of subscription methods. Usually, this code looks the same for all types of publishers, so the obvious place to put it is in an abstract class derived directly from the publisher interface. Concrete publishers extend that class, inheriting the subscription behavior.
    
    However, if you’re applying the pattern to an existing class hierarchy, consider an approach based on composition: put the subscription logic into a separate object, and make all real publishers use it.
    
5. Create concrete publisher classes. Each time something important happens inside a publisher, it must notify all its subscribers.
    
6. Implement the update notification methods in concrete subscriber classes. Most subscribers would need some context data about the event. It can be passed as an argument of the notification method.
    
    But there’s another option. Upon receiving a notification, the subscriber can fetch any data directly from the notification. In this case, the publisher must pass itself via the update method. The less flexible option is to link a publisher to the subscriber permanently via the constructor.
    
7. The client must create all necessary subscribers and register them with proper publishers.

### Step 1: Create the `Observer` interface

This interface declares the update method, which the subject will call to notify observers of a change in state.

```java
public interface Observer {
    void update(String news);
}
```

### Step 2: Create the `Subject` class

This class maintains a list of observers and notifies them of any changes.

```java
import java.util.ArrayList;
import java.util.List;

public class Subject {
    private List<Observer> observers = new ArrayList<>();
    private String state;

    public void attach(Observer observer) {
        observers.add(observer);
    }

    public void detach(Observer observer) {
        observers.remove(observer);
    }

    public void setState(String state) {
        this.state = state;
        notifyAllObservers();
    }

    public String getState() {
        return state;
    }

    private void notifyAllObservers() {
        for (Observer observer : observers) {
            observer.update(state);
        }
    }
}
```

### Step 3: Create concrete observer classes

These classes implement the `Observer` interface and define how they react to updates from the subject.

#### `NewsChannel` class

```java
public class NewsChannel implements Observer {
    private String name;

    public NewsChannel(String name) {
        this.name = name;
    }

    @Override
    public void update(String news) {
        System.out.println(name + " received news update: " + news);
    }
}
```

### Step 4: Use the Observer pattern

Here's an example of how you might set up and use the observer pattern.

```java
public class ObserverPatternDemo {
    public static void main(String[] args) {
        Subject newsAgency = new Subject();

        Observer channel1 = new NewsChannel("Channel 1");
        Observer channel2 = new NewsChannel("Channel 2");
        Observer channel3 = new NewsChannel("Channel 3");

        newsAgency.attach(channel1);
        newsAgency.attach(channel2);
        newsAgency.attach(channel3);

        newsAgency.setState("Breaking News: Observer Pattern Implemented!");
        newsAgency.setState("Update: Observer Pattern Example in Java!");
    }
}
```

### Explanation

1. **Observer Interface**: Declares the `update` method that the subject will call to notify observers of state changes.
2. **Subject Class**: Maintains a list of observers, provides methods to attach and detach observers, and notifies all observers of any state changes by calling their `update` method.
3. **Concrete Observer Class**: Implements the `Observer` interface and defines how they react to updates from the subject. In this example, the `NewsChannel` class prints the received news update.
4. **ObserverPatternDemo Class**: Demonstrates setting up the observer pattern, attaching observers to the subject, and changing the subject's state to trigger notifications to the observers.
