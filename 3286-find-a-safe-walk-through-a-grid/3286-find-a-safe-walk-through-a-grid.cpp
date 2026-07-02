class Solution {
public:
    bool findSafeWalk(std::vector<std::vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
     
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        std::vector<std::vector<int>> dist(m, std::vector<int>(n, 1e9));
        
        std::deque<std::pair<int, int>> dq;
        
        dist[0][0] = grid[0][0];
        dq.push_front({0, 0});
        
        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            
            if (r == m - 1 && c == n - 1) {
                break;
            }
            
            for (int i = 0; i < 4; ++i) {
                int nr = r + dirs[i][0];
                int nc = c + dirs[i][1];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int weight = grid[nr][nc];
                    
                    if (dist[r][c] + weight < dist[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + weight;
                        
                        if (weight == 0) {
                            dq.push_front({nr, nc});
                        } else {
                            dq.push_back({nr, nc});
                        }
                    }
                }
            }
        }
        
       
        return dist[m - 1][n - 1] < health;
    }
};