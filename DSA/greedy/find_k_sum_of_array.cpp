You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.

We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).

Return the K-Sum of the array.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Note that the empty subsequence is considered to have a sum of 0.

So isme find the smalles sum possible first, this can be done with the help of minQ.
toh make all the number positive and get the max sum also.

class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        int n = nums.size();
        long long maxsum = 0;
	    //subtract stores the sum which needs to be subtracted from the maximum sum
        vector<long long> subtract;
        //find the maxsum and update nums so that all elements are positive
        for(int i=0;i<n;i++){
            if(nums[i]>=0){
                maxsum+=nums[i];
            }else{
                nums[i] = abs(nums[i]);
            }
        }
        //sorting nums as per absolute values
        sort(nums.begin(), nums.end());
        
        //Initialize priority queue (minheap) to store current least value which needs to be
        //subtracted from maxsum and the index of nums we are currently at.
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        //start from index 0 with minimum value as nums[0]
        pq.push({nums[0], 0});
        while(!pq.empty() && subtract.size()<k-1){
            pair<long long,int> topp = pq.top(); 
            pq.pop();
            long long subt = topp.first;
            int idx = topp.second;
            //push this value to subtract array
            subtract.push_back(subt);
            //if we are not at last idx then we can add further values to pq
            if(idx<n-1){
                pq.push({subt+nums[idx+1] , idx+1});
                pq.push({nums[idx+1] + (subt-nums[idx]) , idx+1});
            }
        }
        
        //ans stores all the largest sum in decreasing order
        vector<long long>ans;
        ans.push_back(maxsum);
        for(long long subt:subtract) {
            ans.push_back(maxsum - subt);
        }
        //return Kth largest sum 
        return ans[k-1];
    }
};

