class Solution {
public:
    static const int MOD = 1e9 + 7;

    int gcd(int a, int b) {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    int subsequencePairCount(vector<int>& nums) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<vector<long long>> dp(mx + 1, vector<long long>(mx + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<long long>> ndp(mx + 1, vector<long long>(mx + 1, 0));

            for (int g1 = 0; g1 <= mx; g1++) {
                for (int g2 = 0; g2 <= mx; g2++) {

                    long long ways = dp[g1][g2];
                    if (ways == 0) continue;

                    // Ignore current number
                    ndp[g1][g2] = (ndp[g1][g2] + ways) % MOD;

                    // Put in first subsequence
                    int ng1 = (g1 == 0) ? x : gcd(g1, x);
                    ndp[ng1][g2] = (ndp[ng1][g2] + ways) % MOD;

                    // Put in second subsequence
                    int ng2 = (g2 == 0) ? x : gcd(g2, x);
                    ndp[g1][ng2] = (ndp[g1][ng2] + ways) % MOD;
                }
            }

            dp = move(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= mx; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};