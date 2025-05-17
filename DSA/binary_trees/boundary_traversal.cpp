vector <int> boundary(Node *root)
    {
        //Your code here
        vector<int> l,lv,r;
        l.push_back(root->data);
        preorder(root->left,l);
        getleaf(root->left,l);
        getleaf(root->right,l);
        postorder(root->right,l);
        
        return l;
    }
    
    void preorder(Node *root, vector<int> &ans)
    {
        if(root)
        {
            if(root->left==NULL && root->right==NULL)
                return ;
                
            ans.push_back(root->data);
            
            if(root->left)
                preorder(root->left,ans);
            else
                preorder(root->right,ans);
            
            
        }
    }
    void postorder(Node *root, vector<int> &ans)
    {
        if(root)
        {
             if(root->left==NULL && root->right==NULL)
                return ;
                
            if(root->right)
                postorder(root->right,ans);
            else
                postorder(root->left,ans);
                
            ans.push_back(root->data);

        }
    }
    
    void getleaf(Node *root, vector<int> &ans)
    {
        if(root)
        {
            
            getleaf(root->left,ans);
            getleaf(root->right,ans);

            if(root->left==NULL && root->right==NULL)    
                ans.push_back(root->data);

        }
    }