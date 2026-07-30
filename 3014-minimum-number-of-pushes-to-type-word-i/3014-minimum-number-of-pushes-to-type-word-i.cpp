class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int totalPushes = 0;
        
        for (int i = 0; i < n; ++i) {
            totalPushes += (i / 8) + 1;
        }
        
        return totalPushes;
    }
};