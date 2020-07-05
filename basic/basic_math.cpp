//
// Created by sen on 2020/6/8.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class BasicMath {
public:
    void shift() {
        int n = 5;
        cout << (n >> 1) << endl; // 右移一位相当于整除2，这里5=101，变成2=10
        cout << (n << 1) << endl; // 左移一位相当于乘2，这里5=101，变成10=1010
    }

    void cubenum(int i, int j) {
        // 9X9的网格，判断是属于第几个3X3网格
        int r = i / 3;
        int c = j / 3;
        cout << r * 3 + c << endl;

        // nXn网格，判断属于45度方向上的第几列
        int n = 10;
        vector<bool> ans(2 * n - 1, false); // 45度对角线标记数据的长度为2*n-1
        int id45 = i + j; // 第i行第j列的位置对应45度对角线坐标为i+j

        // nXn网格，判断属于135度方向上的第几列
        vector<bool> ans2(2 * n - 1, false); // 135度对角线标记数据的长度为2*n-1
        int id135 = n - 1 - (i - j); // 第i行第j列的位置对应135度对角线坐标为n-1-(i-j)
    }

    // 关于取余
    void mod() {
        // 涉及整除问题时，经常需要取余数操作
        int a = 4;
        int t1 = a % 5; // 4
        int a2 = -1;
        int t2 = a2 % 5; // -1，由于负数有时候不好处理，因为6%5==1%5，所以-1%5可以理解为4%5
        int t3 = ((a2 % 5) + 5) % 5; // 4，将负数的mod值也取正
    }

    // 判断奇数偶数
    void jiou() {
        int a = 3;
        // 常规做法，除2取余
        if (a % 2 == 0) cout << "偶数";
        if (a % 2 == 1) cout << "奇数";

        // 高级做法，与1做与操作
        if (a&1) cout << "奇数";
        if (!(a&1)) cout << "偶数";

    }


};