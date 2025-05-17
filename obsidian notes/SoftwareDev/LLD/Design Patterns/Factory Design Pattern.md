## Intent

**Factory Method** is a [[Creational Design Patters]] that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.

the main idea here is to decouple the object creation code from client to library. Object creation will be handled by our factory class and depending on the config passed may return different objects provided that all those object implements a common interface.The Factory Method separates product construction code from the code that actually uses the product. Therefore it’s easier to extend the product construction code independently from the rest of the code.

For example, to add a new product type to the app, you’ll only need to create a new creator subclass and override the factory method in it.

Example: Factory Design Pattern in Java
Step 1: Create a Shape interface.

```java

public interface Shape {
    void draw();
}

public class Circle implements Shape {
    @Override
    public void draw() {
        System.out.println("Inside Circle::draw() method.");
    }
}

public class Rectangle implements Shape {
    @Override
    public void draw() {
        System.out.println("Inside Rectangle::draw() method.");
    }
}

public class Square implements Shape {
    @Override
    public void draw() {
        System.out.println("Inside Square::draw() method.");
    }
}
Step 3: Create a ShapeFactory class to generate objects of concrete classes based on given information.
```

``` java
public class ShapeFactory {

    // Use getShape method to get object of type Shape
    public Shape getShape(String shapeType) {
        if (shapeType == null) {
            return null;
        }
        if (shapeType.equalsIgnoreCase("CIRCLE")) {
            return new Circle();
        } else if (shapeType.equalsIgnoreCase("RECTANGLE")) {
            return new Rectangle();
        } else if (shapeType.equalsIgnoreCase("SQUARE")) {
            return new Square();
        }
        return null;
    }
}
```
Step 4: Use the ShapeFactory to get the object of concrete class by passing an information such as type.

```java

public class FactoryPatternDemo {

    public static void main(String[] args) {
        ShapeFactory shapeFactory = new ShapeFactory();

        // Get an object of Circle and call its draw method.
        Shape shape1 = shapeFactory.getShape("CIRCLE");
        shape1.draw();

        // Get an object of Rectangle and call its draw method.
        Shape shape2 = shapeFactory.getShape("RECTANGLE");
        shape2.draw();

        // Get an object of Square and call its draw method.
        Shape shape3 = shapeFactory.getShape("SQUARE");
        shape3.draw();
    }
}
```

### Pros
-  You avoid tight coupling between the creator and the concrete products.
-  _Single Responsibility Principle_. You can move the product creation code into one place in the program, making the code easier to support.
-  _Open/Closed Principle_. You can introduce new types of products into the program without breaking existing client code.
### Cons
* The code may become more complicated since you need to introduce a lot of new subclasses to implement the pattern. The best case scenario is when you’re introducing the pattern into an existing hierarchy of creator classes.