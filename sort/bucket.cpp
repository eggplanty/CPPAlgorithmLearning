#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * 347. 前 K 个高频元素
 * 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。
 */

class Solution {
public:
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> m; // n, freq
        for (auto &n : nums)
            ++m[n];

        vector<vector<int>> buckets(nums.size()+1);
        for (auto iter = m.begin(); iter != m.end(); iter++)
            buckets[iter->second].push_back(iter->first);

        vector<int> ans;
        for (int i = buckets.size()-1; i >= 0; i--) {
            for (auto &b : buckets[i]) {
                ans.push_back(b);
                if (ans.size() == k)
                    return ans;
            }
        }
        return ans;
    }
};

/**
 * 451. 根据字符出现频率排序
 * 给定一个字符串，请将字符串里的字符按照出现的频率降序排列。
 */
class Solution2 {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m;
        for (auto &c : s)
            m[c]++;

        vector<vector<char>> buckets(s.size()+1);
        for (auto iter = m.begin(); iter != m.end(); iter++)
            buckets[iter->second].push_back(iter->first);

        string ans;
        for (int i = buckets.size()-1; i >= 0; i--) {
            for (auto &b : buckets[i]) {
                ans += string(i, b);
            }
        }
        return ans;
    }
};

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