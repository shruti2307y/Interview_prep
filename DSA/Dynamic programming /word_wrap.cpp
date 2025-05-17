
space complexity n2

int solveWordWrap(vector<int>nums, int k) 
    { 
        // Code here
        vector<vector<int>> dp(nums.size()+1,vector<int>(k+2,-1));
        return find(0,k,nums,k,dp);
    } 
    
    int find(int i, int rem, vector<int> &num, int k, vector<vector<int>> &dp)
    {
        if(i==num.size())
            return 0;
        else
        {
            if(dp[i][rem+1]!=-1)
                return dp[i][rem+1];
            
            int ans;
            
            if(num[i]>rem)
                {
                    ans=(rem+1)*(rem+1) +find(i+1,k-num[i]-1,num,k,dp);
                }
            else
            {
                int ch1=(rem+1)*(rem+1) + find(i+1,k-num[i]-1,num,k,dp);
                int ch2=find(i+1,rem-num[i]-1,num,k,dp);
                ans=min(ch1,ch2);
            }
            
            // cout<<ans<<endl;
            dp[i][rem+1]=ans;
            return ans;
        }
    }



    o(n) space complexity

    int solveWordWrap(vector<int>arr, int k) 
    { 
        // Code here
        
        int n=arr.size();
        vector<int> dp(n,INT_MAX);
        int cost;
        dp[n-1]=0;
        
        for(int i=n-2;i>=0;i--)
        {
            int currlen=-1;
            
            pick as every element and check ki uske aage remaining ka ans and get it added up to cost
            do it till we reach the word limit
            for(int j=i;j<n;j++)
            {
                currlen+=arr[j]+1;
                
                if(currlen>k)
                    break;
                
                if(j==n-1)
                    cost=0;
                else
                    cost=(k-currlen)*(k-currlen)+dp[j+1];
                    
                dp[i]=min(dp[i],cost);
            }
        }
        
        return dp[0];
    } 