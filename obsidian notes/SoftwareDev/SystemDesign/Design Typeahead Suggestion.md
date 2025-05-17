

### Gathering Requirements

* Users will get suggestion for a text completion.
* Top 10 suggestion should be displayed.


### Asking right questions

* will this be updated real time?
* any threshold length only after which suggestion should be displayed?
* DAU?


### High Level Design

```mermaid
flowchart LR;

user([user]) -- query text --> lb([Load Balancer])
lb --> server([Suggestion server])
server --> db([Database])
```


### Deep dive

#### a. Suggestion server
* Now we want very low latency for suggestions, and this can't be achieved using an database. 
* Hence we will be storing the texts in queryable database for search based on prefix text Trie.
* Trie will be loaded with corpus of texts and upon receiving a prefix text, it will generate top 10 texts from its children tree.

#### b. Trie structure
*  We will store the text corpus within a trie.
* We can merge nodes which has only one children. this will reduce some space.
* Also whenever we would need to get top suggestion we will traverse the whole child subtree of entered prefix text, get all the terminal nodes with full text, sort them according to frequency and return top 10 results.
* Now this traversal will cost us a great computing time. for such large scale system with least latency.
* So we will store the top result for each node's subtree within that node. This will reduce the time and but will, increase space. 
* One more optimisation we can do is to store not the full text result, as this can wasting too much space as it is redundant. we can store only reference to terminal node and traverse back to parent node to get the full text.

#### c. Storing user queries
* Now this trie will need to be updated from time to time. yes obv not on every single user query but in some interval.
* So we will store the queried text within a store and will count how many times users searched for that text. 
* this can be done with database that offers high write speed.

#### d. Updating the trie
* We can update the trie with newer frequencies values. Updating a terminal node will update its parents too, so we will check that if that terminal node qualifies for top 10 at that level, update it if its there already.
* We can also remove terminal nodes in such fashion too.
* we can also incorporate additional info into the ranking mechanism.



### Data partition

* Now we can store all the trie into a single server but lets try to break it down.
* Range based partitioning can be problematic here. 
* partition based on some length of prefix text. now keeping a threshold for suggestion will result in many benefits. We can do a hash based partitioning of prefix text and this will lead to almost distributed load on server.
* Also will reduce the load on the system to a certain bit.