int kthElement(int arr1[], int arr2[], int n, int m, int k)
    {
        int l=max(0,k-m),r=min(k,n);
        
        return search(arr1,arr2,0,n-1,0,m-1,k-1);
    }
    
    int search(int a[],int b[], int la,int ra,int lb, int rb, int k)
    {
        if(la>ra)
            return b[lb+k];
        if(lb>rb)
            return a[la+k];
            
        int m1=(la+ra)/2;
        int m2=(lb+rb)/2;
        
        // cout<<a[m1]<<". "<<b[m2]<<"   "<<k<<endl;
        
        if(m1+m2-la-lb<k)
        {
            if(a[m1]>b[m2])
                return search(a,b,la,ra,m2+1,rb,k-(m2-lb+1));
            else
                return search(a,b,m1+1,ra,lb,rb,k-(m1-la+1));
        }
        else
        {
            if(a[m1]>b[m2])
                return search(a,b,la,m1-1,lb,rb,k);
            else
                return search(a,b,la,ra,lb,m2-1,k);
        }
    }