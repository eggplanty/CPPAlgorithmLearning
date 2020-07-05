//
// Created by XBB-PC on 2020/6/17.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

// TODO: 构建二叉树的方法

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

        fun(root->left, sum - root->val);
        fun(root->right, sum - root->val);
    }

    bool hasPathSum2(TreeNode *root, int sum) {
        if (!root) return false;
        fun(root, sum);
        return ans;
    }

    // 上面的两个函数可以简化到一个函数里面
    bool hasPathSum(TreeNode *root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right && sum == root->val) return true;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};


/**
 * 437. 路径总和 III
 * 给定一个二叉树，它的每个结点都存放着一个整数值。
 * 找出路径和等于给定数值的路径总数。
 * 路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
 * 二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。
 */
class Solution7 {
public:

    // 关键在于不一定从父节点开始，以子节点为头，路劲总和为sum也可
    int onePathSum(TreeNode *root, int sum) { // 求某个节点向下的满足条件路径数
        if (!root) return 0;
        int ans = 0;
        if (root->val == sum) ans++; // 判断当前节点是否满足要求
        return onePathSum(root->left, sum - root->val) + onePathSum(root->right, sum - root->val) + ans;
    }

    int pathSum(TreeNode *root, int sum) {
        if (!root) return 0;
        // 注意这里是sum，不是sum-root->type，因为可以以子节点为头
        return onePathSum(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
};

/**
 * 572. 另一个树的子树
 * 给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
 *
 * 思路为对每个s的子树判断是否与t相等，双重递归
 */
class Solution8 {
public:

    bool fun(TreeNode *s, TreeNode *t) { // 判断两棵树是否相等
        if (!s && !t) return true;
        if (!s || !t || s->val != t->val) return false;
        return fun(s->left, t->left) && fun(s->right, t->right);
    }

    bool isSubtree(TreeNode *s, TreeNode *t) {
        if (!s) return false;
        return fun(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t); // 判断当前子树以及左右子树是否存在与t相等
    }
};


/**
 * 101. 对称二叉树
 * 给定一个二叉树，检查它是否是镜像对称的。
 * 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
 *
 * 思路是将原树分成左右两个子树，比较两者是否镜像相等
 */
class Solution9 {
public:
    bool fun(TreeNode *t1, TreeNode *t2) { // 判断两棵树是否镜像相等
        if (!t1 && !t2) return true;
        if (!t1 || !t2 || t1->val != t2->val) return false;
        return fun(t1->left, t2->right) && fun(t1->right, t2->left); // 判断镜像相等
    }

    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        return fun(root->left, root->right); // 对左右两颗子树做判断
    }
};

/**
 * 101. 对称二叉树
 * 使用迭代实现和递归一样的效果，区别在于上面的递归本质是DFS，这里的迭代本质是BFS
 */
class Solution10 {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        queue<TreeNode *> q;
        q.push(root->left);
        q.push(root->right);
        while (!q.empty()) { // 经典BFS模型
            TreeNode *u = q.front();
            q.pop(); // 弹出队首的两个节点
            TreeNode *v = q.front();
            q.pop();
            if (!u && !v) continue;
            if (!u || !v || u->val != v->val) return false;
            q.push(u->left);
            q.push(v->right); // 将下一层的节点入队
            q.push(u->right);
            q.push(v->left);
        }
        return true;
    }
};

/**
 * 111. 二叉树的最小深度
 * 给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * 说明: 叶子节点是指没有子节点的节点。
 *
 * 二叉树经常出现的特例为只有单个左或者右孩子的节点，这种节点非叶子节点，经常需要单独考虑
 */
class Solution11 {
public:
    int minDepth(TreeNode *root) {
        if (!root) return 0;
        int left = minDepth(root->left);
        int right = minDepth(root->right);
        if (left == 0 || right == 0) return 1 + left + right; // 处理叶子节点或者只有单孩子的非叶子节点
        return 1 + min(left, right);
    }
};

/**
 * 404. 左叶子之和
 * 计算给定二叉树的所有左叶子之和。
 */
class Solution12 {
public:
    int sumOfLeftLeaves(TreeNode *root) {
        if (!root) return 0;
        queue<TreeNode *> q;
        q.push(root->left);
        q.push(root->right);
        int sum = 0;
        while (!q.empty()) { // 使用BFS可以确定左节点
            TreeNode *u = q.front();
            q.pop();
            TreeNode *v = q.front();
            q.pop();
            if (u && !u->left && !u->right) sum += u->val; // 确定左节点为叶子节点
            if (u) {
                q.push(u->left); // 每次成对推入，先推入的那个就是左节点
                q.push(u->right);
            }
            if (v) {
                q.push(v->left);
                q.push(v->right);
            }
        }
        return sum;
    }
};

/**
 * 404. 左叶子之和
 * 使用递归的方法，关键问题在于知道左节点的时候如何判断左节点是不是叶子节点，可以使用双重递归来做，第二重递归只有一层
 */
class Solution13 {
public:
    // 第二重递归，用来判断是否是叶子节点
    int isLeaf(TreeNode *root) {
        if (!root) return false;
        return !root->left && !root->right;
    }

    int sumOfLeftLeaves(TreeNode *root) {
        if (!root) return 0;
        if (isLeaf(root->left)) return root->left->val + sumOfLeftLeaves(root->right); // 返回左叶子节点的值+右节点下属左叶子节点的和
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};

/**
 * 687. 最长同值路径
 * 给定一个二叉树，找到最长的路径，这个路径中的每个节点具有相同值。 这条路径可以经过也可以不经过根节点。
 * 注意：两个节点之间的路径长度由它们之间的边数表示。
 *
 * 下面的做法先递归所有点，然后对每个点递归下属点求路径，最后计算路径最大值，由于记录路径最大值和递归过程可以并行，所以可以用一个递归实现
 */
class Solution14 {
public:
    int ans = 0;

    int fun(TreeNode *root, bool top) { // 计算从某个节点开始(包含这个节点)向下的最大路径
        if (!root) return 0;
        int left = root->left && root->left->val == root->val ? fun(root->left, false) : 0;
        int right = root->right && root->right->val == root->val ? fun(root->right, false) : 0;
        if (top) return 1 + left + right; // 使用top参数区分是否考虑横向路径
        return 1 + max(left, right);
    }

    void fun2(TreeNode *root) { // 递归所有节点，计算以各个节点开始的最大路径，求其中的最大值
        if (!root) return;
        ans = max(fun(root, true) - 1, ans);
        fun2(root->left);
        fun2(root->right);
    }

    int longestUnivaluePath(TreeNode *root) {
        fun2(root);
        return ans;
    }
};

/**
 * 687. 最长同值路径
 * 一次递归方法，关键在于递归返回值的处理
 */
class Solution15 {
public:
    int ans = 0;

    int fun(TreeNode *root) { // 返回值为最大同值边数=同值点数-1
        if (!root) return 0;
        int left = fun(root->left);
        int right = fun(root->right);
        int pl = root->left && root->val == root->left->val ? left + 1 : 0; // 当是叶子节点时，为0，这导致返回值由同值点数变成了同值点数-1
        int pr = root->right && root->val == root->right->val ? right + 1 : 0;
        ans = max(ans, pl + pr); // 左右同值边数相加之和
        return max(pl, pr); // 左右最大同值边数
    }

    int longestUnivaluePath(TreeNode *root) {
        fun(root);
        return ans;
    }
};

/**
 * 337. 打家劫舍 III
 * 在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房
 * 子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在
 * 同一天晚上被打劫，房屋将自动报警。
 *
 * 计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。
 */
class Solution16 {
public:

    // 这种做法由于深度下降是逐层下降的，时间复杂度过大
    int fun(TreeNode *root, bool up) { // 返回当前节点开始向下的最大金额, up=上层节点是否纳入计算
        if (!root) return 0;
        int tmp = fun(root->left, false) + fun(root->right, false); // 根据当前当前节点和上层节点是否纳入计算分成两类处理
        if (up) return tmp;
        else return max(tmp, fun(root->left, true) + fun(root->right, true) + root->val);
    }

    int rob(TreeNode *root) {
        return fun(root, false);
    }
};

/**
 * 337. 打家劫舍 III
 *
 * 正确做法是使用树形dp，类似处理青蛙跳格子问题
 */
class Solution17 {
public:

    pair<int, int> dfs(TreeNode *root) { // 返回first=包含root的最大值，second=不包含root的最大值
        if (!root) return {0, 0};
        auto left = dfs(root->left); // auto可以省的写一些比较复杂的定义
        auto right = dfs(root->right);
        // 包含root的最大值是 当前节点 + 左儿子情况2 + 右二子情况2
        // 不包含root的最大值是 max(左儿子情况1, 左儿子情况2) + max(右儿子情况1, 右儿子情况2) 对应下面四种情况
        // 左儿子情况1 + 右儿子情况1
        // 左儿子情况1 + 右儿子情况2
        // 左儿子情况2 + 右儿子情况1
        // 左儿子情况2 + 右儿子情况2
        return {root->val + left.second + right.second, max(left.first, left.second) + max(right.first, right.second)};
    }

    int rob(TreeNode *root) { // 返回当前节点下的最大金额
        auto res = dfs(root);
        return max(res.first, res.second);
    }
};

/**
 * 671. 二叉树中第二小的节点
 * 给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么这个节点的值不大于它的子节点的值。
 * 给出这样的一个二叉树，你需要输出所有节点中的第二小的值。如果第二小的值不存在的话，输出 -1 。
 *
 * 做法一：dfs递归，直接找出第二小的点，记录
 */
class Solution18 {
public:
    int ans = -1;

    void dfs(TreeNode *root, int target) {
        if (!root) return;
        if (root->val > target) {
            ans = ans < 0 ? root->val : min(ans, root->val);
            return;
        }
        dfs(root->left, target);
        dfs(root->right, target);
    }

    int findSecondMinimumValue(TreeNode *root) {
        dfs(root, root->val);
        return ans;
    }
};

/**
 * 671. 二叉树中第二小的节点
 * 做法二，直接递归完成
 */
class Solution19 {
public:
    int findSecondMinimumValue(TreeNode *root) { // 返回root节点向下的第二小的值
        if (!root) return -1;
        if (!root->left && !root->right) return -1;
        int v1 = -1, v2 = -1;
        // 如果有左孩子，且左孩子的值与root值相同，则递归获取下层第二小的值，否则取左孩子的值
        if (root->left) v1 = root->val == root->left->val ? findSecondMinimumValue(root->left) : root->left->val;
        if (root->right) v2 = root->val == root->right->val ? findSecondMinimumValue(root->right) : root->right->val;
        if (v1 == -1) return v2; // 如果左子树值相等，则返回右子树
        else if (v2 == -1) return v1;
        return min(v1, v2); // 如果左右子树都存在第二小的值，则返回两者较小值
    }
};

/**
 * 637. 二叉树的层平均值
 * 给定一个非空二叉树, 返回一个由每层节点平均值组成的数组.
 * 典型BFS
 */
class Solution20 {
public:
    vector<double> averageOfLevels(TreeNode *root) {
        vector<double> ans;
        if (!root) return ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            int cnt = q.size();
            double tmp = 0; // double 防止超出INT32限制
            int size = cnt;
            while (cnt-- > 0) {
                TreeNode *t = q.front();
                q.pop();
                tmp += t->val;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            ans.emplace_back(tmp / size);
        }
        return ans;
    }
};

/**
 * 513. 找树左下角的值
 * 给定一个二叉树，在树的最后一行找到最左边的值。
 *
 * 典型BFS框架
 */
class Solution21 {
public:
    int findBottomLeftValue(TreeNode *root) {
        if (!root) return 0;
        queue<TreeNode *> q;
        q.push(root);
        int ans = 0;
        while (!q.empty()) {
            int size = q.size();
            ans = size > 0 ? q.front()->val : ans;
            while (size-- > 0) {
                TreeNode *t = q.front();
                q.pop();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return ans;
    }
};

/**
 * 513. 找树左下角的值
 * 上述代码可以做一些优化，比如写入队列的时候先写右孩子，再写左孩子，这样最后处理的就是左下角的值
 */
class Solution22 {
public:
    int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            root = q.front();
            q.pop();
            if (root->right) q.push(root->right); // 先写右孩子，再写左孩子
            if (root->left) q.push(root->left);
        }
        return root->val;
    }
};

/**
 * 前中后序遍历
 *      1
 *    2   3
 *   4 5    6
 * 层次遍历：123456
 * 先序遍历：124536
 * 中序遍历：425136
 * 后序遍历：452631
 */
class Solution23 {
public:
    void front_dfs(TreeNode *root) {
        // do()
        front_dfs(root->left);
        front_dfs(root->right);
    }

    void middle_dfs(TreeNode *root) {
        middle_dfs(root->left);
        //do()
        middle_dfs(root->right);
    }

    void back_dfs(TreeNode *root) {
        back_dfs(root->left);
        back_dfs(root->right);
        //do()
    }
};

/**
 * 144. 二叉树的前序遍历
 * 给定一个二叉树，返回它的 前序 遍历。
 * 递归实现很简单
 */
class Solution24 {
public:
    vector<int> ans;

    void dfs(TreeNode *root) {
        if (!root) return;
        ans.emplace_back(root->val);
        dfs(root->left);
        dfs(root->right);
    }

    vector<int> preorderTraversal(TreeNode *root) {
        dfs(root);
        return ans;
    }
};

/**
 * 144. 二叉树的前序遍历
 * 非递归实现， 类似BFS，但是是从后入队，从后出队，后进先出，实现类似递归的效果
 */
class Solution25 {
public:

    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ans;
        vector<TreeNode *> q;
        q.emplace_back(root);
        while (!q.empty()) {
            TreeNode *t = q.back();
            q.pop_back(); // 从后出队
            if (!t) continue;
            ans.emplace_back(t->val);
            q.emplace_back(t->right);// 先入右孩子，再入左孩子，保证出队时左孩子先出
            q.emplace_back(t->left);
        }
        return ans;
    }
};

/**
 * 145. 二叉树的后序遍历
 * 给定一个二叉树，返回它的 后序 遍历。
 *
 * 前序遍历为 root -> left -> right，后序遍历为 left -> right -> root。可以修改前序遍历成为 root -> right -> left，那么这个顺序就和后序遍历正好相反。
 */
class Solution26 {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ans;
        vector<TreeNode *> q;
        q.emplace_back(root);
        while (!q.empty()) {
            TreeNode *t = q.back();
            q.pop_back();// 从后出队
            if (!t) continue;
            ans.emplace_back(t->val);
            q.emplace_back(t->left);// 先入左孩子，再入右孩子，保证出队时右孩子先出
            q.emplace_back(t->right);
        }
        reverse(ans.begin(), ans.end()); // 翻转结果
        return ans;
    }
};

/**
 * 94. 二叉树的中序遍历
 * 给定一个二叉树，返回它的中序 遍历。
 *
 * 通过while循环先循环左孩子，然后处理中间节点，再对右孩子重复处理
 */
class Solution27 {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ans;
        vector<TreeNode *> q;
        TreeNode *cur = root;
        while (cur || !q.empty()) { // 初始的时候需要cur != NULL 这个判断，用来加入root节点
            while (cur) { // 循环找最左边的孩子
                q.emplace_back(cur);
                cur = cur->left;
            }
            TreeNode *t = q.back();
            q.pop_back(); // 获取左孩子
            ans.emplace_back(t->val);
            cur = t->right; // 对右孩子执行同样操作
        }
        return ans;
    }
};

/**
 * 669. 修剪二叉搜索树
 */
class Solution28 {
public:
    TreeNode *trimBST(TreeNode *root, int L, int R) { // 返回以root为根的子树裁剪以后的根节点
        if (!root) return NULL;
        if (root->val > R) return trimBST(root->left, L, R); // 当root不在[L, R]中时，裁剪root
        if (root->val < L) return trimBST(root->right, L, R);
        root->left = trimBST(root->left, L, R); // 修正root的值
        root->right = trimBST(root->right, L, R);
        return root;
    }
};

/**
 * 230. 二叉搜索树中第K小的元素
 * 给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。
 * 你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。
 *
 * 二叉搜索树的中序遍历解法
 */
class Solution29 {
public:
    int ans = 0, kk = 0;

    void dfs(TreeNode *root) {
        if (!root) return;
        dfs(root->left);
        kk--;
        if (kk == 0) ans = root->val;
        dfs(root->right);
    }

    int kthSmallest(TreeNode *root, int k) {
        kk = k;
        dfs(root);
        return ans;
    }
};

/**
 * 230. 二叉搜索树中第K小的元素
 * 递归解法，核心思路在于根节点的为第m小个元素，左子树有m-1个节点
 */
class Solution30 {
public:
    int count(TreeNode *root) {
        if (!root) return 0;
        return 1 + count(root->left) + count(root->right);
    }

    int kthSmallest(TreeNode *root, int k) {
        if (!root) return 0;
        int left_cnt = count(root->left);
        if (left_cnt == k - 1) return root->val; // 如果左子树有k-1个节点
        if (left_cnt > k - 1) return kthSmallest(root->left, k); // 如果左子树大于k-1个节点，说明第k小个元素在左子树上
        // 如果左子树小于k-1个节点，说明第k小个元素在右子树上，对应右子树的节点的左子树数量为k-left_cnt-1，1为root
        return kthSmallest(root->right, k - left_cnt - 1);
    }
};

/**
 * 538. 把二叉搜索树转换为累加树
 * 给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和。
 *
 * 对中序遍历做修改，先遍历右孩子，并累计遍历过的值
 */
class Solution31 {
public:
    int sum = 0;

    void dfs(TreeNode *root) {
        if (!root) return;
        dfs(root->right); // 先遍历右孩子
        sum += root->val; // 累积遍历过的值
        root->val = sum;
        dfs(root->left);
    }

    TreeNode *convertBST(TreeNode *root) {
        dfs(root);
        return root;
    }
};

/**
 * 235. 二叉搜索树的最近公共祖先
 * 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 * 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
 *
 * 对二叉搜索树找公共祖先只需要按照值来找即可，公共祖先一定是第一个值在[p, q]之间的节点
 */
class Solution32 {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        // q>p后者p>q都可，所以需要两个同时判断，这里不考虑root==NULL，因为题目描述必定存在父节点
        if (p->val > root->val && q->val > root->val) return lowestCommonAncestor(root->right, p, q);
        if (q->val < root->val && p->val < root->val) return lowestCommonAncestor(root->left, p, q);
        return root; // 等于的情况表示自己是自己的父节点
    }
};


/**
 * 236. 二叉树的最近公共祖先
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 *
 * 不是二叉搜索树了，不能再直接用值去求解了
 * 考虑两种情况，一种是公共祖先为其中一个点，另一种是公共祖先为另外的点
 */
class Solution33 {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (!root || root == p || root == q) return root; // 递归时遇到这两个点即返回
        TreeNode *left = lowestCommonAncestor(root->left, p, q); // 左子树上的公共祖先
        TreeNode *right = lowestCommonAncestor(root->right, p, q); // 右子树上的公共祖先
        // 1.如果一个子树上不存在这两个点，即为NULL，则说明公共祖先如果存在一定是另一个子树上的公共祖先
        // 2.如果两个子树上的公共祖先都存在，则说明各分支各一个目标节点
        return !left ? right : !right ? left : root;
    }
};


/**
 * 108. 将有序数组转换为二叉搜索树
 * 将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
 * 本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
 *
 * 二叉搜索树，高度平衡，排序数组，只需要将排序数组二分，依次写入二叉搜索树即可
 */
class Solution34 {
public:
    TreeNode *toBST(vector<int> &nums, int l, int r) {
        if (l > r) return NULL;
        int m = l + (r - l) / 2;
        TreeNode *t = new TreeNode(nums[m]); // 为了高度平衡，将数组中间值写入二叉搜索树
        t->left = toBST(nums, l, m - 1); // 对数组左边递归并设置二叉搜索树当前节点的左孩子
        t->right = toBST(nums, m + 1, r);
        return t;
    }

    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return toBST(nums, 0, nums.size() - 1);
    }
};


/**
 * 109. 有序链表转换二叉搜索树
 *
 * 给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
 * 本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
 *
 * 和上题思路一样，二分，这里用到了链表的二分，使用快慢指针
 */
class Solution35 {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) return NULL;
        if (!head->next) return new TreeNode(head->val); // 防止pre指针的next的next出错
        ListNode *pre = getpre(head);
        ListNode *mid = pre->next;
        TreeNode *t = new TreeNode(mid->val);
        pre->next = NULL; // 断开链表
        ListNode *nt = mid->next;
        t->left = sortedListToBST(head); // 和上题一样，分别处理左右两边
        t->right = sortedListToBST(nt);
        return t;
    }

    ListNode *getpre(ListNode *head) {
        ListNode *slow = head, *fast = head->next, *pre = head; // 使用快慢指针找到链表的中间点
        while (fast && fast->next) {
            pre = slow; // 前指针用来记录中间点之前的值，方便二分之后左边界处理
            slow = slow->next;
            fast = fast->next->next;
        }
        return pre;
    }
};


/**
 * 653. 两数之和 IV - 输入 BST
 * 给定一个二叉搜索树和一个目标结果，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。
 *
 * 先用中序遍历获得升序列表，然后用双指针找目标值
 */
class Solution36 {
public:

    void fun(TreeNode *root, vector<int> &nums) {
        if (!root) return;
        fun(root->left, nums);
        nums.emplace_back(root->val);
        fun(root->right, nums);
    }

    bool findTarget(TreeNode *root, int k) {
        vector<int> nums;
        fun(root, nums); // 先中序遍历
        int i = 0, j = nums.size() - 1;
        while (i < j) { // 双指针找值
            int t = nums[i] + nums[j];
            if (t == k) return true;
            else if (t < k) i++;
            else j--;
        }
        return false;
    }
};


/**
 * 530. 二叉搜索树的最小绝对差
 * 给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。
 *
 * 利用二叉搜索树中序遍历的有序性来处理
 */
class Solution37 {
public:
    int pre_val = -1;
    int ans = INT32_MAX;

    void fun(TreeNode *root) {
        if (!root) return;
        fun(root->left);
        if (pre_val < 0) pre_val = root->val; // 记录中序遍历的上一个节点
        else {
            ans = min(root->val - pre_val, ans); // 在中序遍历过程中得到结果
            pre_val = root->val;
        }
        fun(root->right);
    }

    int getMinimumDifference(TreeNode *root) {
        fun(root);
        return ans;
    }
};

/**
 * 501. 二叉搜索树中的众数
 * 给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。
 *
 * 考虑到二叉搜索树的中序遍历是有序的，对中序遍历结果求众数即可，求众数可以通过一次遍历记录众数结果列表nums，当前重复次数curcnt和最大重复次数maxcnt来计算
 */
class Solution38 {
public:
    int maxcnt = 0;
    int curcnt = 0;
    TreeNode *prev = NULL; // 记录节点而不是int值，防止初始化重复

    void fun(TreeNode *root, vector<int> &nums) {
        if (!root) return;

        fun(root->left, nums);
        if (!prev || prev->val == root->val) {
            prev = root;
            curcnt++; // 增加重复次数
        }
        else {
            prev = root;
            curcnt = 1; // 新值，重新计算重复次数
        }

        if (curcnt > maxcnt) { // 更大的众数
            maxcnt = curcnt;
            nums.clear(); // 清空众数结果列表
            nums.emplace_back(root->val);
        } else if (curcnt == maxcnt) { // 相同重复次数的众数
            nums.emplace_back(root->val);
        }
        fun(root->right, nums);
    }

    vector<int> findMode(TreeNode *root) {
        vector<int> ans;
        fun(root, ans);
        return ans;
    }
};