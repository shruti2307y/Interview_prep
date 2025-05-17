
For n-th person there are two choices:
1) n-th person remains single, we use recursion for f(n - 1)
2) n-th person pairs up with any of the remaining (n-1) persons. Call (n - 1) * f(n - 2


long long  solve(int n , vector<int>& dp)
    {  int mod = 1000000007;
        
        if(n==1)
        return 1;
        if(n==2)
        return 2;
        if(dp[n]!=-1)
        return dp[n];
        
        int r = solve(n-1, dp)*1%mod + ((n-1)*(solve(n-2, dp)%mod))%mod;
        return  dp[n]=r%mod;
        
    }
    int countFriendsPairings(int n) 
    { 
        vector<int>dp(n+1, -1);
        int x= solve(n , dp);
        return  x;
    }