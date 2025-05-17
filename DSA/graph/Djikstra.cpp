vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Code here
        vector<int> ans(V,INT_MAX);
        vector<bool> vis(V,false);
        ans[S]=0;
        
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
        
        q.push(make_pair(0,S));
        pair<int,int> curr;
        int curr_i,curr_d;
        while(!q.empty())
        {
            curr=q.top();
            q.pop();
            curr_i=curr.second;
            curr_d=curr.first;
                
            if(vis[curr_i])
                continue;
            else
            {
               vis[curr_i]=true;
                
                for(auto p:adj[curr_i])
                {
                    if(ans[p[0]]>curr_d+p[1])
                    {
                        ans[p[0]]=curr_d+p[1];
                        q.push(make_pair(ans[p[0]],p[0]));
                    }
                }
            }
        }
        
        return ans;
    }