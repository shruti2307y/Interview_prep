
https://leetcode.com/problems/queue-reconstruction-by-height/description/

You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). 
Each people[i] = [hi, ki] represents the ith person of height hi with exactly ki other people in front who have a height 
greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array 
queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).


can be done simply like this or using BIT in N*logN*logN


struct LLNode{

    LLNode *next,*prev;
    int h,k;
    LLNode(int height, int kth)
    {
        h=height;
        k=kth;

        next=nullptr;
        prev=nullptr;
    }
};

class Solution {
private:
    LLNode *root;
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        
        sort(people.begin(),people.end(), [](const vector<int> &a, const vector<int> &b){
            if(a[0]==b[0])
                return a[1]<=b[1];
            return a[0]>b[0];
        });

        for(auto a: people){
            insert(a);
        }

        vector<vector<int>> ans;    
        while(root)
        {
            ans.push_back({root->h,root->k});
            root=root->next;
        }

        return ans;
    }

    void insert(vector<int> &people)
    {
        int greater=people[1];
        LLNode *curr=root, *prev=nullptr;
        while(greater>0 && curr)
        {
            if(curr->h>=people[0])
                greater--;
            prev=curr;
            curr=curr->next;
        }
        LLNode *nn= new LLNode(people[0],people[1]);
        nn->next=curr;
        if(prev)
            prev->next=nn;
        if(root==curr)
            root=nn;
    }
};


https://leetcode.com/problems/queue-reconstruction-by-height/solutions/427157/three-different-c-solutions-from-o-n-2-to-o-nlogn-faster-than-99/