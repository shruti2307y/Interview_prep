Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is 
the smallest in lexicographical order
 among all possible results.

class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> pres(26,0);
        int uniq=0;

        for(char a: s)
        {
            if(pres[a-'a']==0)
                uniq++;
            pres[a-'a']++;
        }

        stack<char> st1,st2;
        vector<int> pres2(26,0);

        for(char a: s)
        {
            if(st1.empty())
                {
                    st1.push(a);
                    pres2[a-'a']++;
                }
            else if(pres2[a-'a']==0)    
            {
                while(!st1.empty() && st1.top()>a && pres[st1.top()-'a']>0)
                {
                    pres2[st1.top()-'a']=0;
                    st1.pop();

                }
                
                st1.push(a);
                pres2[a-'a']++;

            }
            
            pres[a-'a']--;
        }

        string ret;

        while(!st1.empty())
        {
            ret.push_back(st1.top());
            st1.pop();
        }

        reverse(ret.begin(),ret.end());

        return ret;
    }
};