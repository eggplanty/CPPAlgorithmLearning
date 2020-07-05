//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * 有 N 件物品和一个容量是 V 的背包。每件物品只能使用一次。
 * 第 i 件物品的体积是 vi，价值是 wi。
 * 求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
 * 输出最大价值。
 *
 * 输入格式
 * 第一行两个整数，N，V，用空格隔开，分别表示物品数量和背包容积。
 * 接下来有 N 行，每行两个整数 vi,wi，用空格隔开，分别表示第 i 件物品的体积和价值。
 * 输出格式
 * 输出一个整数，表示最大价值。
 *
 * 数据范围
 * 0<N,V≤1000
 * 0<vi,wi≤1000
 * 输入样例
 * 4 5
 * 1 2
 * 2 4
 * 3 4
 * 4 5
 *
 * 输出样例：
 * 8
 */


/**
 * f[i][j] 为前i个元素，容量不超过j时的最大价值
 * 递归公式：
 * 当 j < w[i] 即当前容量不足以放入物品时，则不放入 f[i][j] = f[i-1][j]
 * 当容量足够放入当前物品时，考虑可以放入也可以不放入 f[i][j] = max(f[i-1][j], f[i-1][j-w[i]] + v[i])
 */
const int MAXN = 1024;

class Solution {
public:
    int f[MAXN][MAXN]; // 全局变量默认初始化为0
    int w[MAXN];
    int v[MAXN];

    int solution() {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            cin >> w[i] >> v[i];

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (j < w[i])
                    f[i][j] = f[i - 1][j];
                else
                    f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + v[i]);
            }
        cout << f[n][m];
        return 0;
    }
};


/**
 * 空间优化版本
 */
class Solution2 {
    int f[MAXN]; // 全局变量默认初始化为0
    int w[MAXN];
    int v[MAXN];

    int solution2() {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            cin >> w[i] >> v[i];

        for (int i = 1; i <= n; ++i) // 由于每次计算只与上次计算结果有关，所以可以将二维数组压缩撑一维数组
            for (int j = m; j >= w[i]; --j) // 由于需要计算f[i - 1][j - w[i]]，如果从前向后取j，则这个值会被f[i][j - w[i]]取代
                f[j] = max(f[j], f[j - w[i]] + v[i]);

        /*
         * 这里之所以可以直接取f[m]，而不是遍历取最大值，是因为初始化的时候把所有f都设为了0
         * 假设f[k]为最大值
         * 又因为f[m-k] = 0，这是初始化决定的
         * 那么所以存在从f[m-k] -> f[m]的转移方法，使得f[m] = f[k]
         *
         * 如果初始化时设为
         * f[0] = 0;
         *
         * f[other] = -inf;
         *
         * 那么只有f[k] 为最大值，即只有f[0] -> f[k]的转移时合法的
         * 其他的都是-inf
         */
        cout << f[m];
        return 0;
    }
};
