Dis-joint set

int detectCycle(int V, vector<int>adj[])
	{
	    // Code here
	    vector<int> par(V),rank(V);
	    for(int i=0;i<V;i++)
	    {
	        par[i]=i;
	        rank[i]=1;
	    }
	    vector<int> vis(V,false);
	    for(int i=0;i<V;i++)
	    {
	        vis[i]=true;
	        for(auto v: adj[i])
	        {
	            if(vis[v])
	                continue;
	            if(find_parent(i,par)==find_parent(v,par))
	                return 1;
	            else
	            {
	                union_(v,i,par,rank);
	            }
	        }
	    }
	    
	    return 0;
	}
	
	int find_parent(int e, vector<int> &par)
	{
	    if(e==par[e])
	        return e;
	   
	    return find_parent(par[e],par);
	}
	
	void union_(int a, int b, vector<int> &par, vector<int> &rank)
	{
	    
	    int par_a=find_parent(a,par);
	    int par_b=find_parent(b,par);
	    if(par_a==par_b)
	        return ;
	    
	    if(rank[par_a]>rank[par_b])
	    {
	        par[par_b]=par_a;
	        return;
	    }
	    else if(rank[par_b]>rank[par_a])
	    {
	        par[par_a]=par_b;
	        return ;
	    }
	    else
	    {
	        par[par_b]=par_a;
	        rank[par_a]++;
	        return;
	    }
	}