## Introduction

**Design principles encourage us to create more maintainable, understandable, and flexible software.** Consequently, **as our applications grow in size, we can reduce their complexity** and save ourselves a lot of headaches further down the road!

The following five concepts make up our SOLID principles:

1. **S**ingle Responsibility
2. **O**pen/Closed
3. **L**iskov Substitution
4. **I**nterface Segregation
5. **D**ependency Inversion


### Single Responsibility

Let’s begin with the single responsibility principle. As we might expect, this principle states that **a class should only have one responsibility. Furthermore, it should only have one reason to change.**

**How does this principle help us to build better software?** Let’s see a few of its benefits:

1. **Testing** – A class with one responsibility will have far fewer test cases.
2. **Lower coupling** – Less functionality in a single class will have fewer dependencies.
3. **Organization** – Smaller, well organised classes are easier to search than monolithic ones.

### Open/Closed: Open for extension, closed for modification

In Simpler words it states that when we try to add a new functionality into a existing flow it shouldn't change the existing classes, instead you can extend those classes and add newer features without affecting the existing flow. In this way lots of flows don't break and it encourages a better segregation of features.\

Let's take an example of a car class, now you have decided that your application will also have cars with extra features, so what do you do. 
1. Change the existing car class, that could lead to N number of new bugs if that class is being used by other.
2. Instead changing the car class you extend that class and do changed in that specialized car class. In this way your new feature didn't break anything.

### Liskov's Substitution Principle

That's is much simpler to remember that if your code depends on a class object, that your code should be affected if that class object is replaced with its parent's class object.

Simply put, **if class _A_ is a subtype of class _B_, we should be able to replace _B_ with _A_ without disrupting the behavior of our program.**

for example if your object depends on a specialised car object then your code shouldn't break if its been replaced by simple car object. 

So it means that your code should depend on the basic functionality of the car object and not to the specialised functionality.


### Interface Segregation Principle

**larger interfaces should be split into smaller ones. By doing so, we can ensure that implementing classes only need to be concerned about the methods that are of interest to them.**

So It is kinda intuitive for example you have a car interface and you have added automatic with pedal shifter and gearbox that will be needed by concrete classes to be implemented.

Now you know that it shouldn't be the case you have to segregate this functionality into two interface and then the specialized class can decide which interface it needs to implement.


### Dependency Inversion

**The principle of dependency inversion refers to the decoupling of software modules. This way, instead of high-level modules depending on low-level modules, both will depend on abstractions.**

Again this principle says that your code shouldn't depend on the concrete classes but on abstraction defined by interfaces. This way in the runtime you can decide what concrete object to be used for a flow and your code doesn't depend on the concrete objects.
