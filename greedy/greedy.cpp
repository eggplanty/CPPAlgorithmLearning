//
// Created by sen on 2020/5/26.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 455. 分发饼干
 */
class Solution {
public:
    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int cnt = 0, i = 0, j = 0;
        while (i < g.size() && j < s.size()) {
            if (s[j] >= g[i])
                i++, cnt++;
            j++;
        }
        return cnt;
    }
};

/**
 * 121. 买卖股票的最佳时机
 * 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 * 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
 * 注意：你不能在买入股票前卖出股票。
 */
class Solution2 {
public:
    int maxProfit(vector<int> &prices) {
        int mins = INT16_MAX, mm = 0;
        for (auto &p : prices) {
            mm = max(mm, p - mins);
            mins = min(mins, p);
        }
        return mm;
    }
};

/**
 * 605. 种花问题
 * 假设你有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花卉不能种植在相邻的地块上，它们会争夺水源，两者都会死去。
 * 给定一个花坛（表示为一个数组包含0和1，其中0表示没种植花，1表示种植了花），和一个数 n 。能否在不打破种植规则的情况下种入 n 朵花？能则返回True，不能则返回False。
 */
class Solution3 {
public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        int cnt = 0;
        for (int i = 0; i < flowerbed.size(); i++) {
            int l = (i - 1 >= 0) ? i - 1 : 0;
            int r = (i + 1 < flowerbed.size()) ? i + 1 : flowerbed.size() - 1;
            if (flowerbed[i] == 0 && flowerbed[l] == 0 && flowerbed[r] == 0)
                cnt++, flowerbed[i] = 1;
        }
        return cnt >= n;
    }
};

/**
 * 53. 最大子序和
 * 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 *
 */
class Solution4 {
public:
    int maxSubArray(vector<int> &nums) {
        int ss = nums[0], mm = nums[0]; // 使用[0]的值做初始化
        for (int i = 1; i < nums.size(); i++) {
            ss = ss > 0 ? ss + nums[i] : nums[i];
            mm = max(ss, mm);
        }
        return mm;
    }
};

/**
 * 763. 划分字母区间
 * 字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表。
 * 贪心法，每个字符的最后一次出现位置决定了字符串片段的长度，尽可能选择字符串片段的字符的最后一个位置靠前的情况。
 */
class Solution5 {
public:
    vector<int> partitionLabels(string S) {
        vector<int> v(26, -1), m(S.size(), -1);
        for (int i = 0; i < S.size(); i++)
            v[S[i] - 'a'] = i; // 记录每个字符最后出现的位置

        vector<int> ans;
        int cnt = 0, mpos = 0;
        for (int i = 0; i < S.size(); i++) {
            mpos = max(v[S[i] - 'a'], mpos);
            cnt++;
            if (mpos == i) { // 当字符片段最后字符不再增长时认为是一个最小片段
                ans.push_back(cnt);
                cnt = 0, mpos = 0;
            }
        }
        return ans;
    }
};


/**
 * 剑指 Offer 14- II. 剪绳子 II
 * 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 *
 * 这里不能用dp，不然取模结果不确定
 */
class Solution6 {
public:
    int M = 1e9 + 7;

    inline long fun(int x, int a, int m) { // 这里需要用long，不能用int，因为掉完函数之后还要取一次模
        long rem = 1; // 这里必须用long， 不然(rem%m)*x 可能会超
        while (a-- > 0)
            rem = ((rem % m) * x) % m;
        return rem;
    }

    int cuttingRope(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        if (n == 4) return 4;
        if (n == 5) return 6;

        int a = n / 3;
        int b = n % 3;
        if (b == 0)
            return fun(3, a, M);
        else if (b == 1)
            return fun(3, a - 1, M) * 4 % M; // 这里fun得到的是long，不然*4会可能会超
        else
            return fun(3, a, M) * 2 % M;
    }
};