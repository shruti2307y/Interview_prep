
so suc will be latest entry in the left subtree stack

and ri will be smallest element in right subtree 

now check which is smaller 
and put it in next

void populateNext(Node *root)
    {
        //code here
        Node *r= find(root,NULL);
    }
    
    Node* find(Node *root, Node* suc)
    {
        if(root!=NULL)
        {
            Node *le=root,*ri=NULL;
            if(root->left)
                le=find(root->left,root);
            if(root->right)
                ri=find(root->right,suc);
            
            if(ri==NULL)
                root->next=suc;
            else if(suc!=NULL && suc->data<ri->data)
                root->next=suc;
            else
                root->next=ri;
            
            return le;
        }
    }


or else do a inorder and keep track of prev in inorder

 void populateNext(Node *root)
    {
        //code here
        
        Node *prev=NULL;
        Node *curr=root;
        
        stack<Node*> st;
        
        while(!st.empty() || curr)
        {
            if(curr)
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
                    prev->next=curr;
                }
                prev=curr;
                
                curr=curr->right;
            }
        }   
    }