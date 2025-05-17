**Strategy** is a [[Behavioural Design Patterns]] that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.


The Strategy pattern suggests that you take a class that does something specific in a lot of different ways and extract all of these algorithms into separate classes called _strategies_.

The original class, called _context_, must have a field for storing a reference to one of the strategies. The context delegates the work to a linked strategy object instead of executing it on its own.

### Implementation

1. In the context class, identify an algorithm that’s prone to frequent changes. It may also be a massive conditional that selects and executes a variant of the same algorithm at runtime.
    
2. Declare the strategy interface common to all variants of the algorithm.
    
3. One by one, extract all algorithms into their own classes. They should all implement the strategy interface.
    
4. In the context class, add a field for storing a reference to a strategy object. Provide a setter for replacing values of that field. The context should work with the strategy object only via the strategy interface. The context may define an interface which lets the strategy access its data.
    
5. Clients of the context must associate it with a suitable strategy that matches the way they expect the context to perform its primary job.