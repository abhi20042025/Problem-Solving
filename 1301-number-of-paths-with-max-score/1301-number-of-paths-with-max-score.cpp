class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        long long MOD = 1e9 + 7;

        vector<vector<int>> max_score(n, vector<int>(n, -1));
        vector<vector<int>> path_count(n, vector<int>(n, 0));

        max_score[n - 1][n - 1] = 0;
        path_count[n - 1][n - 1] = 1;

        int dr[] = {1, 0, 1};
        int dc[] = {0, 1, 1};

        for (int r = n - 1; r >= 0; --r) {
            for (int c = n - 1; c >= 0; --c) {
                if ((r == n - 1 && c == n - 1) || board[r][c] == 'X') {
                    continue;
                }

                int best_score = -1;
                long long paths = 0;

                for (int i = 0; i < 3; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr < n && nc < n && max_score[nr][nc] != -1) {
                        if (max_score[nr][nc] > best_score) {
                            best_score = max_score[nr][nc];
                            paths = path_count[nr][nc];
                        } else if (max_score[nr][nc] == best_score) {
                            paths = (paths + path_count[nr][nc]) % MOD;
                        }
                    }
                }

                if (best_score != -1) {
                    int current_val = (board[r][c] == 'E') ? 0 : (board[r][c] - '0');
                    max_score[r][c] = best_score + current_val;
                    path_count[r][c] = paths;
                }
            }
        }

        if (max_score[0][0] == -1) {
            return {0, 0};
        }

        return {max_score[0][0], static_cast<int>(path_count[0][0])};
    }
};