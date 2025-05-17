
using trie 

struct TrieNode
{
    struct TrieNode *child[26];
    bool isEndWord;
};

class StreamChecker {
public:

    TrieNode *root;
    vector<char> stack;
    StreamChecker(vector<string>& words) {
        
        root = initTrie();

        for(auto s: words)
        {
            reverse(s.begin(),s.end());
            makeTrie(s);
        }


    }
    
    struct TrieNode *initTrie()
    {
            TrieNode *p = new TrieNode;

            p->isEndWord=false;

            for(int i=0;i<26;i++)
            {
                p->child[i]=nullptr;
            }

            return p;
    }
    void makeTrie(string word)
    {
        TrieNode *curr = root;
        for(auto c: word)
        {
            if(curr->child[c-'a']==nullptr)
            {
                curr->child[c-'a']= initTrie();
            }

            curr=curr->child[c-'a'];
        }

        curr->isEndWord=true;
        
    }

    bool query(char letter) {
        stack.push_back(letter);

        return checkTrie();
    }

    bool checkTrie()
    {
        int n=stack.size();

        TrieNode *curr = root;
        cout<<endl;
        for(int i=n-1;i>=0;i--)
        {
            cout<<stack[i]<<" ";
            if(curr->child[stack[i]-'a']==nullptr)
                return false;
            else if(curr->child[stack[i]-'a']->isEndWord)
                return true;
            else
            {
                curr=curr->child[stack[i]-'a'];
            }
        }

        return curr->isEndWord;
    }
};
