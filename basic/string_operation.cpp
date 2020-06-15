//
// Created by sen on 2020/6/3.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;


class StringOperation {
public:

    void string_int_convert() {
        string str = "123";
        int stri = stoi(str); // 字符串转数字

        char c = '3';
        int ci = int(c-'0'); // 字符转数字

        int a = 255;
        string as = to_string(a); // 数字转字符串

        char d = 'd';
        string ds(1, d); //单个字符转string
    }

    void normal_operation() {
        string s(10, '.');
        cout << s << endl; // ".........."
    }

};