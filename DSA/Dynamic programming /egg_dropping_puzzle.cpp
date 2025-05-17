
so isme trick yeh h ki partion from each tower and check if uske around check krne se optimal solution aayega kya
toh basically base condition h ki n<=2 return n and also check for k=1 to j-1 ki in towers pr check


recursive solution

int eggDrop(int n, int k) 
    {
        
        vector<vector<int>> dp(n+1,vector<int>(k+1,-1));
        
        return check(n,k,dp);
        
        
    }
    
    
    int check(int n, int k, vector<vector<int>> &dp)
    {
        if(n==1)
            return k;
            
        if(k<=2)
            return k;
        
        if(dp[n][k]!=-1)
            return dp[n][k];
        
        int st=INT_MAX;        
        for(int j=1;j<k;j++)
        {
            st=min(st,max(check(n-1,j-1,dp)+1,check(n,k-j,dp)+1));
        }
        
        return dp[n][k]=st;
    }




tabulation ==========

int eggDrop(int n, int k) 
    {
        // your code here
        vector<vector<int>> dp(n+1,vector<int>(k+1,0));
        
        for(int i=0;i<=k;i++)
        dp[1][i]=i;
        
        for(int i=2;i<=n;i++)
        {
            dp[i][1]=1;
            dp[i][2]=2;
            for(int j=3;j<=k;j++)
            {
                int st=INT_MAX;
                for(int k=1;k<j;k++)
                {
                    st=min(st,max(dp[i-1][k-1]+1,dp[i][j-k]+1));
                }
                dp[i][j]=st;
            }
        }
        
      
        
        return dp[n][k];
        
        
    }