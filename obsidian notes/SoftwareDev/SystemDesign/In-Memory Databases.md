

some resources:
- https://www.gridgain.com/resources/papers/introducing-apache-ignite


### Basic architecture:
So a basic in-memory database could be a collection of rows, which resides within a table and that table belongs to a database.

Now rows could have ID object which is hashable, and map of column name and object to actually store them. 

Now this can result in easy storage like array.append() any time a new rows comes, but retrieval will take time, so we also implement a hash-map to store the pointer to that row which is requested. 

 this can serve a basic necessity of storing some group of objects in a table format in memory.

but idk will it suffice to fully understand the internal workings of state of the art tools like ignite, redis and hazelcast.

## Requirements:

* Key-value data stores that can store data in a relational manner.
* Implement a client - server architecture.
* Server will be written in C++. IDK where will it lead me.
* client can be written in java. Future spec maybe.
* Need to use a protocol maybe [RESP](https://redis.io/docs/latest/develop/reference/protocol-spec/). Need to look into that or any other options i can get.
* Server will implement TCP socket.
* Partitioned/ fault tolerant/ masterless cluster.
* Queryable data structure with performant queries.

## Step 0: Prep the material

### 1. Socket Programming C++, Java
### 2. Data storage 

