//
// Created by sen on 2020/5/29.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * 241. 为运算表达式设计优先级
 * 给定一个含有数字和运算符的字符串，为表达式添加括号，改变其运算优先级以求出不同的结果。你需要给出所有可能的组合的结果。有效的运算符号包含 +, - 以及 * 。
 */
class Solution {
public:

    int handle(int a, int b, char p) {
        int ans = 0;
        if (p == '+') ans = a + b;
        else if (p == '-') ans = a - b;
        else if (p == '*') ans = a * b;
        return ans;
    }

    vector<int> diffWaysToCompute(string input) {
        vector<int> ans;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i + 1, input.size()));

                for (auto &ll : left)
                    for (auto &rr: right)
                        ans.push_back(handle(ll, rr, input[i]));
            }
        }

        if (ans.size() == 0) // 作为递归终止条件，应该放在函数最初，但是由于for循环判断是否存在+-*，所以可以放在这里一起判断
            return {stoi(input)}; //stoi(string) , atoi(char *) 对应string.to_str()，char可以用 char-'0'来转换

        return ans;
    }
};


/**
 * 95. 不同的二叉搜索树 II
 * 给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution2 {
public:

    vector<TreeNode *> fun(int st, int ed) {
        if (st > ed)
            return {NULL}; //必须要有NULL，否则不能创建TreeNode(i)，结果会为空

        vector<TreeNode *> ans;
        for (int i = st; i <= ed; i++) {
            vector<TreeNode *> left = fun(st, i - 1); // 缩小问题规模
            vector<TreeNode *> right = fun(i + 1, ed);
            for (auto &ll: left)
                for (auto &rr: right) {
                    TreeNode *t = new TreeNode(i); // 指针创建
                    t->left = ll;
                    t->right = rr;
                    ans.push_back(t);
                }
        }

        return ans;
    }

    vector<TreeNode *> generateTrees(int n) {
        if (n == 0)
            return {};
        return fun(1, n);
    }
};


/**
 * 剑指 Offer 19. 正则表达式匹配
 * 请实现一个函数用来匹配包含'. '和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。在本
 * 题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。
 *
 * 考虑p[m-1]的三种情况，本问题可以划分为子问题来处理，所以可以用分治来做
 */
class Solution3 {
public:

    bool isMatch(string s, string p) {
        // 1. p[m-1] = 普通字符, if s[n-1] == p[m-1] isMatch(s[0:n-2], p[0:m-2])
        // 2. p[m-1] = . isMatch(s[0:n-2], p[0:m-2])
        // 3. p[m-1] = *
        //      3.1 p[m-2]==s[n-1]  isMatch(s[0:n-2], p)
        //      3.2 p[m-2]!=s[n-1]  isMatch(s, p[0:m-2])

        int n = s.size(), m = p.size();
        if (n == 0 && m == 0) return true;
        if (m == 0 && n != 0) return false;
        if (n == 0 && p[m - 1] != '*') return false;

        if (p[m - 1] == '.')
            return isMatch(s.substr(0, n - 1), p.substr(0, m - 1));
        else if (p[m - 1] == '*') {
            if (m == 1 || p[m - 2] == '*') return false;
                // 分两种情况，匹配之后消耗掉*组合，或者不消耗*组合，因为*组合可以是0次或任意次，可能存在*组合取代了左边本来能匹配的字符，导致左边字符无法匹配
            else if (n > 0 && (p[m - 2] == '.' || p[m - 2] == s[n - 1]))
                return isMatch(s.substr(0, n - 1), p) || isMatch(s, p.substr(0, m - 2));
            else return isMatch(s, p.substr(0, m - 2));
        } else {
            if (p[m - 1] != s[n - 1]) return false;
            return isMatch(s.substr(0, n - 1), p.substr(0, m - 1));
        }
        return false;
    }
};