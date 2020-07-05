//
// Created by sen on 2020/6/5.
//
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;


class MySort {
public:
    void testsort() {
        vector<int> a = {3, 4, 2, 1, 2, 6};
        // sort 第一个参数为开始位置，第二个参数为结束位置，comp参数为自定义对比函数
        sort(a.begin(), a.end(), [](int x, int y) {
            return x > y; // 降序，返回为643221
        });

        // 对pair进行排序，默认会按照pair的first排序
        vector<pair<int, int>> p = {{1, 2},
                                    {4, 2},
                                    {2, 1},
                                    {8, 10}};
        sort(p.begin(), p.end(), less<pair<int, int>>()); // 升序，这里写法像函数调用，实际是指向重载()函数
        sort(p.begin(), p.end(), greater<pair<int, int>>()); // 降序

        // 优先级队列，常用来构建大小顶堆
        priority_queue<int, vector<int>, greater<>> pq; // greater小顶堆， less大顶堆
        pq.push(1); // 入堆
        pq.pop(); // 出堆
        pq.top(); // 堆顶元素
    }
};