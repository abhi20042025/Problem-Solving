class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        int n = nums.size();
        int ans = 0;

        unordered_set<int> s(nums.begin(), nums.end());

        for (auto& val : s) {
            if (s.contains(val - 1))
                continue; // Not the start of a sequence

            int num = val;
            int cur = 1;

            while (s.contains(num + 1)) {
                cur++;
                num++;
            }

            ans = max(ans, cur);
        }

        return ans;
    }
};
