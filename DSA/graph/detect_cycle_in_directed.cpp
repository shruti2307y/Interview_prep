
using DFS
// Function to detect cycle in a directed graph.
     bool isloopexist(int V, vector<int>adj[],vector<bool>&visited,vector<bool>&recst,int src){
        visited[src]=true;
        recst[src]=true;
        for(auto child:adj[src]){
            if(visited[child]==false){
                if(isloopexist(V,adj,visited,recst,child)==true) return true;
            }
            else if(recst[child]==true) return true;
        }
        recst[src]=false;
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        // code here
        vector<bool>visited(V,false);
        vector<bool>recst(V,false);
        for(int i=0;i<V;i++){
            if(isloopexist(V,adj,visited,recst,i)==true) return true;
        }
        return false;
    }

Using BFS => use topological sort