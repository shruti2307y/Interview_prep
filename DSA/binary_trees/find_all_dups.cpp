string findall(Node *root, vector<Node *>&ans, unordered_map<string,int> &subtree)
{
    string s="";
    
    if(root==NULL)
        return "N";
    
    string left=findall(root->left,ans,subtree);
    string right=findall(root->right,ans,subtree);

    s= s + to_string(root->data)+"," +left+","+right;
    // cout<<s<<endl;
    if(subtree.find(s)!=subtree.end())
    {
        if(subtree[s]==1)
            ans.push_back(root);
            
        subtree[s]++;
    }
    else
        subtree[s]=1;
    
    return s;
    
}
vector<Node*> printAllDups(Node* root)
{
    // Code here

    unordered_map<string,int> subtree;
    vector<Node*> ans;
    string s=findall(root,ans,subtree);
    // sort(ans.begin(),ans.end(),compare);
    return ans;
}