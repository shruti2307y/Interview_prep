vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        vector<int> ans;
        int n=matrix.size()-1;
        int m=matrix[0].size()-1;
        getOrder(matrix,0,n,0,m,ans);

        return ans;
    }

    void getOrder(vector<vector<int>> &mat, int row_start, int row_end, int col_start, int col_end, vector<int> &ans)
    {
        if(row_start>row_end || col_start>col_end)
            return ;
        else
        {
            for(int j=col_start;j<=col_end;j++)
                ans.push_back(mat[row_start][j]);
            for(int i=row_start+1;i<row_end;i++)
                ans.push_back(mat[i][col_end]);
            for(int j=col_end;j>=col_start && row_start<row_end;j--)
                ans.push_back(mat[row_end][j]);
            for(int i=row_end-1;i>row_start && col_start<col_end;i--)
                ans.push_back(mat[i][col_start]);

            getOrder(mat,row_start+1,row_end-1,col_start+1,col_end-1,ans);
        }
    }