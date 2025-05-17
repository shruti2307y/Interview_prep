
**Chain of Responsibility** is a [[Behavioural Design Patterns]] that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

Like many other behavioral design patterns, the **Chain of Responsibility** relies on transforming particular behaviors into stand-alone objects called _handlers_. In our case, each check should be extracted to its own class with a single method that performs the check. The request, along with its data, is passed to this method as an argument.

The pattern suggests that you link these handlers into a chain. Each linked handler has a field for storing a reference to the next handler in the chain. In addition to processing a request, handlers pass the request further along the chain. The request travels along the chain until all handlers have had a chance to process it.

Here’s the best part: a handler can decide not to pass the request further down the chain and effectively stop any further processing.


### Applicability

 Use the Chain of Responsibility pattern when your program is expected to process different kinds of requests in various ways, but the exact types of requests and their sequences are unknown beforehand.
 The pattern lets you link several handlers into one chain and, upon receiving a request, “ask” each handler whether it can process it. This way all handlers get a chance to process the request.


 Use the pattern when it’s essential to execute several handlers in a particular order.
 Since you can link the handlers in the chain in any order, all requests will get through the chain exactly as you planned.

Use the CoR pattern when the set of handlers and their order are supposed to change at runtime.

### Implementation

1. Declare the handler interface and describe the signature of a method for handling requests.
    
    Decide how the client will pass the request data into the method. The most flexible way is to convert the request into an object and pass it to the handling method as an argument.
    
2. To eliminate duplicate boilerplate code in concrete handlers, it might be worth creating an abstract base handler class, derived from the handler interface.
    
    This class should have a field for storing a reference to the next handler in the chain. Consider making the class immutable. However, if you plan to modify chains at runtime, you need to define a setter for altering the value of the reference field.
    
    You can also implement the convenient default behavior for the handling method, which is to forward the request to the next object unless there’s none left. Concrete handlers will be able to use this behavior by calling the parent method.
    
3. One by one create concrete handler subclasses and implement their handling methods. Each handler should make two decisions when receiving a request:
    
    - Whether it’ll process the request.
    - Whether it’ll pass the request along the chain.
4. The client may either assemble chains on its own or receive pre-built chains from other objects. In the latter case, you must implement some factory classes to build chains according to the configuration or environment settings.
    
5. The client may trigger any handler in the chain, not just the first one. The request will be passed along the chain until some handler refuses to pass it further or until it reaches the end of the chain.
    
6. Due to the dynamic nature of the chain, the client should be ready to handle the following scenarios:
    
    - The chain may consist of a single link.
    - Some requests may not reach the end of the chain.
    - Others may reach the end of the chain unhandled.


### Step 1: Create a `Request` class

This class represents the request to be handled.

```java
public class Request {
    private String type;
    private String message;

    public Request(String type, String message) {
        this.type = type;
        this.message = message;
    }

    public String getType() {
        return type;
    }

    public String getMessage() {
        return message;
    }
}
```

### Step 2: Create an abstract `Handler` class

This class defines the interface for handling requests and holds a reference to the next handler in the chain.

```java
public abstract class Handler {
    protected Handler nextHandler;

    public void setNextHandler(Handler nextHandler) {
        this.nextHandler = nextHandler;
    }

    public abstract void handleRequest(Request request);
}
```

### Step 3: Create concrete handler classes

Each concrete handler class processes a specific type of request or passes it to the next handler if it cannot process it.

#### `TechnicalSupportHandler` class

```java
public class TechnicalSupportHandler extends Handler {
    @Override
    public void handleRequest(Request request) {
        if (request.getType().equalsIgnoreCase("Technical")) {
            System.out.println("Technical Support: Handling request - " + request.getMessage());
        } else if (nextHandler != null) {
            nextHandler.handleRequest(request);
        }
    }
}
```

#### `BillingSupportHandler` class

```java
public class BillingSupportHandler extends Handler {
    @Override
    public void handleRequest(Request request) {
        if (request.getType().equalsIgnoreCase("Billing")) {
            System.out.println("Billing Support: Handling request - " + request.getMessage());
        } else if (nextHandler != null) {
            nextHandler.handleRequest(request);
        }
    }
}
```

#### `GeneralSupportHandler` class

```java
public class GeneralSupportHandler extends Handler {
    @Override
    public void handleRequest(Request request) {
        if (request.getType().equalsIgnoreCase("General")) {
            System.out.println("General Support: Handling request - " + request.getMessage());
        } else if (nextHandler != null) {
            nextHandler.handleRequest(request);
        }
    }
}
```

### Step 4: Use the Chain of Responsibility pattern

Here's an example of how you might set up and use the chain of handlers.

```java
public class SupportSystem {
    public static void main(String[] args) {
        // Create handlers
        Handler technicalSupport = new TechnicalSupportHandler();
        Handler billingSupport = new BillingSupportHandler();
        Handler generalSupport = new GeneralSupportHandler();

        // Set up the chain of responsibility
        technicalSupport.setNextHandler(billingSupport);
        billingSupport.setNextHandler(generalSupport);

        // Create requests
        Request techRequest = new Request("Technical", "Cannot connect to the internet.");
        Request billingRequest = new Request("Billing", "Incorrect charge on my bill.");
        Request generalRequest = new Request("General", "How can I reset my password?");

        // Process requests
        technicalSupport.handleRequest(techRequest);
        technicalSupport.handleRequest(billingRequest);
        technicalSupport.handleRequest(generalRequest);
    }
}
```

### Explanation

1. **Request Class**: Represents the request with a type and message.
2. **Handler Class**: An abstract class defining the interface for handling requests and a reference to the next handler.
3. **Concrete Handlers**: Each concrete handler (`TechnicalSupportHandler`, `BillingSupportHandler`, `GeneralSupportHandler`) processes specific types of requests or passes them to the next handler.
4. **SupportSystem Class**: Demonstrates setting up the chain of responsibility and processing requests through the chain.


## Cons
-  Some requests may end up unhandled.