class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        
        vector<vector<pair<int, int>>> adj(n);
        vector<int> uniqueCosts;
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            
           
            if ((u != 0 && !online[u]) || (v != n - 1 && !online[v])) {
                continue;
            }
            
            adj[u].push_back({v, cost});
            uniqueCosts.push_back(cost);
        }
        
        sort(uniqueCosts.begin(), uniqueCosts.end());
        uniqueCosts.erase(unique(uniqueCosts.begin(), uniqueCosts.end()), uniqueCosts.end());
        
      
        int low = 0, high = uniqueCosts.size() - 1;
        int ans = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int minEdgeCostThreshold = uniqueCosts[mid];
            
            if (isValidPathPossible(n, adj, minEdgeCostThreshold, k)) {
                ans = minEdgeCostThreshold; 
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        return ans;
    }

private:
    bool isValidPathPossible(int n, const vector<vector<pair<int, int>>>& adj, int threshold, long long maxBudget) {
        
        vector<long long> dp(n, -1);
        
        long long minTotalCost = getMinCost(0, n, adj, threshold, dp);
        
        return minTotalCost <= maxBudget;
    }
    
    long long getMinCost(int u, int n, const vector<vector<pair<int, int>>>& adj, int threshold, vector<long long>& dp) {
        if (u == n - 1) return 0;
        if (dp[u] != -1) return dp[u];
        
        long long minCost = 1e18; 
        
        for (const auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            
            if (weight >= threshold) {
                long long nextCost = getMinCost(v, n, adj, threshold, dp);
                if (nextCost != 1e18) {
                    minCost = min(minCost, weight + nextCost);
                }
            }
        }
        
        return dp[u] = minCost;
    }
};