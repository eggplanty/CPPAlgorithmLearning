//
// Created by sen on 2020/5/26.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>

using namespace std;

/**
 * 215. 数组中的第K个最大元素
 * 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
 */

class Solution {
public:
    int findKthLargest(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<>> pq; // greater小顶堆， less大顶堆
        for (auto &n : nums) {
            if (pq.size() >= k && pq.top() >= n)
                continue;
            pq.push(n);
            if (pq.size() > k)
                pq.pop();
        }
        return pq.top();
    }
};


/**
 * 5429. 数组中的 k 个最强值
 * 给你一个整数数组 arr 和一个整数 k 。
 * 设 m 为数组的中位数，只要满足下述两个前提之一，就可以判定 arr[i] 的值比 arr[j] 的值更强：
 *  |arr[i] - m| > |arr[j] - m|
 *  |arr[i] - m| == |arr[j] - m|，且 arr[i] > arr[j]
 *
 * 请返回由数组中最强的 k 个值组成的列表。答案可以以 任意顺序 返回。
 * 中位数 是一个有序整数列表中处于中间位置的值。形式上，如果列表的长度为 n ，那么中位数就是该有序列表（下标从 0 开始）中位于 ((n - 1) / 2) 的元素。
 */
class Solution2 {
public:

    struct node { // 额外参数可以通过构建node来加入
        int x, m;
        node(int a, int b): x(a), m(b){}
    };

    struct cmp { // 若要构建小顶堆，则满足>条件的应该设为true，true对应的值会被放到堆底
        bool operator()(node a, node b) {
            if (abs(a.x - a.m) < abs(b.x - b.m))
                return false;
            else if (abs(a.x - a.m) > abs(b.x - b.m))
                return true;
            else if (a.x > b.x)
                return true;
            else
                return false;
        }
    };

    vector<int> getStrongest(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end());
        int m = arr[(arr.size()-1)/2];
        priority_queue<node, vector<node>, cmp> pq;

        cmp tcmp = cmp();

        for (auto &a : arr) {
            if (pq.size() >= k && tcmp(pq.top(), node(a, m))) // 如果top和新点相比满足cmp条件，则跳过
                continue;
            pq.push(node(a, m));
            if (pq.size() > k)
                pq.pop();
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.emplace_back(pq.top().x);
            pq.pop();
        }
        return ans;
    }
};

/**
 * 上题更好的解法
 */
class Solution3 {
    vector<int> ans;
    vector<pair<int,int>> a;
    int A(int x)
    {
        return x<0?-x:x;
    }
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        sort(arr.begin(),arr.end());
        int n=arr.size(),i;
        a.clear();
        ans.clear();
        for(auto c:arr)a.push_back(make_pair(A(c-arr[n-1>>1]),c)); //位运算，等价于(n-1)/2
        sort(a.begin(),a.end(),greater<pair<int,int>>()); //默认按照pair的first排序
        for(i=0;i<k;i++)ans.push_back(a[i].second);
        return ans;
    }
};