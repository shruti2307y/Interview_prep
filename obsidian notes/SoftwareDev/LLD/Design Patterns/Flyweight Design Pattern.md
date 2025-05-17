
Flyweigh is a [[Structural Design Patterns]]  that lets you fit more objects into the available amount of RAM by sharing common parts of state between multiple objects instead of keeping all of the data in each object.


### Problem

lets suppose you are trying to build a text editor. Now at each character you will want to render a font and for that you need to have the data to render that font at that specific location. Sounds right but the memery consumption will explode with size of your doc, as now memory will have all the fonts data at each location and will lead to inefficient memory consumption.


### Solution

This constant data of an object is usually called the _intrinsic state_. It lives within the object; other objects can only read it, not change it. The rest of the object’s state, often altered “from the outside” by other objects, is called the _extrinsic state_.

The Flyweight pattern suggests that you stop storing the extrinsic state inside the object. Instead, you should pass this state to specific methods which rely on it. Only the intrinsic state stays within the object, letting you reuse it in different contexts. As a result, you’d need fewer of these objects since they only differ in the intrinsic state, which has much fewer variations than the extrinsic.

### Flyweight factory

For more convenient access to various flyweights, you can create a factory method that manages a pool of existing flyweight objects. The method accepts the intrinsic state of the desired flyweight from a client, looks for an existing flyweight object matching this state, and returns it if it was found. If not, it creates a new flyweight and adds it to the pool.


### Implementation

### Step 1: Create a `CharacterFlyweight` class

This class represents a flyweight object that contains intrinsic state (the character itself) and methods for rendering the character.

```java
public class CharacterFlyweight {
    private final char character;

    public CharacterFlyweight(char character) {
        this.character = character;
    }

    public void render(int fontSize, String fontColor) {
        System.out.println("Rendering character: " + character + " with fontSize: " + fontSize + " and fontColor: " + fontColor);
    }
}
```

### Step 2: Create a `CharacterFactory` class

This class manages the flyweights and ensures that they are shared appropriately.

```java
import java.util.HashMap;
import java.util.Map;

public class CharacterFactory {
    private Map<Character, CharacterFlyweight> characters = new HashMap<>();

    public CharacterFlyweight getCharacter(char c) {
        CharacterFlyweight flyweight = characters.get(c);
        if (flyweight == null) {
            flyweight = new CharacterFlyweight(c);
            characters.put(c, flyweight);
        }
        return flyweight;
    }
}
```

### Step 3: Use the Flyweight pattern in the text editor

Here's an example of how you might use the `CharacterFactory` to render text in a text editor.

```java
public class TextEditor {
    private CharacterFactory characterFactory = new CharacterFactory();

    public void renderText(String text, int fontSize, String fontColor) {
        for (char c : text.toCharArray()) {
            CharacterFlyweight flyweight = characterFactory.getCharacter(c);
            flyweight.render(fontSize, fontColor);
        }
    }

    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        editor.renderText("Hello Flyweight", 12, "black");
        editor.renderText("Flyweight Pattern", 14, "blue");
    }
}
```

### Explanation

1. **CharacterFlyweight Class**: Represents a character and its rendering method.
2. **CharacterFactory Class**: Manages and provides instances of `CharacterFlyweight`. If a character has already been created, it returns the existing instance; otherwise, it creates a new one.
3. **TextEditor Class**: Uses the `CharacterFactory` to render text, ensuring that characters are shared to save memory.


