**Bridge** is a [[Structural Design Patterns]] that lets you split a large class or a set of closely related classes into two separate hierarchies—abstraction and implementation—which can be developed independently of each other.

###  Problem
* Well let's suppose you have two hierarchies cars and tyres. Now cars can be of the kind suv, sedan , hatchback etc. and tyres can also have road tyres, off road etc.
* Now whenver you want to extend a new car type or tyre type you will use inheritance and implement a seperate concrete class with the combination of car type and tyre type.But this car grow out of hand quickly. Here instead of inheritance we will rely on composition.

The Bridge pattern attempts to solve this problem by switching from inheritance to the object composition. What this means is that you extract one of the dimensions into a separate class hierarchy, so that the original classes will reference an object of the new hierarchy, instead of having all of its state and behaviors within one class.

### Application
 * Use the Bridge pattern when you want to divide and organize a monolithic class that has several variants of some functionality (for example, if the class can work with various database servers).
 * Use the pattern when you need to extend a class in several orthogonal (independent) dimensions.
 *  Use the Bridge if you need to be able to switch implementations at runtime.



### Implementation

The Bridge design pattern is a structural pattern that decouples an abstraction from its implementation so that the two can vary independently. This pattern is useful when you want to avoid a permanent binding between an abstraction and its implementation and allows both the abstraction and the implementation to be developed independently.

### Step 1: Define the Implementor Interface
```java
// Implementor
interface DrawAPI {
    void drawCircle(int radius, int x, int y);
}
```

### Step 2: Create Concrete Implementations
```java
// ConcreteImplementor 1
class RedCircle implements DrawAPI {
    @Override
    public void drawCircle(int radius, int x, int y) {
        System.out.println("Drawing Circle[ color: red, radius: " + radius + ", x: " + x + ", " + y + "]");
    }
}

// ConcreteImplementor 2
class GreenCircle implements DrawAPI {
    @Override
    public void drawCircle(int radius, int x, int y) {
        System.out.println("Drawing Circle[ color: green, radius: " + radius + ", x: " + x + ", " + y + "]");
    }
}
```

### Step 3: Define the Abstraction
```java
// Abstraction
abstract class Shape {
    protected DrawAPI drawAPI;
    
    protected Shape(DrawAPI drawAPI) {
        this.drawAPI = drawAPI;
    }
    
    public abstract void draw();
}
```

### Step 4: Create Concrete Abstraction Implementations
```java
// RefinedAbstraction
class Circle extends Shape {
    private int x, y, radius;

    public Circle(int x, int y, int radius, DrawAPI drawAPI) {
        super(drawAPI);
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    @Override
    public void draw() {
        drawAPI.drawCircle(radius, x, y);
    }
}
```

### Step 5: Use the Bridge
```java
public class BridgePatternDemo {
    public static void main(String[] args) {
        Shape redCircle = new Circle(100, 100, 10, new RedCircle());
        Shape greenCircle = new Circle(100, 100, 10, new GreenCircle());

        redCircle.draw();
        greenCircle.draw();
    }
}
```

