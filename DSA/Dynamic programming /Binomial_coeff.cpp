 
  so the question is straight forward nCr nikalne ka h
  using this formula which is 
    nCr = n-1Cr + n-1Cr-1;

    so using memoization we can find it out.
 
 
 
 int nCr(int n, int r){
        if(r>n)return 0;
        ## here apn ne dp array bna diya h
        vector<vector<int>> dp(n+1,vector<int> (n+1));
        for(int i = 0; i <= n; i++){
            dp[i][0] = 1;
            dp[i][i] = 1;
        }
        
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= r; j++){
                ## using the formula as well
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%mod;
            }
        }
        return dp[n][r]%mod;
       
    }
