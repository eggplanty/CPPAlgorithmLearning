//
// Created by sen on 2020/6/9.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

class Test {
public:
    void double_pointer() {
        string s = "abcba";
        int start = 0, end = 4;
        while (start < end) // 回文字符串的判断，左右双指针的快速写法
            if (s[start++] != s[end--]) {
                cout << s[start-1] << " " << s[end+1] << endl;
                break;
            }
    }
};