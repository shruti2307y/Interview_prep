
here count the number of elements that would make the sum less that target using two pointers

long long countTriplets(long long arr[], int n, long long sum)
	{
	    sort(arr,arr+n);
	    long long int ans=0;
	    long long int curr=0;
	    for(int i=0;i<n;i++)
	    {
	        int j=i+1;
	        int k=n-1;
	        curr=arr[i];
	        while(j<k)
	        {
	            curr=arr[i]+arr[j]+arr[k];
	            
	            if(curr<sum)
	            {
	                ans+=(k-j);
	                j++;
	            }
	            else
	            {
	                k--;
	            }
	        }
	    }
	    
	    return ans;
	}