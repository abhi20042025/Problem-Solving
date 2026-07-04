class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int dist = road[2];
            graph[u].push_back({v, dist});
            graph[v].push_back({u, dist});
        }

        queue<int> q;
        vector<bool> visited(n + 1, false);
        int min_score = INT_MAX;

        q.push(1);
        visited[1] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (const auto& edge : graph[node]) {
                int neighbor = edge.first;
                int dist = edge.second;

                min_score = min(min_score, dist);

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return min_score;
    }
};