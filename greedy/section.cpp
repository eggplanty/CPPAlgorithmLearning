//
// Created by sen on 2020/5/26.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

/**
 * 435. 无重叠区间
 * 给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
 *
 * 注意:
 * 可以认为区间的终点总是大于它的起点。
 * 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
 */
class Solution {
public:
    static bool fun(vector<int> a, vector<int> b) {
        return a[1] < b[1];
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), fun);

        int cnt = 1, last = intervals[0][1];
        for (auto &t : intervals) {
            if (t[0] < last)
                continue;
            last = t[1];
            cnt++;
        }
        return intervals.size() - cnt;
    }
};

/**
 * 452. 用最少数量的箭引爆气球
 * 在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束
 * 坐标。由于它是水平的，所以y坐标并不重要，因此只要知道开始和结束的x坐标就足够了。开始坐标
 * 总是小于结束坐标。平面内最多存在104个气球。一支弓箭可以沿着x轴从不同点完全垂直地射出。
 * 在坐标x处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend，
 * 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。可以射出的弓箭的数量没有限制。
 * 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小
 * 数量。
 */
class Solution2 {
public:

    static bool cmp(vector<int> &a, vector<int> &b) {
        return a[1] < b[1];
    }

    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int cnt = 1, last = points[0][1];
        for (auto &p : points) {
            if (p[0] <= last)
                continue;
            last = p[1];
            cnt++;
        }
        return cnt;
    }
};


/**
 * 406. 根据身高重建队列
 * 假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身
 * 高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。
 */
class Solution3 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(), people.end(),
             [](vector<int> &a, vector<int> &b)
             {
                 if (a[0] == b[0])
                     return a[1] < b[1];
                 return a[0] > b[0];
             }); // lambda表达式

        list<vector<int>> ans;
        for (auto &p : people) {
            auto beg = ans.begin();
            advance(beg, p[1]);
            ans.insert(beg, p); // list未复写+方法，所以需要用advance，vector可以直接用+
            // ans.insert(ans.begin()+p[1], p);
        }
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};


