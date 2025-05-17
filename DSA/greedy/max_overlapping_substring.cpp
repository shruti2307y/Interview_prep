Here is the question link: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/description/

Here the idea is to find out whether one subsring is part of another or not/ overlapping.

Here is the close up solution i could find out

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        
        vector<int> fst(26, INT_MAX);
        vector<int> lst(26, INT_MIN);
        for (int i = 0; i < n; i++) {
            fst[s[i] - 'a'] = min(fst[s[i] - 'a'], i);
            lst[s[i] - 'a'] = max(lst[s[i] - 'a'], i);
        }
        
        vector<pair<int, int>> t;
        for (int i = 0; i < 26; i++) {
            if (fst[i] < n) {
                int b = fst[i];
                int e = lst[i];
                for (int j = b; j <= e; j++) {
                    b = min(b, fst[s[j] - 'a']);
                    e = max(e, lst[s[j] - 'a']);
                }
                if (b == fst[i]) {
                    t.emplace_back(e, b);
                }
            }
        }
        
        sort(t.begin(), t.end());
        vector<string> ans;
        int prev = -1;
        for (auto &[e, b] : t) {
            if (b > prev) {
                ans.push_back(s.substr(b, e - b + 1));
                prev = e;
            }
        }
        
        return ans;
    }
};

and here is another one which is also working fine i guess.



class Solution {
public:
   int checkSubstr(string &s, int i, vector<int> &l, vector<int> &r) {
    int right = r[s[i] - 'a'];
    for (auto j = i; j <= right; ++j) {
        if (l[s[j] - 'a'] < i)
            return -1;
        right = max(right, r[s[j] - 'a']);
    }
    return right;
}
vector<string> maxNumOfSubstrings(string s) {
    vector<int> l(26, INT_MAX), r(26, INT_MIN);
    vector<string> res;
    for (int i = 0; i < s.size(); ++i) {
        l[s[i] - 'a'] = min(l[s[i] - 'a'], i);
        r[s[i] - 'a'] = i;
    }
    int right = -1;
    for (int i = 0; i < s.size(); ++i) {
        if (i == l[s[i] - 'a']) {
            int new_right = checkSubstr(s, i, l, r);
            if (new_right != -1) {
                if (i > right)
                    res.push_back("");                     
                right = new_right;
                res.back() = s.substr(i, right - i + 1);
            }
        }
    }
    return res;
}
};



