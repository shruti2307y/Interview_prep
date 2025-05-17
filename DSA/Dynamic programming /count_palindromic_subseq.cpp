

here formula yeh h ki
    for i and j apn ek substring bnate h and dp[i][j] uss substring ka answer hoga

    toh apn yeh krte ki prefix and suffix lete h 
            (i+1,j) suffix
            (i,j-1) prefix
            (i+1,j-1) middle

            ab dono suffix + prefix me middle ke elements do bar aate h 
    toh will check if(string[i]==string[j])
        matlab middle ke sare elements add krege

        dp[i][j]=prefix+suffix-middle+middle+1;

    else    
        dp[i][j]=prefix+suffix-middle;    

long long int  countPS(string str)
    {
       //Your code here
       long long int mod=1000000007;
       
       int n=str.size();
       vector<vector<long long int>> dp(n+1,vector<long long int>(n+1,0));
       
        for(int i=n-1;i>=0;i--)
        {
            for(int j=i;j<=n;j++)
            {
                if(i==j)
                    dp[i][j]=1;
                else
                {
                    if(str[i]==str[j])
                        dp[i][j]=(dp[i][j-1]%mod+dp[i+1][j]%mod+1)%mod;
                    else
                        dp[i][j]=(dp[i][j-1]%mod+dp[i+1][j]%mod-dp[i+1][j-1]%mod)%mod;
                }
               
            }
        }
        
        if(dp[0][n]<0)
            return dp[0][n]+mod;
        return dp[0][n]%mod;
    }