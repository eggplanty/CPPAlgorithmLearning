//
// Created by XBB-PC on 2020/6/20.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include "sort7.h"

using namespace std;

/**
 * 选择排序
 * 每次交换最小的元素，排列成排序队列
 * 时间复杂度 O(n^2)
 * 不稳定
 */
class SelectSort : public MySort {
public:
    void sort(vector<int> &q) {
        int n = q.size();
        for (int i = 0; i < (n - 1); i++)
            for (int j = i; j < n; j++)
                if (q[j] < q[i])
                    swap(q[i], q[j]);
    }
};

/**
 * 每个元素从头向尾冒泡，直到序列不在发生交换
 * 时间复杂度 最好 O(n) 有序，直接退出
 *           最坏 O(n^2)
 *           平均 O(n^2)
 * 稳定性：稳定
 * 适用情况：少量数据
 */
class BubbleSort : public MySort {
public:
    void sort(vector<int> &q) {
        int n = q.size();
        for (int i = n - 1; i > 0; i--) {
            int is_sorted = true;

            for (int j = 0; j < i; j++)
                if (q[j] > q[j + 1]) {
                    swap(q[j], q[j + 1]);
                    is_sorted = false;
                }
            if (is_sorted) return;
        }
    }
};

/**
 * 插入排序
 * 每个元素对之前已经排序的序列选择合适位置插入
 * 时间复杂度: 最坏 O(n^2)
 *            最好 O(n) 基本有序时达到
 *            平均 O(n^2)
 * 稳定性：稳定
 * 适用情况：少量数据时快于快速排序
 */
class InsertionSort : public MySort {
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

/**
 * 希尔排序
 * 分组插入排序，缩小增量
 * 时间复杂度和增量序列有关  最坏O(n^1.3-2)
 *                        最好O(nlog2n)
 * 稳定性：不稳定 分组插入排序会导致跳跃性交换值
 * 适用情况：中等大小序列
 */
class ShellSort : public MySort{
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

/**
 * 归并排序
 * 先对半分，然后分别排序再合并，递归
 * 时间复杂度 传统归并排序  最好O(nlogn)
 *                       最坏O(nlogn)
 *                       平均O(nlogn)
 *                       需要额外T(n)存储
 * 稳定性：稳定
 * 适用情况：不限制额外存储的序列
 */
class MergeSort : public MySort {
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
        recur(q, m + 1, r); // 这里必须是l->m ,m+1->r 不能是l->m-1, m->r，因为m为向下取整，如果是后者可能导致m->r死循环
        merge(q, l, m, r);
    }

    void sort(vector<int> &q) {
        recur(q, 0, (int)q.size() - 1);
    }
};

/**
 * 快速排序
 * 通过一个元素将序列切分成两个部分，左边小于该元素，右边大于该元素，递归
 * 时间复杂度: 最好O(nlogn)，在每次恰好将数组对半分时达到
 *            最坏O(n^2)，有序
 *            平均O(nlogn)
 * 稳定性：不稳定
 * 适用情况：大量无序数据
 */
class QuickSort : public MySort{
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

    void recur2(vector<int> &v, int l, int r) {
        if (l >= r)
            return ;
        int p = v[l], i = l+1, j = r;
        while (i <= j) {
            while (i <= j && v[i] < p) i++;
            while (i <= j && v[j] > p) j--;
            if (i <= j)
                swap(v[i++], v[j--]);
        }
        swap(v[j], v[l]); // 以第一个数为基准时，交换的是j不是i
        for (int k = 0; k < v.size(); ++k)
            cout << v[k] << " ";
        cout << endl;
        recur2(v, l, j-1);
        recur2(v, j+1, r);
    }

    void sort(vector<int> &q) {
        recur(q, 0, (int)q.size() - 1);
    }
};



/**
 * 堆排序
 * 首先构建堆，然后每次将堆顶元素与序列最后一个元素互换，不考虑原堆顶元素，继续构建堆，循环即可得到有序序列
 * 时间复杂度: 最好O(nlogn)
 *            最坏O(nlogn)
 *            平均O(nlogn)
 * 稳定性：不稳定
 * 适合非常大量的数据，空间复杂度为O(1)，不像快排递归栈需要空间
 * 速度比快速排序慢，因为建堆有序程度低，并且下沉上浮交换多
 */
class HeapSort : public MySort {
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