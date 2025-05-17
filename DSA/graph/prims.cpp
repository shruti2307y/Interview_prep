prims MST algo is quite similar to dijkstras algo

bas isme queue me total distance ki jgh current node se next node ka weight data h


int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > p_q;
        vector<bool> vis(V,false);
        
        int ans=0;
        
        p_q.push(make_pair(0,0));
        pair<int,int> curr;
        int curr_v;
        while(!p_q.empty())
        {
            curr=p_q.top();
            p_q.pop();
            
            curr_v=curr.second;
            if(vis[curr_v])
                continue;
            else
            {
                vis[curr_v]=true;
                ans+=curr.first;

                for(auto p: adj[curr_v])
                {
                    if(vis[p[0]]==false)
                    {
                        p_q.push(make_pair(p[1],p[0]));
                    }
                }
            }
        }
        
        return ans;
    }