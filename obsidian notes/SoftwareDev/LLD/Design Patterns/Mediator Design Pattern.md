
**Mediator** is a [[Behavioural Design Patterns]] that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.

### Problem

let us assume an objects that based on some flow needs to communicate with multiple of different objects. Now whenever a new flow comes in we may have to add pointer to another object that might be called in that new flow.

In this case there would be a graph of objects, where interdependent components will try to talk to each other. In this case we can have huge numbers of edges/connections , and that could increase the complexity of the whole system.

### Solution

The Mediator pattern suggests that you should cease all direct communication between the components which you want to make independent of each other. Instead, these components must collaborate indirectly, by calling a special mediator object that redirects the calls to appropriate components. As a result, the components depend only on a single mediator class instead of being coupled to dozens of their colleagues.


### Applicability

* Use the Mediator pattern when it’s hard to change some of the classes because they are tightly coupled to a bunch of other classes.
* Use the pattern when you can’t reuse a component in a different program because it’s too dependent on other components.


### Implementation

1. Identify a group of tightly coupled classes which would benefit from being more independent (e.g., for easier maintenance or simpler reuse of these classes).
    
2. Declare the mediator interface and describe the desired communication protocol between mediators and various components. In most cases, a single method for receiving notifications from components is sufficient.
    
    This interface is crucial when you want to reuse component classes in different contexts. As long as the component works with its mediator via the generic interface, you can link the component with a different implementation of the mediator.
    
3. Implement the concrete mediator class. Consider storing references to all components inside the mediator. This way, you could call any component from the mediator’s methods.

### Step 1: Create a `Mediator` interface

This interface declares methods for communication between components.

```java
public interface Mediator {
    void notify(Component sender, String event);
}
```

### Step 2: Create an abstract `Component` class

This class represents a component that communicates through a mediator.

```java
public abstract class Component {
    protected Mediator mediator;

    public Component(Mediator mediator) {
        this.mediator = mediator;
    }

    public void setMediator(Mediator mediator) {
        this.mediator = mediator;
    }
}
```

### Step 3: Create concrete component classes

These classes represent different UI components that communicate via the mediator.

#### `Button` class

```java
public class Button extends Component {
    public Button(Mediator mediator) {
        super(mediator);
    }

    public void click() {
        mediator.notify(this, "click");
    }
}
```

#### `TextBox` class

```java
public class TextBox extends Component {
    private String text;

    public TextBox(Mediator mediator) {
        super(mediator);
    }

    public void setText(String text) {
        this.text = text;
        mediator.notify(this, "textChanged");
    }

    public String getText() {
        return text;
    }
}
```

#### `Label` class

```java
public class Label extends Component {
    private String text;

    public Label(Mediator mediator) {
        super(mediator);
    }

    public void setText(String text) {
        this.text = text;
        System.out.println("Label text: " + text);
    }
}
```

### Step 4: Create a concrete `Mediator` class

This class implements the mediator interface and coordinates communication between components.

```java
public class UIControlMediator implements Mediator {
    private Button button;
    private TextBox textBox;
    private Label label;

    public void setButton(Button button) {
        this.button = button;
    }

    public void setTextBox(TextBox textBox) {
        this.textBox = textBox;
    }

    public void setLabel(Label label) {
        this.label = label;
    }

    @Override
    public void notify(Component sender, String event) {
        if (sender instanceof Button && event.equals("click")) {
            String text = textBox.getText();
            label.setText("Button clicked! Text: " + text);
        } else if (sender instanceof TextBox && event.equals("textChanged")) {
            label.setText("Text changed to: " + textBox.getText());
        }
    }
}
```

### Step 5: Use the Mediator pattern

Here's an example of how you might set up and use the mediator and components.

```java
public class MediatorPatternDemo {
    public static void main(String[] args) {
        UIControlMediator mediator = new UIControlMediator();

        Button button = new Button(mediator);
        TextBox textBox = new TextBox(mediator);
        Label label = new Label(mediator);

        mediator.setButton(button);
        mediator.setTextBox(textBox);
        mediator.setLabel(label);

        textBox.setText("Hello, Mediator!");
        button.click();
    }
}
```

### Explanation

1. **Mediator Interface**: Defines the `notify` method for communication between components.
2. **Component Class**: An abstract class representing a component that uses a mediator to communicate.
3. **Concrete Components**: `Button`, `TextBox`, and `Label` classes represent different UI components that communicate via the mediator.
4. **UIControlMediator Class**: Implements the `Mediator` interface and coordinates communication between the components.
5. **MediatorPatternDemo Class**: Demonstrates how to set up and use the mediator and components.
