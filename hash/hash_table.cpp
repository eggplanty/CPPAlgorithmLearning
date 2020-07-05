//
// Created by XBB-PC on 2020/6/23.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;


/**
 * 1. 两数之和
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 *
 * 排序之后用双指针或者二分查找，时间复杂度为O(NlogN)
 *
 * 用hashmap记录查找，时间复杂度为O(N)，空间复杂度为O(N)，时间还空间
 */
class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) { // 可以再一次循环中查找，由于每个符合目标值的时一组，两个元素，第一个会写入map，第二个会找到第一个
            if (m.count(target - nums[i]) > 0) return {i, m[target - nums[i]]};
            m[nums[i]] = i;
        }
        return {};
    }
};


/**
 * 217. 存在重复元素
 * 给定一个整数数组，判断是否存在重复元素。
 * 如果任意一值在数组中出现至少两次，函数返回 true 。如果数组中每个元素都不相同，则返回 false 。
 *
 * 用set判断重复
 */
class Solution2 {
public:
    bool containsDuplicate(vector<int> &nums) {
        set<int> m;
        for (auto n : nums) {
            if (m.count(n) > 0) return true;
            m.emplace(n);
        }
        return false;
    }
};


/**
 * 594. 最长和谐子序列
 * 和谐数组是指一个数组里元素的最大值和最小值之间的差别正好是1。
 * 现在，给定一个整数数组，你需要在所有可能的子序列中找到最长的和谐子序列的长度。
 *
 * 关键是最大值-最小值正好是1，且求的是子序列长度，子序列不一定要连续
 */
class Solution3 {
public:
    int findLHS(vector<int> &nums) {
        map<int, int> m;
        int ans = 0;
        for (auto n: nums) // 计算各个值的出现此处
            m[n]++;
        for (auto n: nums)
            ans = max(ans, m[n + 1] > 0 ? m[n + 1] + m[n] : 0); // 由于最大值和最小值差距正好是1，所以需要判断m[n+1]是否存在
        return ans;
    }
};


/**
 * 128. 最长连续序列
 * 给定一个未排序的整数数组，找出最长连续序列的长度。
 * 要求算法的时间复杂度为 O(n)。
 *
 */
class Solution4 {
public:
    int longestConsecutive(vector<int>& nums) {
        map<int, int> m;
        for (auto n: nums) // 遍历一遍确定哪些存在
            m[n] = 1;

        for (auto n: nums) // 第二次遍历确定各个值的子序列长度
            forward(m, n);

        int ans = 0;
        for (auto iter = m.begin(); iter != m.end(); iter++) // 遍历确定最长子序列
            ans = max(ans, iter->second);
        return ans;
    }

    int forward(map<int, int> &m, int n) {
        if (m[n] != 1) return m[n]; // 如果已经计算过则不重复计算
        m[n] = 1 + forward(m, n+1); // 修改各个值子序列长度，
        return m[n];
    }
};