here key is removing the search space effieciently 

int search(vector<int>& nums, int target) {
        

        int n = nums.size();

        int l=0,r=n-1;

        while(l<=r)
        {
            int mid=(l+r)/2;

            if(nums[mid]==target)
                return mid;

            this means that left subarray does not have the pivot
            if(nums[l]<=nums[mid])
            {
                check if answer lies in left subarray
                if(nums[l]<= target && target<=nums[mid])
                    r=mid-1;
                else just reduce the search space
                else
                    l=mid+1;
            }
            else
            {
                if(nums[mid]<=target && target<=nums[r])
                    l=mid+1;
                else
                    r=mid-1;
            }
        }

        return -1;
    }
