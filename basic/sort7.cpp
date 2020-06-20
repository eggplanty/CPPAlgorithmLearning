//
// Created by XBB-PC on 2020/6/20.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

//TODO: 验证正确性

// 选择排序
class SelectSort {
public:
    void sort(vector<int> &q) {
        for (int i = 0; i < q.size() - 1; i++)
            for (int j = 0; j < q.size(); j++)
                if (q[i] < q[j])
                    swap(q[i], q[j]);
    }
};

// 冒泡排序
class BubbleSort {
public:
    void sort(vector<int> &q) {
        for (int i = q.size() - 1; i > 0; i--) {
            int is_sorted = true;

            for (int j = 0; j < i; j++)
                if (q[j] < q[j + 1]) {
                    swap(q[j], q[j + 1]);
                    is_sorted = false;
                }
            if (is_sorted) return;
        }
    }
};

// 插入排序
class InsertionSort {
public:
    void sort(vector<int> &q) {
        for (int i = 1; i < q.size(); i++)
            for (int j = i; j > 0; j--) {
                if (q[j] < q[j - 1])
                    swap(q[j], q[j - 1]);
                else
                    break;
            }
    }
};

// 希尔排序
class ShellSort {
public:
    void sort(vector<int> &q) {
        int h = 1;
        while (h < q.size() / 3)
            h = h * 3 + 1;

        while (h >= 1) {
            for (int i = h; i < q.size(); i++) {
                for (int j = i; j >= h; j -= h) {
                    if (q[j] < q[j - h])
                        swap(q[j], q[j - h]);
                    else
                        break;
                }
            }
            h /= 3;
        }
    }
};

// 归并排序
class MergeSort {
public:
    void merge(vector<int> &q, int l, int m, int r) {
        vector<int> tmp(q.begin(), q.end());
        int i = l, j = m + 1;
        for (int k = l; k <= r; k++) {
            if (i > m) q[k] = tmp[j++];
            else if (j > r) q[k] = tmp[i++];
            else if (tmp[i] <= tmp[j]) q[k] = tmp[i++];
            else q[k] = tmp[j++];
        }
    }

    void recur(vector<int> &q, int l, int r) {
        if (r <= l) return;
        int m = l + (r - l) / 2;
        recur(q, l, m);
        recur(q, m + 1, r);
        merge(q, l, m, r);
    }

    void sort(vector<int> &q) {
        recur(q, 0, q.size() - 1);
    }
};

// 快速排序
class QuickSort {
public:
    void recur(vector<int> &q, int l, int r) {
        if (l > r) return;

        int i = l, j = r - 1, t = q[r];
        while (i <= j) {
            while (i <= j && q[i] < t) i++;
            while (i <= j && q[j] > t) j--;
            if (i <= j) swap(q[i++], q[j--]);
        }
        swap(q[i], q[r]);
        recur(q, l, i - 1);
        recur(q, i + 1, r);
    }

    void sort(vector<int> &q) {
        recur(q, 0, q.size() - 1);
    }
};

// 堆排序
class HeapSort {
public:

    void sink(vector<int> &q, int k, int n) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && q[j] < q[j + 1]) j++;
            if (q[j] < q[k]) break;

            swap(q[j], q[k]);
            k = j;
        }
    }

    void sort(vector<int> &q) {
        q.insert(q.begin(), 0);
        int N = q.size() - 1;

        for (int i = N / 2; i > 0; i--)
            sink(q, i, N);

        for (int i = N; i > 1; i--) {
            swap(q[i], q[1]);
            sink(q, 1, i - 1);
        }
        q.erase(q.begin());
    }
};