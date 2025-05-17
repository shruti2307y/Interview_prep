

3 cases hoge
    agar wt uska total weight se kam ya equal h
        include krke next call me bhi lena
        include krke next call me nhi lena

        include hi nhi krna 
    else    
        include hi nhi krna

int knapSack(int N, int W, int val[], int wt[])
    {
        // code here
        
        vector<vector<int>> dp(N+1,vector<int>(W+1));
    
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=W;j++)
            {
                if(wt[i-1]<=j)
                {
                    dp[i][j]=max(dp[i-1][j],max(val[i-1]+dp[i-1][j-wt[i-1]],val[i-1]+dp[i][j-wt[i-1]]));
                }
                else
                {
                    dp[i][j]=dp[i-1][j];
                }
            }
        }
        
        return dp[N][W];
    }


    little more space optimized

    vector<int> dp(W+1);
    
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=W;j++)
            {
                if(wt[i-1]<=j)
                {
                    dp[j]=max(dp[j],val[i-1]+dp[j-wt[i-1]]);
                }
                
            }
        }
        
        return dp[W];