so here easy hi h
just woh start pointer will be lagging by 1 iteration of reversing.


struct node *reverse (struct node *head, int k)
    { 
        
        node  *last=NULL, *curr, *next, *ans=NULL,*start=NULL;
        
        int t=k;
        curr=head;
        if(k==1)
            return head;
        while(curr!=NULL)
        {
            while(t>0 && curr!=NULL)
            {
                next=curr->next;
                curr->next=last;
                last=curr;
                curr=next;
                t--;
                

            }
            if(ans==NULL)
                ans=last;
                
            if(start!=NULL){
                start->next=last;

            }
            start=head;
            head=curr;
            last=NULL;
            t=k;
        }
        
        return ans;
    }