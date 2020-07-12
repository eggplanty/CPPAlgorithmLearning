//
// Created by XBB-PC on 2020/6/28.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <queue>
#include <vector>
#include <set>
#include <math.h>

using namespace std;


/**
 * 918. 环形子数组的最大和
 * 给定一个由整数数组 A 表示的环形数组 C，求 C 的非空子数组的最大可能和。
 * 在此处，环形数组意味着数组的末端将会与开头相连呈环状。（形式上，当0 <= i < A.length 时 C[i] = A[i]，而当 i >= 0 时 C[i+A.length] = C[i]）
 * 此外，子数组最多只能包含固定缓冲区 A 中的每个元素一次。（形式上，对于子数组 C[i], C[i+1], ..., C[j]，不存在 i <= k1, k2 <= j 其中 k1 % A.length = k2 % A.length)
 *
 * kadane算法，用于求数组中的最大或最小子序列
 * dp[j] 为以 A[j] 结尾的最大子段和
 * 递推公式为 dp[j+1]=A[j+1]+max(dp[j],0)
 */
class Solution {
public:
    int maxSubarraySumCircular(vector<int> &A) {
        if (A.size() == 1) return A[0];

        int sum = 0;
        for (int i = 0; i < A.size(); ++i)
            sum += A[i];

        // 求不算双边循环的情况下的最大值
        int ans1 = INT32_MIN;
        int cur1 = 0;
        for (int i = 0; i < A.size(); i++) {
            cur1 = A[i] + max(cur1, 0);
            ans1 = max(cur1, ans1);
        }

        // 考虑双边循环，求内部最小子序列的和，由于最小子序列不能为全序列，所以执行两次，分别不考虑第一个元素和最后一个元素
        int ans2 = INT32_MAX;
        int cur2 = 0;
        for (int i = 0; i < A.size() - 1; i++) {
            cur2 = A[i] + min(cur2, 0);
            ans2 = min(cur2, ans2);
        }

        int ans3 = INT32_MAX;
        int cur3 = 0;
        for (int i = 1; i < A.size(); i++) {
            cur3 = A[i] + min(cur3, 0);
            ans3 = min(cur3, ans3);
        }

        return max(ans1, max(sum - ans2, sum - ans3));
    }
};


/**
 * 198. 打家劫舍
 *
 * 典型的爬楼梯题
 * 动态规划+滚动数组
 *
 * dp[i] 表示 偷到第i个房子能获得的最大金额
 * dp[i] = max(dp[i-1], dp[i-2] + v[i]) 由于不能相邻，所以dp[i]有两种可能，偷到第i-1个房子的最大金额或者偷到第[i-2]个房子的最大金额+第[i]个房子的金额
 */
class Solution2 {
public:

    int rob(vector<int> &nums) {
        int pre = 0, cur = 0; // 由于每次计算只涉及到dp[i-1]和dp[i-2]，所以可以用两个常量存储
        for (int i = 0; i < nums.size(); i++) {
            int tmp = max(cur, pre + nums[i]); // 交换数据
            pre = cur;
            cur = tmp;
        }

        return cur;
    }
};


/**
 * 213. 打家劫舍 II
 * 区别与上题，数组循环，最后一个值被认为和第一个值相邻
 * 分别处理从第0个元素开始和从第1个元素开始的结果，取大的值即可
 */
class Solution3 {
public:
    int rob(vector<int> &nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int pre1 = 0, cur1 = 0;
        int pre2 = 0, cur2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i != nums.size() - 1) { // 从第0个开始，不经过最后一个元素
                int tmp = max(cur1, pre1 + nums[i]);
                pre1 = cur1;
                cur1 = tmp;
            }
            if (i != 0) { // 从第1个开始，经过最后一个元素
                int tmp = max(cur2, pre2 + nums[i]);
                pre2 = cur2;
                cur2 = tmp;
            }
        }

        return max(cur1, cur2); // 两种情况取最大值
    }
};


/**
 * 64. 最小路径和
 *
 * 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 *
 * dp[i][j] = 第i行第j列最小路径和
 * dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + A[i][j]
 * 需要单独考虑第一行和第一列
 *
 * 由递推公式可知，dp[i][j]仅与上次循环的dp[i-1][j]以及这次循环的上一个dp[i][j-1]有关，所以可以用一维数组做优化
 * dp[j] = 当前行第j列最小路径和
 * dp[j] = max(dp[j], dp[j-1]) + A[i][j]
 *
 */
class Solution4 {
public:
    int minPathSum(vector<vector<int>> &grid) {

        if (grid.size() == 0) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<int> dp(m, 0);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (j == 0) // 仅能向下走
                    dp[j] = dp[j] + grid[i][j];
                else if (i == 0) // 仅能向右走
                    dp[j] = dp[j - 1] + grid[i][j];
                else
                    dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }


        return dp[m - 1];
    }
};


/**
 * 62. 不同路径
 * 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
 * 问总共有多少条不同的路径？
 *
 * dp[i][j] = 到达第i行第j列的位置有多少不同路径
 * dp[i][j] = dp[i-1][j] + dp[i][j-1]
 *
 * 显然可以优化
 * dp[j] = 当前行第j列的位置有多少不同路径
 * dp[j] = dp[i][j] + dp[i][j-1]
 */
class Solution5 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1); // 显然第一行路径数都是1，所以可以直接初始化成1
        for (int i = 1; i < m; ++i) // 第一行路径数是1，所以可以跳过
            for (int j = 1; j < n; ++j) // 第一列路径数都是1，可以跳过，这样不用处理特殊情况
                dp[j] = dp[j] + dp[j - 1];

        return dp[n - 1];
    }
};


/**
 * 303. 区域和检索 - 数组不可变
 * 给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。
 *
 * 最直接的做法是暴力求解，每次for循环求和
 *
 * 显然可以缓存结果来求解
 * dp[i] = 第i个位置之前的所有元素之和
 * dp[i] = dp[i-1] + A[i-1]
 */
class Solution6 {
public:
    vector<int> arr;
    vector<int> dp;

    Solution6(vector<int> &nums) {
        arr = nums;
        dp = vector<int>(arr.size() + 1, 0); // 由于是第i个位置之前的所有元素和，所以需要增加一个位置
        for (int i = 1; i <= nums.size(); i++)
            dp[i] = dp[i - 1] + nums[i - 1];
    }

    int sumRange(int i, int j) {
        return dp[j + 1] - dp[i];
    }
};


/**
 * 413. 等差数列划分
 * 如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列。
 * 求一个数组的连续子数组中等差数列的个数
 *
 * 注意到这里是连续子数组，也就是说1,2,3,4,5不存在1,3,5这个子数组
 * 所以以第i个元素结尾的子数组中的等差数列个数就是以i-1结尾的等差数列数+1，即每个等差数列后面加1个数字，以及最后三个构成新的等差数列
 *
 * dp[i] = 以A[i]结尾的等差数列数
 * dp[i] = dp[i-1] + 1
 *
 * 显然可以优化，用一个变量替代dp
 */
class Solution7 {
public:
    int numberOfArithmeticSlices(vector<int> &A) {
        // dp[i] = 以A[i]结尾的子区间中等差数列的个数
        // if A[i]-A[i-1] == A[i-1]-A[i-2] dp[i] = dp[i-1]+1
        // else dp[i] = 0

        vector<int> dp(A.size(), 0);
        int tmp = 0, res = 0;
        for (int i = 2; i < A.size(); i++)
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                tmp = tmp + 1;
                res += tmp;
            } else
                tmp = 0;

        return res;
    }
};


/**
 * 915. 分割数组
 * 给定一个数组 A，将其划分为两个不相交（没有公共元素）的连续子数组 left 和 right， 使得：
 *  left 中的每个元素都小于或等于 right 中的每个元素。
 *  left 和 right 都是非空的。
 *  left 要尽可能小。
 * 在完成这样的分组后返回 left 的长度。可以保证存在这样的划分方法。
 *
 * 第一种最直观的想法是双重循环，循环每个分割点，判断左边的最大值是否小于右边的最小值
 * 时间复杂度O(N^2)，在A.length<=30000这个量级上肯定会超时
 *
 * 第二种想法是记录两个数组，
 * 数组A：A[i] = 第i个位置及其左边元素的最大值
 * 数组B：B[j] = 第j个位置右边元素的最小值
 * 最后只需要遍历一遍AB，找到第一个A[k]-B[k] <= 0的坐标即可
 * 时间复杂度是O(3N)，空间复杂度是O(2N)
 *
 * 第三种想法是只需要保证右边的值一定大于左边的值，所以只需要在一次遍历的时候找到恒小于右值的pos即可
 * pos用来记录左值区间的右边界
 * left_max用来记录左值区间的最大值
 * cur_max用来记录当前的最大值
 * 当当前值A[i] < 左值区间最大值left_max时，意味着左值区间需要增大
 */
class Solution8 {
public:
    int partitionDisjoint(vector<int> &A) {
        int pos = 0, left_max = A[0], cur_max = A[0];
        for (int i = 0; i < A.size(); ++i) {
            cur_max = max(cur_max, A[i]);
            if (A[i] < left_max) {
                pos = i;
                left_max = cur_max;
            }
        }
        return pos + 1;
    }
};


/**
 * 343. 整数拆分
 * 给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。
 *
 * 第一种方法是找规律，很容易发现，应尽可能的拆分出3，才能使得乘积最大，但是4应该被拆成2*2而不是3*1
 *
 * 第二种方法是dp
 * dp[i] = 整数i至少拆成两个数的最大乘积
 * dp[i]有两种可能，一种是分成两个数，j*(i-j)，但是i-j不一定是最大的，i-j还可能被拆成2个及以上的值，其中最大的是dp[i-j]，所以需要取最大值
 * dp[i] = max(j*(i-j), j*dp[i-j])   j = 1,2 ... i-2
 */
class Solution9 {
public:
    int integerBreak(int n) {
        // dp[i] = 整数i至少拆成两个数的最大乘积
        // dp[i] = max(j*(i-j), j*dp[i-j])   j = 1,2 ... i-2
        vector<int> dp(n + 1, 1);
        for (int i = 3; i <= n; ++i)
            for (int j = 1; j <= i - 2; ++j)
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
        return dp[n];
    }
};


/**
 * 279. 完全平方数
 * 给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
 *
 * dp的思路比较简单
 * dp[i] = 组成整数i的最小完全平方数个数
 * 显然，i可以拆成一个完全平方数k和i-k
 * 所以 dp[i] = min{dp[i-k] + 1}   k = 1,4,9 ...
 * 每次遍历完全平方数即可求解各个i，最后求最小值即可
 */
class Solution10 {
public:
    int numSquares(int n) {
        // dp[i] = 组成整数i的最小完全平方数个数
        // dp[i] = min{dp[i-k] + 1}   k = 1,4,9 ...

        vector<int> dp(n + 1, INT32_MAX);
        dp[0] = 0;
        vector<int> d;
        for (int i = 1; i * i <= n; ++i)
            d.push_back(i * i);

        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < d.size() && i >= d[j]; ++j)
                dp[i] = min(dp[i], dp[i - d[j]] + 1);

        return dp[n];
    }
};


/**
 * 91. 解码方法
 * 一条包含字母 A-Z 的消息通过以下方式进行了编码：
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * 给定一个只包含数字的非空字符串，请计算解码方法的总数。
 *
 * 这道题麻烦的不是dp，而是如何处理‘0’
 * 显然
 * dp[i] = 以第[i]个元素结尾的字符串包含的解码方法总数
 * dp[i] = dp[i-1] + dp[i-2]
 * 这里需要考虑几种情况
 * 1. A[i] = '0'，此时不能加上dp[i-1]，因为'0'没有单独编码
 * 2. A[i-1,i] = '09' '27'，此时不能加上dp[i-2]因为，'09', '27'不能构成编码
 * 3. 初始化的时候需要考虑 A[0] = '0' , A[0, 1] = '00' '01' 等情况
 */
class Solution11 {
public:
    int numDecodings(string s) {
        // dp[i] = 以第[i]个元素结尾的字符串包含的解码方法总数
        // dp[i] = (s[i] != '0' ? dp[i-1] : 0) + (s[i-1,i] <= 26 ? dp[i-2] : 0)

        int pre1 = 0, pre2 = 0; // 令pre2 = 0 可以处理 A[0, 1] = '00' 的情况
        pre1 = s[0] != '0' ? 1 : 0; // A[0] = '0]
        for (int i = 1; i < s.size(); ++i) {
            int tmp1 = 0, tmp2 = 0;
            int t = stoi(s.substr(i - 1, 2));
            if (s[i] != '0') tmp1 = pre1;
            if (t >= 10 && t <= 26) tmp2 = i >= 2 ? pre2 : 1;

            pre2 = pre1;
            pre1 = tmp1 + tmp2;
        }
        return pre1;
    }
};


/**
 * 300. 最长上升子序列
 * 给定一个无序的整数数组，找到其中最长上升子序列的长度。
 *
 * dp思路比较简单
 * dp[i] = 以第i个元素结尾的最长上升子序列的长度
 * dp[i] = max{dp[j]+1}  j = 0,1,2,...,i-1  if A[i] > A[j]
 *
 * TODO：这道题还有O(nlogn)的贪心+二分优化解法
 */
class Solution12 {
public:
    int lengthOfLIS(vector<int> &nums) {
        // dp[i] = 以第i个元素结尾的最长上升子序列的长度
        // dp[i] = max{dp[j]+1}  j = 0,1,2,...,i-1  if A[i] > A[j]

        int n = nums.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < nums.size(); ++i)
            for (int j = 0; j < i; ++j)
                if (nums[i] > nums[j]) // 内层循环遍历的时候要考虑递增关系，否则无法构成以第i个元素结尾的上升子序列
                    dp[i] = max(dp[i], dp[j] + 1);

        int res = 0;
        for (int i = 0; i < dp.size(); i++) res = max(res, dp[i]);
        return res;
    }
};


/**
 * 646. 最长数对链
 * 给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。
 * 现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。
 * 给定一个对数集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
 *
 * 直观的方法是使用dp
 * dp[i] = 以第i个数对结尾的最长链的长度
 * dp[i] = max{dp[j] + 1}  j = 0,...,i-1  if (A[j][1] < A[i][0])
 * 这里还是需要对A排序
 *
 * 优化的做法是将问题转化为求最大不相交子区间个数问题
 * 使用贪心法求解
 */
class Solution13 {
public:
    int findLongestChain(vector<vector<int>> &pairs) {
        // dp[i] = 以第i个数对结尾的最长链的长度
        // dp[i] = max{dp[j] + 1}  j = 0,...,i-1  if (A[j][1] < A[i][0])

        sort(pairs.begin(), pairs.end());

        vector<int> dp(pairs.size(), 1);
        for (int i = 0; i < pairs.size(); ++i)
            for (int j = 0; j < i; ++j)
                if (pairs[j][1] < pairs[i][0])
                    dp[i] = max(dp[i], dp[j] + 1);

        int res = 0;
        for (auto a : dp) res = max(res, a);
        return res;
    }

    // 将问题转化为求最大不相交子区间个数问题
    int findLongestChain2(vector<vector<int>> &pairs) {
        // 找最大不相交数对的个数

        sort(pairs.begin(), pairs.end(), [](vector<int> a, vector<int> b) { return a[1] < b[1]; });
        int cnt = 1, last = pairs[0][1];
        for (int i = 1; i < pairs.size(); ++i)
            if (pairs[i][0] > last) {
                cnt++;
                last = pairs[i][1];
            }

        return cnt;
    }
};


/**
 * 376. 摆动序列
 * 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。
 */
class Solution14 {
public:
    /**
     * 直观想法是dp来计算
     * dp[i] = 以第i个元素为结尾的最长摆动子序列长度
     * dp[i] = max{dp[j] + 1} j = 0,1,...,i-1   if A[j] > A[i] || A[j] < A[i]
     * 这里求解dp[i]的时候，由于最后两位上升时需要考虑的是下降的子序列的长度+1，最后两位下降时需要考虑的是上升的子序列长度+1
     * 所以需要分开考虑，用两个dp数组记录
     */
    int wiggleMaxLength(vector<int> &nums) {
        // dp[i] = 以第i个元素为结尾的最长摆动子序列长度
        // dp[i] = max{dp[j] + 1} j = 0,1,...,i-1   if A[j] > A[i] || A[j] < A[i]

        int n = nums.size();
        vector<int> dp1(n, 1); // 最后两位是上升
        vector<int> dp2(n, 1); // 最后两位是下降

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j) { // 这个for循环其实每次都会找到dp1或者dp2的一个合理的最大值来更新，但实际上有一些是不需要的
                if (nums[i] < nums[j])
                    dp2[i] = max(dp2[i], dp1[j] + 1);
                if (nums[i] > nums[j])
                    dp1[i] = max(dp1[i], dp2[j] + 1);
            }

        int res = 0;
        for (int i = 0; i < n; ++i) res = max(res, max(dp1[i], dp2[i]));
        return res;
    }

    /**
     * 这里由于
     * up[i] = max{down[j] + 1} if A[i] > A[j]
     * down[i] = max{up[j] + 1} if A[i] < A[j]
     * 显然，有意义的up和down应该是递增的，但实际上由于每次都会遍历找一个合理的最大值，
     * 所以up和down会存在一些非递增的数据，这些对于最后求最大摆动子序列长度是没用的
     *
     * 所以可以修改up 和 down的定义
     * up[i] = 第[i]个位置元素及之前的所有的元素的子序列中，最大摆动子序列长度，末尾上升，在增长子序列的时候，一定是以第i个元素为末尾的
     * down[i] = 第[i]个位置元素及之前的所有的元素的子序列中，最大摆动子序列长度，末尾下降
     *
     */
    int wiggleMaxLength2(vector<int> &nums) {
        // dp[i] = 以第i个元素为结尾的最长摆动子序列长度
        // dp[i] = max{dp[j] + 1} j = 0,1,...,i-1   if A[j] > A[i] || A[j] < A[i]

        int n = nums.size();
        vector<int> up(n, 1); // 最后两位是上升
        vector<int> down(n, 1); // 最后两位是下降

        if (n == 0) return 0;
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) { // 如果最后两位是下降
                down[i] = up[i - 1] + 1; // 下降队列的第i个元素应该是上升队列的最大值+1
                up[i] = up[i - 1]; // 上升队列复制不变
            } else if (nums[i] > nums[i - 1]) {
                up[i] = down[i - 1] + 1;
                down[i] = down[i - 1];
            } else {
                up[i] = up[i - 1];
                down[i] = down[i - 1];
            }
        }

        return max(up[n - 1], down[n - 1]);
    }
};


/**
 * 1143. 最长公共子序列
 * 给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
 * 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
 *
 * dp[i][j] = text1的前i个元素和text2的前j个元素的最长公共子序列的长度
 * dp[i][j] = dp[i-1][j-1] + 1   if A[i] == B[j]
 *          = max(dp[i-1][j], dp[i][j-1])   if A[i] != B[j]
 *
 * 子序列dp，通常的定义方式有两种
 * 1. dp[i] = 以第i个元素为结尾的子序列的...
 * 2. dp[i] = 前i个元素的子序列中的...
 *
 * 第一种定义方式通常要多一重循环，用来遍历i以前的以第j个元素为结尾的子序列的dp值
 *
 * dp常见的一种处理是增加一个0行，例如定义dp[n+1]
 * 这样可以方便初始化处理
 */
class Solution15 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // dp[i][j] = text1的前i个元素和text2的前j个元素的最长公共子序列的长度
        // dp[i][j] = dp[i-1][j-1] + 1   if A[i] == B[j]
        //          = max(dp[i-1][j], dp[i][j-1])   if A[i] != B[j]

        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
            }

        return dp[n][m];
    }
};


/**
 * 416. 分割等和子集
 * 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 *  每个数组中的元素不会超过 100
 *  数组的大小不会超过 200
 *
 * 根据数组大小200可知最多支持O(N^3)时间复杂度
 *
 * 显然数组中的每个元素只能选一次，目标是选一些数，令他们的和等于sum/2
 *
 * 这可以看成是一个容量为sum/2的01背包问题
 * 这里不需要考虑价值，所以对比01背包问题可以将价值部分转成是否存在问题
 *
 * dp[i][j] = 前i个元素，是否存在和等于j的子序列
 * dp[i][j] = dp[i-1][j] || dp[i-1][j-A[i]]
 * 考虑两种情况
 * 1.不加入A[i] ，则此时dp[i][j] = dp[i-1][j]
 * 2.加入A[i]，此时如果存在j-A[i]的子序列，则也会存在j的子序列
 */
class Solution16 {
public:
    bool canPartition(vector<int> &nums) {
        // dp[i][j] = 前i个元素，是否存在和等于j的子序列
        // dp[i][j] = max(dp[i-1][j], dp[i-1][j-w] + v)
        // dp[i][j] = dp[i-1][j] || dp[i-1][j-A[i]]

        int n = nums.size(), sum = 0;
        for (auto nu : nums) sum += nu;
        if (sum & 1) return false;
        int m = sum / 2;

        vector<bool> dp(m + 1, false);
        dp[0] = true; // 可以理解为任意序列必然存在和为0的子序列
        for (int i = 1; i <= n; ++i)
            for (int j = m; j >= 1 && j >= nums[i - 1]; --j)
                dp[j] = dp[j] || dp[j - nums[i - 1]];

        return dp[m];
    }
};


/**
 * 494. 目标和
 * 给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
 * 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
 * 可以转化成01背包问题
 */
class Solution17 {
public:
    int findTargetSumWays(vector<int> &nums, int S) {
        // 容量为S的01背包问题
        //                  sum(P) - sum(N) = target
        // sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
        //               2 * sum(P) = target + sum(nums)
        // dp[i][j] = 前i个元素，目标值不超过j的方法数, j<= (target + sum(nums)) / 2
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-A[i]]

        int sum = 0;
        for (auto nu : nums) sum += nu;
        if (S > sum || (S + sum) % 2 == 1) return 0;

        int n = nums.size(), m = (S + sum) / 2;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // 下面这个初始化的意思是前i个元素，和<=0的方法数都是1，考虑数列为0，0，0，0，1的情况，前4个元素，和为0的方法显然是16，而不是1，只是由于下面的dp[i][j] = ... 所以恰好结果正确
//        for (int i = 0; i <= n; ++i)
//            dp[i][0] = 1;

        // 正确的初始化应该是下面这样的，意思是前0个元素，选取若干个元素，和恰好为0的方法数为1
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= m; ++j) { // 这里从0开始，因为nums中存在0，所以显然，0也是容量的一种
                if (j < nums[i - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
            }

        return dp[n][m];
    }
};

/**
 * 494. 目标和
 * 空间优化解法
 */
class Solution18 {
public:
    int findTargetSumWays(vector<int> &nums, int S) {
        // 容量为S的01背包问题
        //                  sum(P) - sum(N) = target
        // sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
        //               2 * sum(P) = target + sum(nums)
        // dp[i][j] = 前i个元素，目标值不超过j的方法数, j<= (target + sum(nums)) / 2
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-A[i]]

        int sum = 0;
        for (auto nu : nums) sum += nu;
        if (S > sum || (S + sum) % 2 == 1) return 0;

        int n = nums.size(), m = (S + sum) / 2;
        vector<int> dp(m + 1, 0);
        dp[0] = 1; // 这个初始化的意思是从前0个物品中选取若干物品放入背包，容量为恰为0时的方法数为1

        for (int i = 1; i <= n; ++i)
            for (int j = m; j >= nums[i - 1]; --j) {
                dp[j] = dp[j] + dp[j - nums[i - 1]];
            }

        return dp[m];
    }
};


/**
 * 474. 一和零
 * 在计算机界中，我们总是追求用有限的资源获取最大的收益。
 * 现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。
 * 你的任务是使用给定的 m 个 0 和 n 个 1 ，找到能拼出存在于数组中的字符串的最大数量。每个 0 和 1 至多被使用一次。
 *  给定 0 和 1 的数量都不会超过 100。
 *  给定字符串数组的长度不会超过 600。
 *
 * 典型二维背包问题
 */
class Solution19 {
public:

    vector<int> fun(string str) {
        int ones = 0, zeros = 0;
        for (auto c : str) {
            if (c == '0')
                zeros++;
            else
                ones++;
        }
        return {zeros, ones};
    }

    int findMaxForm(vector<string> &strs, int m, int n) {
        // dp[i][j][k] = 前i个字符串，0的个数不大于j，1的个数不大于k的最大数量
        // dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-A[i]][k-B[i]])

        vector<vector<vector<int>>> dp(strs.size() + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));

        for (int i = 1; i <= strs.size(); ++i) {
            vector<int> tmp = fun(strs[i - 1]);
            int zeros = tmp[0], ones = tmp[1];

            for (int j = 0; j <= m; ++j)
                for (int k = 0; k <= n; ++k) {
                    if (j < zeros || k < ones)
                        dp[i][j][k] = dp[i - 1][j][k];
                    else
                        dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - zeros][k - ones] + 1);
                }
        }
        return dp[strs.size()][m][n];
    }

    int findMaxForm2(vector<string> &strs, int m, int n) {
        // 空间优化

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= strs.size(); ++i) {
            vector<int> tmp = fun(strs[i - 1]);
            int zeros = tmp[0], ones = tmp[1];

            for (int j = m; j >= zeros; --j)
                for (int k = n; k >= ones; --k) {
                    dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
                }
        }
        return dp[m][n];
    }
};


/**
 * 322. 零钱兑换
 * 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
 * 每个硬币可以看成一个物品，面值可以看成物品体积，总金额可以看成背包容量
 * 则这个问题显然是一个背包问题，由于每个硬币可以选无限次，所以是个完全背包问题
 *
 * dp[i][j] = 前i个硬币，总金额为j，用到的最少硬币数
 * 递推公式为
 * dp[i][j] = min(dp[i-1][j], dp[i-1][j-w[i]] + 1)
 * 也就是说有两种情况，选其中的较小值
 * 1.不选第[i]个硬币，则当前硬币数等于dp[i-1][j]
 * 2.选第[i]个硬币，则当前硬币数等于dp[i-1][j-w[i]] + 1
 */
class Solution20 {
public:
    int coinChange(vector<int> &coins, int amount) {
        // dp[i][j] = 前i个硬币，总金额为j，用到的最少硬币数
        // dp[i][j] = min(dp[i-1][j], dp[i-1][j-w[i]] + 1)

        // 由于目标是求恰为amount的最小值，所以初始化要使用最大值，之所以要减1是防止下面dp[j-coins[i]] + 1超出int32范围
        vector<int> dp(amount + 1, INT32_MAX - 1);
        dp[0] = 0; // 这个初始化的意思是起点为前0个元素，总金额为0的最少硬币数为0，保证是从无硬币开始转移
        int n = coins.size();

        for (int i = 0; i < n; ++i)
            for (int j = coins[i]; j <= amount; ++j)
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);

        return dp[amount] == INT32_MAX - 1 ? -1 : dp[amount]; // 除了恰为amount的位置为一个合适值外，其他的都是转移路径上都是INT32_MAX - 1
    }
};


/**
 * 518. 零钱兑换 II
 * 给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
 * 还是完全背包
 * dp[i][j] = 前i个元素，总金额为j时的组合数
 * dp[i][j] = dp[i-1][j] + dp[i-1][j-coins[i]]
 * 有两种情况，前i个元素，总金额为j时的组合数应该时两者之和
 * 1.不选第[i]个元素，dp[i-1][j]
 * 2.选第[i]个元素，dp[i-1][j-coins[i]]
 */
class Solution21 {
public:
    int change(int amount, vector<int> &coins) {
        // dp[i][j] = 前i个元素，总金额为j时的组合数
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-coins[i]]

        int n = coins.size();
        // 递推公式相加的情况，初始化必不可能时INT32_MAX或者INT32_MIN，一般都是0
        vector<int> dp(amount + 1, 0);
        dp[0] = 1; // 由于递推公式中没有1，所以如果第0个值不为1的话所有的值都会是0，这里第[0]个位置为1，说明允许从第[0]个物品开始的这条递推链

        for (int i = 0; i < n; ++i)
            for (int j = coins[i]; j <= amount; ++j) // 标准完全背包
                dp[j] = dp[j] + dp[j - coins[i]];

        return dp[amount];
    }
};


/**
 * 887. 鸡蛋掉落
 * 你将获得 K 个鸡蛋，并可以使用一栋从 1 到 N  共有 N 层楼的建筑。
 * 每个蛋的功能都是一样的，如果一个蛋碎了，你就不能再把它掉下去。
 * 你知道存在楼层 F ，满足 0 <= F <= N 任何从高于 F 的楼层落下的鸡蛋都会碎，从 F 楼层或比它低的楼层落下的鸡蛋都不会破。
 * 每次移动，你可以取一个鸡蛋（如果你有完整的鸡蛋）并把它从任一楼层 X 扔下（满足 1 <= X <= N）。
 * 你的目标是确切地知道 F 的值是多少。
 * 无论 F 的初始值如何，你确定 F 的值的最小移动次数是多少？
 *
 * 不能简单地用二分来做，而应该从动态规划地角度思考
 * dp[i][j] = i个鸡蛋，j层楼的情况下，确定F的最小移动次数
 * dp[i][j] = 1 + min{max(dp[i][j-x], dp[i-1][x-1]), x=1,2,...,j}
 * 由于要考虑任意F，确定F的最小次数，所以对任意楼层x需要考虑F在楼层x上还是下两种情况，
 * 因此我们必须保证 鸡蛋碎了之后接下来需要的步数 和 鸡蛋没碎之后接下来需要的步数 二者的 最大值 最小
 */
class Solution22 {
public:
    int superEggDrop(int K, int N) {
        // dp[i][j] = i个鸡蛋，j层楼的情况下，确定F的最小移动次数
        // dp[i][j] = 1 + min{max(dp[i][j-x], dp[i-1][x-1]), x=1,2,...,j}

        vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= K; ++i) dp[i][1] = 1; // 初始化显然楼层为1时，只需要一次即可判定
        for (int i = 1; i <= N; ++i) dp[1][i] = i; // 显然只有一个鸡蛋时应该从第一层开始尝试，所以是N

        for (int i = 1; i <= K; ++i)
            for (int j = 1; j <= N; ++j) {
                if (i == 1 || j == 1) continue; // 使用初始化的值即可
                int tmp = INT32_MAX;

                int lo = 1, hi = j; // dp[i][j-x]为递减序列，dp[i-1][x-1]为x递增序列，所以可以用二分查找他们两者的最大值最小的位置
                while (lo + 1 < hi) {
                    int k = lo + (hi - lo) / 2;
                    int d1 = dp[i][j - k];
                    int d2 = dp[i - 1][k - 1];
                    if (d1 > d2) lo = k;
                    else if (d1 < d2) hi = k;
                    else lo = hi = k;
                }
                dp[i][j] = 1 + min(max(dp[i][j - lo], dp[i - 1][lo - 1]), max(dp[i][j - hi], dp[i - 1][hi - 1]));
            }
        return dp[K][N];
    }
};


/**
 * 139. 单词拆分
 * 给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
 *     拆分时可以重复使用字典中的单词。
 *     你可以假设字典中没有重复的单词。
 *
 * 典型dp
 * dp[i] = 前i个元素是否空格可拆分
 * dp[i] = dp[i] || (dp[j] && check(s.substr(j, i-j))), j=0,1,...i-1
 * 递推公式可以理解为，前i个元素，遍历每个位置，分成左右两部分，两部分都是在字典里的即为可拆分
 */
class Solution23 {
public:
    bool wordBreak(string s, vector<string> &wordDict) {
        // dp[i] = 前i个元素是否空格可拆分
        // dp[i] = dp[i] || (dp[j] && check(s.substr(j, i-j))), j=0,1,...i-1

        set<string> st(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true; // 初始化前0个元素一定是空格可拆分的
        for (int i = 1; i <= s.size(); ++i)
            for (int j = 0; j < i; ++j)
                // dp[i] = dp[i] || (dp[j] && (st.count(s.substr(j, i-j)) > 0));
                if (dp[j] && (st.count(s.substr(j, i - j)) > 0)) { // 或等于可以优化，提前跳出循环
                    dp[i] = true;
                    break;
                }

        return dp[s.size()];
    }
};


/**
 * 377. 组合总和 Ⅳ
 * 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
 * 请注意，顺序不同的序列被视作不同的组合。
 *
 * 显然这是一个完全背包问题
 * 但是区别与一般的完全背包问题，这里需要考虑顺序
 *
 * 所以需要把物品循环放到内层，容量循环放到外层
 */
class Solution24 {
public:
    int combinationSum4(vector<int> &nums, int target) {
        // dp[i][j] = 前i个元素，和为j的组合的个数
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]

        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        sort(nums.begin(), nums.end()); // 方便循环物品的时候通过j >= nums[i]来提前终止
        for (int j = 1; j <= target; ++j)
            for (int i = 0; i < nums.size() && j >= nums[i]; ++i)
                // dp[j] = dp[j] + dp[j-nums[i]];
                dp[j] = (dp[j] >= INT32_MAX - dp[j - nums[i]]) ? INT32_MAX : dp[j] + dp[j - nums[i]]; // 限制超出C++ INT上限

        return dp[target];
    }
};


/**
 * 309. 最佳买卖股票时机含冷冻期
 * 给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。​
 * 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
 *  你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *  卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
 *
 * 买入后可以立即卖出，卖出后不能立即买入
 * 所以除了要记录今天买卖股票后的状态(持有，不持有)之外，还要记录今天的操作(不操作，买入，卖出)，为明天判断是否在冷冻期提供支持
 *
 */
class Solution25 {
public:
    int maxProfit(vector<int> &prices) {
        // dp[i][j][k] = 第i天，执行操作j(j=0(不操作),1(买入),2(卖出))后处于状态k(k=0(不持有)),1(持有))的最大利润
        // 不执行操作后不持有   dp[i][0][0] = max(dp[i-1][2][0], dp[i-1][0][0])
        // 不执行操作后持有   dp[i][0][1] = max(dp[i-1][1][1], dp[i-1][0][1])
        // 卖出后不持有     dp[i][2][0] = max(dp[i-1][0][1], dp[i-1][1][1]) + prices[i-1] 买入后可以立刻卖出
        // 买入后持有     dp[i][1][1] = dp[i-1][0][0] - prices[i-1] 卖出后不能立刻买入

        int n = prices.size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(3, vector<int>(2, INT32_MIN))); // 由于求最大值，所以初始化为最小值
        dp[0][0][0] = 0; // 状态转移原点设为0

        for (int i = 1; i <= n; ++i) {
            dp[i][0][0] = max(dp[i - 1][2][0], dp[i - 1][0][0]);
            dp[i][0][1] = max(dp[i - 1][1][1], dp[i - 1][0][1]);
            dp[i][2][0] = max(dp[i - 1][0][1], dp[i - 1][1][1]) + prices[i - 1];
            dp[i][1][1] = dp[i - 1][0][0] - prices[i - 1];
        }

        return max(dp[n][2][0], dp[n][0][0]);
    }

    // 直观能想到的空间优化，压缩一维数据
    int maxProfit2(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> dp(vector<vector<int>>(3, vector<int>(2, INT32_MIN)));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            int tmp00 = max(dp[2][0], dp[0][0]); // 临时存储，防止在处理的时候修改
            int tmp01 = max(dp[1][1], dp[0][1]);
            int tmp20 = max(dp[0][1], dp[1][1]) + prices[i - 1];
            int tmp11 = dp[0][0] - prices[i - 1];
            dp[0][0] = tmp00, dp[0][1] = tmp01, dp[2][0] = tmp20, dp[1][1] = tmp11;
        }

        return max(dp[2][0], dp[0][0]);
    }
};


/**
 * 714. 买卖股票的最佳时机含手续费
 * 给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用
 * 你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
 * 返回获得利润的最大值。
 * 这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
 *
 * 已知状态的动态规划问题
 * 第i天的利润与上一天是否持有股票有关
 */
class Solution26 {
public:
    int maxProfit(vector<int> &prices, int fee) {
        // dp[i][j] 第i天，状态为j(j=0(不持有),1(持有))的最大利润
        // 不持有 dp[i][0] = max(dp[i-1][1] + prices[i] - fee, dp[i-1][0]) 仅在卖出股票的时候考虑手续费即可
        // 持有 dp[i][1] = max(dp[i-1][0] - prices[i], dp[i-1][1])

        int n = prices.size();
        vector<int> dp(2, INT32_MIN + 2 * fee); // max初始化为MIN
        dp[0] = 0; // 状态转移原点
        for (int i = 0; i < n; ++i) {
            int tmp0 = max(dp[1] + prices[i] - fee, dp[0]); // 临时存储，防止修改
            int tmp1 = max(dp[0] - prices[i], dp[1]);
            dp[0] = tmp0, dp[1] = tmp1;
        }

        return dp[0];
    }
};


/**
 * 123. 买卖股票的最佳时机 III
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
 * 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * 同样是已知状态的动态规划
 * 由于一直最多两笔交易，所以可以将交易笔数设为状态0，1，2 另一个状态就是当前是否持有
 */
class Solution27 {
public:
    int maxProfit(vector<int> &prices) {
        // dp[i][j][k] 第i天，完成j(j=0,1,2)笔交易后状态为k(k=0(未持有)),1(持有)) 的最大利润
        // 完成了0次交易后持有 dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][0][0] - prices[i])
        // 完成了1次交易后未持有 dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][0][1] + prices[i])
        // 完成了1次交易后持有 dp[i][1][1] = max(dp[i-1][1][0] - prices[i], dp[i-1][1][1])
        // 完成了2次交易后未持有 dp[i][2][0] = max(dp[i-1][1][1] + prices[i], dp[i-1][2][0])

        int n = prices.size();
        vector<vector<int>> dp(3, vector<int>(2, INT32_MIN / 2)); // max初始化
        dp[0][0] = 0; // 状态转移原点
        for (int i = 0; i < n; ++i) {
            int tmp01 = max(dp[0][1], dp[0][0] - prices[i]);
            int tmp10 = max(dp[1][0], dp[0][1] + prices[i]);
            int tmp11 = max(dp[1][0] - prices[i], dp[1][1]);
            int tmp20 = max(dp[1][1] + prices[i], dp[2][0]);
            dp[0][1] = tmp01, dp[1][0] = tmp10, dp[1][1] = tmp11, dp[2][0] = tmp20;
        }
        return max(dp[2][0], max(dp[1][0], dp[0][0])); // 最大利润可能出现在交易0次或1次或2次时
    }
};


/**
 * 188. 买卖股票的最佳时机 IV
 * 给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
 * 设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。
 * 注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 *
 * 当k>=prices.size()/2时
 * 可以认为不限制交易笔数k，这时就是一个普通的买卖股票获得最大收益问题，将所以的增益加起来即可
 *
 * 当k<prices.size()时
 * 这是可以按照上题逻辑，从状态转移的角度来做
 */
class Solution28 {
public:
    int maxProfit(int k, vector<int> &prices) {
        // dp[i][j][t] = 前i天，完成j(j=1,2,3,...,k)笔交易后状态为t(t=0(未持有),1(持有))时最大利润
        // 完成0次交易后状态为未持有 dp[i][0][0]] = dp[i-1][0][0]
        // 完成0次交易后状态为持有 dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][0][0] - prices[i])
        // 完成j次交易后状态为未持有 dp[i][j][0] = max(dp[i-1][j-1][1] + prices[i], dp[i-1][j][0])
        // 完成j次交易后状态为持有 dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j][0] - prices[i])
        // 完成k次交易后状态为未持有 dp[i][k][0] = max(dp[i-1][k][1] + prices[i], dp[i-1][k][0])

        int n = prices.size();

        if (k >= n / 2) {
            // 退化成普通股票问题，即可以获得所有收益，理论利润最大
            int max_profit = 0;
            for (int i = 1; i < n; ++i)
                if (prices[i] - prices[i - 1] > 0)
                    max_profit += prices[i] - prices[i - 1];

            return max_profit;
        }

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, INT32_MIN / 2)));
        dp[0][0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k && j <= i / 2; ++j) {
                if (j > 0)
                    dp[i][j][0] = max(dp[i - 1][j - 1][1] + prices[i - 1], dp[i - 1][j][0]);
                else
                    dp[i][j][0] = dp[i - 1][j][0];

                if (j != k)
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j][0] - prices[i - 1]);
            }
        }

        int ans = INT32_MIN;
        for (int i = 0; i <= k; ++i) ans = max(ans, dp[n][i][0]);
        return ans;
    }
};


/**
 * 583. 两个字符串的删除操作
 * 给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。
 *
 * 显然是找最长公共子串问题
 */
class Solution29 {
public:
    int minDistance(string word1, string word2) {
        // dp[i][j] = s1的前i个字符和s2的前j个字符的最长公共子序列长度
        // dp[i][j] = dp[i-1][j-1] + 1   if s1[i] == s2[j]
        //          = max(dp[i-1][j], dp[i][j-1])   if s1[i] != s2[j]

        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); // 求解数目，不会有负数

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1]) // 调整ij坐标,由于字符串，越界不会报错，使得错误更不易察觉
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        return n + m - 2 * dp[n][m]; // 求需要删除的字符数
    }
};


/**
 * 72. 编辑距离
 * 给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
 * 你可以对一个单词进行如下三种操作：
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 *
 * 显然，对word1插入一个字符等价于对word2删除一个字符，对word1替换一个字符，等价于对word2替换一个字符
 * 所以只有三种操作，对word1插入一个字符，对word2插入一个字符，对word1替换一个字符
 *
 * dp[i][j] = word1前i个字符和word2前j个字符的编辑距离
 * 当word1[i] == word2[j]时，显然dp[i][j] == dp[i-1][j-1]，即如果这两个字符相同时，编辑距离等价于没有这两个字符
 * 当两者不等时，编辑距离等与
 * 修改一个字符 dp[i-1][j-1]
 * 对word1增加一个字符 dp[i-1][j]
 * 对word2增加一个字符 dp[i][j-1]
 * 三者中的最小值 + 1
 */
class Solution30 {
public:
    int minDistance(string word1, string word2) {
        // dp[i][j] = word1前i个字符和word2前j个字符的编辑距离
        // dp[i][j] = dp[i-1][j-1]  if s1[i] == s2[j]
        //          = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1   if s1[i] != s2[j]

        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; ++i) dp[i][0] = i; // 边界处理，显然一个字符串为0的时候，编辑距离就是另一个字符串的长度
        for (int i = 0; i <= m; ++i) dp[0][i] = i;

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }

        return dp[n][m];
    }
};


/**
 * 650. 只有两个键的键盘
 * 最初在一个记事本上只有一个字符 'A'。你每次可以对这个记事本进行两种操作：
 * Copy All (复制全部) : 你可以复制这个记事本中的所有字符(部分的复制是不允许的)。
 * Paste (粘贴) : 你可以粘贴你上一次复制的字符。
 * 给定一个数字 n 。你需要使用最少的操作次数，在记事本中打印出恰好 n 个 'A'。输出能够打印出 n 个 'A' 的最少操作次数。
 *
 * 显然，素数n需要n操作才能得到
 * 和数 n = i * j
 * 如果i >= j 则 i 先复制一次，然后黏贴j-1次即可得到n
 * 所以 minSteps(n) = minSteps(i) + 1 + j-1 = minSteps(i) + j = minSteps(i) + n/i;
 */
class Solution31 {
public:
    int minSteps(int n) {
        // 如果n = i * j
        // minSteps(n) = minSteps(i) + 1 + j-1 = minSteps(i) + j = minSteps(i) + n/i;
        if (n == 1) return 0;
        for (int i = 2; i < n; ++i)
            if (n % i == 0) return minSteps(n / i) + i; // 这里由于i从小到大，所以显然n/i要大于i，所以minStep(n/i)
        return n;
    }
};


/**
 * 剑指 Offer 48. 最长不含重复字符的子字符串
 * 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
 *
 * dp结合哈希表
 */
class Solution32 {
public:
    int lengthOfLongestSubstring(string s) {
        // dp[i] = 以i结尾的最长子序列的长度
        // dp[i] = dp[i-1] + 1    if dp[i-1] < i-j    ,s[i] == s[j]，j为上一个与s[i]相等的位置
        //       = i-j            if dp[i-1] >= i-j
        // 如何快速求i？如何快速求与当前坐标值相同的上一个值的坐标?
        // 哈希表记录最后一个相同值的坐标

        vector<int> mp(256, -1);
        vector<int> dp(s.size()+1, 0);
        int maxlen = 0;
        for (int i = 1; i <= s.size(); ++i) {
            int idx = mp[s[i-1]];
            if (dp[i-1] < i-1-idx)
                dp[i] = dp[i-1] + 1;
            else
                dp[i] = i-1-idx;

            mp[s[i-1]] = i-1;
            maxlen = max(maxlen, dp[i]);
        }
        return maxlen;
    }
};


/**
 * 剑指 Offer 49. 丑数
 * 我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。
 */
class Solution33 {
public:
    int nthUglyNumber(int n) {
        // dp[i] = 第i个丑数
        // dp[i] = min{dp[a]*2, dp[b]*3, dp[c]*5}, 为了使丑数最小，要求dp[a,b,c]为第一组*235后大于dp[i-1]的abc
        vector<int> dp(n+1, 0);
        int a = 1, b = 1, c = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = min(dp[a]*2, min(dp[b]*3, dp[c]*5));
            if (dp[i] == dp[a]*2) a++;
            if (dp[i] == dp[b]*3) b++; // 由于dp[i] 可能同时等于多个，所以这里不能用else
            if (dp[i] == dp[c]*5) c++;
        }
        return dp[n];
    }
};


/**
 * 剑指 Offer 60. n个骰子的点数
 * 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
 * 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。
 *
 * 计算n个色子投出的各个点数的可能数 / 总可能数
 */
class Solution34 {
public:
    vector<double> twoSum(int n) {
        // dp[i][j] = 投掷i个色子，点数为j的可能数
        // dp[i][j] += dp[i-1][j-k]    k=1,2,3,...min(j-1, 6) 一个色子的点数不可能超过6

        vector<vector<int>> dp(n+1, vector<int>(70, 0));
        for (int i = 1; i <= 6; ++i) dp[1][i] = 1;

        for (int i = 2; i <= n; ++i)
            for (int j = i; j <= 6*i; ++j)
                for (int k = 1; k <= 6 && j>k; ++k) // 这里k表示第i个色子可能投出的点数
                    dp[i][j] += dp[i-1][j-k];

        vector<double> ans;
        for (int j = 1*n; j <= 6*n; j++)
            ans.push_back(double(dp[n][j]) / pow(6,n));
        return ans;
    }
};