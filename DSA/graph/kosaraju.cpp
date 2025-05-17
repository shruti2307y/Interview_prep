algo to get strongly connected components

void dfs(int node,vector<vector<int>> &adj, vector<bool> &vis, stack<int> &st)
	{
	    if(!vis[node])
	    {
	        vis[node]=true;
	        for(auto e: adj[node])
	        {
	            if(vis[e]==false)
	            {
	                dfs(e,adj,vis,st);
	            }
	        }
	        
	        st.push(node);
	    }
	}
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //code here
        
        vector<bool> vis(V,false);
        
        stack<int> st;
        
        first we found the topological sort of all the vertices
        for(int i=0;i<V;i++)
        {
            dfs(i,adj,vis,st);
        }
        
        vector<vector<int>> adjT(V);
        
        reverse all the edges
        for(int i=0;i<V;i++)
        {
            vis[i]=false;
            for(auto v: adj[i])
            {
                adjT[v].push_back(i);
            }
        }
        
        int ans=0;
        now do the traversing with topological sort output and find if with the edges reversed we can get to traverse
        other vertices too.
         while(!st.empty())
        {
            int i=st.top();
            st.pop();
            if(vis[i]==false)
            {
                dfs(i,adjT,vis,st);
                ans++;
            }
        }
        return ans;
        
        
    }