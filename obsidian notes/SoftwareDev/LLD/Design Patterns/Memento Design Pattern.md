The Memento pattern is a [[Behavioural Design Patterns]] that provides the ability to restore an object to its previous state. It's particularly useful for implementing undo mechanisms.

Use the pattern when direct access to the object’s fields/getters/setters violates its encapsulation.

Here’s an example of how you might implement the Memento pattern in Java, using a simple text editor scenario.

### Step 1: Create a `Memento` class

This class stores the state of the `Originator` object.

```java
public class Memento {
    private final String state;

    public Memento(String state) {
        this.state = state;
    }

    public String getState() {
        return state;
    }
}
```

### Step 2: Create an `Originator` class

This class creates a `Memento` containing a snapshot of its current state and uses the `Memento` to restore its state.

```java
public class Originator {
    private String state;

    public void setState(String state) {
        this.state = state;
    }

    public String getState() {
        return state;
    }

    public Memento saveStateToMemento() {
        return new Memento(state);
    }

    public void getStateFromMemento(Memento memento) {
        state = memento.getState();
    }
}
```

### Step 3: Create a `Caretaker` class

This class is responsible for keeping the `Memento`s. It never modifies or examines the contents of the `Memento`.

```java
import java.util.ArrayList;
import java.util.List;

public class Caretaker {
    private List<Memento> mementoList = new ArrayList<>();

    public void add(Memento state) {
        mementoList.add(state);
    }

    public Memento get(int index) {
        return mementoList.get(index);
    }
}
```

### Step 4: Use the Memento pattern

Here's an example of how you might use the `Originator`, `Memento`, and `Caretaker` classes to implement undo functionality.

```java
public class MementoPatternDemo {
    public static void main(String[] args) {
        Originator originator = new Originator();
        Caretaker caretaker = new Caretaker();

        originator.setState("State #1");
        originator.setState("State #2");
        caretaker.add(originator.saveStateToMemento());

        originator.setState("State #3");
        caretaker.add(originator.saveStateToMemento());

        originator.setState("State #4");
        System.out.println("Current State: " + originator.getState());

        originator.getStateFromMemento(caretaker.get(1));
        System.out.println("First saved State: " + originator.getState());

        originator.getStateFromMemento(caretaker.get(0));
        System.out.println("Second saved State: " + originator.getState());
    }
}
```

### Explanation

1. **Memento Class**: Stores the state of the `Originator`. It is a simple POJO (Plain Old Java Object) with a constructor and a getter for the state.
2. **Originator Class**: The object whose state needs to be saved and restored. It can create a `Memento` containing a snapshot of its current state and use the `Memento` to restore its state.
3. **Caretaker Class**: Manages the `Memento` objects. It adds and retrieves `Memento` objects but never modifies them.
4. **MementoPatternDemo Class**: Demonstrates how to use the `Originator`, `Memento`, and `Caretaker` to implement undo functionality.

In this example, the Memento pattern is used to save and restore the state of the `Originator` object. The `Caretaker` keeps track of the `Memento` objects, allowing the state to be restored to a previous state. This is useful for implementing features like undo and redo in applications.