class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = *max_element(nums.begin(), nums.end());
        
        vector<long long> count(max_val + 1, 0);
        for (int num : nums) {
            count[num]++;
        }
        
      
        vector<long long> count_multiples(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            for (int j = i; j <= max_val; j += i) {
                count_multiples[i] += count[j];
            }
        }
        
       
        vector<long long> gcd_pairs(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            gcd_pairs[i] = (count_multiples[i] * (count_multiples[i] - 1)) / 2;
        }
        
        for (int i = max_val; i >= 1; --i) {
            for (int j = 2 * i; j <= max_val; j += i) {
                gcd_pairs[i] -= gcd_pairs[j];
            }
        }
        
        vector<long long> prefix_sums(max_val + 1, 0);
        for (int i = 1; i <= max_val; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + gcd_pairs[i];
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(prefix_sums.begin(), prefix_sums.end(), q);
            answer.push_back(distance(prefix_sums.begin(), it));
        }
        
        return answer;
    }
};