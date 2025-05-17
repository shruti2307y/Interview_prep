int lower_bound(int arr[] , int low  , int high , int key)
{
    int min=-1;
    while(low<=high)
    {
        int mid = low+(high-low)/2;
        
        if(arr[mid]>=key)
        {
            min=mid;
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return min;
}