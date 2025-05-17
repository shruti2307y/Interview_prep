https://leetcode.com/problems/predict-the-winner/description/?source=submission-ac

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        
        vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),INT_MIN));
        return (find(0,nums.size()-1,nums,dp)>=0);
    }

    int find(int l, int r, vector<int> &nums,vector<vector<int>> &dp)
    {

        if(l==r)
        {
            return nums[l];
        }
        else
        {
            if(dp[l][r]!=INT_MIN)
                return dp[l][r];
            return dp[l][r]=max(nums[l]-find(l+1,r,nums,dp),nums[r]-find(l,r-1,nums,dp));
        }
    }
};