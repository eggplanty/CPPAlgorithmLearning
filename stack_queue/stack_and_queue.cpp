//
// Created by XBB-PC on 2020/6/23.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <map>

using namespace std;

/**
 * 232. 用栈实现队列
 * 使用栈实现队列的下列操作：
 *  push(x) -- 将一个元素放入队列的尾部。
 *  pop() -- 从队列首部移除元素。
 *  peek() -- 返回队列首部的元素。
 *  empty() -- 返回队列是否为空。
 *
 * 使用双栈实现队列
 */
class MyQueue {
public:
    vector<int> v1; // 双栈
    vector<int> v2;
    int cnt;

    /** Initialize your data structure here. */
    MyQueue() {
        cnt = 0;
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        v1.emplace_back(x);
        cnt++;
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (v2.empty())
            move();

        int tmp = v2.back();
        v2.pop_back();
        cnt--;
        return tmp;
    }

    void move() {
        while (!v1.empty()) { // 将数据从栈v1弹出再写入v2的过程相当于调换顺序，这时候v2弹出的就是队列先入队的
            int tmp = v1.back();
            v1.pop_back();
            v2.emplace_back(tmp);
        }
    }

    /** Get the front element. */
    int peek() {
        if (v2.empty())
            move();
        return v2.back();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return cnt == 0;
    }
};


/**
 * 225. 用队列实现栈
 * 使用队列实现栈的下列操作：
 *  push(x) -- 元素 x 入栈
 *  pop() -- 移除栈顶元素
 *  top() -- 获取栈顶元素
 *  empty() -- 返回栈是否为空
 *
 *  你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。
 *
 * 队列实现栈需要每次入队新数据之后将之前的所有数据重新入队一次。
 * 在将一个元素 x 插入队列时，为了维护原来的后进先出顺序，需要让 x 插入队列首部。而队列的默认插入顺序是队列尾部，因此在将 x 插入队列尾部之后，需要让除了 x 之外的所有元素出队列，再入队列。
 */
class MyStack {
public:
    queue<int> q;

    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        q.push(x);
        int size = q.size();
        while (size-- > 1) { // 将除了刚写入的数据以外的数据重新入队
            int tmp = q.front();
            q.pop();
            q.push(tmp);
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int tmp = q.front();
        q.pop();
        return tmp;
    }

    /** Get the top element. */
    int top() {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};

/**
 * 155. 最小栈
 * 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
 *  push(x) —— 将元素 x 推入栈中。
 *  pop() —— 删除栈顶的元素。
 *  top() —— 获取栈顶元素。
 *  getMin() —— 检索栈中的最小元素。
 *
 * 最小栈可以通过维护最小值对应的栈来实现
 */
class MinStack {
public:
    vector<int> v1;
    vector<int> v2;
    int minx;

    /** initialize your data structure here. */
    MinStack() {
        minx = INT32_MAX;
    }

    void push(int x) {
        v1.emplace_back(x);
        minx = min(x, minx);
        v2.emplace_back(minx); // 维护最小值对应的栈
    }

    void pop() {
        v1.pop_back();
        v2.pop_back();
        int tmp = v2.empty() ? INT32_MAX : v2.back(); // 如果v2为空，此时需要设为INT32_MAX
        minx = tmp;
    }

    int top() {
        return v1.back();
    }

    int getMin() {
        return minx;
    }
};


/**
 * 20. 有效的括号
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 * 有效字符串需满足：
 *  左括号必须用相同类型的右括号闭合。
 *  左括号必须以正确的顺序闭合。
 *
 * 注意空字符串可被认为是有效字符串。
 *
 * 用栈实现即可
 */
class Solution {
public:

    bool isValid(string s) {
        map<char, char> m = {{'(', ')'},
                             {'[', ']'},
                             {'{', '}'}}; // map映射，都转成右括号方便处理
        vector<char> stack;
        for (auto c : s) {
            if (m[c]) stack.emplace_back(m[c]);
            else {
                if (stack.empty()) return false; // 防止越界
                char tmp = stack.back();
                stack.pop_back();
                if (tmp != c) return false;
            }
        }
        return stack.empty(); // 全部匹配算解决
    }
};


/**
 * 739. 每日温度
 * 请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。
 * 例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。
 * 提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。
 *
 * 考虑下一个比之前温度高的温度，只需要使用栈记录温度，将当前温度与栈顶温度对比即可
 */
class Solution2 {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        vector<int> s1; // 记录温度对应id
        vector<int> ans(T.size(), 0);
        for (int i = 0; i < T.size(); i++) {
            while (!s1.empty() && T[i] > T[s1.back()]) { // 如果记录温度不为空，且栈顶温度小于当前温度，则弹出栈顶元素并计算步数
                ans[s1.back()] = i - s1.back();
                s1.pop_back();
            }
            s1.emplace_back(i);
        }
        return ans;
    }
};


/**
 * 503. 下一个更大元素 II
 * 给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历
 * 顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。
 *
 * 下一个更大元素，考虑栈缓存历史元素序号，将当前元素与栈顶元素对比
 */
class Solution3 {
public:
    vector<int> nextGreaterElements(vector<int> &nums) {
        vector<int> stack;
        vector<int> ans(nums.size(), -1);
        int cnt = 2;
        while (cnt-- > 0) // 2次循环，处理循环数组
            for (int i = 0; i < nums.size(); i++) {
                while (!stack.empty() && nums[stack.back()] < nums[i]) { // 当栈顶元素小于当前元素时
                    ans[stack.back()] = nums[i];
                    stack.pop_back();
                }
                stack.emplace_back(i);
            }
        return ans;
    }
};