//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

/**
 * 分组背包问题和01背包问题的区别在于 每个组只能选一个，多重背包问题是它的一个特例，多重背包可以理解为同一组中的不同k*w k*v的物品
 * 做法和01背包类似，加一重循环用来判断使用选择组中的哪个
 */
class Solution {
    int f[N], w[N], v[N];

    int main() {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            int s;
            cin >> s;
            for (int k = 1; k <= s; ++k) cin >> w[k] >> v[k];

            for (int j = m; j >= 1; --j) // 01背包问题，反向求解
                for (int k = 1; k <= s; k++) // 增加一重循环，选择组中的任意一个
                    if (j >= w[k]) // 物体体积不能小于j
                        f[j] = max(f[j], f[j - w[k]] + v[k]);
        }

        cout << f[m];
        return 0;
    }
};