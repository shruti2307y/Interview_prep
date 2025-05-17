

so idhr we maintain an array of elements which are incresing ese
toh agar new element khi kisi bich me lie krta toh add it or else
push back krdo array me or size badh jayegi

lower_bound acha use kiya h yhaa


int longestSubsequence(int n, int a[])
    {
       // your code here
       
       vector<int>ans;
       for(int i=0;i<n;i++){
           int index=lower_bound(ans.begin(),ans.end(),a[i])-ans.begin();
           
           int low=0,high=ans.size()-1;
           int ind=0;

           ## yeh mene apne se likha lower bound 
           while(low<=high)
           {
               int mid=(low+high)/2;
               if(ans[mid]<=a[i])
               {
                   ind=mid;
                   low=mid+1;
               }
               else
                high=mid-1;
           }
          if(ind<ans.size() && ans[ind]<a[i])
                ind++;
            // cout<<ind<<" "<<index<<endl;
           if(ind>=ans.size()){
               ans.push_back(a[i]);
           }
           else{
               ans[ind]=a[i];
           }
       }
       return (int) ans.size();
    }