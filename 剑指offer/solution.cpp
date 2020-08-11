#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

/**
 * 剑指 Offer 03. 数组中重复的数字
 */
class Solution {
public:
    int findRepeatNumber(vector<int> &nums) {
        if (nums.size() <= 1) return -1;
        for (int i = 0; i < nums.size(); ++i) {
            while (nums[i] != i) {
                if (nums[nums[i]] == nums[i])
                    return nums[i];
                else
                    swap(nums[i], nums[nums[i]]);
            }
        }
        return -1;
    }
};

/**
 * 剑指 Offer 04. 二维数组中的查找
 */
class Solution2 {
public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target) {
        if (matrix.size() == 0) return false;
        int R = matrix.size(), C = matrix[0].size();
        int i = 0, j = C - 1;
        while (i < R && j >= 0) {
            if (matrix[i][j] == target) return true;
            else if (matrix[i][j] > target) j--;
            else i++;
        }
        return false;
    }
};

/**
 * 剑指 Offer 05. 替换空格
 */
class Solution3 {
public:
    string replaceSpace(string s) {
        int cnt = 0, n = s.size();
        for (int i = 0; i < n; ++i)
            if (s[i] == ' ') cnt++;

        s += string(cnt * 2, ' ');
        int m = s.size();

        for (int i = n - 1, j = m - 1; i >= 0 && j >= 0;) {
            if (s[i] == ' ') {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
                i--;
            } else
                s[j--] = s[i--];
        }
        return s;
    }
};

/**
 * 剑指 Offer 06. 从尾到头打印链表
 * 面试常考的是头插法，递归法和压栈法
 */
class Solution4 {
public:
    vector<int> reversePrint(ListNode *head) {
        vector<int> tmp;
        while (head) {
            tmp.push_back(head->val);
            head = head->next;
        }
        reverse(tmp.begin(), tmp.end());
        return tmp;
    }
};

/**
 * 剑指 Offer 07. 重建二叉树
 */
class Solution {
public:
    map<int, int> mp;

    TreeNode *dfs(vector<int> &pre, int l, int r, int inl) {
        if (l > r) return NULL;
        TreeNode *root = new TreeNode(pre[l]);
        int idx = mp[pre[l]];
        int len = idx - inl;
        root->left = dfs(pre, l + 1, l + len, inl);
        root->right = dfs(pre, l + len + 1, r, idx + 1);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        for (int i = 0; i < inorder.size(); ++i) mp[inorder[i]] = i;
        return dfs(preorder, 0, preorder.size() - 1, 0);
    }
};


/**
 * 剑指 Offer 09. 用两个栈实现队列
 */
class CQueue {
public:
    vector<int> v1;
    vector<int> v2;

    CQueue() {

    }

    void appendTail(int value) {
        v1.push_back(value);
    }

    int deleteHead() {
        if (v2.empty()) {
            while (!v1.empty()) {
                v2.push_back(v1.back());
                v1.pop_back();
            }
        }
        if (v2.empty()) return -1;
        int tmp = v2.back();
        v2.pop_back();
        return tmp;
    }
};

/**
 * 剑指 Offer 10- I. 斐波那契数列
 */
class Solution {
public:

    int M = 1000000007;

    int fib(int n) {
        if (n <= 1) return n;
        int f1 = 1, f2 = 0;
        for (int i = 2; i <= n; ++i) {
            int tmp = (f1 + f2) % M;
            f2 = f1;
            f1 = tmp;
        }
        return f1;
    }
};

/**
 * 剑指 Offer 10- II. 青蛙跳台阶问题
 */
class Solution {
public:
    int M = 1000000007;
    int numWays(int n) {
        if (n <= 1) return 1;
        int f1 = 1, f2 = 1;
        for (int i = 2; i <= n; ++i) {
            int tmp = (f1 + f2) % M;
            f2 = f1;
            f1 = tmp;
        }
        return f1;
    }
};

/**
 * 剑指 Offer 11. 旋转数组的最小数字
 */
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int i = 0, j = numbers.size()-1;
        while (i < j) {
            int m = i + (j-i) / 2;
            if (numbers[m] > numbers[j]) i = m+1;
            else if (numbers[m] < numbers[j]) j = m; // 小于时该位置也可能时最小值
            else j -= 1; // 不能是i+=1，那样会错过1,3,3的1，也就是有序序列的最小值
        }
        return numbers[i];
    }
};


/**
 * 剑指 Offer 12. 矩阵中的路径
 */
class Solution {
public:

    vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    bool backtracking(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, string word, int k) {
        int n = board.size(), m = board[0].size();
        if (k == word.size()) return true;
        if (i<0 || j<0 || i>=n || j>=m || visited[i][j] || word[k] != board[i][j]) return false;

        visited[i][j] = true;
        for (auto d : directions) {
            if (backtracking(board, visited, i+d[0],j+d[1], word, k+1))
                return true;
        }
        visited[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (backtracking(board, visited, i, j, word, 0))
                    return true;
        return false;
    }
};

/**
 * 剑指 Offer 13. 机器人的运动范围
 */
class Solution {
public:
    vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};

    int fun(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    int dfs(vector<vector<bool>> &visited, int m, int n, int k, int i, int j) {
        if (i<0 || j<0 || i>=m ||j>=n || visited[i][j] || fun(i) + fun(j) > k) return 0;
        visited[i][j] = true;
        int cnt = 0;
        for (auto d : directions)
            cnt += dfs(visited, m, n, k, i+d[0], j+d[1]);
        return 1 + cnt;
    }

    int movingCount(int m, int n, int k) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        return dfs(visited, m, n, k, 0, 0);
    }
};


/**
 * 剑指 Offer 14- I. 剪绳子
 */
class Solution {
public:
    int cuttingRope(int n) {
        // dp[i] = 长度为i时最大乘积
        // dp[i] = max{dp[j] * (i-j), j*(i-j)}

        vector<int> dp(n+1, 0);
        dp[2] = 1, dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j < i; ++j)
                dp[i] = max(dp[i], max(dp[j] * (i-j), j*(i-j)));
        return dp[n];
    }
};