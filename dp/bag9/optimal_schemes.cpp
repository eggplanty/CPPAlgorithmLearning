//
// Created by XBB-PC on 2020/7/1.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;
const int M = 1000000007;


/**
 * 01背包问题的最有方案数
 *
 * 思路是在f数组之外单独建立一个cnt数组，用来记录f中出现的最大价值的方案数
 *
 * f[i][j] = 前i个物品，容量不大于j的情况下的最大价值
 * cnt[j] = 容量不大于j的情况下的最大价值的方案数
 * cnt[j] = cnt[j-w]  if f[i][j-w]+v > f[i-1][j]  说明最大价值变大了，需要重新设定方案数
 *        = cnt[j] if f[i][j-w]+v < f[i-1][j]  说明最大价值不变，并且新物品不选，所以不影响最大价值方案数
 *        = cnt[j] + cnt[j-w] if i[i][j-w] + v == f[i-1][j] 最大价值一样，说明最大价值方案数需要求和
 */
class Solution {

    int f[N];
    int cnt[N];

    int main() {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < N; ++i) cnt[i] = 1; // 这个初始化意味着任意容量下达到最大价值的方案数至少为1

        for (int i = 1; i <= n; ++i) {
            int w, v;
            cin >> w >> v;

            for (int j = m; j >= w; --j) {
                int val = f[j - w] + v;
                if (val > f[j]) cnt[j] = cnt[j - w]; // 说明最大价值变大了，需要重新设定方案数
                else if (val < f[j]) cnt[j] = cnt[j]; // 说明最大价值不变，并且新物品不选，所以不影响最大价值方案数
                else cnt[j] = (cnt[j] + cnt[j - w]) % M; // 最大价值一样，说明最大价值方案数需要求和

                f[j] = max(val, f[j]);
            }
        }

        cout << cnt[m];
        return 0;
    }

};