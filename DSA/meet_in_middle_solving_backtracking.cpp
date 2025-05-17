You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute 
difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.

Return the minimum possible absolute difference.

class Solution {
public:

    int ans=INT_MAX;
    int minimumDifference(vector<int>& nums) {

        int n=nums.size()/2;

        if(n==1)
        {
            return abs(nums[0]-nums[1]);
        }

        vector<vector<long long int>> s1(n+1);
        vector<vector<long long int>> s2(n+1);

        find(0,n,nums,0,0,s1);
        find(n,nums.size(),nums,0,0,s2);

        long long int tsum=0;
        for(auto x: nums)
        {
            tsum+=x;
        }
        for(int i=0;i<=n;i++)
        {
            if(i==0)
            {
                ans=min(ans,abs(tsum-s2[n][0]*2));
                
            }
            else if(i==n)
            {
                ans=min(ans,abs(tsum-s1[n][0]*2));
            }
            else
            {
                sort(s2[n-i].begin(),s2[n-i].end());

                for(auto t1: s1[i])
                {
                    int conn= (tsum-2*t1)/2;
                    auto itr = lower_bound(s2[n-i].begin(),s2[n-i].end(),conn);

                    if(itr!=s2[n-i].end())
                    {
                        ans=min(ans,abs(tsum-2*(t1+(*itr))));
                    }
                    if(itr!=s2[n-i].begin())
                    {
                        ans=min(ans,abs(tsum-2*(t1+(*--itr))));
                    }
                    
                }
            }
        }

        return ans;
    }

    int min(int a, long long int b)
    {
        if(a<b)
            return a;
        else
            return int(b);
    }


    void find(int i,int end, vector<int> &nums, long long int lsum, int l, vector<vector<long long int>> &v)
    {

        if(l==nums.size()/2 || i==end)
        {
            v[l].push_back(lsum);   
        }
        else
        {
            find(i+1,end,nums,lsum+nums[i],l+1,v);
            find(i+1,end,nums,lsum,l,v);
        }
    }
};