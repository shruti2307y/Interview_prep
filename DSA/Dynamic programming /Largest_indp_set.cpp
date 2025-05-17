
function returns the max the node can get including current node and dp[node] stores max it can get without including current node



int find(Node *root, map<Node*,int> &dp)
{
    if(root==NULL)
        return 0;
    
        if(root->left==NULL && root->right==NULL)
        {
            dp[root]=0;
            return 1;
        }
        
        int left=find(root->left,dp);
        int right=find(root->right,dp);
        
        
        dp[root]=left+right;
        
        int ll=0;
        if(root->left)
            ll=dp[root->left];
        int rr=0;
        if(root->right)
            rr=dp[root->right];
            
        return max(ll+rr+1,dp[root]);

    
    
}

int LISS(Node *root)
{
    //Code here
    map<Node*,int> dp;
    return find(root,dp);
}