//
// Created by XBB-PC on 2020/6/30.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 1033. 移动石子直到连续
 * 三个数，只可以将两边元素移动到中间
 * 求移动到连续的最多移动次数和最少移动次数
 */
class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        // 最大移动次数 = 空隙数
        // 最小移动次数 = n - 最大滑动窗口占用元素数

        vector<int> nums = {a, b, c};
        sort(nums.begin(), nums.end());

        int n = 3;
        int maxval = nums[n - 1] - nums[0] + 1 - n;

        int minval = 2; // 默认滑动窗口至少占用一个元素
        if (nums[2] - nums[0] + 1 == 3) // 已经连续
            minval = 0;
        else if (nums[1] - nums[0] <= 2 || nums[2] - nums[1] <= 2) // 滑动窗口占用两个，例如 1,2,4 或者1,3,6
            minval = 1;

        return {minval, maxval};
    }
};

/**
 * 1040. 移动石子直到连续 II
 * 一个不重复数列，每个位置的值可以变成其他不重复的非端点值，这被称作一次变换
 * 求使得数列连续的最小变换次数和最大变换次数
 *
 * 由于要求数列连续，可以认为变换过程其实就是插空
 * 直观理解最大变换次数就是空隙数，因为每次可以插一个空
 * 但是需要考虑两边的特殊情况，端点旁边的空隙不可选，因为会变成端点，例如4,7,9 则7，9中间的8不可选
 * 所以最大变换数就是 空隙数-两边较小的端点附近空隙数
 *
 * 由于最终变换结果为连续数列，所以可以理解为一个长度为n的滑动窗口
 * 要使得变换数尽可能的小，就是使得原始数列出现在滑动窗口中的元素数尽可能的多。
 * 考虑特殊情况1,2,3,4,7 这是7不能直接转换成5，所以这种情况最小转换不是1，而是2
 */
class Solution2 {
public:
    vector<int> numMovesStonesII(vector<int> &stones) {
        // 最大值 = sum(空隙) - min(边界空隙)
        // 最小值 = 滑动窗口最小值

        int n = stones.size();
        sort(stones.begin(), stones.end());

        int d = stones[n - 1] - stones[0] + 1 - n;
        int maxval = d - min(stones[1] - stones[0] - 1, stones[n - 1] - stones[n - 2] - 1);

        int j = 0, minval = INT32_MAX;
        for (int i = 2; i < n; ++i) {
            int left = stones[i] - n + 1; // 滑动窗口左边界值
            while (stones[j] < left) j++; // 向右移动直到进入滑动窗口区域

            // 如果滑动窗口内部为连续值，则由于剩下的一个点为端点，端点不能直接到端点，需要经过另一个端点的一次转换，所以是2
            if (i - j + 1 == n - 1 && stones[i] - stones[j] + 1 == n - 1)
                minval = min(minval, 2);
            else
                minval = min(minval, n - (i - j + 1)); // 记录最小空隙数
        }

        return {minval, maxval};
    }
};