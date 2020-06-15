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
};