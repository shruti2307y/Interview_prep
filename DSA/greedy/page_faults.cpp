int pageFaults(int N, int C, int pages[]){
        // code here
        
        map<int,int> present;
        int ans=0;
        int j=0;
        int dist=0;
        for(int i=0;i<N;i++)
        {
            if(present.find(pages[i])==present.end())
            {
                ans++;
                dist++;
                present[pages[i]]=1;
            }
            else
            {
                if(present[pages[i]]<=0)
                {
                    ans++;
                    dist++;
                }
                present[pages[i]]++;
            }
            
            while(j<i && dist>C)
            {
                present[pages[j]]--;
                if(present[pages[j]]==0)
                    dist--;
                j++;
            }
        }
        
        return ans;
    }
};