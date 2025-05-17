class Node{ 
public: 
 int key;
    int val;
    Node *next,*prev;
    Node(int key_v, int val_v)
    {
        
        key=key_v;
        val=val_v;
        next=nullptr;
        prev=nullptr;
    }
};

class LRUCache {
    int cache_size;
    Node *head, *tail;
    map<int,Node*> nodeLocation;
    
    void addNode(Node *curr)
    {
        if(tail==nullptr)
            tail=curr;
        
        nodeLocation[curr->key]=curr;
        if(head==nullptr)
        {
            head=curr;
        }
        else
        {
            head->next=curr;
            curr->prev=head;
            curr->next=nullptr;
            head=curr;
        }
    }
    void reEnterNode(Node *curr)
    {
        if(curr==head)
            return ;
        
        remove(curr);

        addNode(curr);
        
    }

    void remove(Node *curr)
    {
        Node *prev,*next;
        next=curr->next;
        prev=curr->prev;

        if(prev)
            prev->next=next;
        if(next)
            next->prev=prev;
        nodeLocation.erase(curr->key);
        curr->next=nullptr;
        curr->prev=nullptr;

        if(tail==curr)
            tail=next;

    }
public:
    LRUCache(int capacity) {

        cache_size=capacity;
        head=nullptr;
        tail=nullptr;
    }
    
    int get(int key) {
        
        if(nodeLocation.find(key)!=nodeLocation.end())
        {
            Node *curr= nodeLocation[key];
           
           reEnterNode(curr);

           return curr->val;

        }
        return -1;
    }
    
    void put(int key, int value) {
        
        if(nodeLocation.find(key)!=nodeLocation.end())
        {
            Node *curr=nodeLocation[key];
            
            reEnterNode(curr);

            curr->val=value;
        }
        else
        {
            Node *curr= new Node(key,value);
            addNode(curr);
            nodeLocation[key]=curr;

            if(nodeLocation.size()>cache_size)
            {
                remove(tail);
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
