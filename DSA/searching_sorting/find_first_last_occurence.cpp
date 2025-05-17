 int smallest(int arr[] , int low  , int high , int key)
{
    int min=-1;
    while(low<=high)
    {
        int mid = low+(high-low)/2;
        
        if(arr[mid]==key)
        {
            min=mid;
            high=mid-1;
        }
        else if(arr[mid]>key)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return min;
}
int largest(int arr[] , int low  , int high , int key)
{
    int max=-1;
    while(low<=high)
    {
        int mid = low+(high-low)/2;
        
        if(arr[mid]==key)
        {
            max=mid;
            low=mid+1;
        }
        else if(arr[mid]>key)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    
    return max;
}


vector<int> find(int arr[], int n , int x )
{
    // code here
    return { smallest(arr,0,n-1,x) , largest(arr,0,n-1,x) };
}