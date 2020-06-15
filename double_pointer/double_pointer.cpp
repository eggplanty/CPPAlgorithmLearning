//
// Created by sen on 2020/5/27.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 392. 判断子序列
 * 后续挑战
 * 如果有大量输入的 S，称作S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
 * 思路可以是使用一个数组存储下一个(a-z)字符的位置，从而使得字串搜索是跳跃的而不是遍历原字符串
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        t = " " + t; // 开头加入空字符，处理第一个字符只出现一次时直接是-1的情况
        vector<vector<int>> vv(t.size(), vector<int>(26, -1)); // 跳跃表
        vector<int> tmp(26, -1); // 记录各个字符的下一个位置
        for (int i = t.size()-1; i >= 0; i--) {
            vv[i] = vector<int>(tmp.begin(), tmp.end()); // 一次遍历，同时赋值
            if (t[i] != ' ') tmp[t[i] - 'a'] = i; // 处理空字符，防止越界
        }

        int pos = 0;
        for (auto &c : s) { // 跳跃查找
            pos = vv[pos][c - 'a'];
            if (pos < 0)
                return false;
        }
        return true;
    }
};

/**
 * 923. 三数之和的多种可能
 * 给定一个整数数组 A，以及一个整数 target 作为目标值，返回满足 i < j < k 且 A[i] + A[j] + A[k] == target 的元组 i, j, k 的数量。
 * 由于结果会非常大，请返回 结果除以 10^9 + 7 的余数。
 *
 */

class Solution2 {
public:
    const long M = 1e9+7;
    int threeSumMulti(vector<int>& A, int target) {
        sort(A.begin(), A.end());

        int i = 0, j = 0, k = 0, cnt = 0;

        for (; i < A.size()-1; i++) {
            j = i+1, k = A.size()-1;
            int tar = target - A[i];
            while (j < k) {
                int tmp = A[j] + A[k];
                if (tmp == tar) {
                    if (A[j] == A[k]) {
                        cnt += (1+k-j) * (k-j) / 2;
                        cnt %= M;
                        break;
                    }
                    else {
                        int tj = j, tk = k;
                        while (A[tj] == A[++j]);

                        while (A[tk] == A[--k]);

                        cnt += (j-tj) * (tk-k);
                        cnt %= M;
                    }
                }
                else if (tmp > tar)
                    k--;
                else
                    j++;
            }
        }
        return cnt;
    }
};