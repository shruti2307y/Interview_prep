Node * bToDLL(Node *root)
    {
        // your code here
        
        Node *prev=NULL,*curr=root,*ans=NULL;
        
        stack<Node *> st;
        
        while(!st.empty() || curr)
        {
            if(curr!=NULL)
            {
                st.push(curr);
                curr=curr->left;
            }
            else
            {
                curr=st.top();
                st.pop();
                
                if(prev)
                {
                    prev->right=curr;
                }
                if(ans==NULL)
                {
                    ans=curr;
                }
                curr->left=prev;
                prev=curr;
                
                curr=curr->right;
            }
        }
        
        return ans;
    }