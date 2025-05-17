https://leetcode.com/problems/minimum-time-to-finish-the-race/


yha pr esa h ki ek path ko break kiya ja rha 2 paths me and these two divided paths are precomputed.
also we cover each cornercase that what if the answer is not changing the tire at all till a particular lap

class Solution {
public:
    #define lint long long
    lint dp[1001];
    lint minc[1001];
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        lint n = tires.size();
        const lint inf = (int)1e9;
        for (int i = 0; i < numLaps; i++) minc[i] = inf, dp[i] = inf;
        for (int i = 0; i < n; i++) {
            lint f = tires[i][0], r = tires[i][1];
            lint ct = 0;
            lint cost = f;
            lint run = 0;
            while (cost < changeTime + f) {
                run += cost;
                minc[ct] = min(minc[ct], run);
                cost *= r;
                ct++;
            }
        }
        for (int i = 0; i < numLaps; i++) {
            if (i == 0) {
                dp[i] = minc[0]; continue;
            }
            dp[i] = minc[i];
            for (int j = 0; j < i; j++) {
                dp[i] = min(dp[i], dp[j] + dp[i-j-1] + changeTime);
            }
        }
        return dp[numLaps-1];
    }
};