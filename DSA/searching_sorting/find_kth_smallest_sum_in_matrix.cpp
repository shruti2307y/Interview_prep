https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/description/

You are given an m x n matrix mat that has its rows sorted in non-decreasing order and an integer k.

You are allowed to choose exactly one element from each row to form an array.

Return the kth smallest array sum among all possible arrays.


simplest solution to cap

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int> ans = {0};
        int maxSize = k + 1;
        
        for(int i = 0; i < mat.size(); i++){
            // cal
            vector<int> temp;
            for(int j = 0; j < mat[i].size(); j++){
                for(int k = 0; k < ans.size(); k++){
                    temp.push_back(mat[i][j] + ans[k]);
                }
            }
            
            sort(temp.begin(), temp.end());
            
            // update answer
            ans.clear();
            int till = min((int)maxSize, (int)temp.size()); // cut Line
         
            for(int j = 0; j < till; j++){
                ans.push_back(temp[j]);
            }
            
        }
        return ans[k -1];
    }
};


min heap solution 
class Solution {
public:
vector<int> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&nums1,&nums2](pair<int,int> a, pair<int,int>b){
            return nums1[a.first]+nums2[a.second] >
                nums1[b.first]+nums2[b.second];
        };
        int n = nums1.size();
        int m = nums2.size();
        vector<int> ans;
        if(n==0 || m==0)
            return ans;
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)>pq(cmp);
        pq.push({0,0});
        while(k-- && !pq.empty())
        {
            int i = pq.top().first;
            int j = pq.top().second;
            pq.pop();
            
            if(j+1<m)
                pq.push({i,j+1});
            if(j==0 && i+1 <n)
                pq.push({i+1,j});
            
            ans.push_back(nums1[i]+nums2[j]);
        }
        return ans;
    }
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int> nums1 = mat[0];
        int n =  mat.size();
        for(int i = 1; i<n; ++i)
        {
            nums1 = kSmallestPairs(nums1,mat[i],k);
        }
        return nums1[k-1];
    }
};