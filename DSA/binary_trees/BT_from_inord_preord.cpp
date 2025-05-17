Node* buildTree(int in[],int pre[], int n)
    {
        // Code here
        
        Node *t=build(in,pre,0,n-1,0,n);
        
        Node *he=new Node(0);
        return t;
    }
    
    Node *build(int in[], int pre[], int l, int r, int p,int n)
    {
        
        if(l>r)
            return NULL;
        if(l==r)
        {
            Node *t= new Node(in[l]);
            
            return t;
        }
        else
        {
            Node *t=new Node(pre[p]);
            
            int i=l;
            while(in[i]!=pre[p])
                i++;
            
            t->left=build(in,pre,l,i-1,p+1,n);
            
            if(p+i-l+1<n)
            t->right=build(in,pre,i+1,r,p+i-l+1,n);
            
            return t;
        }
        