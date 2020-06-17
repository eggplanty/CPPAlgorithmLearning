//
// Created by XBB-PC on 2020/6/17.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};


/**
 * 104. 二叉树的最大深度
 * 给定一个二叉树，找出其最大深度。
 * 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
 * 说明: 叶子节点是指没有子节点的节点。
 */
class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (!root) return 0; // NULL节点深度为0
        return max(maxDepth(root->left), maxDepth(root->right)) + 1; // 当前节点的最大深度加1
    }
};

/**
 * 110. 平衡二叉树
 * 给定一个二叉树，判断它是否是高度平衡的二叉树。
 * 本题中，一棵高度平衡二叉树定义为：
 * 一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。
 */
class Solution2 {
public:
    bool balace = true;

    int treedepth(TreeNode *root) { // 计算每个子树的高度
        if (!root) return 0;
        int dep1 = treedepth(root->left);
        int dep2 = treedepth(root->right);
        if (abs(dep1 - dep2) > 1) balace = false; // 若左右子树高度差大于1则不平衡
        return max(dep1, dep2) + 1;
    }

    bool isBalanced(TreeNode *root) {
        treedepth(root);
        return balace;
    }
};

/**
 * 543. 二叉树的直径
 * 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
 */
class Solution3 {
public:
    int cnt = 0;

    int treeDepth(TreeNode *root) {
        if (!root) return 0;

        int dep1 = treeDepth(root->left);
        int dep2 = treeDepth(root->right);
        cnt = max(cnt, dep1 + dep2); // 计算左右子树深度和最大的值
        return max(dep1, dep2) + 1;
    }

    int diameterOfBinaryTree(TreeNode *root) {
        treeDepth(root);
        return cnt;
    }
};

/**
 * 226. 翻转二叉树
 * 翻转一棵二叉树。
 */
class Solution4 {
public:
    TreeNode *invertTree(TreeNode *root) {
        if (!root) return root;

        TreeNode *left = invertTree(root->left);
        TreeNode *right = invertTree(root->right);
        root->left = right; // 左右子树翻转
        root->right = left;
        return root;
    }
};


/**
 * 617. 合并二叉树
 * 给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
 * 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。
 */
class Solution5 {
public:
    TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2) {
        if (!t1 && !t2) return NULL;
        if (!t2) return t1; // 当一棵树的某个分支为空时，直接使用另一棵树的值
        if (!t1) return t2;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;// 返回的是某个子树合并后的结果
    }
};

/**
 * 112. 路径总和
 * 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。
 * 说明: 叶子节点是指没有子节点的节点。
 */
class Solution6 {
public:
    bool ans = false;
    void fun(TreeNode *root, int sum) {
        if (!root) return;
        if (!root->left && !root->right && (sum - root->val) == 0) // 叶子节点，且sum==root->val，则满足目标
            ans = true;

        fun(root->left, sum-root->val);
        fun(root->right, sum-root->val);
    }

    bool hasPathSum2(TreeNode* root, int sum) {
        if (!root) return false;
        fun(root, sum);
        return ans;
    }

    // 上面的两个函数可以简化到一个函数里面
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right && sum == root->val) return true;
        return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
    }
};