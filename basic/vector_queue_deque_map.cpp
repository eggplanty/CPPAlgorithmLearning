//
// Created by XBB-PC on 2020/6/18.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>
#include <map>

using namespace std;

class Test {
    void test_vector_deque_deque_unordered_map() {
        queue<int> q; // queue是一个先进先出的受限队列
        q.push(1);
        q.push(2); // 入队为末尾
        q.push(3);
        q.push(4);
        cout << q.front() << " " << q.back() << endl; // 1 4
        q.pop(); // 弹出的是第一个元素
        cout << q.front() << " " << q.back() << endl; // 2 4

        vector<int> v; // vector 为一般队列，相较于list，区别在于连续存储，所以查询快，中间插入删除慢
        v.emplace_back(1); // vector 只有emplace_back或者push_back方法，如果需要指定位置，要用迭代器
        v.pop_back(); // vector 只有pop_back方法

        deque<int> d; // 双向队列，内部实现为小片连续，片段间用链表链接，速度比vector慢
        d.emplace_back(1);
        d.emplace_front(2); // 对比vector增加了front相关操作
        d.pop_back();
        d.pop_front();

        unordered_map<char, int> um; // 无序字典，内部通过hash表来实现，所以插入顺序和读取顺序不一定一致
        um['a'] = 1; // 赋值操作
        um.insert(make_pair('b', 2));
        for (auto iter = um.begin(); iter != um.end(); iter++) // 遍历操作
            cout << iter->first << " " << iter->second << endl;

        map<char, int> m; // 普通字典，内部通过红黑树实现，所以是有序的，插入顺序和读取顺序一致
        m['a'] = 1; // 赋值操作，所有操作和无序字典一致
        m.insert(make_pair('b', 2));
        for (auto iter = m.begin(); iter != m.end(); iter++) // 遍历操作
            cout << iter->first << " " << iter->second << endl;
    }
};