//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

/**
 * 和01背包的问题的区别在于每件物品可以用无限次
 *
 *
 * f[i] 表示体积为i的情况下，最大价值时f[i]
 * result = max{f[0...m]}
 *
 */

const int N = 1024;

class Solution {
    int f[N];
    int w[N];
    int v[N];

    int solu() {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];

        for (int i = 1; i <= n; ++i)
            for (int j = w[i]; j <= m; j++) // 和01背包不同，从w[i]开始，向后计算，这保证每个f[j]都计算了至少一次f[i]，而不是f[i-1]，随着j的增加，计算的f[i]的个数增加
                f[j] = max(f[j], f[j - w[i]] + v[i]);

        cout << f[m];
        return 0;
    }
};


/**
 * 377. 组合总和 Ⅳ
 * 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
 * 请注意，顺序不同的序列被视作不同的组合。
 *
 * 显然这是一个完全背包问题
 * 但是区别与一般的完全背包问题，这里需要考虑顺序
 *
 * 所以需要把物品循环放到内层，容量循环放到外层
 */
class Solution24 {
public:
    int combinationSum4(vector<int> &nums, int target) {
        // dp[i][j] = 前i个元素，和为j的组合的个数
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]

        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        sort(nums.begin(), nums.end());
        for (int j = 1; j <= target; ++j) // 容量循环放外层
            for (int i = 0; i < nums.size() && j >= nums[i]; ++i) // 物品循环放内层
                // dp[j] = dp[j] + dp[j-nums[i]];
                dp[j] = (dp[j] >= INT32_MAX - dp[j - nums[i]]) ? INT32_MAX : dp[j] + dp[j - nums[i]]; // 限制超出C++ INT上限

        return dp[target];
    }
};