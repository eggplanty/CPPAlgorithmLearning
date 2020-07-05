//
// Created by XBB-PC on 2020/6/24.
//

#include <iostream>
#include <cstring>
#include <math.h>
#include <vector>
#include <queue>
#include <deque>
#include <map>

using namespace std;


/**
 * 283. 移动零
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 必须在原数组上操作，不能拷贝额外的数组。
 * 尽量减少操作次数。
 *
 * 考虑双指针，慢指针前的所有元素都是非零的，快慢指针间的元素都是0
 */
class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        for (int prev = 0, cur = 0; cur < nums.size(); cur++)
            if (nums[cur] != 0)
                swap(nums[prev++], nums[cur]);
    }
};


/**
 * 566. 重塑矩阵
 * 在MATLAB中，有一个非常有用的函数 reshape，它可以将一个矩阵重塑为另一个大小不同的新矩阵，但保留其原始数据。
 * 给出一个由二维数组表示的矩阵，以及两个正整数r和c，分别表示想要的重构的矩阵的行数和列数。
 * 重构后的矩阵需要将原始矩阵的所有元素以相同的行遍历顺序填充。
 * 如果具有给定参数的reshape操作是可行且合理的，则输出新的重塑矩阵；否则，输出原始矩阵。
 * 给定矩阵的宽和高范围在 [1, 100]。
 * 给定的 r 和 c 都是正数。
 *
 * 其实就是重新确定坐标
 */
class Solution2 {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c) {
        int row = nums.size(), col = nums[0].size();
        if (r * c != row * col) return nums;

        int idx = 0;
        vector<vector<int>> ans(r, vector<int>(c, 0));
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                ans[idx / c][idx % c] = nums[i][j]; // 重新确定坐标
                idx++;
            }
        return ans;
    }
};


/**
 * 485. 最大连续1的个数
 * 给定一个二进制数组， 计算其中最大连续1的个数。
 *
 * 典型的最大连续值计算方法
 */
class Solution3 {
public:
    int findMaxConsecutiveOnes(vector<int> &nums) {
        int ans = 0, curcnt = 0; // 记录当前连续值和历史最大连续值
        for (auto n : nums) {
            if (n == 0) { // 当不在连续时
                ans = max(ans, curcnt); // 对比最大连续值
                curcnt = 0; // 重新开始计数
                continue;
            }
            curcnt++;
        }
        return max(ans, curcnt); // 由于最后一组连续值未切换，所以需要最后判断下
    }
};


/**
 * 240. 搜索二维矩阵 II
 * 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：
 * 每行的元素从左到右升序排列。
 * 每列的元素从上到下升序排列。
 *
 * 利用数组性质做搜素，从右上角开始，如果小于目标值则向下移动，如果大于目标值则向左移动
 */
class Solution4 {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.size() <= 0 || matrix[0].size() <= 0) return false;
        int r = matrix.size(), c = matrix[0].size();
        int i = 0, j = c - 1; // 从右上角开始

        while (i < r && j >= 0) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] < target) i++; //如果小于目标值则向下移动，如果大于目标值则向左移动
            else j--;
        }
        return false;
    }
};


/**
 * 378. 有序矩阵中第K小的元素
 * 给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
 * 请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。
 *
 * 第k小的元素，常用大顶堆和快速选择，这里由于是二维数据，大顶堆会方便很多
 */
class Solution5 {
public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        priority_queue<int, vector<int>, less<>> pq; // less 大顶堆
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < matrix[0].size(); j++) {
                if (pq.size() >= k && pq.top() < matrix[i][j]) continue;
                pq.push(matrix[i][j]);
                if (pq.size() > k) pq.pop();
            }
        return pq.top();
    }
};


/**
 * 378. 有序矩阵中第K小的元素
 * 给定一个 n x n 矩阵，其中每行和每列元素均按升序排序，找到矩阵中第 k 小的元素。
 * 请注意，它是排序后的第 k 小元素，而不是第 k 个不同的元素。
 *
 * 二分查找法
 */
class Solution6 {
public:

    int fun(vector<vector<int>> &matrix, int m, int r, int c) {
        int i = 0, j = c - 1, cnt = 0;
        while (i < r && j >= 0) {
            if (matrix[i][j] <= m) { // 如果当前值小于等于m，则它左边的值必然都小于m， =m保证了能够取到其他列也等于m的值
                cnt += j + 1;
                i++; // 这是典型的找这种行列升序数组目标值的方法
            } else
                j--;
        }
        return cnt;
    }

    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int r = matrix.size(), c = matrix[0].size();
        int lo = matrix[0][0], hi = matrix[r - 1][c - 1];
        while (lo <= hi) { // 二分查找，按照值而不是按照id
            int mid = lo + (hi - lo) / 2;
            int cnt = fun(matrix, mid, r, c);
            if (cnt < k) lo = mid + 1;
            else hi = mid - 1;// =分支放在hi里，保证lo最后一定会停在目标值上
        }
        return lo;
    }
};

/**
 * 645. 错误的集合
 * 集合 S 包含从1到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个元素复制了成了集合里面的另外一个元素的值，导致集合丢失了一个整数并且有一个元素重复。
 * 给定一个数组 nums 代表了集合 S 发生错误后的结果。你的任务是首先寻找到重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。
 *
 * 先将各个位置的值交换到正确的位置，然后搜索不正确的值
 */
class Solution7 {
public:
    vector<int> findErrorNums(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++)
            while (i != nums[i] - 1 && nums[i] != nums[nums[i] - 1]) // 交换到正确位置，迭代交换，直到正确，或者遇到缺失的值
                swap(nums[i], nums[nums[i] - 1]);

        for (int j = 0; j < nums.size(); j++)
            if (j != nums[j] - 1)
                return {nums[j], j + 1}; // 缺失值

        return {};
    }
};


/**
 * 645. 错误的集合
 * 不用交换到正确的序列也可以求解，只需要知道重复的点，然后用1-n的点求和-当前序列的和+重复点值即可得到缺失的点
 */
class Solution8 {
public:
    vector<int> findErrorNums(vector<int> &nums) {
        int d = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++) { // 使用正负值来记录点坐标是否被使用过
            int tmp = abs(nums[i]);
            sum += tmp;
            if (nums[tmp - 1] < 0) d = tmp; // 找到重复点
            else nums[tmp - 1] *= -1;
        }
        int n = nums.size();
        int ori_sum = (1 + n) * n / 2;
        return {d, ori_sum - sum + d};
    }
};