//
// Created by XBB-PC on 2020/7/4.
//

#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * 136. 只出现一次的数字
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 * 你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
 *
 * 任何数和 0 做异或运算，结果仍然是原来的数，即 a⊕0=a
 * 任何数和其自身做异或运算，结果是 0，即 a⊕a=0
 * 异或运算满足交换律和结合律，即 a⊕b⊕a=b⊕a⊕a=b⊕(a⊕a)=b⊕0=b
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (auto n : nums)
            ret ^= n;
        return ret;
    }
};


/**
 * 剑指 Offer 56 - I. 数组中数字出现的次数
 * 一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
 *
 * 如果求出现一次，可以对所有值求异或，结果就是目标值
 * 两个出现一次的数，可以将所有值分为两部分，这两个数分别在其中一部分中，然后分别对这两部分求异或
 */
class Solution2 {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int val = 0;
        for (auto n : nums)
            val = val ^ n;

        int det = 1;
        while (!(det&val)) det <<= 1; // 异或值为1的位置必然是两个只出现一次的值不同的位置

        int v1 = 0, v2 = 0;
        for (auto n : nums) {
            if (n&det) v1 = v1 ^ n; // 分别求异或
            else v2 = v2 ^ n;
        }
        return {v1, v2};
    }
};


/**
 * 剑指 Offer 56 - II. 数组中数字出现的次数 II
 * 在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。
 *
 * 位运算+有限自动机
 */
class Solution3 {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0; // 从00状态开始
        for (auto n : nums) {
            ones = ones ^ n & ~twos;
            twos = twos ^ n & ~ones;
        }
        return ones; // 只有出现一次的，才是01，其他one都是0
    }
};


/**
 * 剑指 Offer 64. 求1+2+…+n
 * 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
 * 利用短路效应
 */
class Solution4 {
public:
    int res = 0;
    int sumNums(int n) {
        n>1 && sumNums(n-1) > 0; // 短路效应，当n>1不满足时，后续不会执行
        res+=n;
        return res;
    }
};


/**
 * 剑指 Offer 65. 不用加减乘除做加法
 * 写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。
 * 由于C++数值用的是补码，所以正负值可以统一加法来做
 * 将数据分为非进位和 以及进位， 分别处理
 */
class Solution5 {
public:
    int add(int a, int b) {
        while (b!=0) {
            int c = (unsigned int)(a&b)<<1;
            a ^= b;
            b = c;
        }
        return a;
    }
};