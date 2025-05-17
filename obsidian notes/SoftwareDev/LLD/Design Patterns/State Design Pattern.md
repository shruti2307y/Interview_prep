
State is a [[Behavioural Design Patterns]] that lets an object alter its behaviour when its internal state changes. it appears as if the object changed its class.

The State pattern is closely related to the concept of a _Finite-State Machine_.

The main idea is that, at any given moment, there’s a _finite_ number of _states_ which a program can be in. Within any unique state, the program behaves differently, and the program can be switched from one state to another instantaneously. However, depending on a current state, the program may or may not switch to certain other states. These switching rules, called _transitions_, are also finite and predetermined.

### Implementation

### Step 1: Create a `State` interface

This interface declares methods for handling state-specific behavior.

```java
public interface State {
    void handleRequest();
}
```

### Step 2: Create concrete state classes

These classes implement the `State` interface and define state-specific behavior.

#### `RedLightState` class

```java
public class RedLightState implements State {
    private TrafficLightContext context;

    public RedLightState(TrafficLightContext context) {
        this.context = context;
    }

    @Override
    public void handleRequest() {
        System.out.println("Red Light: Stop");
        context.setState(context.getGreenLightState());
    }
}
```

#### `GreenLightState` class

```java
public class GreenLightState implements State {
    private TrafficLightContext context;

    public GreenLightState(TrafficLightContext context) {
        this.context = context;
    }

    @Override
    public void handleRequest() {
        System.out.println("Green Light: Go");
        context.setState(context.getYellowLightState());
    }
}
```

#### `YellowLightState` class

```java
public class YellowLightState implements State {
    private TrafficLightContext context;

    public YellowLightState(TrafficLightContext context) {
        this.context = context;
    }

    @Override
    public void handleRequest() {
        System.out.println("Yellow Light: Caution");
        context.setState(context.getRedLightState());
    }
}
```

### Step 3: Create the `Context` class

This class maintains an instance of a concrete state class that defines the current state.

```java
public class TrafficLightContext {
    private State redLightState;
    private State greenLightState;
    private State yellowLightState;

    private State currentState;

    public TrafficLightContext() {
        redLightState = new RedLightState(this);
        greenLightState = new GreenLightState(this);
        yellowLightState = new YellowLightState(this);

        currentState = redLightState;
    }

    public void setState(State state) {
        currentState = state;
    }

    public void request() {
        currentState.handleRequest();
    }

    public State getRedLightState() {
        return redLightState;
    }

    public State getGreenLightState() {
        return greenLightState;
    }

    public State getYellowLightState() {
        return yellowLightState;
    }
}
```

### Step 4: Use the State pattern

Here's an example of how you might set up and use the state pattern.

```java
public class StatePatternDemo {
    public static void main(String[] args) {
        TrafficLightContext trafficLight = new TrafficLightContext();

        // Transition through states
        trafficLight.request(); // Red to Green
        trafficLight.request(); // Green to Yellow
        trafficLight.request(); // Yellow to Red
    }
}
```

### Explanation

1. **State Interface**: Declares the `handleRequest` method for handling state-specific behavior.
2. **Concrete State Classes**: Implement the `State` interface and define state-specific behavior. In this example, `RedLightState`, `GreenLightState`, and `YellowLightState` classes handle traffic light behavior.
3. **Context Class**: Maintains an instance of a concrete state class that defines the current state. In this example, the `TrafficLightContext` class transitions between `RedLightState`, `GreenLightState`, and `YellowLightState`.
4. **StatePatternDemo Class**: Demonstrates how to set up the state pattern and transition through different states.

In this example, the State pattern is used to change the behavior of a traffic light based on its current state. The `TrafficLightContext` transitions through different states (`RedLightState`, `GreenLightState`, `YellowLightState`), and each state defines its behavior, promoting a cleaner and more maintainable design.