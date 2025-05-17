int lps(string s) {
	    // Your code goes here
	    
	    int n=s.size();
	    
	    vector<int> lps(n);
	    
	    lps[0]=0;
	    
	    for(int i=1;i<n;i++)
	    {
	        int j=lps[i-1];
	        
	        while(j>=1 && s[i]!=s[j])
	        {
	            j=lps[j-1];
	        }
	        
	        if(s[i]==s[j])
	            lps[i]=j+1;
	        else
	            lps[i]=j;
	    }
	    
	    return lps[n-1];
	    
	}