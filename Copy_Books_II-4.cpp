/*
Copy Books II

Given n books( the page number of each book is the same) and an array of integer with size k means k people to copy the book and the i th integer is the time i th person to copy one book). You must distribute the continuous id books to one people to copy. (You can give book A[1],A[2] to one people, but you cannot give book A[1], A[3] to one people, because book A[1] and A[3] is not continuous.) Return the number of smallest minutes need to copy all the books.

Have you met this question in a real interview? Yes
Example
Given n = 4, array A = [3,2,4], .

Return 4( First person spends 3 minutes to copy book 1, Second person spends 4 minutes to copy book 2 and 3, Third person spends 4 minutes to copy book 4. )
*/

// Time:  O(nk)
// Space: O(n)

class Solution {
public:
    /**
     * @param n: an integer
     * @param times: a vector of integers
     * @return: an integer
     */
    int copyBooksII(int n, vector<int> &times) {
        // write your code here
        if(times.empty() || n < 1) return 0;
        sort(times.begin(), times.end());
        int k = times.size();
        k = min(k, n);
        vector<vector<int>> dp(2, vector<int>(n, INT_MAX));
        dp[1][0] = times[0] * 2;
        for(int j = 0; j < n; j++) {
            dp[0][j] = times[0] * (j + 1);
        }

        for(int i = 1; i < k; i++) {
            int left = 0;
            int right = 1;
            while(right < n) {
                int cur = max(dp[(i - 1) % 2][left], times[i] * (right - left));
                dp[i % 2][right] = min(dp[i % 2][right], cur);
                if(left < right && dp[(i - 1) % 2][left] < times[i] * (right - left)) {
                    left++;
                } else {
                    right++;
                    if(left > 0) {
                        left--;
                    }
                }
            }
        }
        
        return dp[(k - 1) % 2][n - 1];
    }
};
