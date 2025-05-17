
abhi idhr na ese smjh ki dp[i][0] ki next element mujhe increasing chahiye
                         dp[i][1] ki next decreasing chahiye 
                        
                        and agar dp at element i agar ho jata h toh update toh dp[i][0]+1 will become next element dp[i+1][1] as ab next decreasing chahiye 

int AlternatingaMaxLength(vector<int>&nums){
   // Code here
   int n = nums.size();
   
   vector<vector<int>> dp(n, vector<int>(2,1));
   int maxLen = 1;
   for(int i = 1; i<n; i++)
   {
       for(int j = 0; j<i; j++)
       {
           if(nums[i] > nums[j])
               dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            if(nums[i] < nums[j])
               dp[i][1] = max(dp[i][1], dp[j][0] + 1);
       }
       maxLen = max(maxLen, max(dp[i][0], dp[i][1]));
    }
    return maxLen;
    
            
            
    //optimising the above solution to time complexity -> O(n)
    int maxi = 1; // same as dp[i][0]
    int mini = 1; // sames as dp[i][1]
    for(int i = 1; i<n; i++)
    {
       if(nums[i] > nums[i-1])
            maxi = max(maxi, mini+1);
       else if(nums[i] < nums[i-1])
            mini = max(mini, maxi+1);
     }
     return max(mini, maxi);
}