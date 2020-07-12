//
// Created by sen on 2020/5/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 69. x 的平方根
 * 计算并返回 x 的平方根，其中 x 是非负整数
 * 由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
 */
class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1) return x;
        int l = 1, r = x;
        while (l <= r) { // l == r时继续执行
            int m = l + (r - l) / 2; // 防止越界
            int sqr = x / m; // 防止越界
            if (m == sqr)
                return m;
            if (m > sqr)
                r = m - 1;
            else
                l = m + 1;
        }
        return r; // 由于r=m-1，在lr相等时再执行一次可以得到小于等于的整数，相反取l可以得到大于等于的整数
    }
};

/**
 * 744. 寻找比目标字母大的最小字母
 * 给你一个排序后的字符列表 letters ，列表中只包含小写英文字母。另给出一个目标字母 target，请你寻找在这一有序列表里比目标字母大的最小字母。
 * 如果不存在，则返回第一个字符。
 *
 */
class Solution2 {
public:
    char nextGreatestLetter(vector<char> &letters, char target) {
        int l = 0, r = letters.size(); // 初始r设为size()时，如果不存在，则l=size()
        char ans = letters[0];
        while (l < r) {
            int m = l + (r - l) / 2;
            if (letters[m] > target)
                r = m;
            else // <= 时，while循环的条件不能有=
                l = m + 1;
        }
        return l == letters.size() ? letters[0] : letters[l];
    }
};

/**
 * 540. 有序数组中的单一元素
 * 给定一个只包含整数的有序数组，每个元素都会出现两次，唯有一个数只会出现一次，找出这个数。
 */
class Solution3 {
public:
    int singleNonDuplicate(vector<int> &nums) {
        int i = 0, j = nums.size() - 1; // 这里必须时size()-1，否则会越界
        while (i < j) {
            int m = i + (j - i) / 2;
            m = m % 2 == 1 ? m - 1 : m; // 统一成双数处理
            if (nums[m] == nums[m + 1]) // 判断前后两个值是否相同
                i = m + 2;
            else
                j = m;
        }
        return nums[i];
    }
};


/**
 * 278. 第一个错误的版本
 * 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
 */
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
class Solution4 {
public:
    bool isBadVersion(int a) {
        return a > 0;
    }

    int firstBadVersion(int n) {
        int i = 0, j = n;
        while (i < j) { // 由于j=m，这里就不能再取=了，否则会死循环
            int m = i + (j - i) / 2;
            if (isBadVersion(m))
                j = m; // 错误的版本有可能是第一个
            else
                i = m + 1;
        }
        return i;
    }
};


/**
 * 153. 寻找旋转排序数组中的最小值
 * 假设按照升序排序的数组在预先未知的某个点上进行了旋转。( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
 * 请找出其中最小的元素。你可以假设数组中不存在重复元素。
 */
class Solution5 {
public:
    int findMin(vector<int> &nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            int m = i + (j - i) / 2;
            if (nums[m] > nums[j]) // 与右边的值做比较来判断在旋转点前后
                i = m + 1;
            else
                j = m;
        }
        return nums[i];
    }
};


/**
 * 34. 在排序数组中查找元素的第一个和最后一个位置
 * 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置
 * 如果数组中不存在目标值，返回 [-1, -1]
 */
class Solution6 {
public:

    int getPos(vector<int> &nums, int target) {
        int i = 0, j = nums.size(); // 在超出最大值时会得到nums.size()
        while (i < j) {
            int m = i + (j - i) / 2;
            if (nums[m] < target)
                i = m + 1; // 若target=6, [4,5,7]，会定位到7的位置
            else
                j = m;
        }
        return i; // 返回目标值对应的位置，若没有，则返回它应存在的下一个位置
    }

    vector<int> searchRange(vector<int> &nums, int target) {
        int st = getPos(nums, target);
        int ed = getPos(nums, target + 1) - 1;
        if (st == nums.size() || nums[st] != target)
            return {-1, -1};
        return {st, ed};
    }
};


/**
 * 剑指 Offer 11. 旋转数组的最小数字
 * 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  
 */
class Solution7 {
public:
    int minArray(vector<int> &numbers) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            int m = i + (j - i) / 2;
            if (numbers[m] > numbers[j]) i = m + 1;
            else if (numbers[m] < numbers[j]) j = m; // 小于时该位置也可能时最小值
            else j -= 1; // 不能是i+=1，那样会错过1,3,3的1，也就是有序序列的最小值
        }
        return numbers[i];
    }
};


/**
 * 剑指 Offer 16. 数值的整数次方
 * 实现函数double Power(double base, int exponent)，求base的exponent次方。不得使用库函数，同时不需要考虑大数问题。
 */
class Solution8 {
public:
    double myPow(double x, int n) {
        if (x == 0) return 0; // 防止n<0时1/x出错
        long ln = n;
        if (ln < 0) x = 1/x, ln = -ln; // n有可能为INT32_MAX，取负数超出下界
        double res = 1.0;
        while (ln) {
            if (ln&1) res*=x; // 必然会走到n==1，将之间没乘的x一次乘完
            x*=x;
            ln/=2;
        }
        return res;
    }
};