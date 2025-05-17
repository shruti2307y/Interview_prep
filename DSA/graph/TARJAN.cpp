int isBridge(int V, vector<int> adj[], int c, int d) 
    {
        // Code here
       
        vector<bool> vis(V,false);
        vector<int> min_d(V,INT_MAX),levell(V,0);
        dfs(c,adj,vis,min_d,levell,0,-1);
        
        if(c==d)return 0; // if self edge
        int ct=0;
        for(int nb:adj[c]){
            if(nb==d)ct++;
        }
        if(ct>1)return 0;
        if(levell[d]==min_d[d])
            return 1;
        else
            return 0;
        
    }
    
    void dfs(int curr, vector<int> adj[], vector<bool> &vis, vector<int> &min_d, vector<int> &levell, int level, int par)
    {
        if(vis[curr])
            return ;
        else
        {
            vis[curr]=true;
            min_d[curr]=level;
            levell[curr]=level;
            // cout<<curr<<" at level "<<min_d[curr]<<endl;
            for(auto e: adj[curr])
            {
                if(e==par)
                    continue;
                    
                if(!vis[e])
                   {
                       dfs(e,adj,vis,min_d,levell,level+1,curr);
                       min_d[curr]=min(min_d[curr],min_d[e]);

                       now to check 
                       if the child node can be visited by any other node which came before curr node

                       if(min_d[e]>levell[curr])
                       {
                         then we have a bridge.
                       }
                   }
                
                else
                   {
                       min_d[curr]=min(min_d[curr],levell[e]);
                   }
                
            }
        }
    }
    