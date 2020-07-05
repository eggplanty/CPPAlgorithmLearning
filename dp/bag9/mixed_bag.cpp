//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1010;

/**
 * 混合背包问题，将01背包，完全背包和多重背包混合起来
 * 将多重背包拆分成二进制优化的01背包问题，这样就只有01背包和完全背包了，分别处理
 */

class Solution {
    int f[N];

    struct Thing {
        int kind;
        int w, v;
    };

    vector<Thing> things;

    int solu() {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < n; ++i) {
            int w, v, s;
            cin >> w >> v >> s;
            if (s < 0) things.push_back({-1, w, v});
            else if (s == 0) things.push_back({0, w, v});
            else {
                for (int k = 1; k <= s; k *= 2) { // 二进制优化拆分多重背包
                    s -= k;
                    things.push_back({-1, w * k, v * k});
                }
                if (s > 0) things.push_back({-1, w * s, v * s});
            }
        }

        for (auto thing : things) {
            if (thing.kind < 0) // 01背包
                for (int j = m; j >= thing.w; j--)
                    f[j] = max(f[j], f[j - thing.w] + thing.v);
            else // 完全背包
                for (int j = thing.w; j <= m; j++)
                    f[j] = max(f[j], f[j - thing.w] + thing.v);
        }

        cout << f[m];
        return 0;
    }
};