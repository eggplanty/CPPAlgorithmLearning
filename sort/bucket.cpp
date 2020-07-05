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

        vector<vector<int>> buckets(nums.size() + 1);
        for (auto iter = m.begin(); iter != m.end(); iter++)
            buckets[iter->second].push_back(iter->first);

        vector<int> ans;
        for (int i = buckets.size() - 1; i >= 0; i--) {
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

        vector<vector<char>> buckets(s.size() + 1);
        for (auto iter = m.begin(); iter != m.end(); iter++)
            buckets[iter->second].push_back(iter->first);

        string ans;
        for (int i = buckets.size() - 1; i >= 0; i--) {
            for (auto &b : buckets[i]) {
                ans += string(i, b);
            }
        }
        return ans;
    }
};

/**
 * 1481. 不同整数的最少数目
 * 给你一个整数数组 arr 和一个整数 k 。现需要从数组中恰好移除 k 个元素，请找出移除后数组中不同整数的最少数目。
 *
 * 典型的桶排序，这里只需要记录各个频率的元素有多少即可，不用明确知道是什么
 */
class Solution3 {
public:
    int findLeastNumOfUniqueInts(vector<int> &arr, int k) {
        unordered_map<int, int> m;
        for (auto n : arr)
            m[n]++;

        int cnt = m.size();
        vector<int> buckets(arr.size() + 1, 0);
        for (auto iter = m.begin(); iter != m.end(); iter++)
            buckets[iter->second]++;

        for (int i = 0; i < buckets.size(); i++) {
            for (int j = 0; j < buckets[i]; ++j) {
                k -= i;
                if (k < 0)
                    return cnt;
                cnt--;
            }
        }
        return cnt;
    }
};