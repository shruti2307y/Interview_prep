

**Proxy** is a [[Structural Design Patterns]] that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

The Proxy pattern suggests that you create a new proxy class with the same interface as an original service object. Then you update your app so that it passes the proxy object to all of the original object’s clients. Upon receiving a request from a client, the proxy creates a real service object and delegates all the work to it.

### Applicability

 * Lazy initialization (virtual proxy). This is when you have a heavyweight service object that wastes system resources by being always up, even though you only need it from time to time.
 *  Access control (protection proxy). This is when you want only specific clients to be able to use the service object; for instance, when your objects are crucial parts of an operating system and clients are various launched applications (including malicious ones).
 * Local execution of a remote service (remote proxy). This is when the service object is located on a remote server.
 *  Logging requests (logging proxy). This is when you want to keep a history of requests to the service object.
 *  Caching request results (caching proxy). This is when you need to cache results of client requests and manage the life cycle of this cache, especially if results are quite large.

### Implementation

### Step 1: Create a `Document` interface

This interface defines the methods that both the real subject and the proxy will implement.

```java
public interface Document {
    void display();
}
```

### Step 2: Create a `RealDocument` class

This class represents the actual document that will be loaded and displayed.

```java
public class RealDocument implements Document {
    private String fileName;

    public RealDocument(String fileName) {
        this.fileName = fileName;
        loadFromDisk();
    }

    private void loadFromDisk() {
        System.out.println("Loading document from disk: " + fileName);
    }

    @Override
    public void display() {
        System.out.println("Displaying document: " + fileName);
    }
}
```

### Step 3: Create a `ProxyDocument` class

This class represents the proxy that controls access to the `RealDocument`.

```java
public class ProxyDocument implements Document {
    private String fileName;
    private RealDocument realDocument;

    public ProxyDocument(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void display() {
        if (realDocument == null) {
            realDocument = new RealDocument(fileName);
        }
        realDocument.display();
    }
}
```

### Step 4: Use the Proxy pattern in the text editor

Here's an example of how you might use the `ProxyDocument` in a text editor.

```java
public class TextEditor {
    public static void main(String[] args) {
        Document document = new ProxyDocument("example.txt");

        // The document will be loaded and displayed
        document.display();

        // The document will be displayed again without loading
        document.display();
    }
}
```

### Explanation

1. **Document Interface**: Defines the `display` method that both the real document and the proxy will implement.
2. **RealDocument Class**: Implements the `Document` interface and represents the actual document. It simulates loading from disk in the constructor.
3. **ProxyDocument Class**: Also implements the `Document` interface and acts as a proxy for the `RealDocument`. It controls access to the `RealDocument`, loading it only when necessary.
4. **TextEditor Class**: Demonstrates the use of the `ProxyDocument` to control access to a `RealDocument`.
