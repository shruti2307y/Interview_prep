The longest path problem for a general graph is not as easy as the shortest path problem because the longest path problem doesn’t have optimal substructure 
property. In fact, the Longest Path problem is NP-Hard for a general graph. However, the longest path problem has a linear time solution for directed acyclic 
graphs. The idea is similar to linear time solution for shortest path in a directed acyclic graph., we use Topological Sorting. 

We initialize distances to all vertices as minus infinite and distance to source as 0, then we find a topological sorting of the graph. Topological Sorting of a 
graph represents a linear ordering of the graph (See below, figure (b) is a linear representation of figure (a) ). Once we have topological order 
(or linear representation), we one by one process all vertices in topological order. For every vertex being processed, we update distances 
of its adjacent using distance of current vertex.

vector <int> maximumDistance(vector<vector<int>> edges,int V,int e,int src)
      {
            // code here
            vector<int> dist(V,INT_MIN);
            
            vector<int> ind(V,0);
            vector<vector<int>> adj(V,vector<int>(V,-10000));
            for(int i=0;i<e;i++)
            {
                adj[edges[i][0]][edges[i][1]]=edges[i][2];
                ind[edges[i][1]]++;
            }
            queue<int> q;
            for(int i=0;i<V;i++)
            {
                if(ind[i]==0)
                    q.push(i);
            }
            
            dist[src]=0;
            
            int curr;
            while(!q.empty())
            {
                curr=q.front();
                q.pop();
                
                for(int i=0;i<V;i++)
                {
                    if(adj[curr][i]>-10000)
                    {
                        if(dist[curr]!=INT_MIN)
                        {
                            dist[i]=max(dist[i],dist[curr]+adj[curr][i]);
                            
                        }
                        ind[i]--;
                            
                        if(ind[i]==0)
                            q.push(i);
                    }
                }
            }
            
            return dist;
      }