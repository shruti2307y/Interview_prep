
Iterator ia a [[Behavioural Design Patterns]]. that lets you traverse elements of a collection without exposing its underlying representation.

### Implementation

The Iterator pattern is a behavioral design pattern that allows sequential access to elements of a collection without exposing the underlying representation. It is commonly used in Java to traverse collections like lists, sets, and maps.

### Step 1: Create an `Iterator` interface

This interface defines the methods for traversing a collection.

```java
public interface Iterator<T> {
    boolean hasNext();
    T next();
}
```

### Step 2: Create a `Collection` interface

This interface defines the method for creating an iterator.

```java
public interface Collection<T> {
    Iterator<T> createIterator();
}
```

### Step 3: Create a concrete collection class

This class implements the `Collection` interface and contains elements.

```java
import java.util.ArrayList;
import java.util.List;

public class CustomCollection<T> implements Collection<T> {
    private List<T> items;

    public CustomCollection() {
        this.items = new ArrayList<>();
    }

    public void addItem(T item) {
        items.add(item);
    }

    public T getItem(int index) {
        return items.get(index);
    }

    public int getSize() {
        return items.size();
    }

    @Override
    public Iterator<T> createIterator() {
        return new CustomIterator<>(this);
    }
}
```

### Step 4: Create a concrete iterator class

This class implements the `Iterator` interface and traverses the collection.

```java
public class CustomIterator<T> implements Iterator<T> {
    private CustomCollection<T> collection;
    private int currentIndex = 0;

    public CustomIterator(CustomCollection<T> collection) {
        this.collection = collection;
    }

    @Override
    public boolean hasNext() {
        return currentIndex < collection.getSize();
    }

    @Override
    public T next() {
        return collection.getItem(currentIndex++);
    }
}
```

### Step 5: Use the Iterator pattern

Here's an example of how you might use the `CustomCollection` and `CustomIterator` to traverse elements.

```java
public class IteratorPatternDemo {
    public static void main(String[] args) {
        CustomCollection<String> collection = new CustomCollection<>();
        collection.addItem("Item 1");
        collection.addItem("Item 2");
        collection.addItem("Item 3");

        Iterator<String> iterator = collection.createIterator();

        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}
```

### Explanation

1. **Iterator Interface**: Defines the methods `hasNext` and `next` for traversing the collection.
2. **Collection Interface**: Defines the `createIterator` method for creating an iterator.
3. **CustomCollection Class**: Implements the `Collection` interface and manages a list of items.
4. **CustomIterator Class**: Implements the `Iterator` interface and traverses the `CustomCollection`.
5. **IteratorPatternDemo Class**: Demonstrates how to use the `CustomCollection` and `CustomIterator` to traverse the collection.
