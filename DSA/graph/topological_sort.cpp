
iterative method

vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    // code here
	   vector<int> ind(V,0);
	   
	   for(int i=0;i<V;i++)
	   {
	       for(auto x: adj[i])
	            ind[x]++;
	   }
	   
	   queue<int> q;
	   
	   for(int i=0;i<V;i++)
	   {
	       if(ind[i]==0)
	        q.push(i);

	   }
	   vector<int> ans;
	   while(!q.empty())
	   {
	       int curr=q.front();
	       q.pop();
	       
	       ans.push_back(curr);
	       
	       for(auto x: adj[curr])
	       {
	           ind[x]--;
	           if(ind[x]==0)
	            q.push(x);
	       }
	   }
	   
	   return ans;
	}


    DFS way

    void dfs(int i, vector<int> adj[], vector<bool> &vis, stack<int> &st)
    {
        if(!vis[i])
        {
            vis[i]=true;
            for(auto x: adj[i])
            {
                if(vis[x]==false)
                    dfs(x,adj,vis,st);
            }
            
            st.push(i);
        }
    }
	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    // code here
	    stack<int> st;
	    vector<bool> vis(V,false);
	    
	    for(int i=0;i<V;i++)
	    {
	        if(!vis[i])
	        {
	            dfs(i,adj,vis,st);
	        }
	    }
	    vector<int> ans;
	    while(!st.empty())
	        {
	            ans.push_back(st.top());
	            st.pop();
	        }
	   return ans;
	}