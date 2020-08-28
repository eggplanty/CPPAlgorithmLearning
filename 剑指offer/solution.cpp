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
    int minArray(vector<int> &numbers) {
        int i = 0, j = numbers.size() - 1;
        while (i < j) {
            int m = i + (j - i) / 2;
            if (numbers[m] > numbers[j]) i = m + 1;
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

    vector<vector<int>> directions = {{1,  0},
                                      {-1, 0},
                                      {0,  1},
                                      {0,  -1}};

    bool backtracking(vector<vector<char>> &board, vector<vector<bool>> &visited, int i, int j, string word, int k) {
        int n = board.size(), m = board[0].size();
        if (k == word.size()) return true;
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || word[k] != board[i][j]) return false;

        visited[i][j] = true;
        for (auto d : directions) {
            if (backtracking(board, visited, i + d[0], j + d[1], word, k + 1))
                return true;
        }
        visited[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>> &board, string word) {
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
    vector<vector<int>> directions = {{0,  1},
                                      {0,  -1},
                                      {1,  0},
                                      {-1, 0}};

    int fun(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    int dfs(vector<vector<bool>> &visited, int m, int n, int k, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || fun(i) + fun(j) > k) return 0;
        visited[i][j] = true;
        int cnt = 0;
        for (auto d : directions)
            cnt += dfs(visited, m, n, k, i + d[0], j + d[1]);
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

        vector<int> dp(n + 1, 0);
        dp[2] = 1, dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 1; j < i; ++j)
                dp[i] = max(dp[i], max(dp[j] * (i - j), j * (i - j)));
        return dp[n];
    }

    int cuttingRope(int n) {
        // 尽可能拆3
        if (n <= 2) return 1;
        if (n == 3) return 2;

        int ans = 1;
        while (n > 4) {
            ans *= 3;
            n -= 3;
        }
        ans *= n;

        return ans;
    }
};


/**
 * 剑指 Offer 14- II. 剪绳子 II
 * 不能用dp，否则取模会出错
 */
class Solution {
public:
    int M = 1e9 + 7;

    inline long fun(int x, int a, int m) {
        long rem = 1;
        while (a-- > 0)
            rem = ((rem % m) * x) % m;
        return rem;
    }

    int cuttingRope(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        if (n == 4) return 4;
        if (n == 5) return 6;

        int a = n / 3;
        int b = n % 3;
        if (b == 0)
            return fun(3, a, M);
        else if (b == 1)
            return fun(3, a - 1, M) * 4 % M;
        else
            return fun(3, a, M) * 2 % M;
    }

    int cuttingRope(int n) {
        if (n <= 2) return 1;
        if (n == 3) return 2;

        long ans = 1;
        while (n > 4) {
            ans = (ans * 3) % M;
            n -= 3;
        }
        ans = (ans * n) % M;
        return ans;
    }
};


/**
 * 剑指 Offer 15. 二进制中1的个数
 */
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while (n > 0) {
            if (n & 1) cnt++;
            n = n >> 1;
        }
        return cnt;
    }
};


/**
 * 剑指 Offer 16. 数值的整数次方
 */
class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) return 0; // 防止n<0时1/x出错
        long ln = n;
        if (ln < 0) x = 1 / x, ln = -ln; // n有可能为INT32_MAX，取负数超出下界
        double res = 1.0;
        while (ln) {
            if (ln & 1) res *= x; // 必然会走到n==1，将之间没乘的x一次乘完
            x *= x;
            ln /= 2;
        }
        return res;
    }
};

/**
 * 剑指 Offer 17. 打印从1到最大的n位数
 */
class Solution {
public:

    vector<int> ans;

    void dfs(int n, string prefix) {
        if (n == 0) {
            // if (prefix.size() != 0 && prefix[0] != '0')
            int tmp = stoi(prefix);
            if (tmp != 0)
                ans.push_back(tmp);
            return;
        }

        for (int i = 0; i < 10; ++i)
            dfs(n - 1, prefix + to_string(i));
    }

    vector<int> printNumbers(int n) {
        dfs(n, "");
        return ans;
    }
};


/**
 * 剑指 Offer 18. 删除链表的节点
 */
class Solution {
public:
    ListNode *deleteNode(ListNode *head, int val) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *p = dummy;
        while (p && p->next) {
            if (p->next->val == val)
                p->next = p->next->next;
            p = p->next;
        }
        return dummy->next;
    }
};

/**
 * 剑指 Offer 19. 正则表达式匹配
 */
class Solution {
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


/**
 * 剑指 Offer 20. 表示数值的字符串
 */
class Solution {
public:

    bool isNumber(string s) {
        vector<map<char, int>> vm = {
                {{'b', 0}, {'s', 1}, {'d', 2}, {'.', 4}},
                {{'.', 4}, {'d', 2}},
                {{'d', 2}, {'.', 3}, {'b', 8}, {'e', 5}},
                {{'d', 3}, {'e', 5}, {'b', 8}},
                {{'d', 3}},
                {{'s', 6}, {'d', 7}},
                {{'d', 7}},
                {{'d', 7}, {'b', 8}},
                {{'b', 8}}
        };
        set<int> st = {2, 3, 7, 8};
        int p = 0;
        for (auto c: s) {
            char k;
            if (c >= '0' && c <= '9') k = 'd';
            else if (c == ' ') k = 'b';
            else if (c == '.') k = '.';
            else if (c == 'e') k = 'e';
            else if (c == '+' || c == '-') k = 's';
            else return false;
            if (vm[p].count(k) <= 0) return false;
            p = vm[p][k];
        }
        return st.count(p) > 0;
    }
};


/**
 * 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
 */
class Solution {
public:
    vector<int> exchange(vector<int> &nums) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            while (i < j && nums[i] & 1) i++;
            while (i < j && !(nums[j] & 1)) j--;
            swap(nums[i++], nums[j--]);
        }
        return nums;
    }

    vector<int> exchange(vector<int> &nums) {
        for (int i = nums.size() - 1; i >= 0; --i) {
            bool flag = true;
            for (int j = 0; j < i; ++j)
                if (nums[j] % 2 == 0 && nums[j + 1] % 2 == 1) {
                    swap(nums[j], nums[j + 1]);
                    flag = false;
                }
            if (flag)
                break;
        }
        return nums;
    }
};


/**
 * 剑指 Offer 22. 链表中倒数第k个节点
 */
class Solution {
public:
    ListNode *getKthFromEnd(ListNode *head, int k) {
        ListNode *p = head;
        while (k-- > 0)
            p = p->next;

        while (p) {
            head = head->next;
            p = p->next;
        }
        return head;
    }
};


/**
 * 剑指 Offer 24. 反转链表
 */
class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *dummy = new ListNode(-1);
        while (head) {
            ListNode *tmp = head->next;
            head->next = dummy->next;
            dummy->next = head;
            head = tmp;
        }
        return dummy->next;
    }

    ListNode *reverseList(ListNode *head) {
        if (!head || !head->next) return head;
        ListNode *nt = head->next;
        ListNode *newhead = reverseList(nt);
        head->next = nt->next;
        nt->next = head;
        return newhead;
    }
};


/**
 * 剑指 Offer 25. 合并两个排序的链表
 */
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *p = dummy;
        while (l1 && l2) {
            if (l1->val > l2->val) {
                p->next = l2;
                l2 = l2->next;
            } else {
                p->next = l1;
                l1 = l1->next;
            }
            p = p->next;
        }
        if (!l1) p->next = l2;
        if (!l2) p->next = l1;
        return dummy->next;
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->val > l2->val) {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        } else {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
    }
};


/**
 * 剑指 Offer 26. 树的子结构
 */
class Solution {
public:
    bool fun(TreeNode *A, TreeNode *B) {
        if (!B) return true;
        if (!A) return false;
        if (A->val != B->val) return false;
        return fun(A->left, B->left) && fun(A->right, B->right);
    }

    bool isSubStructure(TreeNode *A, TreeNode *B) {
        if (!B || !A) return false;

        return fun(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};


/**
 * 剑指 Offer 27. 二叉树的镜像
 */
class Solution {
public:
    TreeNode *mirrorTree(TreeNode *root) {
        if (!root) return NULL;
        TreeNode *tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }
};


/**
 * 剑指 Offer 28. 对称的二叉树
 */
class Solution {
public:

    bool fun(TreeNode *ll, TreeNode *rr) {
        if (!ll && !rr) return true;
        if (!ll || !rr) return false;

        if (ll->val != rr->val) return false;
        return fun(ll->left, rr->right) && fun(ll->right, rr->left);
    }

    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        return fun(root->left, root->right);
    }
};


/**
 * 剑指 Offer 29. 顺时针打印矩阵
 */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.size() == 0) return {};
        int l = 0, r = matrix[0].size() - 1, u = 0, d = matrix.size() - 1, t = 0;
        vector<int> res((r + 1) * (d + 1), 0);
        while (true) {
            for (int i = l; i <= r; ++i) res[t++] = matrix[u][i];
            if (++u > d) break;
            for (int i = u; i <= d; ++i) res[t++] = matrix[i][r];
            if (--r < l) break;
            for (int i = r; i >= l; --i) res[t++] = matrix[d][i];
            if (--d < u) break;
            for (int i = d; i >= u; --i) res[t++] = matrix[i][l];
            if (++l > r) break;
        }
        return res;
    }
};


/**
 * 剑指 Offer 31. 栈的压入、弹出序列
 */
class Solution {
public:
    bool validateStackSequences(vector<int> &pushed, vector<int> &popped) {
        vector<int> stack;
        for (int i = 0, j = 0; i < pushed.size(); ++i) {
            stack.push_back(pushed[i]);
            while (!stack.empty() && j < popped.size() && stack.back() == popped[j]) {
                j++;
                stack.pop_back();
            }
        }
        return stack.empty();
    }
};

/**
 * 剑指 Offer 32 - I. 从上到下打印二叉树
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode *root) {
        if (!root) return {};
        queue < TreeNode * > q;
        q.push(root);
        vector<int> res;
        while (!q.empty()) {
            int size = q.size();
            while (size-- > 0) {
                auto tmp = q.front();
                q.pop();
                res.push_back(tmp->val);
                if (tmp->left) q.push(tmp->left);
                if (tmp->right) q.push(tmp->right);
            }
        }
        return res;
    }
};


/**
 * 剑指 Offer 32 - II. 从上到下打印二叉树 II
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> ans;
        queue < TreeNode * > q;
        q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> one;
            while (sz-- > 0) {
                TreeNode *tmp = q.front();
                q.pop();
                if (tmp) {
                    one.push_back(tmp->val);
                    q.push(tmp->left);
                    q.push(tmp->right);
                }
            }
            if (!one.empty())
                ans.push_back(one);
        }
        return ans;
    }
};


/**
 * 剑指 Offer 32 - III. 从上到下打印二叉树 III
 * 先从左到右，再从右到左
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> ans;
        queue < TreeNode * > q;
        q.push(root);
        int k = 0;
        while (!q.empty()) {
            int sz = q.size();
            deque<int> one;
            k++;
            while (sz-- > 0) {
                TreeNode *tmp = q.front();
                q.pop();
                if (tmp) {
                    if (k & 1)
                        one.push_back(tmp->val);
                    else
                        one.push_front(tmp->val);

                    q.push(tmp->left);
                    q.push(tmp->right);
                }
            }
            if (!one.empty())
                ans.push_back(vector<int>(one.begin(), one.end()));
        }
        return ans;
    }
};


/**
 * 剑指 Offer 33. 二叉搜索树的后序遍历序列
 */
class Solution {
public:
    bool recur(vector<int> &nums, int i, int j) {
        if (i >= j) return true;
        int root = nums[j];
        int m = 0;
        while (nums[m] < root) m++; // i->m-1为左子树
        int k = m; // 判断m->j-1是否都大于root
        while (nums[k] > root) k++;
        if (k != j) return false;
        return recur(nums, i, m - 1) && recur(nums, m, j - 1);
    }

    bool verifyPostorder(vector<int> &postorder) {
        // 左子树 | 右子树 | 根
        if (postorder.size() == 0) return true;
        int i = 0, j = postorder.size() - 1;
        return recur(postorder, i, j);
    }
};


/**
 * 剑指 Offer 34. 二叉树中和为某一值的路径
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        if (!root) return {};
        if (!root->left && !root->right && sum == root->val) return {{root->val}};

        auto ll = pathSum(root->left, sum - root->val);
        auto rr = pathSum(root->right, sum - root->val);
        vector<vector<int>> ans;
        for (int i = 0; i < ll.size(); ++i) {
            vector<int> one = {root->val};
            for (int j = 0; j < ll[i].size(); ++j)
                one.push_back(ll[i][j]);
            ans.push_back(one);
        }

        for (int i = 0; i < rr.size(); ++i) {
            vector<int> one = {root->val};
            for (int j = 0; j < rr[i].size(); ++j)
                one.push_back(rr[i][j]);
            ans.push_back(one);
        }
        return ans;
    }
};


/**
 * 剑指 Offer 35. 复杂链表的复制
 */
class Solution {
public:
    Node *copyRandomList(Node *head) {
        map<Node *, Node *> mp;
        Node *p = head;
        while (p) {
            Node *cp = new Node(p->val);
            mp[p] = cp;
            p = p->next;
        }
        p = head;
        while (p) {
            mp[p]->next = mp[p->next];
            mp[p]->random = mp[p->random];
            p = p->next;
        }
        return mp[head];
    }
};


/**
 * 剑指 Offer 36. 二叉搜索树与双向链表
 */
class Solution {
public:
    Node *prev = NULL;
    Node *head = NULL;

    void dfs(Node *root) {
        if (!root) return;
        dfs(root->left);
        if (!head) head = root;
        if (prev) prev->right = root;
        root->left = prev;
        prev = root;
        dfs(root->right);
    }

    Node *treeToDoublyList(Node *root) {
        if (!root) return root;
        dfs(root);
        head->left = prev;
        prev->right = head;
        return head;
    }
};


/**
 * 剑指 Offer 37. 序列化二叉树
 * 层序遍历
 * 或者通过先序加中序
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode *root) {
        queue < TreeNode * > q;
        q.push(root);
        string ans = "";
        while (!q.empty()) {
            int sz = q.size();
            while (sz-- > 0) {
                TreeNode *tmp = q.front();
                q.pop();
                string s = "null";
                if (tmp) {
                    q.push(tmp->left);
                    q.push(tmp->right);
                    s = to_string(tmp->val);
                }
                ans += s + " ";
            }
        }
        ans = ans.substr(0, ans.size() - 1);
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) {
        vector<TreeNode *> vt;

        istringstream in(data);
        string temp;
        while (in >> temp) {
            if (temp == "null") vt.push_back(NULL);
            else {
                vt.push_back(new TreeNode(stoi(temp)));
            }
        }

        int cnt = 0;
        for (int i = 0; i < vt.size(); ++i) {
            if (!vt[i]) {
                cnt++;
                continue;
            }
            if (2 * (i - cnt) + 1 >= vt.size()) break;
            vt[i]->left = vt[2 * (i - cnt) + 1];
            vt[i]->right = vt[2 * (i - cnt) + 2];
        }
        return vt[0];
    }
};


/**
 * 剑指 Offer 38. 字符串的排列
 */
class Solution {
public:
    vector<string> ans;

    void backtracking(string s, string prefix, vector<bool> visited) {
        if (prefix.size() == s.size()) {
            ans.push_back(prefix);
            return;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (visited[i] || (i > 0 && s[i] == s[i - 1] && !visited[i - 1])) continue;
            visited[i] = true;
            backtracking(s, prefix + s[i], visited);
            visited[i] = false;
        }
    }

    vector<string> permutation(string s) {
        sort(s.begin(), s.end());
        vector<bool> visited(s.size(), false);
        backtracking(s, "", visited);
        return ans;
    }
};


/**
 * 剑指 Offer 39. 数组中出现次数超过一半的数字
 */
class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int cnt = 1, n = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (n == nums[i]) {
                cnt++;
                continue;
            }
            if (cnt == 0) {
                n = nums[i];
                cnt = 1;
            } else
                cnt--;
        }
        return n;
    }
};


/**
 * 剑指 Offer 40. 最小的k个数
 */
class Solution {
public:
    vector<int> getLeastNumbers(vector<int> &arr, int k) {
        if (k == 0) return {};
        priority_queue<int, vector<int>, less<int>> pq;
        for (int i = 0; i < arr.size(); ++i) {
            if (pq.size() >= k && pq.top() <= arr[i])
                continue;

            pq.push(arr[i]);
            if (pq.size() > k)
                pq.pop();
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top());
            pq.pop();
        }
        return ans;
    }
};


/**
 * 剑指 Offer 41. 数据流中的中位数
 * 这种做法不好，应该使用大顶堆小顶堆来做
 */
class MedianFinder {
public:
    /** initialize your data structure here. */
    deque<int> v;

    MedianFinder() {

    }

    void addNum(int num) {
        int i = 0, j = v.size();
        while (i < j) {
            int m = i + (j - i) / 2;
            if (v[m] >= num)
                j = m;
            else
                i = m + 1;
        }
        v.insert(v.begin() + i, num);
    }

    double findMedian() {
        if (v.size() & 1) return v[v.size() / 2];
        else return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0;
    }
};


/**
 * 剑指 Offer 42. 连续子数组的最大和
 */
class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        int cur = nums[0], mm = cur;
        for (int i = 1; i < nums.size(); ++i) {
            if (cur < 0)
                cur = nums[i];
            else
                cur += nums[i];
            mm = max(cur, mm);
        }
        return mm;
    }
};


/**
 * 剑指 Offer 43. 1～n整数中1出现的次数
 */
class Solution {
public:
    int f(int n) {
        if (n == 0) return 0;
        int pow = 1, t = n;
        while (t >= 10) {
            pow *= 10;
            t /= 10;
        }
        int last = n % pow, high = n / pow;
        if (high == 1) return f(pow - 1) + last + 1 + f(last);
        return pow + high * f(pow - 1) + f(last);
    }

    int countDigitOne(int n) {
        return f(n);
    }
};


/**
 * 剑指 Offer 44. 数字序列中某一位的数字
 */
class Solution {
public:
    int findNthDigit(int n) {
        long start = 1, digit = 1, count = 9;
        while (n > count) { // 说明n在该数位的数值范围内
            n = n - count;
            digit++;
            start *= 10;
            count = 9 * start * digit;
        }
        int num = start + (n - 1) / digit; // 确定属于该数值范围内的某个数字
        return to_string(num)[(n - 1) % digit] - '0';// 确定属于该数字的位数
    }
};


/**
 * 剑指 Offer 45. 把数组排成最小的数
 */
class Solution {
public:
    string minNumber(vector<int> &nums) {
        vector<string> tmp;
        for (int n : nums)
            tmp.push_back(to_string(n));
        sort(tmp.begin(), tmp.end(), [](string a, string b) {
            if (a + b < b + a) return true;
            else return false;
        });
        string ans = "";
        for (string s : tmp)
            ans += s;
        return ans;
    }
};


/**
 * 剑指 Offer 46. 把数字翻译成字符串
 */
class Solution {
public:
    int translateNum(int num) {
        // dp[i] = 前i个数字有多少种翻译方法
        // dp[i] = dp[i-1] + dp[i-2]  if (num[i-1]+num[i] < 26)

        string s = to_string(num);
        int dp1 = 1, dp2 = 1;
        for (int i = 1; i < s.size(); ++i) {
            string sk = s.substr(i - 1, 2);
            int k = stoi(sk);
            if (k >= 10 && k < 26) {
                int tmp = dp1 + dp2;
                dp2 = dp1;
                dp1 = tmp;
            } else
                dp2 = dp1;
        }
        return dp1;
    }
};


/**
 * 剑指 Offer 47. 礼物的最大价值
 */
class Solution {
public:
    int maxValue(vector<vector<int>> &grid) {
        // dp[i][j] = 第i行第j列最多能达到的礼物价值
        // dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + grid[i][j]

        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
        return dp[n][m];
    }

    int maxValue(vector<vector<int>> &grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> dp(m + 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                dp[j] = max(dp[j], dp[j - 1]) + grid[i - 1][j - 1];
            }
        return dp[m];
    }
};

/**
 * 剑指 Offer 48. 最长不含重复字符的子字符串
 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // dp[i] = 以i结尾的最长子序列的长度
        // dp[i] = dp[i-1] + 1    if dp[i-1] < i-j    ,s[i] == s[j]，j为上一个与s[i]相等的位置
        //       = i-j            if dp[i-1] >= i-j
        // 如何快速求i？如何快速求与当前坐标值相同的上一个值的坐标?
        // 哈希表记录最后一个相同值的坐标

        vector<int> mp(256, -1);
        vector<int> dp(s.size() + 1, 0);
        int maxlen = 0;
        for (int i = 1; i <= s.size(); ++i) {
            int idx = mp[s[i - 1]];
            if (dp[i - 1] < i - 1 - idx)
                dp[i] = dp[i - 1] + 1;
            else
                dp[i] = i - 1 - idx;

            mp[s[i - 1]] = i - 1;
            maxlen = max(maxlen, dp[i]);
        }
        return maxlen;
    }
};


/**
 * 剑指 Offer 49. 丑数
 */
class Solution {
public:
    int nthUglyNumber(int n) {
        // dp[i] = 第i个丑数
        // dp[i] = min{dp[a]*2, dp[b]*3, dp[c]*5}, 为了使丑数最小，要求dp[a,b,c]为第一组*235后大于dp[i-1]的abc
        // dp数组的作用是提供历史上的丑数，新的丑数是基于历史丑数做235的乘法得到的，这样可以防止引入235之外的质数。
        vector<int> dp(n + 1, 0);
        int a = 1, b = 1, c = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = min(dp[a] * 2, min(dp[b] * 3, dp[c] * 5));
            if (dp[i] == dp[a] * 2) a++;
            if (dp[i] == dp[b] * 3) b++; // 由于dp[i] 可能同时等于多个，所以这里不能用else
            if (dp[i] == dp[c] * 5) c++;
        }
        return dp[n];
    }
};

/**
 * 剑指 Offer 50. 第一个只出现一次的字符
 */
class Solution {
public:
    char firstUniqChar(string s) {
        vector<int> v(256, 0);
        for (auto c: s)
            v[int(c)]++;

        for (auto c : s)
            if (v[int(c)] == 1) return c;

        return ' ';
    }

    char firstUniqChar(string s) {
        vector<int> v(256); // 记录字符出现的位置，减少二次遍历字符出串s获取先后顺序
        for (int i = 0; i < s.size(); ++i) {
            if (v[s[i]] > 0) v[s[i]] = -1;
            else if (v[s[i]] < 0) continue;
            else v[s[i]] = i + 1;
        }

        int minval = INT32_MAX;
        char c = ' ';
        for (int i = 0; i < v.size(); ++i)
            if (v[i] > 0) {
                if (v[i] < minval) {
                    c = i;
                    minval = v[i];
                }
            }

        return c;
    }
};

/**
 * 剑指 Offer 51. 数组中的逆序对
 */
class Solution {
public:
    vector<int> tmp;

    int merge(vector<int> &nums, int l, int r, int m) {
        int i = l, j = m + 1;
        for (int k = l; k <= r; ++k) tmp[k] = nums[k];

        int cnt = 0;
        for (int k = l; k <= r; k++) {
            if (j > r) {
                nums[k] = tmp[i++];
                cnt += r - m; // 如果超出右边界，则右序列的所有值都可以构成逆序列
            } else if (i > m) nums[k] = tmp[j++];
            else if (tmp[i] <= tmp[j]) {
                nums[k] = tmp[i++];
                cnt += j - m - 1; // 右边界和m之间的值可以构成逆序列
            } else nums[k] = tmp[j++];
        }
        return cnt;
    }

    int mergesort(vector<int> &nums, int i, int j) {
        if (i >= j) return 0;
        int m = i + (j - i) / 2;
        int cnt = mergesort(nums, i, m) + mergesort(nums, m + 1, j);
        return cnt + merge(nums, i, j, m);
    }

    int reversePairs(vector<int> &nums) {
        // 归并排序的应用
        tmp = vector<int>(nums.size(), 0);
        return mergesort(nums, 0, nums.size() - 1);
    }
};


/**
 * 剑指 Offer 52. 两个链表的第一个公共节点
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA, *p2 = headB;
        while (p1 != p2) {
            if (!p1) p1 = headB;
            else p1 = p1->next;
            if (!p2) p2 = headA;
            else p2 = p2->next;
        }
        return p1;
    }
};


/**
 * 剑指 Offer 53 - I. 在排序数组中查找数字 I
 */
class Solution {
public:
    int fun(vector<int> nums, int target) {
        int i = 0, j = nums.size();
        while (i < j) {
            int m = i + (j - i) / 2;
            if (nums[m] >= target)
                j = m;
            else
                i = m + 1;
        }
        return i;
    }

    int search(vector<int> &nums, int target) {
        return fun(nums, target + 1) - fun(nums, target);
    }

    // 另一种写法
    int search(vector<int> &nums, int target) {
        auto fun = [](vector<int> &v, int x) {
            int l = 0, r = v.size();
            while (l < r) {
                int mid = (l + r) >> 1;
                if (v[mid] >= x) r = mid; else l = mid + 1;
            }
            return l;
        };

        int t1 = fun(nums, target);
        if (t1 == nums.size() || nums[t1] != target) return 0;
        int t2 = fun(nums, target + 1);
        return t2 - t1;
    }
};

/**
 * 剑指 Offer 53 - II. 0～n-1中缺失的数字
 */
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i = 0, j = nums.size();
        while (i < j) {
            int m = i + (j-i) / 2;
            if (nums[m] > m)
                j = m;
            else
                i = m + 1;
        }
        return i;
    }

    int missingNumber(vector<int>& nums) {
        int l = 0, r = nums.size();
        while (l < r) {
            int mid = (l+r) >> 1; // 如果是 l = mid，则需要考虑死循环的情况，因为 l+r >> 1可以取到l， 所以需要改成 l+r+1 >> 1
            if (nums[mid] > mid) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};


/**
 * 剑指 Offer 54. 二叉搜索树的第k大节点
 */
class Solution {
public:
    int val = 0;
    void fun(TreeNode *node, int &k) {
        if (!node) return;
        fun(node->right, k); // 右节点 | 根节点 | 左节点，相当于逆序
        k--;
        if (k==0) {
            val = node->val;
            return;
        }
        fun(node->left, k);
    }

    int kthLargest(TreeNode* root, int k) {
        fun(root, k);
        return val;
    }
};


/**
 * 剑指 Offer 55 - I. 二叉树的深度
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        int ll = maxDepth(root->left);
        int rr = maxDepth(root->right);
        return max(ll, rr) + 1;
    }
};

/**
 * 剑指 Offer 55 - II. 平衡二叉树
 */
class Solution {
public:

    int fun(TreeNode *node) {
        if (!node) return 0;
        int ll = fun(node->left);
        int rr = fun(node->right);
        return max(ll, rr) + 1;
    }

    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        if (abs(fun(root->left) - fun(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }


    // 一次遍历即可得到结果
    bool fun(TreeNode *root, int &depth) {
        if (!root) {
            depth = 0;
            return true;
        }
        int x, y;
        if (fun(root->left, x) && fun(root->right, y)) {
            if (abs(x-y) <= 1) {
                depth = max(x, y)+1;
                return true;
            }
        }
        return false;
    }

    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return fun(root, depth);
    }
};


/**
 * 剑指 Offer 56 - I. 数组中数字出现的次数
 */
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int val = 0;
        for (auto n : nums)
            val = val ^ n;

        int det = 1;
        while (!(det&val)) det <<= 1;

        int v1 = 0, v2 = 0;
        for (auto n : nums) {
            if (n&det) v1 = v1 ^ n;
            else v2 = v2 ^ n;
        }
        return {v1, v2};
    }
};

/**
 * 剑指 Offer 56 - II. 数组中数字出现的次数 II
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (auto n : nums) {
            ones = ones ^ n & ~twos;
            twos = twos ^ n & ~ones;
        }
        return ones;
    }
};

/**
 * 剑指 Offer 57. 和为s的两个数字
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target)
                return {nums[i], nums[j]};
            else if (nums[i] + nums[j] > target)
                j--;
            else
                i++;
        }
        return {};
    }
};

/**
 * 剑指 Offer 57 - II. 和为s的连续正数序列
 */
class Solution {
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
 * 剑指 Offer 58 - I. 翻转单词顺序
 */
class Solution {
public:
    void reverse(string &s, int i, int j) {
        for (; i < j ; i++, j--) {
            swap(s[i], s[j]);
        }
    }
    string reverseWords(string s) {
        int n = s.size();
        reverse(s, 0, n-1);
        int start = 0, end = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && s[i] == ' ' && s[i-1] != ' ') {
                end = i-1;
                reverse(s, start, end);
            }
            if (i+1 < n && s[i] == ' ' && s[i+1] != ' ') start = i+1;
        }
        reverse(s, start, n-1);
        return s;
    }
};

/**
 * 剑指 Offer 58 - II. 左旋转字符串
 */
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        auto reverse = [] (string &str, int i , int j) {
            while(i < j) swap(str[i++], str[j--]);
        };
        reverse(s, 0, n-1);
        reverse(s, n, s.size() - 1);
        reverse(s, 0, s.size() - 1);
        return s;
    }
};

/**
 * 剑指 Offer 59 - I. 滑动窗口的最大值
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> v;
        deque<int> q; // 双端队列

        for (int i = 0; i < k; ++i) { // 未构成滑动窗口
            while (!q.empty() && q.back() < nums[i])
                q.pop_back();
            q.push_back(nums[i]);
        }

        if (!q.empty())
            v.push_back(q[0]); // 0->k-1的最大值，即第一个窗口的最大值

        for (int i = k; i < nums.size(); ++i) {
            if (q[0] == nums[i-k]) q.pop_front(); // 弹出左值
            while (!q.empty() && q.back() < nums[i]) q.pop_back();
            q.push_back(nums[i]); // 添加右值
            v.push_back(q[0]);
        }

        return v;
    }
};

/**
 * 剑指 Offer 59 - II. 队列的最大值
 */
class MaxQueue {
public:
    deque<int> d;
    queue<int> q;

    MaxQueue() {
    }

    int max_value() {
        if (q.empty())
            return -1;
        return d.front();
    }

    void push_back(int value) {
        while(!d.empty() && d.back() < value) d.pop_back();
        d.push_back(value);
        q.push(value);
    }

    int pop_front() {
        if (q.empty())
            return -1;

        int ans = q.front();
        if (d.front() == ans)
            d.pop_front();
        q.pop();
        return ans;
    }
};

/**
 * 剑指 Offer 60. n个骰子的点数
 */
class Solution {
public:
    vector<double> twoSum(int n) {
        // dp[i][j] = 投掷i个色子，点数为j的可能数
        // dp[i][j] += dp[i-1][j-k]    k=1,2,3,...min(j-1, 6) 一个色子的点数不可能超过6

        vector<vector<int>> dp(n+1, vector<int>(70, 0));
        for (int i = 1; i <= 6; ++i) dp[1][i] = 1;

        for (int i = 2; i <= n; ++i)
            for (int j = i; j <= 6*i; ++j)
                for (int k = 1; k <= 6 && j>k; ++k) // 这里k表示第i个色子可能投出的点数
                    dp[i][j] += dp[i-1][j-k];

        vector<double> ans;
        for (int j = 1*n; j <= 6*n; j++)
            ans.push_back(double(dp[n][j]) / pow(6,n));
        return ans;
    }
};

/**
 * 剑指 Offer 61. 扑克牌中的顺子
 */
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        vector<int> v(14, 0);
        int minval = 13, maxval = 1;
        for (int n : nums) {
            v[n]++;
            if (n != 0 && v[n] > 1) return false;
            minval = n != 0 ? min(n, minval) : minval;
            maxval = max(n, maxval);
        }

        if (maxval - minval < 5)
            return true;
        return false;
    }
};

/**
 * 剑指 Offer 62. 圆圈中最后剩下的数字
 *
 * 假设取第3个               取得元素    反推坐标(最终结果在当前数组中的坐标) = (当前idx+每次删除第n个) % 上一轮的数组长度
 * 0 1 [2] 3 4 0 1 2 3 4    2           (0+3)%5 = 3
 * 3 4 [0] 1 3 4 0 1        3           (1+3)%4 = 0
 * 1 3 [4] 1 3 4            4           (1+3)%3 = 1
 * 1 3 [1] 3                1           (0+3)%2 = 1
 * 3
 */
class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = 0;
        for (int i = 2;i <= n; ++i)
            ans = (ans+m) % i;
        return ans;
    }
};

/**
 * 剑指 Offer 63. 股票的最大利润
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0) return 0;
        int minp = prices[0], maxv = 0;
        for (int i = 1; i < prices.size(); ++i) {
            maxv = max(maxv, prices[i] - minp);
            minp = min(minp, prices[i]);
        }
        return maxv;
    }
};

/**
 * 剑指 Offer 64. 求1+2+…+n
 */
class Solution {
public:
    int res = 0;
    int sumNums(int n) {
        n>1 && sumNums(n-1) > 0;
        res+=n;
        return res;
    }
};

/**
 * 剑指 Offer 65. 不用加减乘除做加法
 * 负数一般用补码的形式表示，这时加减计算方法会和正数一样
 */
class Solution {
public:
    int add(int a, int b) {
        while (b!=0) {
            int c = (unsigned int)(a&b)<<1;
            a ^= b;
            b = c;
        }
        return a;
    }
};

/**
 * 剑指 Offer 66. 构建乘积数组
 */
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int> dp(n, 1);
        for(int i = 1; i < n; ++i)
            dp[i] = dp[i-1]*a[i-1];

        int tmp = 1;
        for (int i = n-2; i >= 0; --i) {
            tmp *= a[i+1];
            dp[i] *= tmp;
        }
        return dp;
    }
};

/**
 * 剑指 Offer 67. 把字符串转换成整数
 */
class Solution {
public:

    int strToInt(string str) {
        int idx = str.find_first_not_of(' ');
        str.erase(0, idx);
        if (str.size() == 0) return 0;

        int ans = 0, i = 1, sign = 1;
        if (str[0] == '-') sign = -1;
        else if (str[0] != '+') i = 0;

        for (int k = i; k < str.size(); ++k) {
            if (str[k] < '0' || str[k] > '9') break;
            // INT32_MIN = -2147483648
            // INT32_MAX = 2147483647
            if ((ans > INT32_MAX/10) || (ans == INT32_MAX/10 && str[k] > '7')) return sign < 0 ? INT32_MIN : INT32_MAX;
            ans = ans * 10 + (str[k]-'0');
        }

        return ans*sign;
    }
};

/**
 * 剑指 Offer 68 - I. 二叉搜索树的最近公共祖先
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || !p || !q) return NULL;
        if (root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        if (root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};

/**
 * 剑指 Offer 68 - II. 二叉树的最近公共祖先
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == q || root == p) return root;
        auto ll = lowestCommonAncestor(root->left, p, q);
        auto rr = lowestCommonAncestor(root->right, p, q);
        return !ll ? rr : !rr ? ll : root;
    }
};