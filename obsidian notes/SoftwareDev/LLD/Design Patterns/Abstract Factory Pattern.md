**Abstract Factory** is a  [[Creational Design Patters]]  that lets you produce families of related objects without specifying their concrete classes.

## Intent
Imagine that you’re creating a furniture shop simulator. Your code consists of classes that represent:

1. A family of related products, say: `Chair` + `Sofa` + `CoffeeTable`.
2. Several variants of this family. For example, products `Chair` + `Sofa` + `CoffeeTable` are available in these variants: `Modern`, `Victorian`, `ArtDeco`.
3. You need a way to create individual furniture objects so that they match other objects of the same family. Customers get quite mad when they receive non-matching furniture.
Also, you don’t want to change existing code when adding new products or families of products to the program. Furniture vendors update their catalogs very often, and you wouldn’t want to change the core code each time it happens.

When looked into this we can clearly see there are two dimension of functionality one is the furniture and one the variant of that furniture.

### Applications

Use the Abstract Factory when your code needs to work with various families of related products, but you don’t want it to depend on the concrete classes of those products—they might be unknown beforehand or you simply want to allow for future extensibility.

 The Abstract Factory provides you with an interface for creating objects from each class of the product family. As long as your code creates objects via this interface, you don’t have to worry about creating the wrong variant of a product which doesn’t match the products already created by your app.


###  How to Implement
1. Map out a matrix of distinct product types versus variants of these products.
2. Declare abstract product interfaces for all product types. Then make all concrete product classes implement these interfaces.
3. Declare the abstract factory interface with a set of creation methods for all abstract products.
4. Implement a set of concrete factory classes, one for each product variant.
5. Create factory initialization code somewhere in the app. It should instantiate one of the concrete factory classes, depending on the application configuration or the current environment. Pass this factory object to all classes that construct products.
6. Scan through the code and find all direct calls to product constructors. Replace them with calls to the appropriate creation method on the factory object.



### Example: Abstract Factory Design Pattern in Java

#### Step 1: Create interfaces for `Shape` and `Color`.
```java
public interface Shape {
    void draw();
}

public interface Color {
    void fill();
}
```

#### Step 2: Create concrete classes implementing the `Shape` interface.
```java
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
```

#### Step 3: Create concrete classes implementing the `Color` interface.
```java
public class Red implements Color {
    @Override
    public void fill() {
        System.out.println("Inside Red::fill() method.");
    }
}

public class Green implements Color {
    @Override
    public void fill() {
        System.out.println("Inside Green::fill() method.");
    }
}

public class Blue implements Color {
    @Override
    public void fill() {
        System.out.println("Inside Blue::fill() method.");
    }
}
```

#### Step 4: Create abstract factory classes for `Shape` and `Color`.
```java
public abstract class AbstractFactory {
    abstract Color getColor(String color);
    abstract Shape getShape(String shape);
}
```

#### Step 5: Create Factory classes extending `AbstractFactory` to generate object of concrete class based on given information.
```java
public class ShapeFactory extends AbstractFactory {

    @Override
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

    @Override
    public Color getColor(String color) {
        return null;
    }
}

public class ColorFactory extends AbstractFactory {

    @Override
    public Color getColor(String color) {
        if (color == null) {
            return null;
        }
        if (color.equalsIgnoreCase("RED")) {
            return new Red();
        } else if (color.equalsIgnoreCase("GREEN")) {
            return new Green();
        } else if (color.equalsIgnoreCase("BLUE")) {
            return new Blue();
        }
        return null;
    }

    @Override
    public Shape getShape(String shape) {
        return null;
    }
}
```

#### Step 6: Create a FactoryProducer class to get factories by passing information such as Shape or Color.
```java
public class FactoryProducer {
    public static AbstractFactory getFactory(String choice) {
        if (choice.equalsIgnoreCase("SHAPE")) {
            return new ShapeFactory();
        } else if (choice.equalsIgnoreCase("COLOR")) {
            return new ColorFactory();
        }
        return null;
    }
}
```

#### Step 7: Use the FactoryProducer to get AbstractFactory in order to get factories of concrete classes by passing an information such as type.
```java
public class AbstractFactoryPatternDemo {

    public static void main(String[] args) {
        // Get Shape factory
        AbstractFactory shapeFactory = FactoryProducer.getFactory("SHAPE");

        // Get an object of Shape Circle
        Shape shape1 = shapeFactory.getShape("CIRCLE");
        shape1.draw();

        // Get an object of Shape Rectangle
        Shape shape2 = shapeFactory.getShape("RECTANGLE");
        shape2.draw();

        // Get an object of Shape Square
        Shape shape3 = shapeFactory.getShape("SQUARE");
        shape3.draw();

        // Get Color factory
        AbstractFactory colorFactory = FactoryProducer.getFactory("COLOR");

        // Get an object of Color Red
        Color color1 = colorFactory.getColor("RED");
        color1.fill();

        // Get an object of Color Green
        Color color2 = colorFactory.getColor("GREEN");
        color2.fill();

        // Get an object of Color Blue
        Color color3 = colorFactory.getColor("BLUE");
        color3.fill();
    }
}
```

### Explanation
1. **Shape Interface**: Defines the `draw` method for different shapes.
2. **Color Interface**: Defines the `fill` method for different colors.
3. **Concrete Shape Classes**: `Circle`, `Rectangle`, and `Square` implement the `Shape` interface.
4. **Concrete Color Classes**: `Red`, `Green`, and `Blue` implement the `Color` interface.
5. **Abstract Factory Class**: `AbstractFactory` defines methods to get `Shape` and `Color` objects.
6. **Concrete Factory Classes**: `ShapeFactory` and `ColorFactory` extend `AbstractFactory` and provide implementations to create `Shape` and `Color` objects.
7. **FactoryProducer**: Provides a method to get the appropriate factory (`ShapeFactory` or `ColorFactory`) based on input.
8. **AbstractFactoryPatternDemo**: Demonstrates how to use the `FactoryProducer` to get `Shape` and `Color` objects and call their methods.

This example illustrates how the Abstract Factory pattern can be used to create families of related objects (Shapes and Colors) without specifying their concrete classes.