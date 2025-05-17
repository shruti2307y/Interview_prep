

There are a number of situation in which it is important for nodes to agree.
* Leader Election : 
* Atomic commit: when we want to have distributed transactions, or all nodes agree on a txn.


### Atomic commit and Two-phase commit 

Atomicity prevents failed transactions from littering the database with half-finished results and half-updated state.

Single node transactions are supported by the storage engine themselves, whenever a transaction commits some actions, it pushes writes into WAL to make it durable. Typically till writes and commit tag are written to the disk successfully, we can rollback any changes.

###### What if multiple nodes are involved?

In that case, just sending a commit message to all the nodes and expect each of them to handle txn independently will result in some nodes failing the txn and rolling back and some succeeding with the txn.

These scenarios can be possible :
* Some nodes may detect a constraint violation or conflict, making an abort neces‐ sary, while other nodes are successfully able to commit. 
* Some of the commit requests might be lost in the network, eventually aborting due to a timeout, while other commit requests get through. 
* Some nodes may crash before the commit record is fully written and roll back on recovery, while others successfully commit.


#### 2 Phase commit
Instead of a single commit request, as with a single-node transaction, the commit/abort process in 2PC is split into two phases (hence the name).

A 2PC transaction begins with the application reading and writing data on multiple database nodes, as normal. We call these database nodes participants in the transac‐ tion. When the application is ready to commit, the coordinator begins phase 1: it sends a prepare request to each of the nodes, asking them whether they are able to commit. The coordinator then tracks the responses from the participants: 
* If all participants reply “yes,” indicating they are ready to commit, then the coor‐ dinator sends out a commit request in phase 2, and the commit actually takes place. 
* If any of the participants replies “no,” the coordinator sends an abort request to all nodes in phase 2.

The protocol contains two crucial “points of no return”: when a participant votes “yes,” it promises that it will definitely be able to commit later (although the coordinator may still choose to abort); and once the coordinator decides, that deci‐ sion is irrevocable. Those promises ensure the atomicity of 2PC. (Single-node atomic commit lumps these two events into one: writing the commit record to the transac‐ tion log.)

2PC struggles when coordinator itself crashes after it sends out prepare message to all, all after sending yes to coordinator the nodes will wait indefinitely for the coordinator to pass on commit or abort message back.


#### Three Phase Commit

Two-phase commit is called a blocking atomic commit protocol due to the fact that 2PC can become stuck waiting for the coordinator to recover. In theory, it is possible to make an atomic commit protocol nonblocking, so that it does not get stuck if a node fails. However, making this work in practice is not so straightforward.

* 3PC assumes a network with bounded delay and nodes with bounded response times; in most practical systems with unbounded network delay and process pauses.
* In a network with unbounded delay a timeout is not a reliable failure detector, because a request may time out due to a network problem even if no node has crashed. For this reason, 2PC continues to be used, despite the known problem with coordinator failure.



***distributed transactions in MySQL are reported to be over 10 times slower than single-node transactions*** 

Now we can have two types of distributed transaction implementation
1. ***Database-internal***: Here we have distributed database and within such databases we can have some implementation to handle consensus or txn support.
2. ***Heterogeneous***: Here we wil have two or more systems with different technologies and handling transaction in such scenario could be quite challenging.

Database-internal transactions do not have to be compatible with any other system, so they can use any protocol and apply optimizations specific to that particular tech‐ nology. For that reason, database-internal distributed transactions can often work quite well. On the other hand, transactions spanning heterogeneous technologies are a lot more challenging


## Limitations of Distributed Transactions

The key realization is that the transaction coordinator is itself a kind of database (in which transaction outcomes are stored), and so it needs to be approached with the same care as any other important database:

* If the coordinator is not replicated but runs only on a single machine, it is a sin‐ gle point of failure for the entire system.
* Many server-side applications are developed in a stateless model (as favored by HTTP), with all persistent state stored in a database, which has the advantage that application servers can be added and removed at will.Suddenly, the coordinator’s logs become a crucial part of the durable sys‐ tem state—as important as the databases themselves, since the coordinator logs are required in order to recover in-doubt transactions after a crash. Such applica‐ tion servers are no longer stateless.