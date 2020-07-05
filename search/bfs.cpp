//
// Created by sen on 2020/6/1.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

/**
 * 典型的BFS，套用模板
 *
 * 1091. 二进制矩阵中的最短路径
 * 在一个 N × N 的方形网格中，每个单元格有两种状态：空（0）或者阻塞（1）
 * 一条从左上角到右下角、长度为 k 的畅通路径，由满足下述条件的单元格 C_1, C_2, ..., C_k 组成:
 * 相邻单元格 C_i 和 C_{i+1} 在八个方向之一上连通（此时，C_i 和 C_{i+1} 不同且共享边或角）
 * C_1 位于 (0, 0)（即，值为 grid[0][0]）
 * C_k 位于 (N-1, N-1)（即，值为 grid[N-1][N-1]）
 * 如果 C_i 位于 (r, c)，则 grid[r][c] 为空（即，grid[r][c] == 0）
 * 返回这条从左上角到右下角的最短畅通路径的长度。如果不存在这样的路径，返回 -1
 */
class Solution {
public:

    vector<vector<int>> direction = {{0,1}, {0,-1}, {1,1}, {1,-1}, {-1,0}, {1,0}, {-1,-1}, {-1,1}};

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        deque<pair<int, int>> mm; // 可以使用queue来实现先进先出队列，更简单
        if (grid[0][0] <= 0)
            mm.emplace_back(make_pair(0,0));
        int cnt = 0;

        while (!mm.empty()) {

            int size = mm.size();
            cnt++;
            while (size-- > 0) {
                int x = mm.front().first, y = mm.front().second;
                mm.pop_front();
                if (grid[x][y] > 0)
                    continue;
                if (x == R-1 && y == C-1)
                    return cnt;

                grid[x][y] = 2;

                for (auto &dir : direction) {
                    pair<int, int> tmp = make_pair(x+dir[0], y+dir[1]);
                    if (tmp.first<0 || tmp.second<0 || tmp.first >= R || tmp.second >= C)
                        continue;

                    mm.push_back(tmp);
                }
            }
        }
        return -1;
    }
};


/**
 * 279. 完全平方数
 * 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少
 *
 * 套模板基本可以保证对，但有时候效率不是最高的
 */
class Solution2 {
public:

    vector<int> pp;

    void fun(int n) {
        int i = 1;
        while (i*i <= n)
            pp.emplace_back(i*i++);
    }

    int numSquares(int n) {
        fun(n);

        vector<int> mem(n+1, 0);
        deque<int> q = {n};
        int cnt = -1; // 0会单独跑一次
        while (!q.empty()) {
            int size = q.size();
            cnt++;
            while (size-- > 0) {
                int tmp = q.front();

                q.pop_front();
                if (mem[tmp] > 0)
                    continue;

                if (tmp == 0)
                    return cnt;

                mem[tmp] = 1;

                for (auto &p : pp) {
                    if (tmp - p >= 0)
                        q.emplace_back(tmp-p);
                }
            }
        }
        return cnt;
    }
};

