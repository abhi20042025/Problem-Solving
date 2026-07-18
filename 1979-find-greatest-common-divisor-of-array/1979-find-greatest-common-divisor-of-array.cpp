class Solution {
public:
    int findGCD(std::vector<int>& nums) {
        int min_num = *std::min_element(nums.begin(), nums.end());
        int max_num = *std::max_element(nums.begin(), nums.end());
        
        int a = max_num;
        int b = min_num;
        while (b > 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        
        return a;
    }
};