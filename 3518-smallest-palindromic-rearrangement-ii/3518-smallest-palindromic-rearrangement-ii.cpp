class Solution {
    // Computes permutations of remaining characters: N! / (c1! * c2! * ... * cm!)
    // Caps the result at cap limit to prevent overflow.
    long long countPermutations(const vector<int>& counts, long long cap) {
        int total = 0;
        for (int c : counts) total += c;
        
        long long res = 1;
        int current_n = 0;

        for (int c : counts) {
            for (int j = 1; j <= c; ++j) {
                current_n++;
                res = res * current_n / j;
                if (res > cap) res = cap; // Cap to avoid integer overflow
            }
        }
        return res;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }

        string mid = "";
        vector<int> half_freq(26, 0);

        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 != 0) {
                mid += (char)('a' + i);
            }
            half_freq[i] = freq[i] / 2;
        }

        int half_len = 0;
        for (int c : half_freq) half_len += c;

        // Total total distinct half-string permutations
        long long total = countPermutations(half_freq, k + 1);
        if (k > total) {
            return ""; // Fewer than k distinct palindromes
        }

        string first_half = "";

        // Construct the first half greedily character by character
        for (int pos = 0; pos < half_len; ++pos) {
            for (int c = 0; c < 26; ++c) {
                if (half_freq[c] > 0) {
                    // Try placing character c
                    half_freq[c]--;
                    
                    long long ways = countPermutations(half_freq, k + 1);

                    if (k <= ways) {
                        first_half += (char)('a' + c);
                        break; // Character accepted, move to next position
                    } else {
                        k -= ways;
                        half_freq[c]++; // Undo choice and try next character
                    }
                }
            }
        }

        // Mirror first half to form full palindrome
        string second_half = first_half;
        reverse(second_half.begin(), second_half.end());

        return first_half + mid + second_half;
    }
};