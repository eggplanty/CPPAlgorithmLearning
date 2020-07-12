//
// Created by XBB-PC on 2020/7/4.
//

#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * 75. 颜色分类 (荷兰国旗问题，三向快速切分)
 * 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并
 * 按照红色、白色、蓝色顺序排列。此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 */
class Solution3 {
public:
    void sortColors(vector<int>& nums) {
        int i = 0, k = 0, j = nums.size()-1;
        while (k<=j) {
            if (nums[k] == 0)
                swap(nums[i++], nums[k++]);
            else if (nums[k] == 2)
                swap(nums[k], nums[j--]);
            else
                k++;
        }
    }
};

/**
 * 剑指 Offer 51. 数组中的逆序对
 * 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
 *
 * 逆序对可以从归并的角度来开率
 */
class Solution4 {
public:
    vector<int> tmp;

    int merge(vector<int> &nums, int l, int r, int m) {
        int i = l, j = m+1;
        for (int k = l; k<=r;++k) tmp[k] = nums[k];

        int cnt = 0;
        for (int k = l ; k <= r; k++) {
            if (j > r) {
                nums[k] = tmp[i++];
                cnt += r-m; // 如果超出右边界，则右序列的所有值都可以构成逆序列
            }
            else if (i > m) nums[k] = tmp[j++];
            else if (tmp[i] <= tmp[j]) {
                nums[k] = tmp[i++];
                cnt += j-m-1; // 右边界和m之间的值可以构成逆序列
            }
            else nums[k] = tmp[j++];
        }
        return cnt;
    }

    int mergesort(vector<int> &nums, int i, int j) {
        if (i >= j) return 0;
        int m = i + (j-i) / 2;
        int cnt = mergesort(nums, i, m) + mergesort(nums, m+1, j);
        return cnt + merge(nums, i, j, m);
    }

    int reversePairs(vector<int>& nums) {
        // 归并排序的应用
        tmp = vector<int>(nums.size(), 0);
        return mergesort(nums, 0, nums.size()-1);
    }
};