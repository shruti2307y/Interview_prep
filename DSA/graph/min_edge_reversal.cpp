first make graph undirected and for every reversed edge added to graph. make its weight = 1.

so min distance will be , min reversed edges travelled.

int minimumEdgeReversal(vector<vector<int>> &edges,int n,int src,int dst)
        {
                vector <vector <vector<int>>> adj(n+1);
                for(auto i:edges){
                    adj[i[0]].push_back({i[1],0});
                    adj[i[1]].push_back({i[0],1});
                }
                priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
                pq.push({0,src});
                vector <int> vis(n+1);
                while(!pq.empty()){
                    int node = pq.top().second,cost = pq.top().first;
                    pq.pop();
                    if(node == dst) return cost;
                    if(vis[node]) continue;
                    vis[node] = 1;
                    for(auto it:adj[node]){
                        int next = it[0],nc = cost+it[1];
                        if(!vis[next])
                            pq.push({nc,next});
                    }
                }
                return -1;
        }