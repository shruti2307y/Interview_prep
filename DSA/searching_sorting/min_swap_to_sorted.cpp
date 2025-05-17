using logic of graph cycles 

int minSwaps(vector<int>&nums)
	{
	    // Code here
	    int n=nums.size();
	    vector<pair<int,int>> v;
	    
	    for(int i=0;i<n;i++)
	    {
	        v.push_back({nums[i],i});
	    }
	    
	    sort(v.begin(),v.end());
	    
	    int j=0;
	    int swaps=0;
	    vector<int> vis(n,false);
	    while(j<n)
	    {
	        if(v[j].second!=j)
	        {
	            
	            int k=v[j].second;
	            int cnt=0;
	            while(vis[k]==false)
	            {
	                vis[k]=true;
	                k=v[k].second;
	                cnt++;
	                
	            }
	            if(cnt>0)
	            swaps=swaps+(cnt-1);
	        }
	        j++;
	    }
	    
	    return swaps;
	}