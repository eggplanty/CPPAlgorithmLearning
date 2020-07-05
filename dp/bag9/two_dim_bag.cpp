//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

/**
 * 二维背包问题，对比01背包问题，处理容量之外，加了一个重量限制
 *
 * 相当于增加了一个维度，其他不变
 */
class Solution {
    int f[N][N]; // f[i][j] 表示 容量为i，重量为j的背包能承载的最大价值

    int main() {
        int n, m, t;
        cin >> n >> m >> t;
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            cin >> a >> b >> c;

            for (int j = m; j >= a; j--) // 一维是容量
                for (int k = t; k >= b; k--) // 二维是质量
                    f[j][k] = max(f[j][k], f[j - a][k - b] + c);
        }

        cout << f[m][t];
        return 0;
    }
};