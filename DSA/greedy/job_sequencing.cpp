static bool comp(pair<int,int> a, pair<int,int> b)
    {
        
        if(a.first<b.first)
            return false;
        else if(a.first>b.first)
            return true;
        else
        {
            return a.second>b.second;
        }
    }
    vector<int> JobScheduling(Job arr[], int n) 
    { 
        // your code here
        
        vector<pair<int,int>> v;
        
        for(int i=0;i<n;i++)
        {
            v.push_back(make_pair(arr[i].profit,arr[i].dead));
        }
        
        sort(v.begin(),v.end(),comp);
        

        int n_jobs=0;
        int profit=0;
        
        vector<int> vis(n,-1);
        for(int i=0;i<n;i++)
        {
            for(int j=v[i].second-1;j>=0;j--)
            {
                if(vis[j]==-1)
                {
                    n_jobs++;
                    profit+=v[i].first;
                    vis[j]=1;
                    break;
                }
            }
        }
        
        vector<int> ans;
        
        ans.push_back(n_jobs);
        ans.push_back(profit);
        
        return ans;
    } 