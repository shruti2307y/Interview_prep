
bottom up approach 

here set ko lekr iterate kiya bcoz we want smaller values first and then same values ke liye unke rows and cols value update ek sath ki gyi h
kyuki you want strictly greater values hence ek same value ka answer se dusre same value pr ni use kr sakte


https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/description/

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) 
    {
        int m=mat.size();
        int n=mat[0].size();
        unordered_map<int,vector<pair<int,int>>> mp;
        set<int> uniquevalues;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                mp[mat[i][j]].push_back({i,j});
                // just for equalvalues -> store all pair of i,j
                uniquevalues.insert(mat[i][j]);
            }
        }
        vector<vector<int>> temp(m, vector<int>(n));
        vector<int> row(mat.size(),0);
        // store max count in ith row 
        vector<int> colu(mat[0].size(),0);
        // store max count jth col
        for(auto cur:uniquevalues)
        {
            vector<vector<int>> equalvalued;
            for(auto curpositions:mp[cur])
            {
                int i=curpositions.first;
                int j=curpositions.second;
                // cout<<cur<<" ::   "<< i<<" "<<j<<"   " <<row[i]<<"-"<<colu[j]<<endl;
                equalvalued.push_back({max(row[i],colu[j])+1,i,j});
            }
            // equalvalued cannot update in same single for loop as they can be in same row /column and increase count so just we store and traverse and update for corresponding row and col 
            for(auto e:equalvalued)
            {
                int i=e[1];
                int j=e[2];
                row[i]=max(e[0],row[i]);
                colu[j]=max(e[0],colu[j]);
            }
        }
        int ans=0;
        for(auto e:row)
        {
            ans=max(ans,e);
        }
        for(auto e:colu)
        {
            ans=max(ans,e);
        }
        return ans;
    }
};