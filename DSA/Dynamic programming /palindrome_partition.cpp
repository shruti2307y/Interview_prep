
so dp[i][j] to check if that substring is palindromic or not

then dp2[i] will check it substring ending at i have min number of partition so that each partition is a palindrome 
    toh we check for each j from 0 to i and partition it    
        
        if(dp[j+1][i]) is palindrome    
            toh dp2[j] tk ke ans + 1 
        dp2[i]=min(dp2[i],dp2[j]+1)


int palindromicPartition(string str)
    {
        // code here
        int n=str.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        
        for(int i=0;i<n;i++)
            dp[i][i]=1;
        
        for(int len=2;len<=n;len++)
        {
            for(int i=0;i<n;i++)
            {
                
                int j=i+len-1;
                
                if(j>=n)
                    continue;
                
                if(str[i]==str[j])
                {
                    if(i+1==j)
                        dp[i][j]=1;
                    else if(dp[i+1][j-1]>0)
                        dp[i][j]=1;
                    
                }
                else
                    dp[i][j]=0;
            }
        }
        
        vector<int> dp2(n,INT_MAX);
        dp2[0]=0;
        for(int i=1;i<n;i++)
        {
            if(dp[0][i]==1)
         {           dp2[i]=0;
                    continue;
        }
            for(int j=0;j<i;j++)
            {
                
                if(dp[j+1][i]==1)
                    dp2[i]=min(dp2[i],dp2[j]+1);
            }
        }
        
        return dp2[n-1];
    }