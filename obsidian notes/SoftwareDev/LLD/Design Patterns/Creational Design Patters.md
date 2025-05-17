## Introduction

| Pattern              | Purpose                                                                                                  | Key Characteristics | Ideal Use Case                                                                 |                                                                                                      |
| -------------------- | -------------------------------------------------------------------------------------------------------- | ------------------- | ------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------- |
| **Singleton**        | Ensures a class has only one instance and provides a global access point                                 |                     | Managing shared resources like configuration settings or logging mechanisms    |                                                                                                      |
| **Factory Method**   | Defines an interface for creating objects, but lets subclasses alter the type                            |                     | When the exact type of object isn't known until runtime                        |                                                                                                      |
| **Abstract Factory** | Provides an interface for creating families of related objects without specifying their concrete classes |                     | Creating UI components that need to be consistent across different themes      |                                                                                                      |
| **Builder**          | Separates the construction of a complex object from its representation                                   |                     | Constructing complex objects like documents or meal plans with various options |                                                                                                      |
| **Prototype**        | Creates new objects by copying an existing object, known as the prototype                                |                     | When object creation is expensive or complex, and similar objects are needed   | ([Wikipedia][1], [Medium][2], [GeeksforGeeks][3], [SourceMaking][4], [Wikipedia][5], [Wikipedia][6]) |

[1]: https://en.wikipedia.org/wiki/Factory_method_pattern?utm_source=chatgpt.com "Factory method pattern"
[2]: https://medium.com/%40sharmapraveen91/creational-design-patterns-an-in-depth-exploration-43af77405057?utm_source=chatgpt.com "Creational Design Patterns: An In-Depth Exploration - Medium"
[3]: https://www.geeksforgeeks.org/creational-design-pattern/?utm_source=chatgpt.com "Creational Design Patterns | GeeksforGeeks"
[4]: https://sourcemaking.com/design_patterns/creational_patterns?utm_source=chatgpt.com "Creational patterns - SourceMaking"
[5]: https://en.wikipedia.org/wiki/Creational_pattern?utm_source=chatgpt.com "Creational pattern"
[6]: https://en.wikipedia.org/wiki/Builder_pattern?utm_source=chatgpt.com "Builder pattern"


Creational design patterns provide various object creation mechanisms, which increase flexibility and reuse of existing code.
[  
[URL](https://refactoring.guru/design-patterns/creational-patterns)

