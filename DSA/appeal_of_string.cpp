The appeal of a string is the number of distinct characters found in the string.

For example, the appeal of "abbca" is 3 because it has 3 distinct characters: 'a', 'b', and 'c'.
Given a string s, return the total appeal of all of its substrings.

A substring is a contiguous sequence of characters within a string.


long long appealSum(string s) {
        
        vector<int> last(26);
        long res = 0, n = s.size();
        for (int i = 0; i < n; ++i) {
            last[s[i] - 'a'] = i + 1;
            for (int j: last)
                res += j;
        }
        return res;
    
    }