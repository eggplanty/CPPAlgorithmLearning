//
// Created by XBB-PC on 2020/6/16.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

class BasicSort {


    int partition(int l, int h, vector<int> &nums) {
        int i = l, j = h - 1, q = nums[h];
        while (i <= j) {
            while (i <= j && nums[i] < q) i++;
            while (i <= j && nums[j] > q) j--;
            if (i <= j) swap(nums[i++], nums[j--]);
        }
        swap(nums[i], nums[h]);
        return i;
    }

    // 快速选择，查找第k小的数，也可以用来计算中位数
    int fastSelectFindKthSmall(vector<int> &nums, int k) {
        int i = 0, j = nums.size() - 1;
        while (i <= j) {
            int t = partition(i, j, nums);

            if (t == k) return nums[k];
            if (t < k) i = t + 1;
            else j = t - 1;
        }
        return 0;
    }
};