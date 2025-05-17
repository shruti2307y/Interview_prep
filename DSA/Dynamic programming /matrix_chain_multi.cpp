
## so here given a array of matrix sizes for ex: {40,20,30,10,30}
toh we have n-1 matrices like 40x20, 20x30 .... so on
so here matrix i ke dimensions hoge arr[i-1]xarr[i] 
so partition ese kisi group of matrices ko apn 2 group me divide krege and k will be the martix from where partition will happen

k goes from i to j-1 ki first matrix se lekr last se pehle tk wali ko partion me lege and find out corresponding partions ka value 
and cost of that partion and get min



RECURSIVE APPROACH
int find(int i, int j, int N, int arr[], vector<vector<int>> &dp)
    {
        if(i==j)
            return 0;
        if(dp[i][j]!=-1)
            return dp[i][j];
        
        int steps=INT_MAX;
        for(int k=i;k<j;k++)
        {
            steps=min(steps,find(i,k,N,arr,dp)+find(k+1,j,N,arr,dp)+arr[i-1]*arr[k]*arr[j]);
        }
        
        return dp[i][j]=steps;
    }
    int matrixMultiplication(int N, int arr[])
    {
        vector<vector<int>> dp(N,vector<int>(N,-1));
        
        
        return find(1,N-1,N,arr,dp);
       
    }



TABULATION SE YEH ESE HOGA
int matrixMultiplication(int N, int arr[])
    {
        vector<vector<int>> dp(N,vector<int>(N,-1));
        
        for(int i=0;i<N;i++)
        {
            dp[i][i]=0;
        }
        
        for(int i=N-2;i>=1;i--)
        {
            for(int j=i+1;j<N;j++)
            {
                int steps=INT_MAX;
                for(int k=i;k<j;k++)
                {
                    steps=min(steps,dp[i][k]+dp[k+1][j]+arr[i-1]*arr[k]*arr[j]);  
                }
                dp[i][j]=steps;
            }
        }
        
        return dp[1][N-1];
       
    }