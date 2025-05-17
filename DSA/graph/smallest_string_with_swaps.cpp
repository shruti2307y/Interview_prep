give a string and pair of swappable indices
get the lexographical smallest string


here we can use DSU to group together connected component 
and each connected component will have a list of char from which starting from i=0 we will pick the smallest one
and update the array(pop_back)


class DisjointSet {
private:
    vector<int> parent;
    vector<int> size;

public:

    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);

        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUParent(int node) {
        if(node == parent[node]) {
            return node;
        }
        return parent[node] = findUParent(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUParent(u);
        int ulp_v = findUParent(v);

        if(ulp_u == ulp_v) {
            return;
        }

        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } 
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    } 
};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.length();
        DisjointSet dsu(n);

        for(auto it : pairs) {
            int u = it[0];
            int v = it[1];

            dsu.unionBySize(u, v);
        }

        unordered_map<int, vector<char>> components;

        for(int i = 0; i < n; i++) {
            int root = dsu.findUParent(i);
            components[root].push_back(s[i]);
        }

        // sorting the char array of adj list in reverse order
        for(auto& component : components) {
            sort(component.second.begin(), component.second.end(), greater<char>());
        }

        for(int i = 0; i < n; i++) {
            int root = dsu.findUParent(i);
            s[i] = components[root].back();
            components[root].pop_back();
        }

        return s;
    }
};