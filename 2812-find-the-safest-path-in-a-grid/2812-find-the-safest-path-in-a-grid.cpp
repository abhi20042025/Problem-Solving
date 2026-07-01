class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        queue<pair<int, int>> q;

        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

       
        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

       
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == 1e9) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

       auto isValidPath = [&](int safeness) -> bool {
            if (dist[0][0] < safeness) return false;

            queue<pair<int, int>> check_q;
            vector<vector<bool>> visited(n, vector<bool>(n, false));

            check_q.push({0, 0});
            visited[0][0] = true;

            while (!check_q.empty()) {
                auto [r, c] = check_q.front();
                check_q.pop();

                if (r == n - 1 && c == n - 1) return true;

                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                        if (dist[nr][nc] >= safeness) {
                            visited[nr][nc] = true;
                            check_q.push({nr, nc});
                        }
                    }
                }
            }
            return false;
        };

        int low = 0, high = 2 * n;
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isValidPath(mid)) {
                ans = mid;      
                low = mid + 1;
            } else {
                high = mid - 1;  
            }
        }

        return ans;
    }
};