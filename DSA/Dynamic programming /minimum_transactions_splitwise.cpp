https://leetcode.com/problems/optimal-account-balancing/description/

You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti] indicates that the person with ID = fromi gave amounti $ to the 
person with ID = toi.

Return the minimum number of transactions required to settle the debt.


toh first toh sidha sabke balances calculate krlo, issey jiska balance[0] hoga woh out of the picture.

Now for remaining balances minimum number of transactions could be N which would be the size of balances array.
why? because we can think of an external system which will collect or give money to others, now each balances will take or give money to that centralised entity and this will
result in N transactions, 

Now this central entity can be one of the balance member itself so we get max N-1 txn.


in this we would take the currIndex in balances which is not zero, transfer all its funds to a account to its right, and mark txn + 1;

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        
        map<int,int> balance;

        for(vector<int> &a: transactions)
        {
            balance[a[0]] += a[2];
            balance[a[1]] -= a[2];
        }

        vector<int> bal;

        for(auto a: balance)
        {
            if(a.second!=0)
                bal.push_back(a.second);
        }

        return findMin(bal,0);
    }

    int findMin(vector<int> &balances, int currIndex)
    {
        
        while(currIndex<balances.size() && balances[currIndex]==0)
            currIndex++;

        if(currIndex>=balances.size())
            return 0;

        int result = INT_MAX;

        for(int i=currIndex+1;i<balances.size();i++)
        {
            if(balances[currIndex]*balances[i]<0)
            {
                balances[i] +=balances[currIndex];
                result = min(result, 1+findMin(balances,currIndex+1));
                balances[i] -=balances[currIndex];
            }
        }

        return result;
    }
};



Another solution to this will be of finding out from all the balances, how many subgroup we can make that has sum = 0, because if that subgroup has sum = 0, then no money would be needed
to be transfered out of the subgroup and we can reduce the max txn


class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        
        map<int,int> balance;

        for(vector<int> &a: transactions)
        {
            balance[a[0]] += a[2];
            balance[a[1]] -= a[2];
        }

        vector<int> bal;

        for(auto a: balance)
        {
            if(a.second!=0)
                bal.push_back(a.second);
        }

        int n = bal.size();
        vector<int> dp((1<<n),-1);
        return n-findMin(bal,(1<<n)-1,dp);
    }

    int findMin(vector<int> &balances, int state, vector<int> &dp)
    {
        if(dp[state]!=-1)
            return dp[state];

        int balance = 0, answer = -1;

        for(int i=0;i<balances.size();i++)
        {
            if((1<<i)&state)
            {
                balance += balances[i];
                answer = max(answer, findMin(balances, state ^ (1<<i),dp));
            }
        }

        if(balance==0)
            answer = answer + 1;
        
        return dp[state]= answer;
    }
};