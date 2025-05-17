https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/description/

Given an array nums that represents a permutation of integers from 1 to n. We are going to construct a binary search tree (BST) by inserting the elements of nums in order into an initially empty BST. Find the number of different ways to reorder nums so that the constructed BST is identical to that formed from the original array nums.

For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
Return the number of ways to reorder nums such that the BST formed is identical to the original BST formed from nums.

Since the answer may be very large, return it modulo 109 + 7.


    #define ll long long
    ll mod = 1e9+7;
    ll fact[1001];
        void precalc() {
            fact[0] = 1;
            for(ll i = 1; i < 1001; i++)
                fact[i] =(fact[i - 1]*i)%mod;
    }

    ll inv(ll x)
    {
        return x<=1 ? x: mod-(ll)(mod/x)* inv(mod%x)%mod;
    }
    
    ll mul(ll x, ll y)
    {
        return ((x%mod)*(y%mod))%mod;
    }
    ll divide(ll x, ll y)
    {
        return mul(x,inv(y));
    }

    int numOfWays(vector<int>& nums) {

        int n=nums.size();
        precalc();
        return findCount(nums)-1;
    }

    ll compute(ll left, ll right)
    {
        if(left==0 or right==0)
            return 1ll;
        else
            return divide(fact[left+right],mul(fact[left],fact[right]));
    }
    ll findCount(vector<int> nums)
    {
        if(nums.empty())
            return 0;
        else if(nums.size()==1)
            return 1;
        else
        {
            vector<int> left,right;
            int n=nums.size();
            for(int i=1;i<n;i++)
            {
                if(nums[i]<nums[0])
                    left.push_back(nums[i]);
                else
                    right.push_back(nums[i]);
            }

            ll ls=left.size();
            ll rs=right.size();
            ll pnc=compute(ls,rs)%mod;
            
            ll left_ans=max(1LL,findCount(left));
            ll right_ans=max(1ll,findCount(right));
            


            return mul(mul(left_ans,right_ans),pnc);
        }
    }