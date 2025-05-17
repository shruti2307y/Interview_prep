So here is the question link: https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/

So basically we only need to get 3 best from each row, because mutually exclusive 3 hi hoge.

So here you go get them in old fashioned way.


class Solution {
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        int m=board.size(),n=board[0].size();
        vector<vector<pair<long long,int>>> grid;
        for(int i=0;i<m;i++){
            vector<pair<long long,int>> x;
            for(int j=0;j<n;j++){
                x.push_back({board[i][j],j});
            }
            sort(x.rbegin(),x.rend());
            grid.push_back(x);
        }
        long long ans=-LLONG_MAX;
        for(int i=0;i<m;i++){
            for(int j=0;j<3;j++){
                for(int k=i+1;k<m;k++){
                    for(int q=0;q<3;q++){
                        if(grid[i][j].second==grid[k][q].second) continue;
                        for(int x=k+1;x<m;x++){
                            for(int y=0;y<3;y++){
                                if(grid[i][j].second==grid[x][y].second || grid[x][y].second==grid[k][q].second) continue;
                                long long sum=grid[i][j].first+grid[x][y].first+grid[k][q].first;
                                ans=max(ans,sum);
                            }
                        }
                    }
                }
            }
        }
        return ans;

    }
};
