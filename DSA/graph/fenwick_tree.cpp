
very very important algo for query for sum

// C++ code to demonstrate operations of Binary Index Tree 
#include <iostream> 

using namespace std; 

/*		 n --> No. of elements present in input array. 
	BITree[0..n] --> Array that represents Binary Indexed Tree. 
	arr[0..n-1] --> Input array for which prefix sum is evaluated. */

// Returns sum of arr[0..index]. This function assumes 
// that the array is preprocessed and partial sums of 
// array elements are stored in BITree[]. 
int getSum(int BITree[], int index) 
{ 
	int sum = 0; // Initialize result 

	// index in BITree[] is 1 more than the index in arr[] 
	index = index + 1; 

	// Traverse ancestors of BITree[index] 
	while (index>0) 
	{ 
		// Add current element of BITree to sum 
		sum += BITree[index]; 

		// Move index to parent node in getSum View 
		index -= index & (-index); 
	} 
	return sum; 
} 

// Updates a node in Binary Index Tree (BITree) at given index 
// in BITree. The given value 'val' is added to BITree[i] and 
// all of its ancestors in tree. 
void updateBIT(int BITree[], int n, int index, int val) 
{ 
	// index in BITree[] is 1 more than the index in arr[] 
	index = index + 1; 

	// Traverse all ancestors and add 'val' 
	while (index <= n) 
	{ 
		// Add 'val' to current node of BI Tree 
		BITree[index] += val; 

		// Update index to that of parent in update View 
		index += index & (-index); 
	} 
} 

// Constructs and returns a Binary Indexed Tree for given 
// array of size n. 
int *constructBITree(int arr[], int n) 
{ 
	// Create and initialize BITree[] as 0 
	int *BITree = new int[n+1]; 
	for (int i=1; i<=n; i++) 
		BITree[i] = 0; 

	// Store the actual values in BITree[] using update() 
	for (int i=0; i<n; i++) 
		updateBIT(BITree, n, i, arr[i]); 

	// Uncomment below lines to see contents of BITree[] 
	//for (int i=1; i<=n; i++) 
	//	 cout << BITree[i] << " "; 

	return BITree; 
} 


// Driver program to test above functions 
int main() 
{ 
	int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9}; 
	int n = sizeof(freq)/sizeof(freq[0]); 
	int *BITree = constructBITree(freq, n); 
	cout << "Sum of elements in arr[0..5] is "
		<< getSum(BITree, 5); 

	// Let use test the update operation 
	freq[3] += 6; 
	updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[] 

	cout << "\nSum of elements in arr[0..5] after update is "
		<< getSum(BITree, 5); 

	return 0; 
} 



example for this use case

so here for a particular segment we wanted to get the values less than a index;
so we store arr[index]=1; and every index less than that will be added in
prefixSum[index] and thats what we wanted to get
and here BIT came useful

class Solution {
public:
    int kBigIndices(vector<int>& nums, int k) {

        int n=nums.size();
        int left_bit[n+1];
        int right_bit[n+1];
        for(int i=0;i<=n;i++)
        {
            left_bit[i]=0;
            right_bit[i]=0;
        }
        int count[n][2];

        for(int i=0;i<n;i++)
        {
            count[i][0]=queryBIT(left_bit,nums[i]-1);
            updateBIT(left_bit,nums[i],1,n+1);

            count[n-1-i][1]=queryBIT(right_bit,nums[n-1-i]-1);
            updateBIT(right_bit,nums[n-1-i],1,n+1);
        }
        int res=0;
        for(int i=0;i<n;i++)
        {
            if(count[i][0]>=k && count[i][1]>=k)
                res++;
        }

        return res;
    }

    void updateBIT( int arr[], int index,int diff, int n)
    {
        index++;
        while(index<n)
        {
            arr[index]+=diff;
            index+=index&(-index);
        }
    }

    int queryBIT(int arr[], int index)
    {
        index++;
        int sum=0;
        while(index>0)
        {
            sum+=arr[index];
            index-=index&(-index);
        }
        return sum;
    }
};