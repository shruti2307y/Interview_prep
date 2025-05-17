Suppose you have n integers labeled 1 through n. A permutation of those n integers perm (1-indexed) is 
considered a beautiful arrangement if for every i (1 <= i <= n), either of the following is true:

perm[i] is divisible by i.
i is divisible by perm[i].
Given an integer n, return the number of the beautiful arrangements that you can construct.

int solve(int mask, int n, int idx)
    {
        if(mask==(1<<n)-1)
            return 1;
        int ans=0;

        for(int i=0;i<n;i++)
        {
            if(mask&(1<<i))
                continue;
            else
            {
                if((i+1)%idx==0 || idx%(i+1)==0)
                    ans+=solve(mask|(1<<i),n,idx+1);
            }
        }

        return ans;
    }
    int countArrangement(int n) {
        
        return solve(0,n,1);
    }

