**Singleton** is a [[Creational Design Patters]]  that lets you ensure that a class has only one instance, while providing a global access point to this instance.

### Problem

**Ensure that a class has just a single instance**. Why would anyone want to control how 
many instances a class has? The most common reason for this is to control access to some shared resource—for example, a database or a file.

### Implementation

All implementations of the Singleton have these two steps in common:
- Make the default constructor private, to prevent other objects from using the `new` operator with the Singleton class.
- Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.

```java
public final class Singleton {

    private static volatile Singleton instance;
    public String value;
    private Singleton(String value) {
        this.value = value;
    }
    public static Singleton getInstance(String value) {
        Singleton result = instance;
        if (result != null) {
            return result;
        }
        synchronized(Singleton.class) {
            if (instance == null) {
                instance = new Singleton(value);
            }
            return instance;
        }
    }
}
```

