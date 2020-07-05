//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 110;

/**
 * 多重背包问题和01背包问题的区别在于每个物品可以选择s次
 * f[i] = 体积为i的情况下的最大价值
 *
 */
class Solution {
    int f[N];
    int w[N];
    int v[N];
    int s[N];

    // 暴力解法，三重循环
    int solu() {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) cin >> w[i] >> v[i] >> s[i];

        for (int i = 1; i <= n; ++i)
            for (int j = m; j >= w[i]; j--) // 这里和01背包问题一样
                for (int k = 1; k <= s[i] && k * w[i] <= j; k++) // 这里加了一重循环用于处理多次选择同一个物体的情况
                    f[j] = max(f[j], f[j - k * w[i]] + k * v[i]);

        cout << f[m];
        return 0;
    }
};


/**
 * 多重背包的二进制优化
 * 考虑将一个可以取N次的物品，转成N个物品，这样就将问题转化成了01背包问题
 * 将可以取N次的物品转成N个物品并没有降低时间复杂度，考虑如何转成小于N个物品，但是可以拼成取N次的所有可能性
 * 例如：
 * 7，所有可能包括 0,1,2,3,4,5,6,7
 * 可以转成 1，1，1，1，1，1，1
 * 也可以转成 1，2，4
 *
 * 所以 对于n
 * 最少需要 log(n) 取上界个数，但是考虑到可能超出我们希望的表示范围，所以需要对最后一个数单独处理
 * 例如
 * 10 可以转成 1，2，4，8
 * 但是1，2，4，8可以表示0-15，11-15已经超出10的需要表示范围了
 * 所以应该用1，2，4，3来表示
 */
const int NN = 2010;

class Solution2 {
    int f[N];

    struct Good {
        int w, v;
    };

    int main() {
        vector<Good> goods;
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            int w, v, s;
            cin >> w >> v >> s;
            for (int k = 1; k <= s; k *= 2) { // 寻找物品的二进制拆分组合
                s -= k;
                goods.push_back({w * k, v * k});
            }
            if (s > 0) goods.push_back({w * s, v * s}); // push_back可以用{}初始化，emplace_back不行
        }

        for (auto good : goods)
            for (int j = m; j >= good.w; j--) // 和01背包一样
                f[j] = max(f[j], f[j - good.w] + good.v);

        cout << f[m];
        return 0;
    }
};