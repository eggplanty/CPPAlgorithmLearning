//
// Created by sen on 2020/5/27.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <math.h>
#include <set>

using namespace std;

/**
 * 392. 判断子序列
 * 后续挑战
 * 如果有大量输入的 S，称作S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
 * 思路可以是使用一个数组存储下一个(a-z)字符的位置，从而使得字串搜索是跳跃的而不是遍历原字符串
 */
class Solution {
public:
    bool isSubsequence(string s, string t) {
        t = " " + t; // 开头加入空字符，处理第一个字符只出现一次时直接是-1的情况
        vector<vector<int>> vv(t.size(), vector<int>(26, -1)); // 跳跃表
        vector<int> tmp(26, -1); // 记录各个字符的下一个位置
        for (int i = t.size() - 1; i >= 0; i--) {
            vv[i] = vector<int>(tmp.begin(), tmp.end()); // 一次遍历，同时赋值
            if (t[i] != ' ') tmp[t[i] - 'a'] = i; // 处理空字符，防止越界
        }

        int pos = 0;
        for (auto &c : s) { // 跳跃查找
            pos = vv[pos][c - 'a'];
            if (pos < 0)
                return false;
        }
        return true;
    }
};

/**
 * 923. 三数之和的多种可能
 * 给定一个整数数组 A，以及一个整数 target 作为目标值，返回满足 i < j < k 且 A[i] + A[j] + A[k] == target 的元组 i, j, k 的数量。
 * 由于结果会非常大，请返回 结果除以 10^9 + 7 的余数。
 *
 */

class Solution2 {
public:
    const long M = 1e9 + 7;

    int threeSumMulti(vector<int> &A, int target) {
        sort(A.begin(), A.end());

        int i = 0, j = 0, k = 0, cnt = 0;

        for (; i < A.size() - 1; i++) {
            j = i + 1, k = A.size() - 1;
            int tar = target - A[i];
            while (j < k) {
                int tmp = A[j] + A[k];
                if (tmp == tar) {
                    if (A[j] == A[k]) {
                        cnt += (1 + k - j) * (k - j) / 2;
                        cnt %= M;
                        break;
                    } else {
                        int tj = j, tk = k;
                        while (A[tj] == A[++j]);

                        while (A[tk] == A[--k]);

                        cnt += (j - tj) * (tk - k);
                        cnt %= M;
                    }
                } else if (tmp > tar)
                    k--;
                else
                    j++;
            }
        }
        return cnt;
    }
};


/**
 * 167. 两数之和 II - 输入有序数组
 * 给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
 * 函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
 *
 * 升序队列，典型双指针
 */
class Solution3 {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            while (i < j && numbers[i] + numbers[j] < target) i++;
            while (i < j && numbers[i] + numbers[j] > target) j--;
            if (numbers[i] + numbers[j] == target)
                return {i + 1, j + 1};
        }
        return {i, j};
    }
};


/**
 * 633. 平方数之和
 * 给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c。
 */
class Solution4 {
public:
    bool judgeSquareSum(int c) {
        long i = 0, j = sqrt(c);
        while (i <= j) {
            while (i <= j && i * i + j * j < c) i++;
            while (i <= j && i * i + j * j > c) j--;
            if (i * i + j * j == c)
                return true;
        }
        return false;
    }
};


/**
 * 345. 反转字符串中的元音字母
 * 编写一个函数，以字符串作为输入，反转该字符串中的元音字母。
 */
class Solution5 {
public:
    string reverseVowels(string s) {
        set<char> st = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int i = 0, j = s.size() - 1;
        while (i < j) {
            while (i < j && st.count(s[i]) == 0) i++;
            while (i < j && st.count(s[j]) == 0) j--;
            if (i < j)
                swap(s[i++], s[j--]);
        }
        return s;
    }
};


/**
 * 680. 验证回文字符串 Ⅱ
 * 给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。
 */
class Solution6 {
public:

    bool fun(string s, int l, int r) {
        if (l >= r) return true;
        int i = l, j = r;
        while (i < j) {
            if (s[i] == s[j]) i++, j--;
            else
                return false;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (s[i] == s[j]) i++, j--;
            else
                return fun(s, i + 1, j) || fun(s, i, j - 1);
        }
        return true;
    }
};


/**
 * 88. 合并两个有序数组
 * 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
 * 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
 * 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 */
class Solution7 {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 || j >= 0) {
            if (i < 0) nums1[k--] = nums2[j--];
            else if (j < 0) nums1[k--] = nums1[i--];
            else if (nums1[i] < nums2[j]) nums1[k--] = nums2[j--];
            else nums1[k--] = nums1[i--];
        }
    }
};


struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * 141. 环形链表
 * 给定一个链表，判断链表中是否有环。
 * 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
 *
 * 快慢指针
 */
class Solution8 {
public:
    bool hasCycle(ListNode *head) {
        if (!head) return false;
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            if (fast == slow) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }
};


/**
 * 524. 通过删除字母匹配到字典里最长单词
 * 给定一个字符串和一个字符串字典，找到字典里面最长的字符串，该字符串可以通过删除给定字符串的某些字符来得到。如果答案不止一个，返回长度最长且字典顺序最小的字符串。如果答案不存在，则返回空字符串。
 */
class Solution9 {
public:
    bool fun(string s, string pat) {
        int i = 0, j = 0;
        while (i < s.size() && j < pat.size()) {
            if (s[i] == pat[j]) i++, j++;
            else i++;
        }
        return j == pat.size();
    }

    string findLongestWord(string s, vector<string>& d) {
        string ans = "";
        for (string pat : d)
            if (fun(s, pat))
                if (pat.size() > ans.size() || (pat.size() == ans.size() && pat < ans)) // 字典序
                    ans = pat;
        return ans;
    }
};


/**
 *
 */
class Solution10 {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>>ans;
        vector<int> tmp;
        for (int i=1, j=2; i < j;) {
            int sum = (i+j) * (j-i+1) / 2;
            if (sum == target) {
                tmp.clear();
                for (int k = i; k <= j; ++k) tmp.push_back(k);
                ans.push_back(tmp);
                ++i;
            }
            else if (sum > target) ++i;
            else ++j;
        }
        return ans;
    }
};


/**
 * 18. 四数之和
 * 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
 *
 * 大体思路和三数之和一样，用双指针解，
 * 这里可以通过判断最大值是否小于目标值，最小值是否大于目标值来提前结束循环
 */
class Solution11 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ans;
        int n = nums.size();
        if (n < 4) return {};

        sort(nums.begin(), nums.end());
        for (int i = 0; i < n-3; ++i) {
            if (i>0 && nums[i] == nums[i-1]) continue;
            if (nums[i] + nums[i+1]+nums[i+2]+nums[i+3] > target) continue; // 最小值大于目标值
            if (nums[i] + nums[n-1]+nums[n-2]+nums[n-3] < target) continue; // 最大值小于目标值

            for (int j = i+1; j < n-2; ++j) {
                if (j > i+1 && nums[j] == nums[j-1]) continue;
                if (nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) continue; // 最小值大于目标值
                if (nums[i] + nums[j] + nums[n-1] + nums[n-2] < target) continue; // 最大值小于目标值

                int k = j+1, t = n-1;
                while (k < t) {
                    int tmp = nums[i] + nums[j] + nums[k] + nums[t];
                    if (tmp == target) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[t]});
                        k++;
                        t--;
                        while (k<t && nums[k] == nums[k-1]) k++; // 保证数值发生变化，防止重复
                        while (k<t && nums[t] == nums[t+1]) t--;
                    }
                    else if (tmp > target) {
                        t--;
                    }
                    else {
                        k++;
                    }

                }
            }
        }
        return ans;
    }
};