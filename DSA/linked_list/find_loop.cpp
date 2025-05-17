
here take thie eqn

time taken for both slow and fast will be same 

so 

L+x=(L+C+x)/2

here L is length of linked list which is left from loop
C is cycle size
and x is whatever length slow has traversed in cycle

so we get L+x=C

and C can be subs by C=x+y
y being whatever length we need to traverse to get to the linking point
L=y

so we start a new pointer from head again

void remove(Node *head, Node *f)
    {
        Node *s=head;
        while(s!=f)
        {
            s=s->next;
            f=f->next;
        }
        
        while(s->next!=f)
            s=s->next;
        
        s->next=NULL;
    }
    void removeLoop(Node* head)
    {
        // code here
        // just remove the loop without losing any nodes
        
        Node *s=head,*f=head;
        
        while(s&&f&&f->next)
        {
            s=s->next;
            f=f->next->next;
            
            if(s==f)
            {
                remove(head,f);
                return ;
            }
        }
    }