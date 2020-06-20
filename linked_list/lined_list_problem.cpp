//
// Created by XBB-PC on 2020/6/17.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

/*
 * 160. 相交链表
 * 编写一个程序，找到两个单链表相交的起始节点。
 * 设 A 的长度为 a + c，B 的长度为 b + c，其中 c 为尾部公共部分长度，可知 a + c + b = b + c + a。
 * 如果不存在交点，那么 a + b = b + a，以下实现代码中 l1 和 l2 会同时为 null，从而退出循环。
 *
 * 如果只是判断是否存在交点，有两种解法
 * 把第一个链表的结尾连接到第二个链表的开头，看第二个链表是否存在环；
 * 或者直接比较两个链表的最后一个节点是否相同。
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *l1 = headA, *l2 = headB;
        while (l1 != l2) { // 不论是否相交，两者相等时就退出
            l1 = l1 == NULL ? headB : l1->next; // 如果到尾部，则切换到另一个链表的头部
            l2 = l2 == NULL ? headA : l2->next;
        }
        return l1;
    }
};

/**
 * 206. 反转链表
 * 反转一个单链表。
 *
 * 递归法
 */
class Solution2 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == NULL || head->next == NULL) return head; // head==NULL用来判断链表为空，head->next==NULL用来判断结尾
        ListNode *next = head->next;
        ListNode* newHead = reverseList(next);
        head->next = NULL; // 用来保证最终结尾为NULL
        next->next = head; // 实际反转操作
        return newHead;
    }
};

/**
 * 206. 反转链表
 *
 * 迭代法
 */
class Solution3 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = NULL, *pre = head; // 记录当前位置和下一个位置
        while (pre != NULL) {
            ListNode *t = pre->next; // 记录下下个位置
            pre->next = cur; // 实际反转操作
            cur = pre; // 先给cur复制
            pre = t;
        }
        return cur;
    }
};

/**
 * 206. 反转链表
 *
 * 头插法
 */
class Solution4 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *newhead = new ListNode(-1); //建立伪头部节点
        while (head != NULL) {
            ListNode *t = head->next;
            head->next = newhead->next;
            newhead->next = head;
            head = t;
        }
        return newhead->next; // 排除伪头部节点
    }
};

/**
 * 21. 合并两个有序链表
 * 将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
 *
 * 递归 归并法
 */
class Solution5 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) return l2; // 如果一个链表已经遍历完了，就取另一个链表的值
        if (l2 == NULL) return l1;
        if (l1->val < l2->val) { // 升序
            l1->next = mergeTwoLists(l1->next, l2); //l1->next为后续升序链表的头结点
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};

/**
 * 83. 删除排序链表中的重复元素
 * 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
 */
class Solution6 {
public:
    // 常规做法，遍历
    ListNode* deleteDuplicates1(ListNode* head) {
        if (head == NULL) return head;
        ListNode *cur = head, *pre = head->next;
        while (pre != NULL) {
            if (cur->val == pre->val) {
                cur->next = pre->next;
                pre = pre->next;
            }
            else {
                cur = cur->next;
                pre = pre->next;
            }
        }
        return head;
    }

    // 高级做法
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) return head; // head == NULL 用来处理空链表，
        head->next = deleteDuplicates(head->next); // 当前节点的下一个节点为以下个节点开头的无重复链表
        return head->val == head->next->val ? head->next : head; // 如果当前节点与下个节点值相同，则跳过当前节点
    }
};

/**
 * 19. 删除链表的倒数第N个节点
 * 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 */
class Solution7 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *cur = head, *prev = head;
        while(n-- > 0) // 先向前移动n个位置
            prev = prev->next;
        if (prev == NULL) return head->next; // 如果prev==NULL，表示第一个节点需要舍弃
        while (prev->next != NULL) {
            cur = cur->next;
            prev = prev->next;
        }
        cur->next = cur->next->next;
        return head;
    }
};

/**
 * 24. 两两交换链表中的节点
 *
 * 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 * 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * 例如： 给定 1->2->3->4, 你应该返回 2->1->4->3.
 */
class Solution8 {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummyHead = new ListNode(-1);
        dummyHead->next = head; //加入伪节点，方便处理前置节点
        ListNode *pre = dummyHead;
        while (pre->next != NULL && pre->next->next != NULL) {
            ListNode *l1 = pre->next, *l2 = pre->next->next;// pre为前置节点，l1为左节点，l2为右节点
            l1->next = l2->next;
            l2->next = l1;
            pre->next = l2;
            pre = l1; // 下一个前置节点为修改后的l1
        }
        return dummyHead->next; // 返回值跳过伪节点
    }
};

/**
 * 445. 两数相加 II
 * 给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
 * 你可以假设除了数字 0 之外，这两个数字都不会以零开头。
 * 常规做法，先反转两个链表，相加之后再将结果反转回来
 */
class Solution9 {
public:
    // 翻转链表
    ListNode* fun(ListNode *head) {
        ListNode *dm = new ListNode(-1);
        while (head != NULL) {
            ListNode *t = head->next;
            head->next = dm->next;
            dm->next = head;
            head = t;
        }
        return dm->next;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        l1 = fun(l1);
        l2 = fun(l2);
        int k = 0; // 处理进位
        ListNode *dm = new ListNode(-1);
        ListNode *head = dm;
        while (l1 != NULL || l2 != NULL || k > 0) { // k>0用来处理最高位有进位的情况
            if (l1 != NULL) {
                k += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                k += l2->val;
                l2 = l2->next;
            }
            head->next = new ListNode(k%10);
            k /= 10;
            head = head->next;
        }
        return fun(dm->next); // 将结果翻转
    }
};

/**
 * 445. 两数相加 II
 * 使用堆栈来解决链表反转问题
 */
class Solution10 {
public:
    vector<int> buildStack(ListNode *head) {
        vector<int> ans;
        while (head != NULL) {
            ans.emplace_back(head->val);
            head = head->next;
        }
        return ans;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        vector<int> v1 = buildStack(l1), v2 = buildStack(l2); // 堆栈可以用stack也可以用vector
        int k = 0;
        ListNode *dm = new ListNode(-1);
        while (!v1.empty() || !v2.empty() || k>0) {
            int t1 = v1.empty() ? 0 : v1.back(); // back可以直接取最后一个值，不需要v1[v1.size()-1]
            if (!v1.empty()) v1.pop_back();
            int t2 = v2.empty() ? 0 : v2.back();
            if (!v2.empty()) v2.pop_back();

            ListNode* t = new ListNode((t1+t2+k) % 10);
            t->next = dm->next;
            dm->next = t;
            k = (t1+t2+k) / 10;
        }
        return dm->next;
    }
};

/**
 * 234. 回文链表
 * 请判断一个链表是否为回文链表。
 *
 * 思路为将链表对半切分，将后半部分反转，然后对比两部分是否相同。
 */
class Solution11 {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode *slow = head, *fast = head->next; // 通过快慢指针找到数组中间点，即为fast指针为NULL时的slow指针
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *l2 = slow->next;
        if (fast) slow = slow->next; // 链表长度为双数，则种植节点向后移动一位
        ListNode *l1 = head;
        while (head->next != slow) head = head->next; // head指针调整到截断位置
        head->next = NULL;

        ListNode *dm = new ListNode(-1); // 反转后半部分
        while (l2) {
            ListNode *t = l2->next;
            l2->next = dm->next;
            dm->next = l2;
            l2 = t;
        }
        l2 = dm->next;
        while (l1 && l2) { // 对比值是否相等
            if (l1->val != l2->val) return false;
            l1 = l1->next;
            l2 = l2->next;
        }
        return true;
    }
};

/**
 * 725. 分隔链表
 * 给定一个头结点为 root 的链表, 编写一个函数以将链表分隔为 k 个连续的部分。
 * 每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过 1，也就是说可能有些部分为 null。
 * 这k个部分应该按照在链表中出现的顺序进行输出，并且排在前面的部分的长度应该大于或等于后面的长度。
 * 返回一个符合上述规则的链表的列表。
 * 举例： 1->2->3->4, k = 5 // 5 结果 [ [1], [2], [3], [4], null ]
 *
 * 思路为先计算链表长度，然后计算每个子部分的长度，最后遍历分配。
 */
class Solution12 {
public:
    vector<ListNode*> splitListToParts(ListNode* root, int k) {
        ListNode *head = root;
        int N = 0; // 计算链表长度
        while (head) {
            N++;
            head = head->next;
        }

        int size = N / k, mod = N % k;
        ListNode *cur = root;
        vector<ListNode*> ans(k, NULL);

        for (int i = 0; i < k; i++) {
            int cursize = size + ((mod--) > 0 ? 1 : 0);// 计算子部分的长度时先计算整除的值，然后依次对每个子部分叠加一个mod值，知道mod用完
            if (cursize == 0) continue; // 防止处理截断出错
            ans[i] = cur;
            while (cursize-- > 1) // >1 保证cur停在目标位置的上一个位置，方便处理截断
                cur = cur->next;
            ListNode *t = cur->next; // 需要用NULL来截断子部分
            cur->next = NULL;
            cur = t;
        }
        return ans;
    }
};

/**
 * 328. 奇偶链表
 * 给定一个单链表，把所有的奇数节点和偶数节点分别排在一起。请注意，这里的奇数节点和偶数节点指的是节点编号的奇偶性，而不是节点的值的奇偶性。
 *
 * 简单的方法是遍历节点，将节点分成奇数节点和偶数节点，然后合并
 */
class Solution13 {
public:
    ListNode* oddEvenList(ListNode* head) {
        int N = 0;
        ListNode *dm1 = new ListNode(-1);
        ListNode *dm2 = new ListNode(-1);
        ListNode *l1 = dm1, *l2 = dm2;
        while (head) {
            if (N % 2 == 0) {
                l1->next = head;
                l1 = l1->next;
            }
            else {
                l2->next = head;
                l2 = l2->next;
            }
            N++;
            ListNode *next = head->next;
            head->next = NULL; // 由于要赋值给其他链表，所以需要将对应节点的next设为NULL
            head = next;
        }
        l1->next = dm2->next;
        return dm1->next;
    }
};

/**
 * 328. 奇偶链表
 * 高级做法，时间复杂度O（n），空间复杂度O（1）
 * 思路为将遍历时直接奇偶节点的下层节点复制
 */
class Solution14 {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode *one = head, *two = head->next, *htwo = two; // 需要记录下偶数节点的起始节点
        while (two && two->next) {
            one->next = one->next->next; //解决了两个问题，上层节点的的下级是谁，该层节点的下级是谁
            one = one->next;
            two->next = two->next->next;
            two = two->next;
        }
        one->next = htwo; // 将奇数节点的最后一个链接到偶数节点的第一个
        return head;
    }
};
