class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0;
        int ones = 0;
        
        string ans = "";
        
        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;
            
            // If we have more than k ones, shrink from left
            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }
            
            // We have exactly k ones
            if (ones == k) {
                // Remove leading zeros
                while (left <= right && s[left] == '0')
                    left++;
                
                string curr = s.substr(left, right - left + 1);
                
                // Update answer
                if (ans.empty() ||
                    curr.size() < ans.size() ||
                    (curr.size() == ans.size() && curr < ans)) {
                    ans = curr;
                }
                
                // Move past the first 1 to find another window
                left++;
                ones--;
            }
        }
        
        return ans;
    }
};