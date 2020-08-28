//
// Created by XBB-PC on 2020/8/26.
//

/**
 * 5. 最长回文子串
 */
class Solution {
public:

    // 动态规划，类似区间dp，for循环对应的是区间长度
    string longestPalindrome(string s) {
        int n =s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        string ans;
        for (int l = 1; l <= n; ++ l) {
            for (int i = 0; i + l - 1 < n; ++i) {
                int j = i + l - 1;
                if (l == 1) dp[i][j] = true;
                else if (l == 2) dp[i][j] = s[i]==s[j];
                else
                    dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);

                if (dp[i][j] && l > ans.size())
                    ans = s.substr(i, l);
            }
        }
        return ans;
    }

    // 中心扩展
    string longestPalindrome(string s) {
        auto fun = [=] (string s, int i, int j) {
            while (i>=0 && j<s.size() && s[i] == s[j]) {
                --i;
                ++j;
            }
            return make_pair(i+1, j-1);
        };

        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto [left1, right1] = fun(s, i, i);
            auto [left2, right2] = fun(s, i, i+1);
            if (right1 - left1 > end - start) {
                start = left1;
                end = right1;
            }
            if (right2 - left2 > end-start) {
                start = left2;
                end = right2;
            }
        }
        return s.substr(start, end-start+1);
    }
};


/**
 * 309. 最佳买卖股票时机含冷冻期
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // dp[i][j][k] = 第i天，执行操作j(j=0(不操作),1(买入),2(卖出))后处于状态k(k=0(不持有)),1(持有))的最大利润
        // 不执行操作后不持有   dp[i][0][0] = max(dp[i-1][2][0], dp[i-1][0][0])
        // 不执行操作后持有   dp[i][0][1] = max(dp[i-1][1][1], dp[i-1][0][1])
        // 卖出后不持有     dp[i][2][0] = max(dp[i-1][0][1], dp[i-1][1][1]) + prices[i-1]
        // 买入后持有     dp[i][1][1] = dp[i-1][0][0] - prices[i-1]

        int n = prices.size();
        vector<vector<int>> dp(vector<vector<int>>(3, vector<int>(2, INT32_MIN)));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            int tmp00 = max(dp[2][0], dp[0][0]);
            int tmp01 = max(dp[1][1], dp[0][1]);
            int tmp20 = max(dp[0][1], dp[1][1]) + prices[i-1];
            int tmp11 = dp[0][0] - prices[i-1];
            dp[0][0] = tmp00, dp[0][1] = tmp01, dp[2][0] = tmp20, dp[1][1] = tmp11;
        }

        return max(dp[2][0], dp[0][0]);
    }
};