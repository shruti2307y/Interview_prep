
Decorator is a[[Structural Design Patterns]] that lets you attach new behaviours to objects by placin these objects inside special wrapper objects that contains the behaviour.

### Problem 

So suppose you have to extend a objects to perform multiple functionalities and these can also be chained at times.

So you can think of inheritance where you can implement different types of functionality by extending to the base class.

By that could grow out of hand quick again, and you really can't chain these objects.

### Solution

Extending a class is the first thing that comes to mind when you need to alter an object’s behavior. However, inheritance has several serious caveats that you need to be aware of.

- Inheritance is static. You can’t alter the behavior of an existing object at runtime. You can only replace the whole object with another one that’s created from a different subclass.
- Subclasses can have just one parent class. In most languages, inheritance doesn’t let a class inherit behaviors of multiple classes at the same time.

One of the ways to overcome these caveats is by using _Aggregation_ or _Composition_  instead of _Inheritance_. Both of the alternatives work almost the same way: one object _has a_ reference to another and delegates it some work, whereas with inheritance, the object itself _is_ able to do that work, inheriting the behavior from its superclass.

With this new approach you can easily substitute the linked “helper” object with another, changing the behavior of the container at runtime. An object can use the behavior of various classes, having references to multiple objects and delegating them all kinds of work. Aggregation/composition is the key principle behind many design patterns, including Decorator. On that note, let’s return to the pattern discussion.


### Applicability 

* Use the Decorator pattern when you need to be able to assign extra behaviors to objects at runtime without breaking the code that uses these objects.
* Use the pattern when it’s awkward or not possible to extend an object’s behavior using inheritance.


### How to implement

1. Make sure your business domain can be represented as a primary component with multiple optional layers over it.
    
2. Figure out what methods are common to both the primary component and the optional layers. Create a component interface and declare those methods there.
    
3. Create a concrete component class and define the base behavior in it.
    
4. Create a base decorator class. It should have a field for storing a reference to a wrapped object. The field should be declared with the component interface type to allow linking to concrete components as well as decorators. The base decorator must delegate all work to the wrapped object.
    
5. Make sure all classes implement the component interface.
    
6. Create concrete decorators by extending them from the base decorator. A concrete decorator must execute its behavior before or after the call to the parent method (which always delegates to the wrapped object).
    
7. The client code must be responsible for creating decorators and composing them in the way the client needs.


### Example: Coffee Shop

### Step 1: Create a Component Interface

```java
// Component
public interface Coffee {
    String getDescription();
    double getCost();
}
```

### Step 2: Create Concrete Component

```java
// Concrete Component
public class SimpleCoffee implements Coffee {
    @Override
    public String getDescription() {
        return "Simple Coffee";
    }

    @Override
    public double getCost() {
        return 5.0;
    }
}
```

### Step 3: Create Abstract Decorator Class

```java
// Decorator
public abstract class CoffeeDecorator implements Coffee {
    protected Coffee decoratedCoffee;

    public CoffeeDecorator(Coffee coffee) {
        this.decoratedCoffee = coffee;
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription();
    }

    @Override
    public double getCost() {
        return decoratedCoffee.getCost();
    }
}
```

### Step 4: Create Concrete Decorators

```java
// Concrete Decorator
public class MilkDecorator extends CoffeeDecorator {
    public MilkDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription() + ", Milk";
    }

    @Override
    public double getCost() {
        return decoratedCoffee.getCost() + 1.5;
    }
}

public class SugarDecorator extends CoffeeDecorator {
    public SugarDecorator(Coffee coffee) {
        super(coffee);
    }

    @Override
    public String getDescription() {
        return decoratedCoffee.getDescription() + ", Sugar";
    }

    @Override
    public double getCost() {
        return decoratedCoffee.getCost() + 0.5;
    }
}
```

### Step 5: Use the Decorator Pattern

```java
public class DecoratorPatternDemo {
    public static void main(String[] args) {
        Coffee simpleCoffee = new SimpleCoffee();
        System.out.println(simpleCoffee.getDescription() + " $" + simpleCoffee.getCost());

        Coffee milkCoffee = new MilkDecorator(simpleCoffee);
        System.out.println(milkCoffee.getDescription() + " $" + milkCoffee.getCost());

        Coffee milkSugarCoffee = new SugarDecorator(milkCoffee);
        System.out.println(milkSugarCoffee.getDescription() + " $" + milkSugarCoffee.getCost());
    }
}
```

### Explanation

- **Coffee**: This is the component interface that defines the operations that can be performed on both the component and decorators.
- **SimpleCoffee**: This is the concrete component that implements the component interface.
- **CoffeeDecorator**: This is the abstract decorator class that implements the component interface and contains a reference to a component object.
- **MilkDecorator** and **SugarDecorator**: These are concrete decorators that extend the abstract decorator class and add additional functionalities.
- **DecoratorPatternDemo**: This class demonstrates how to use the decorator pattern by creating a simple coffee and then decorating it with milk and sugar.

### Output

When you run the `DecoratorPatternDemo` class, you will get an output similar to:

```
Simple Coffee $5.0
Simple Coffee, Milk $6.5
Simple Coffee, Milk, Sugar $7.0
```

This shows how we can dynamically add functionalities (milk and sugar) to the base coffee object.


### Cons
- It’s hard to remove a specific wrapper from the wrappers stack.
-  It’s hard to implement a decorator in such a way that its behavior doesn’t depend on the order in the decorators stack.
-  The initial configuration code of layers might look pretty ugly.