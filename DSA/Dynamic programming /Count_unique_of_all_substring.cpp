https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/description/

try to understand this 
https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/solutions/1651064/1d-dp-approach/

https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/solutions/128952/java-c-python-one-pass-o-n/

    int uniqueLetterString(string S) {
        int index[26][2], res = 0, N = S.length(), mod = pow(10, 9) + 7;
        memset(index, -1, sizeof(int) * 52);
        for (int i = 0; i < N; ++i) {
            int c = S[i] - 'A';
            res = (res + (i - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
            index[c][0] = index[c][1];
            index[c][1] = i;
        }
        for (int c = 0; c < 26; ++c)
            res = (res + (N - index[c][1]) * (index[c][1] - index[c][0]) % mod) % mod;
        return res;
    }