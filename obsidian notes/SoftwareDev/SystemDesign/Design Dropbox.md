
### Collecting requirements

* Users should be able to upload a file.
* Users can update the files.
* Users can share their files with other users.
* Should support synch between devices, updation on all devices.
* Storing large files.
* Offline update are also there.
* ACID compliant 

### Asking right questions?

* How do we deal with conflicts?
* versioning of files?
* DAU?

### Scale Estimation

* 500M total users and 100 DAU
* lets assume users have 200 files and each file is of 500KB.
* 500M  *  200 * 500KB = 50PB of data to be stored.


### High Level Design

So user will have a space/folder within their local system where they will be placing the files and upon updates to those file our system should get the update and sync these updates across multiple devices.


 ```mermaid
 flowchart LR;

client(client) --> bs([block server])
bs --> objectstore[(Cloud storage)]
bs --> metadataDB[(Metadata Database)]
client --> metadataServer([MetaData Server])
metadataServer --> metadataDB
metadataServer --> syncServer([Synchronization server])
syncServer --> client
```



### Deep Dive

#### a. Client

Client application will sit inside the users system and will be responsible for:
* Keeping the workspace folder in sync with changes. Detecting changes either locally or remotely.
* Uploading and downloading the files


Then also we need to efficiently transfer and store the files: For this we can divide the file into smaller chunks. This will lead to less overhead wrt sync as only the modified chunks will be needed to be transfered.

Now to be able to handle offline updates, we will also need to have a kinda metadata database within our local. So that whatever offline operation the client performs we can save them into that and make it in sync with the remote metadata database whenever users comes back online.

And for keeping the client in sync with remote changes we can deploy long polling.

Now lets divide our client into 4 smaller parts:

1. Internal Metadata database: will keep track of chunks, versions, locations, files
2. Chunker: will split bigger files into smaller chunks. reconstruction will also be handled. and will detect which chunks has been modified and only those chunks will be transferred.
3. Watcher: will monitor local workspace changes and notify indexer. will also recieves updates from remote server.
4. Indexer: will receive events from watcher, update internal metadata database. and will tell remote server to broadcast changes to other devices.
5. 
#### b. Metadata database

* for maintaining a central datastore for versioning and metadata info. can be relational or nosql based on our need. Since we support concurrent changes we would pick sql.
* Storing info about:
	* chunks
	* files
	* user
	* devices
	* workspace

#### c. Synchronisation Service

* Sync service handles all the updates from/ to clients. 
* Synching remote database with local database and vice-versa.
*  also handling concurrent updates and maybe conflict handling too.


#### d. Message Queuing service

*  as we are dealing with messages to be passed on between clients and remote servers, we can deploy a scalable messaging service queue like kafka.

#### e. Cloud/Block storage

* pretty straight forward.


![[dropbox_design.svg]]


