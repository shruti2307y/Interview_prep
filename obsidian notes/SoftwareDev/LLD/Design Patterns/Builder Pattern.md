**Builder** is a [[Creational Design Patters]] that lets you construct complex objects step by step. The pattern allows you to produce different types and representations of an object using the same construction code.

###  Problem
Imagine a complex object that requires laborious, step-by-step initialization of many fields and nested objects. Such initialization code is usually buried inside a monstrous constructor with lots of parameters. Or even worse: scattered all over the client code.

### Application

Use the Builder pattern when you want your code to be able to create different representations of some product (for example, stone and wooden houses).

 The Builder pattern can be applied when construction of various representations of the product involves similar steps that differ only in the details.

The base builder interface defines all possible construction steps, and concrete builders implement these steps to construct particular representations of the product. Meanwhile, the director class guides the order of construction.

### 🔧 When to Use the Builder Pattern
Consider employing the Builder Pattern when:

- An object has many parameters, especially when some are optional.

- You want to avoid a constructor with numerous parameters, which can be confusing and error-prone.

- You need to create different representations of an object.

- You aim to build objects in a step-by-step manner, improving code clarity.

### How to implement

Step 1: Create a House class that will be built.

```java
Copy code
public class House {
    // Required parameters
    private final String foundation;
    private final String structure;
    private final String roof;

    // Optional parameters
    private final boolean hasGarage;
    private final boolean hasSwimmingPool;
    private final boolean hasGarden;
    private final boolean hasFancyStatues;

    public House(String foundation, String structure, String roof, boolean hasGarage, boolean hasSwimmingPool, boolean hasGarden, boolean hasFancyStatues) {
        this.foundation = foundation;
        this.structure = structure;
        this.roof = roof;
        this.hasGarage = hasGarage;
        this.hasSwimmingPool = hasSwimmingPool;
        this.hasGarden = hasGarden;
        this.hasFancyStatues = hasFancyStatues;
    }

    @Override
    public String toString() {
        return "House{" +
                "foundation='" + foundation + '\'' +
                ", structure='" + structure + '\'' +
                ", roof='" + roof + '\'' +
                ", hasGarage=" + hasGarage +
                ", hasSwimmingPool=" + hasSwimmingPool +
                ", hasGarden=" + hasGarden +
                ", hasFancyStatues=" + hasFancyStatues +
                '}';
    }
}
```

Step 2: Create the HouseBuilder class.
```java
Copy code
public class HouseBuilder {
    // Required parameters
    private final String foundation;
    private final String structure;
    private final String roof;

    // Optional parameters
    private boolean hasGarage;
    private boolean hasSwimmingPool;
    private boolean hasGarden;
    private boolean hasFancyStatues;

    public HouseBuilder(String foundation, String structure, String roof) {
        this.foundation = foundation;
        this.structure = structure;
        this.roof = roof;
    }

    public HouseBuilder setGarage(boolean hasGarage) {
        this.hasGarage = hasGarage;
        return this;
    }

    public HouseBuilder setSwimmingPool(boolean hasSwimmingPool) {
        this.hasSwimmingPool = hasSwimmingPool;
        return this;
    }

    public HouseBuilder setGarden(boolean hasGarden) {
        this.hasGarden = hasGarden;
        return this;
    }

    public HouseBuilder setFancyStatues(boolean hasFancyStatues) {
        this.hasFancyStatues = hasFancyStatues;
        return this;
    }

    public House build() {
        return new House(foundation, structure, roof, hasGarage, hasSwimmingPool, hasGarden, hasFancyStatues);
    }
}
```

Step 3: Use the HouseBuilder to build a House object.
```java
Copy code
public class BuilderPatternDemo {
    public static void main(String[] args) {
        House house1 = new HouseBuilder("Concrete", "Wood", "Tiles")
                .setGarage(true)
                .setSwimmingPool(false)
                .setGarden(true)
                .setFancyStatues(false)
                .build();

        House house2 = new HouseBuilder("Concrete", "Steel", "Shingles")
                .setGarage(false)
                .setSwimmingPool(true)
                .setGarden(false)
                .setFancyStatues(true)
                .build();

        System.out.println(house1);
        System.out.println(house2);
    }
}
```
