
**Template Method** is a [[Behavioural Design Patterns]] that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

The Template Method pattern suggests that you break down an algorithm into a series of steps, turn these steps into methods, and put a series of calls to these methods inside a single _template method._ The steps may either be `abstract`, or have some default implementation. To use the algorithm, the client is supposed to provide its own subclass, implement all abstract steps, and override some of the optional ones if needed (but not the template method itself).

### Applicability 

* Use the Template Method pattern when you want to let clients extend only particular steps of an algorithm, but not the whole algorithm or its structure.
* Use the pattern when you have several classes that contain almost identical algorithms with some minor differences. As a result, you might need to modify all classes when the algorithm changes.


### Implementation

1. Analyze the target algorithm to see whether you can break it into steps. Consider which steps are common to all subclasses and which ones will always be unique.
    
2. Create the abstract base class and declare the template method and a set of abstract methods representing the algorithm’s steps. Outline the algorithm’s structure in the template method by executing corresponding steps. Consider making the template method `final` to prevent subclasses from overriding it.
    
3. It’s okay if all the steps end up being abstract. However, some steps might benefit from having a default implementation. Subclasses don’t have to implement those methods.
    
4. Think of adding hooks between the crucial steps of the algorithm.
    
5. For each variation of the algorithm, create a new concrete subclass. It _must_ implement all of the abstract steps, but _may_ also override some of the optional ones.
### Step 1: Create an abstract class with a template method

This class defines the template method and declares abstract methods for the steps that will be implemented by subclasses.

```java
public abstract class DataParser {
    // Template method
    public final void parseData() {
        readData();
        processData();
        writeData();
    }

    // Steps to be implemented by subclasses
    protected abstract void readData();
    protected abstract void processData();
    
    // Common step implemented in the abstract class
    protected void writeData() {
        System.out.println("Writing data to the output.");
    }
}
```

### Step 2: Create concrete subclasses

These classes implement the abstract methods defined in the abstract class.

#### `CSVDataParser` class

```java
public class CSVDataParser extends DataParser {
    @Override
    protected void readData() {
        System.out.println("Reading data from CSV file.");
    }

    @Override
    protected void processData() {
        System.out.println("Processing data from CSV file.");
    }
}
```

#### `XMLDataParser` class

```java
public class XMLDataParser extends DataParser {
    @Override
    protected void readData() {
        System.out.println("Reading data from XML file.");
    }

    @Override
    protected void processData() {
        System.out.println("Processing data from XML file.");
    }
}
```

### Step 3: Use the Template Method pattern

Here's an example of how you might use the `DataParser` and its subclasses.

```java
public class TemplateMethodPatternDemo {
    public static void main(String[] args) {
        DataParser csvParser = new CSVDataParser();
        csvParser.parseData();
        
        System.out.println();
        
        DataParser xmlParser = new XMLDataParser();
        xmlParser.parseData();
    }
}
```

### Explanation

1. **Abstract Class with Template Method**: The `DataParser` abstract class defines the `parseData` template method, which outlines the steps of the algorithm. It also declares abstract methods `readData` and `processData`, which must be implemented by subclasses, and provides a common implementation for the `writeData` method.
2. **Concrete Subclasses**: `CSVDataParser` and `XMLDataParser` classes implement the `readData` and `processData` methods, providing specific behaviors for reading and processing CSV and XML data, respectively.
3. **TemplateMethodPatternDemo Class**: Demonstrates how to use the template method pattern by creating instances of `CSVDataParser` and `XMLDataParser` and calling their `parseData` methods.

## Cons
 You might violate the _Liskov Substitution Principle_ by suppressing a default step implementation via a subclass.