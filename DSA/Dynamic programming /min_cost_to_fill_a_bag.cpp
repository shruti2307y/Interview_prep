
normall h yrr

int minimumCost(int cost[], int n, int w) 
	{ 
        // Your code goes here
        vector<vector<int>> dp(n+1,vector<int>(w+1,1e7));
        
        for(int i=1;i<=n;i++)
        {
            dp[i][0]=0;
        }
        
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=w;j++)
            {
                
                if(j-i>=0 && cost[i-1]!=-1)
                    dp[i][j]=min(dp[i-1][j],cost[i-1]+min(dp[i-1][j-i],dp[i][j-i]));
                else
                {
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        
        if(dp[n][w]==1e7)
            return -1;
        
        return dp[n][w];
        
	} 