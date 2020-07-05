//
// Created by XBB-PC on 2020/6/23.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

/**
 * 242. 有效的字母异位词
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 *
 * 根据每个字符的数量来判断
 */
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> v(26, 0);
        for (auto c: s)
            v[c - 'a']++; // 记录每个字符出现的数量
        for (auto c: t)
            v[c - 'a']--; // 反向减小每个字符出现的数量

        for (auto tmp : v)
            if (tmp != 0) // 如果不抵消
                return false;
        return true;
    }
};


/**
 * 409. 最长回文串
 * 给定一个包含大写字母和小写字母的字符串，找到通过这些字母构造成的最长的回文串。
 * 在构造过程中，请注意区分大小写。比如 "Aa" 不能当做一个回文字符串。
 * 假设字符串的长度不会超过 1010。
 *
 * 计算偶数组数量即可
 */
class Solution2 {
public:
    int longestPalindrome(string s) {
        vector<int> v(26 * 2, 0);
        for (auto c: s) {
            int t = c >= 'a' ? c - 'a' + 26 : c - 'A';
            v[t]++; // 计算各个字符的数量
        }
        int cnt = 0;
        for (auto tmp : v)
            cnt += tmp / 2 * 2; // 计算各个字符的配对数量之和
        return cnt + (cnt < s.size() ? 1 : 0); // 如果配对数量之和小于总数，说明比存在单个字符
    }
};


/**
 * 205. 同构字符串
 * 给定两个字符串 s 和 t，判断它们是否是同构的。
 * 如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。
 * 所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。
 */
class Solution3 {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> v1(256, -1); // s->t
        vector<int> v2(256, -1); // t->s
        for (int i = 0; i < s.size(); i++) {
            int tmp1 = v1[int(s[i])]; // 获取s到t的映射和t到s的映射
            int tmp2 = v2[int(t[i])];
            if (tmp1 < 0 && tmp2 < 0) { // 两个映射如果都小于0说明还未设置
                v1[int(s[i])] = int(t[i]);
                v2[int(t[i])] = int(s[i]);
                continue;
            }
            if (tmp1 != int(t[i]) || tmp2 != int(s[i])) return false; // 两个映射不相等说明不是同构，单方向不相等不行，如ab和aa
        }
        return true;
    }
};


/**
 * 647. 回文子串
 * 给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
 * 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。
 *
 *
 * 从字符串的某一位开始，尝试着去扩展子字符串。
 */
class Solution4 {
public:
    int cnt = 0;

    void extend(string s, int i, int j) { // 确定start和end，尝试扩展
        while (i >= 0 && j < s.size() && s[i] == s[j]) {
            i--;
            j++;
            cnt++;
        }
    }

    int countSubstrings(string s) {
        for (int i = 0; i < s.size(); i++) {
            extend(s, i, i); // 奇数回文串
            extend(s, i, i + 1); // 偶数回文串
        }
        return cnt;
    }
};


/**
 * 9. 回文数
 * 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 *
 * 不转成字符串处理，可以将数字分为左右两部分，右边需要翻转，然后判断左右值是否相等即可
 */
class Solution5 {
public:
    bool isPalindrome(int x) {
        if (x == 0) return true;
        if (x < 0 || x % 10 == 0) return false;
        int right = 0;
        while (x > right) {
            right = x % 10 + right * 10; // 翻转右边的值
            x /= 10;
        }
        return x == right || x == right / 10; // 偶数时，两者相等，奇数时，x会小于right
    }
};


/**
 * 696. 计数二进制子串
 * 给定一个字符串 s，计算具有相同数量0和1的非空(连续)子字符串的数量，并且这些子字符串中的所有0和所有1都是组合在一起的。
 * 重复出现的子串要计算它们出现的次数。
 *
 * 某个字串的此处和重复0或1的较小值有关，例如00111，包含两个: 0011, 01
 */
class Solution6 {
public:
    int countBinarySubstrings(string s) {
        int pre = 0, cur = 1, cnt = 0; // 只需要记录前一个不相同字符的长度
        for (int i = 1; i < s.size(); i++) {
            if (s[i] != s[i - 1]) { // 当字符发生变化时，计算组合数
                cnt += min(cur, pre);
                pre = cur;
                cur = 1;
            } else
                cur++;
        }
        return cnt + min(cur, pre); // 单独计算最后字符未变的情况
    }
};