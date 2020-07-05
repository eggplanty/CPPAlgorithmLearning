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