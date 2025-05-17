
so this algo is used for single source multiple vertices shortest distance
can detect negative cycles

for each iteration of i it goes one level deeper in the graph starting from source.
and updating the shortest distance to that node from its adjacent node.


int isNegativeWeightCycle(int n, vector<vector<int>>edges){
	    
	    vector<int> dis(n,INT_MAX);
	    dis[1]=0;
	    for(int i=1;i<=n;i++)
	    {
	        for(auto it: edges)
	        {
	            int u = it[0];
                int v = it[1];
                int wt = it[2];
              if(dis[u]!=INT_MAX && dis[v]>dis[u]+wt)
              {
                    if(i==n)
                        return 1;
                  dis[v]=dis[u]+wt;
              }
	           
	        }
	    }
	    
	   
	    return 0;
}