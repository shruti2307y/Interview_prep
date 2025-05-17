**Composite** is a [[Structural Design Patterns]] that lets you compose objects into tree structures and then work with these structures as if they were individual objects.


### Problem 

Using the Composite pattern makes sense only when the core model of your app can be represented as a tree.

### Implementation

### Step 1: Create a Component Interface

```java
// Component
public interface FileSystemComponent {
    void showDetails();
}
```

### Step 2: Create Leaf Class

```java
// Leaf
public class File implements FileSystemComponent {
    private String name;

    public File(String name) {
        this.name = name;
    }

    @Override
    public void showDetails() {
        System.out.println("File: " + name);
    }
}
```

### Step 3: Create Composite Class

```java
// Composite
import java.util.ArrayList;
import java.util.List;

public class Directory implements FileSystemComponent {
    private String name;
    private List<FileSystemComponent> components = new ArrayList<>();

    public Directory(String name) {
        this.name = name;
    }

    public void addComponent(FileSystemComponent component) {
        components.add(component);
    }

    public void removeComponent(FileSystemComponent component) {
        components.remove(component);
    }

    @Override
    public void showDetails() {
        System.out.println("Directory: " + name);
        for (FileSystemComponent component : components) {
            component.showDetails();
        }
    }
}
```

### Step 4: Use the Composite Pattern

```java
public class CompositePatternDemo {
    public static void main(String[] args) {
        // Creating Files
        FileSystemComponent file1 = new File("File1.txt");
        FileSystemComponent file2 = new File("File2.jpg");
        FileSystemComponent file3 = new File("File3.docx");

        // Creating Directories
        Directory directory1 = new Directory("Directory1");
        Directory directory2 = new Directory("Directory2");

        // Composing the directory structure
        directory1.addComponent(file1);
        directory1.addComponent(file2);
        directory2.addComponent(file3);
        directory1.addComponent(directory2);

        // Displaying details
        directory1.showDetails();
    }
}
```

### Explanation

- **FileSystemComponent**: This is the component interface that defines the operations that can be performed on both leaf and composite objects.
- **File**: This is the leaf class that implements the component interface.
- **Directory**: This is the composite class that can contain other components, both leaf and composite. It also implements the component interface.
- **CompositePatternDemo**: This class demonstrates how to use the composite pattern by creating files and directories and composing them into a structure.

### Output

When you run the `CompositePatternDemo` class, you will get an output similar to:

```
Directory: Directory1
File: File1.txt
File: File2.jpg
Directory: Directory2
File: File3.docx
```

This shows the hierarchical structure of the file system, where directories can contain both files and other directories.