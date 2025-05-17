int largestBst(Node *root)
    {
    	//Your code here
    	return find(root).first;
    }
    
    pair<int,pair<int,int>> find(Node* root)
    {
        if(root==NULL)
            return make_pair(0,make_pair(INT_MIN,INT_MAX));
        
        pair<int,pair<int,int>> left,right;
        
        left=find(root->left);
        right=find(root->right);
        
        if(root->data >left.second.first && root->data < right.second.second)
        {
            return make_pair(
                                left.first+right.first+1,
                                make_pair(
                                    max(root->data,right.second.first),
                                    min(root->data,left.second.second)
                            ));
        }
        else
            return make_pair(max(left.first,right.first),
                            make_pair(INT_MAX,INT_MIN));
    }