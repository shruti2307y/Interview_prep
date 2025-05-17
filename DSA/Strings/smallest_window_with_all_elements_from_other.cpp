

so here ek map ke jese dp use kr rhe h
count apna distinct characters rakhega


string smallestWindow (string s, string p)
    {
        // Your code here
        vector<int> dp(26,0);
        int count=0;
        for(auto x: p)
        {
            if(dp[x-'a']==0)
            {
                count++;
            }
            dp[x-'a']++;
        }
        
        int i=0,j=0;
        int minlen=INT_MAX;
        string ans;
        int n=s.size();
        while(j<n)
        {
            dp[s[j]-'a']--;
            if(dp[s[j]-'a']==0)
            {
                count--;
            }
            
            while(count==0)
            {
                if(minlen>j-i+1)
                {
                    minlen=j-i+1;
                    ans=s.substr(i,minlen);
                }
                
                dp[s[i]-'a']++;
                if(dp[s[i]-'a']==1)
                {
                    count++;
                }
                i++;
            }
            
            j++;
        }
        
        if(minlen==INT_MAX)
            return "-1";
        return ans;
    }