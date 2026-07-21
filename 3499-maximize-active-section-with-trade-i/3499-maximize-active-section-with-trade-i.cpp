#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxActiveSectionsAfterTrade(std::string s) {
        int initial_ones = 0;
        std::vector<int> zero_blocks;
        
        int n = s.length();
        int i = 0;
        
        while (i < n) {
            if (s[i] == '1') {
                initial_ones++;
                i++;
            } else {
                int count = 0;
                while (i < n && s[i] == '0') {
                    count++;
                    i++;
                }
                zero_blocks.push_back(count);
            }
        }
        
        if (zero_blocks.size() < 2) {
            return initial_ones;
        }
        
        int max_gain = 0;
        for (size_t j = 0; j < zero_blocks.size() - 1; ++j) {
            max_gain = std::max(max_gain, zero_blocks[j] + zero_blocks[j + 1]);
        }
        
        return initial_ones + max_gain;
    }
};