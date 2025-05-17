
**Command** is a [[Behavioural Design Patterns]] pattern that turns a request into a stand-alone object that contains all information about the request. This transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations.


### Problem

Command pattern can solve many of the problems such as packing up all the request parameter and business logic for command execution into an object and passing that to an executor that can independently execute that command.

One more is implementing undo functionality, from command pattern you can parameterize the execute function and also implement an undo function that reverses that execute command kinda woirking as a compliment to that execute function.

### Applicability

 Use the Command pattern when you want to parametrize objects with operations.
 The Command pattern can turn a specific method call into a stand-alone object. This change opens up a lot of interesting uses: you can pass commands as method arguments, store them inside other objects, switch linked commands at runtime, etc.
 
Use the Command pattern when you want to queue operations, schedule their execution, or execute them remotely.

 Use the Command pattern when you want to implement reversible operations.

### Implementation

### Step 1: Create a `Command` interface

This interface declares a method for executing a command.

```java
public interface Command {
    void execute();
    void undo();
}
```

### Step 2: Create a `TextEditor` class

This class represents the receiver that performs the actual operations.

```java
public class TextEditor {
    private StringBuilder text = new StringBuilder();

    public void write(String words) {
        text.append(words);
    }

    public void eraseLast(int n) {
        int length = text.length();
        if (n > length) {
            n = length;
        }
        text.delete(length - n, length);
    }

    public String getText() {
        return text.toString();
    }
}
```

### Step 3: Create concrete command classes

Each command class implements the `Command` interface and encapsulates a request.

#### `WriteCommand` class

```java
public class WriteCommand implements Command {
    private TextEditor textEditor;
    private String text;

    public WriteCommand(TextEditor textEditor, String text) {
        this.textEditor = textEditor;
        this.text = text;
    }

    @Override
    public void execute() {
        textEditor.write(text);
    }

    @Override
    public void undo() {
        textEditor.eraseLast(text.length());
    }
}
```

### Step 4: Create an `Invoker` class

This class is responsible for initiating requests by calling the execute method on the command.

```java
import java.util.Stack;

public class TextEditorInvoker {
    private Stack<Command> history = new Stack<>();

    public void executeCommand(Command command) {
        command.execute();
        history.push(command);
    }

    public void undo() {
        if (!history.isEmpty()) {
            Command command = history.pop();
            command.undo();
        }
    }
}
```

### Step 5: Use the Command pattern in the text editor

Here's an example of how you might use the Command pattern in a text editor.

```java
public class TextEditorApp {
    public static void main(String[] args) {
        TextEditor textEditor = new TextEditor();
        TextEditorInvoker invoker = new TextEditorInvoker();

        Command writeHello = new WriteCommand(textEditor, "Hello ");
        Command writeWorld = new WriteCommand(textEditor, "World!");

        invoker.executeCommand(writeHello);
        invoker.executeCommand(writeWorld);

        System.out.println("Text after writing: " + textEditor.getText());

        invoker.undo();
        System.out.println("Text after undo: " + textEditor.getText());

        invoker.undo();
        System.out.println("Text after another undo: " + textEditor.getText());
    }
}
```

### Explanation

1. **Command Interface**: Defines the `execute` and `undo` methods.
2. **TextEditor Class**: The receiver that performs actual operations such as writing text and erasing text.
3. **WriteCommand Class**: A concrete command that writes text to the text editor and can undo the writing operation.
4. **TextEditorInvoker Class**: The invoker that executes commands and maintains a history for undo operations.
5. **TextEditorApp Class**: Demonstrates the use of the Command pattern by executing and undoing commands in a text editor.

