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
        if (p == '+') ans = a+b;
        else if (p == '-') ans = a-b;
        else if (p == '*') ans = a*b;
        return ans;
    }

    vector<int> diffWaysToCompute(string input) {
        vector<int> ans;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i));
                vector<int> right = diffWaysToCompute(input.substr(i+1, input.size()));

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

    vector<TreeNode*> fun(int st, int ed) {
        if (st > ed)
            return {NULL}; //必须要有NULL，否则不能创建TreeNode(i)，结果会为空

        vector<TreeNode*> ans;
        for (int i = st; i <= ed; i++) {
            vector<TreeNode*> left = fun(st, i-1); // 缩小问题规模
            vector<TreeNode*> right = fun(i+1, ed);
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

    vector<TreeNode*> generateTrees(int n) {
        if (n == 0)
            return {};
        return fun(1, n);
    }
};