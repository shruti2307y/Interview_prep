https://leetcode.com/problems/last-stone-weight-ii/description/

Abhi we can deduce that breaking stones and all breaks the problems into creating two subgroup and subtracting their sum. and getting minimun of that becomes

getting a subset sum close to totalSum/2 

isme we use knapsack to get a subset sum close to totalSum/2 

class Solution {
public:
        int lastStoneWeightII(vector<int> A) {
        bitset<1501> dp = {1};
        int sumA = 0;
        for (int a : A) {
            sumA += a;
            for (int i = min(1500, sumA); i >= a; --i)
                dp[i] = dp[i] + dp[i - a];
        }
        for (int i = sumA / 2; i >= 0; --i)
            if (dp[i]) return sumA - i - i;
        return 0;
    }
};