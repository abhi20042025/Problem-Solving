class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int, int>> sorted_nodes(n);
        for (int i = 0; i < n; ++i) {
            sorted_nodes[i] = {nums[i], i};
        }
        sort(sorted_nodes.begin(), sorted_nodes.end());

        vector<int> sorted_pos(n);
        for (int i = 0; i < n; ++i) {
            sorted_pos[sorted_nodes[i].second] = i;
        }

        
        int LOG = 18;
        vector<vector<int>> st(n, vector<int>(LOG));
        
        int r = 0;
        for (int i = 0; i < n; ++i) {
            r = max(r, i);
            while (r + 1 < n && sorted_nodes[r + 1].first - sorted_nodes[i].first <= maxDiff) {
                r++;
            }
            st[i][0] = r; 
        }

        
        for (int j = 1; j < LOG; ++j) {
            for (int i = 0; i < n; ++i) {
                st[i][j] = st[st[i][j - 1]][j - 1];
            }
        }

       
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int a = sorted_pos[q[0]];
            int b = sorted_pos[q[1]];
            
            if (a > b) swap(a, b); 
            if (a == b) {
                ans.push_back(0);
                continue;
            }

            int steps = 0;
            int curr = a;

           
            for (int j = LOG - 1; j >= 0; --j) {
                if (st[curr][j] < b) {
                    curr = st[curr][j];
                    steps += (1 << j);
                }
            }

            
            if (st[curr][0] >= b) {
                ans.push_back(steps + 1);
            } else {
                ans.push_back(-1); 
            }
        }

        return ans;
    }
};