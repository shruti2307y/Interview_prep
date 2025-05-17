classic example of two pointers
find if 3 elements sums up to be equal to x
bool find3Numbers(int A[], int n, int X)
    {
        //Your Code Here
        sort(A,A+n);
        for(int i=0;i<n;i++){
            int left=i+1;
            int right=n-1;
            while(left<right){
                int sum=A[i]+A[left]+A[right];
                if(sum==X) return true;
                else if(sum>X) right--;
                else left++;
            }
        }
        return false;
        
    }