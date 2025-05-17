**Adapter** is a [[Structural Design Patterns]] that allows objects with incompatible interfaces to collaborate.
\

### Problem
Imagine that you’re creating a stock market monitoring app. The app downloads the stock data from multiple sources in XML format and then displays nice-looking charts and diagrams for the user.

At some point, you decide to improve the app by integrating a smart 3rd-party analytics library. But there’s a catch: the analytics library only works with data in JSON format.

You could change the library to work with XML. However, this might break some existing code that relies on the library. And worse, you might not have access to the library’s source code in the first place, making this approach impossible.

### Application
 Use the Adapter class when you want to use some existing class, but its interface isn’t compatible with the rest of your code.

 The Adapter pattern lets you create a middle-layer class that serves as a translator between your code and a legacy class, a 3rd-party class or any other class with a weird interface.

### How to implement
1. Make sure that you have at least two classes with incompatible interfaces:
    - A useful _service_ class, which you can’t change (often 3rd-party, legacy or with lots of existing dependencies).
    - One or several _client_ classes that would benefit from using the service class.
2. Declare the client interface and describe how clients communicate with the service.
3. Create the adapter class and make it follow the client interface. Leave all the methods empty for now.
4. Add a field to the adapter class to store a reference to the service object. The common practice is to initialize this field via the constructor, but sometimes it’s more convenient to pass it to the adapter when calling its methods.
5. One by one, implement all methods of the client interface in the adapter class. The adapter should delegate most of the real work to the service object, handling only the interface or data format conversion.
6. Clients should use the adapter via the client interface. This will let you change or extend the adapters without affecting the client code.

### Code : [EX](https://refactoring.guru/design-patterns/adapter/java/example) 