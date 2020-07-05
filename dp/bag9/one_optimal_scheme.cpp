//
// Created by XBB-PC on 2020/7/1.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * 背包问题求具体方案
 * 和传统01背包的区别在于要输出一种最大价值的方案
 *
 * 思路是从第n个物品开始，反向推最大价值，则f[1][m]为最大价值
 * 如果第一个物品可以取
 * 那么f[1][m] = f[2][m-w[1]]+v[1] 意思是取到第一个物品的最大价值 = 从n到第2个物品的最大价值，容量为[m-w]时，加上v[1]即第一个物品的价值
 */
const int N = 1010;

class Solution {
    int f[N][N];
    int w[N], v[N];

    int main() {
        int n, m;

        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i];

        for (int i = n; i >= 1; --i) // 反向求，使得f[1][m]为最大价值，方便从第一个物品开始向后输出
            for (int j = 0; j <= m; ++j) {
                if (j < w[i])
                    f[i][j] = f[i + 1][j]; // 由于i是从大到小，所以上一个i是i+1
                else
                    f[i][j] = max(f[i + 1][j], f[i + 1][j - w[i]] + v[i]);
            }

        int vol = m;
        for (int i = 1; i <= n; ++i) {
            if (f[i][vol] == f[i + 1][vol - w[i]] + v[i] && vol >= w[i]) { // vol体积必需要大于第[i]个物品的体积，否则会越界
                cout << i << ' ';
                vol -= w[i];
            }
        }
        return 0;
    }
};