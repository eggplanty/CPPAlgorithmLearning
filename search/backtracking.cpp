//
// Created by sen on 2020/6/3.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

/**
 * 17. 电话号码的字母组合
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
 * 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
 *
 * 给出了使用dfs和backtracking两种方法
 */
class Solution {
public:
    vector<vector<char>> map = {{},
                                {},
                                {'a', 'b', 'c'},
                                {'d', 'e', 'f'},
                                {'g', 'h', 'i'},
                                {'j', 'k', 'l'},
                                {'m', 'n', 'o'},
                                {'p', 'q', 'r', 's'},
                                {'t', 'u', 'v'},
                                {'w', 'x', 'y', 'z'}};
//    vector<string> dfs(string digits, int k) {
//        if (k >= digits.size())
//            return {""};
//
//        vector<string> ans;
//        vector<char> ws = map[int(digits[k]-'0')];
//        vector<string> ns = dfs(digits, k+1);
//
//        for (auto &w : ws)
//            for (auto &n : ns)
//                ans.emplace_back(w+n);
//
//        return ans;
//    }
//
//    vector<string> letterCombinations(string digits) {
//        if (digits.size() == 0) return {};
//        return dfs(digits, 0);
//    }
    vector<string> ans;

    void backtracking(string digits, int k, string prefix) {
        if (k >= digits.size()) {
            ans.emplace_back(prefix); // emplace_back(string)时是副本而不是指针
            return;
        }
        vector<char> ws = map[int(digits[k] - '0')];
        for (auto &w : ws) {
            prefix += w; //
            backtracking(digits, k + 1, prefix);
            prefix.pop_back();
        }
    }

    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};
        backtracking(digits, 0, "");
        return ans;
    }
};

/**
 * 93. 复原IP地址
 * 给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
 * 有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。
 */
class Solution2 {
public:

    vector<string> ans;

    void backtracking(vector<string> prefix, string s, int k) {
        if (k >= s.size() && prefix.size() == 4) {
            string tmp = "";
            for (auto &tt : prefix)
                tmp = tmp + tt + ".";

            tmp.pop_back();
            ans.emplace_back(tmp);
            return;
        } else if (k >= s.size() || prefix.size() == 4)
            return;

        for (int i = k + 1; i <= s.size(); i++) {
            int tmp = stoi(s.substr(k, i - k));
            if (tmp > 255 || s.substr(k, i - k) != to_string(tmp))
                break;

            prefix.emplace_back(to_string(tmp));
            backtracking(prefix, s, i);
            prefix.pop_back();
        }
    }

    vector<string> restoreIpAddresses(string s) {
        vector<string> prefix;

        backtracking(prefix, s, 0);
        return ans;
    }
};

/**
 * 79. 单词搜索
 * 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
 */
class Solution3 {
public:

    vector<vector<int>> direction = {{0,  1},
                                     {0,  -1},
                                     {1,  0},
                                     {-1, 0}};

    bool backtracking(vector<vector<char>> &board, string word, vector<vector<bool>> &visited, int i, int j, int k) {
        if (k == word.size())
            return true;

        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[k] || visited[i][j])
            return false;

        visited[i][j] = true;
        for (auto &d: direction) {
            int c = i + d[0], r = j + d[1];
            if (backtracking(board, word, visited, c, r, k + 1))
                return true;
        }
        visited[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>> &board, string word) {
        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));

        for (int i = 0; i < board.size(); i++)
            for (int j = 0; j < board[0].size(); j++) {
                if (backtracking(board, word, visited, i, j, 0))
                    return true;
            }
        return false;
    }
};


/**
 * 257. 二叉树的所有路径
 * 给定一个二叉树，返回所有从根节点到叶子节点的路径。
 * 说明: 叶子节点是指没有子节点的节点。
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution4 {
public:

    vector<string> ans;

    void backtracking(string prefix, TreeNode *p) {
        if (!p)
            return;

        if (!p->left && !p->right) {
            prefix += "->" + to_string(p->val);
            ans.emplace_back(prefix.substr(2, prefix.size() - 2));
            return;
        }

        backtracking(prefix + "->" + to_string(p->val), p->left);
        backtracking(prefix + "->" + to_string(p->val), p->right);
    }

    vector<string> binaryTreePaths(TreeNode *root) {
        backtracking("", root);
        return ans;
    }
};


/**
 * 46. 全排列
 * 给定一个 没有重复 数字的序列，返回其所有可能的全排列
 */
class Solution5 {
public:

    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<int>& nums, vector<bool>& mem) {
        if (prefix.size() == nums.size()) {
            ans.emplace_back(prefix);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!mem[i]) {
                mem[i] = true;
                prefix.emplace_back(nums[i]);
                backtracking(prefix, nums, mem);
                prefix.pop_back();
                mem[i] = false;
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> mem(nums.size(), false);
        backtracking(vector<int>(), nums, mem);
        return ans;
    }
};

/**
 * 47. 全排列 II
 * 给定一个可包含重复数字的序列，返回所有不重复的全排列。
 *
 * 防止重复的方法是先排序，然后再每次递归的时候判断当前位置和前一个位置的值是否相同，如果相同则判断前一个值是否已经被使用，
 * 如果未使用，则当前位置的值不能使用，因为会和取上一个位置的值，但是不去当前位置的值的情况重复。
 */
class Solution6 {
public:

    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<int>& nums, vector<bool>& mem) {
        if (prefix.size() == nums.size()) {
            ans.emplace_back(prefix);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (mem[i] || (i>0 && !mem[i-1] && nums[i] == nums[i-1]))
                continue;

            mem[i] = true;
            prefix.emplace_back(nums[i]);
            backtracking(prefix, nums, mem);
            prefix.pop_back();
            mem[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<bool> mem(nums.size(), false);
        backtracking(vector<int>(), nums, mem);
        return ans;
    }
};


/**
 * 77. 组合
 * 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
 */
class Solution7 {
public:

    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, int n, int k, int t) {
        if (prefix.size() == k) {
            ans.emplace_back(prefix);
            return;
        }

        for (int i = t; i <= n; i++) {
            prefix.emplace_back(i);
            backtracking(prefix, n, k, i+1);
            prefix.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        backtracking(vector<int>(), n, k, 1);
        return ans;
    }
};


/**
 * 39. 组合总和
 * 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 * candidates 中的数字可以无限制重复被选取。
 * 所有数字（包括 target）都是正整数。
 * 解集不能包含重复的组合。
 *
 * 不重复可以通过排序并且设定参数k，每次向后取来实现。
 */
class Solution8 {
public:

    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<int>& candidates, int t, int k) {
        if (t <= 0) {
            if (t == 0) ans.emplace_back(prefix);
            return;
        }

        for (int i = k; i < candidates.size(); i++) { // i=k，是为了不重复
            prefix.emplace_back(candidates[i]);
            backtracking(prefix, candidates,t-candidates[i], i); // 由于可以重复取同一个值，所以这里是i，不是i+1
            prefix.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(vector<int>(), candidates, target, 0);
        return ans;
    }
};

/**
 * 40. 组合总和 II
 * 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
 * candidates 中的每个数字在每个组合中只能使用一次。
 *  所有数字（包括目标数）都是正整数。
 *  解集不能包含重复的组合。
 */
class Solution9 {
public:
    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<bool> visited, vector<int>& candidates, int target, int k) {
        if (target == 0) {
            ans.emplace_back(prefix);
            return;
        }

        for (int i = k; i < candidates.size(); i++) {
            if (i > 0 && candidates[i] == candidates[i-1] && !visited[i-1])
                continue; // 典型的去除重复方法，排序+visited+前后判断

            if (target - candidates[i] >= 0) { // 将一部分终止条件放到了循环中，减少递归次数
                prefix.emplace_back(candidates[i]);
                visited[i] = true;
                backtracking(prefix, visited, candidates, target-candidates[i], i+1); // i+1保证每个数字只取一次
                visited[i] = false;
                prefix.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(vector<int>(), vector<bool>(candidates.size(), false), candidates ,target, 0);
        return ans;
    }
};

/**
 * 216. 组合总和 III
 * 找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
 *  所有数字都是正整数。
 *  解集不能包含重复的组合。
 */
class Solution10 {
public:
    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, int k, int n, int t) {
        if (n == 0 && k == 0) {
            ans.emplace_back(prefix);
            return;
        }
        if (k < 0 || n < 0) return;

        for (int i = t; i < 10; i++) {
            prefix.emplace_back(i); // backtracking的push经常是在for循环里面
            backtracking(prefix, k-1, n-i, i+1);
            prefix.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(vector<int>(), k, n, 1);
        return ans;
    }
};

/**
 * 78. 子集
 * 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。
 */
class Solution11 {
public:
    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<int> nums, int k) {
        ans.emplace_back(prefix);

        for (int i = k; i < nums.size(); i++) {
            prefix.emplace_back(nums[i]);
            backtracking(prefix, nums, i+1);
            prefix.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(vector<int>(), nums, 0);
        return ans;
    }
};

/**
 * 90. 子集 II
 * 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。
 */
class Solution12 {
public:
    vector<vector<int>> ans;

    void backtracking(vector<int> prefix, vector<bool> visited, vector<int> nums, int k) {
        ans.emplace_back(prefix);

        for (int i = k; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) continue;

            prefix.emplace_back(nums[i]);
            visited[i] = true;
            backtracking(prefix, visited, nums, i+1);
            visited[i] = false;
            prefix.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(vector<int>(), vector<bool>(nums.size(), false), nums, 0);
        return ans;
    }
};

/**
 * 131. 分割回文串
 * 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
 * 返回 s 所有可能的分割方案。
 */
class Solution13 {
public:
    vector<vector<string>> ans;
    bool fun(string s, int start, int end) {
        while (start < end) // 双指针的快速写法
            if (s[start++] != s[end--])
                return false;
        return true;
    }

    void backtracking(vector<string> prefix, string s, int k) {
        if (k == s.size()) {
            ans.emplace_back(prefix);
            return;
        }

        for (int i = k; i < s.size(); i++) {
            if (!fun(s, k, i)) continue;
            prefix.emplace_back(s.substr(k, i-k+1));
            backtracking(prefix, s, i+1);
            prefix.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        backtracking(vector<string>(), s, 0);
        return ans;
    }
};

/**
 * 37. 解数独
 * 编写一个程序，通过已填充的空格来解决数独问题。
 * 一个数独的解法需遵循如下规则：
 *  1.数字 1-9 在每一行只能出现一次。
 *  2.数字 1-9 在每一列只能出现一次。
 *  3.数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
 * 空白格用 '.' 表示。
 */
class Solution14 {
public:
    int R = 9, C = 9;
    // 类变量需要先定义在初始化，所以需要这么写
    // 记录三个规则是否满足
    vector<vector<bool>> rowused = vector<vector<bool>>(9, vector<bool>(10, false));
    vector<vector<bool>> colused = vector<vector<bool>>(9, vector<bool>(10, false));
    vector<vector<bool>> cubeused = vector<vector<bool>>(9, vector<bool>(10, false));

    int cubenum(int i, int j) { // cube计算
        int r = i / 3;
        int c = j / 3;
        return r * 3 + c;
    }

    bool backtracking(vector<vector<char>> &board, int r, int c) {

        // 不使用双层for循环遍历，而是使用while循环来查找下一个位置，有效降低时间开销
        while (r < R && board[r][c] != '.') {
            r = c == C-1 ? r+1 : r;
            c = c == C-1 ? 0: c+1;
        }
        if (r == R) return true;

        for (int k = 1; k < 10; k++) {

            if (rowused[r][k] || colused[c][k] || cubeused[cubenum(r, c)][k]) continue;

            rowused[r][k] = colused[c][k] = cubeused[cubenum(r, c)][k] = true;
            board[r][c] = '0'+k;
            if (backtracking(board, r, c)) return true;
            board[r][c] = '.';
            rowused[r][k] = colused[c][k] = cubeused[cubenum(r, c)][k] = false;
        }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                if (board[i][j] == '.') continue;
                int k = board[i][j] - '0';
                rowused[i][k] = colused[j][k] = cubeused[cubenum(i, j)][k] = true;
            }
        backtracking(board, 0, 0);
    }
};

/**
 * 51. N皇后
 * n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
 * 每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 *
 */
class Solution15 {
public:
    vector<bool> colused;
    vector<bool> q45used;
    vector<bool> q135used;

    vector<vector<string>> ans;

    void backtracking(int n, vector<string> qq, int row) {
        if (row == n) {
            ans.emplace_back(qq);
            return;
        }

        for (int j = 0; j < n; j++) {
            int q135id = n-1-(row-j);
            if (colused[j] || q45used[row+j] || q135used[q135id]) continue;

            colused[j] = q45used[row+j] = q135used[q135id] = true;
            qq[row][j] = 'Q';
            backtracking(n, qq, row+1);
            qq[row][j] = '.';
            colused[j] = q45used[row+j] = q135used[q135id] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        colused = vector<bool>(n, false);
        q45used = vector<bool>(2*n-1, false);
        q135used = vector<bool>(2*n-1, false);
        backtracking(n, vector<string>(n, string(n, '.')), 0);
        return ans;
    }
};