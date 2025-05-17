 You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other words, the first element of the array is the next element of the 
 last element, and the last element of the array is the previous element of the first element.

You can do the following operation any number of times:

Pick any element from arr and increase or decrease it by 1.
Return the minimum number of operations such that the sum of each subarray of length k is equal.

A subarray is a contiguous part of the array.

https://leetcode.com/problems/make-k-subarray-sums-equal/description/
 
 long long makeSubKSumEqual(vector<int>& arr, int k) {
        
        long long res = 0;
        int n = arr.size();
        k = __gcd(k , n);

        for(int i=0;i<k;i++) {
            vector<int> vec;
            for(int j = i;j<n;j+=k)
                vec.push_back(arr[j]);

            sort(vec.begin() , vec.end());
            long long mid = vec[vec.size()/2];
            
            for(int j=i;j<n;j+=k) 
                res += abs(mid - arr[j]);
        }
        return res;

    }