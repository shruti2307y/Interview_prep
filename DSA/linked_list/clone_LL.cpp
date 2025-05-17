[1]->[2]->[3]->[4]

[1] [2]->   [3]->
 |  |   |   |   |
[1]->   [2]->   [3] ----

and then do the linking and get the original back

Node *copyList(Node *head)
    {
        //Write your code here
        Node *curr=head,*next;
        
        while(curr)
        {
            next=curr->next;
            Node *t= new Node(curr->data);
            curr->next=t;
            t->next=next;
            curr=next;
        }
        curr=head;
        while(curr)
        {
            next=curr->arb;
            curr=curr->next;
            if(next!=NULL)
            curr->arb=next->next;
            
            curr=curr->next;
        }
        
        Node *ans=NULL;
        curr=head;
        while(curr)
        {
            next=curr->next;
            if(next)
            curr->next=next->next;
            if(ans==NULL)
            {
                ans=next;
            }
            curr=next;
        }
        return ans;
        
    }