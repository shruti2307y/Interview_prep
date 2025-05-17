
isme simply gather all n smallest elements in arr1 and sort both of them

void merge(long long arr1[], long long arr2[], int n, int m) 
        { 
            int i=0,j=n-1,k=0;  
            while(i<n && i<=j && k<m)
            {
                if(arr1[i]<=arr2[k])
                {
                    i++;
                }
                else
                {
                    int t=arr1[j];
                    arr1[j]=arr2[k];
                    arr2[k]=t;
                    j--;
                    k++;
                }
            }
            
            sort(arr1,arr1+n);
            sort(arr2,arr2+m);
        } 

approach 2 GAP sort

//Back-end complete function Template for C

//Function to find next gap.
int nextGap(int gap) 
{ 
    //It returns the ceil value of gap/2 or 0 if gap is 1.
	if (gap <= 1) 
		return 0; 
	return (gap / 2) + (gap % 2); 
} 
    
//Function to merge the arrays.
void merge(int arr1[], int arr2[], int n, int m)
{ 
	int i, j, gap = n + m; 
	
	for (gap = nextGap(gap); gap > 0; gap = nextGap(gap)) 
	{ 
	    //Comparing elements in the first array itself with difference in 
	    //index equal to the value of gap. 
		for (i = 0; i + gap < n; i++) {
		    //If element at ith index is greater than element at
		    //(i+gap)th index, we swap them. 
			if (arr1[i] > arr1[i + gap]){
			    int temp = arr1[i];
				arr1[i] = arr1[i + gap];
				arr1[i + gap] = temp;
			} 
		}
    
		//Now comparing elements in both arrays with help of two pointers.
		//The loop stops whenever any pointer exceeds the size of its array.
		for (j = gap > n ? gap-n : 0 ; i < n&&j < m; i++, j++) {
		    //If element in the first array is greater than element in
		    //second array, we swap them. 
			if (arr1[i] > arr2[j]){
			    int temp = arr1[i];
				arr1[i] = arr2[j];
				arr2[j] = temp;
			} 
		}
        
		if (j < m) 
		{ 
			//At last, comparing elements in the second array itself with 
            //difference in index equal to the value of gap.
			for (j = 0; j + gap < m; j++) {
			    //If element at jth index is greater than element at
		        //(j+gap)th index, we swap them. 
				if (arr2[j] > arr2[j + gap]){
				    int temp = arr2[j];
				    arr2[j] = arr2[j + gap];
				    arr2[j + gap] = temp;
				} 
			}
		} 
	} 
}