
here matching all try * for all elements in pattern and ? for only one


bool match(string wild, string pattern)
    {
        // code here
        
        int np = pattern.size();
        int nw = wild.size();
        
        vector<vector<int>> mp(nw+1,vector<int>(np+1,0));
        
        
        
        for(int i=1;i<=nw;i++)
        {
            for(int j=1;j<=np;j++)
            {
                if(wild[i-1]=='*')
                {
                    if(i==1)
                    {
                        mp[i][j]=1;
                    }
                    else
                    {
                        mp[i][j]=max(mp[i-1][j-1],max(mp[i][j-1],mp[i-1][j]));
                    }
                }
                else if(wild[i-1]=='?')
                {
                    if(i==1)
                        mp[i][j]=1;
                    else
                    {
                            mp[i][j]=mp[i-1][j-1];
                    }
                }
                else
                {
                    if(wild[i-1]==pattern[j-1])
                    {
                        if(i==1 || j==1)
                            mp[i][j]=1;
                        else
                            mp[i][j]=mp[i-1][j-1];
                    }
                    else
                        mp[i][j]=0;
                }
                
                // cout<<mp[i][j]<<" ";
            }
            // cout<<endl;
        }
        
        if(mp[nw][np]==1)
            return true;
        
        return false;
    }