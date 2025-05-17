

toh idhr we take a substring and check if that exist in map or not 
    if yes
        then check pehle wala bhi h kya  
    else   
        do nothing coz dp 0 initilized h


int wordBreak(string A, vector<string> &B) {
        //code here
        
        int n=A.size();
        
        vector<int> dp(n+1,0);
        
        dp[0]=1;
        
        map<string,int> mp;
        for(auto s: B)
        {
            mp[s]=1;
        }
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=i;j++)
            {
                string t=A.substr(j,i-j+1);
                if(mp.find(t)!=mp.end())
                {
                    dp[i+1]=max(dp[i+1],dp[j]);
                }
                
            }
        }
        
        return dp[n];
    }