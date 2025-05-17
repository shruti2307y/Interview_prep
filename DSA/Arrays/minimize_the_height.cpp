
so here the one of the solution is that we add k ya sub k from all the elements toh uss case me diff hoga

arr[n-1]-arr[0]

but ab apn ek division wala bhi try krege
toh for each index uske pehle walo ko k add krdo and right walo ko k sub krdo and each step pr check min and max kya
hoga and update the ans


int getMinDiff(int arr[], int n, int k) {
        // code here
        
        sort(arr,arr+n);
        
        int ans=arr[n-1]-arr[0];
        
        int leftmin=arr[0]+k;
        int rightmax=arr[n-1]-k;
        
        for(int i=1;i<n;i++)
        {
            if(arr[i]<k)
                continue;
            ans=min(ans,max(rightmax,arr[i-1]+k)-min(leftmin,arr[i]-k));
        }
        return ans;
        
    }