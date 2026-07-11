class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n), rank(n, 0);
        iota(parent.begin(), parent.end(), 0); 
        
        function<int(int)> find = [&](int x) -> int {
            if (parent[x] != x)
                parent[x] = find(parent[x]); 
            return parent[x];
        };
        
        auto unite = [&](int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return;
            if (rank[px] < rank[py]) swap(px, py);
            parent[py] = px;
            if (rank[px] == rank[py]) rank[px]++;
        };
        
        for (auto& e : edges)
            unite(e[0], e[1]);
        
        unordered_map<int, int> vertexCount, edgeCount;
        
        for (int i = 0; i < n; i++)
            vertexCount[find(i)]++;
        
        for (auto& e : edges)
            edgeCount[find(e[0])]++;
        
        int result = 0;
        for (auto& [root, k] : vertexCount) {
            int e = edgeCount[root]; 
            if (e == k * (k - 1) / 2)
                result++;
        }
        
        return result;
    }
};