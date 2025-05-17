
here for such kinda problems that needs to get largest/smallest value for something that needs to be done
and there is search space
we can use binary search their

the check method should return with O(n) complexity

bool find(int A[], int minPage, int N, int M)
    {
        int currPages=0;
        int reqStudent=0;
        for(int i=0;i<N;i++)
        {
            currPages+=A[i];
            if(currPages>minPage)
            {
                reqStudent++;
                currPages=0;
                i--;
            }
            if(reqStudent>M)
                return false;
        }
        if(currPages>0)
            reqStudent++;
        if(reqStudent<=M)
            return true;
        else
            return false;
    }
    int findPages(int A[], int N, int M) 
    {
        //code here
        int low=1;
        int high=0;
        
        for(int i=0;i<N;i++)
        {
            low=min(low,A[i]);
            high+=A[i];
        }
        if(M>N)
            return -1;
        int ans=-1;
        while(low<=high)
        {
            int mid=(low+high)/2;
            
            if(find(A,mid,N,M))
            {
               ans=mid;
               high=mid-1;
            }
            else
            {
                low=mid+1;
            }
        }
        
        return ans;
        
    }