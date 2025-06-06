for each pair of vertices . find path through a intermediate vertex and get the min path if we travel through that 
intermediate node.

void shortest_distance(vector<vector<int>>&matrix){
	    // Code here
	    
	    int n=matrix.size();
	    
	    for(int i=0;i<n;i++)
	    {
	        for(int j=0;j<n;j++)
	        {
	            if(matrix[i][j]==-1)
	                matrix[i][j]=1e9;
	           
	        }
	        
	        matrix[i][i]=0;
	    }
	    
	    
	    for(int k=0;k<n;k++)
	    {
	        for(int i=0;i<n;i++)
	        {
	            for(int j=0;j<n;j++)
	            {
	                matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
	            }
	        }
	    }
	    
	    for(int i=0;i<n;i++)
	    {
	        for(int j=0;j<n;j++)
	        {
	            if(matrix[i][j]==1e9)
	                matrix[i][j]=-1;
	           
	        }
	        
	        
	    }
	}