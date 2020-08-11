//
// Created by sen on 2020/6/3.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>

using namespace std;


class StringOperation {
public:

    void string_int_convert() {
        string str = "123";
        int stri = stoi(str); // 字符串转数字

        char c = '3';
        int ci = int(c - '0'); // 字符转数字

        int a = 255;
        string as = to_string(a); // 数字转字符串

        char d = 'd';
        string ds(1, d); //单个字符转string
    }

    void normal_operation() {
        string s(10, '.');
        cout << s << endl; // ".........."
    }

    void split() {
        string s = "1,2,3,4,5";
        string pat = ",";
        s += pat;// 方便边界处理
        vector<string> v;
        while (s.size() > 0) { // 字符串分割
            int pos = s.find(pat, 0);
            v.push_back(s.substr(0, pos));
            s = s.substr(pos + 1, s.size() - pos);
        }
    }

    // 按照' '进行字符串分割
    void split2() {
        string data = "   aaa,      bbb, ccc   ";
        istringstream tt(data); // include<ssteam>
        string temp;
        while (tt >> temp) { // 自动处理前缀和后缀空格，中间空格不论多少，会被作为分隔符
            cout << "---" << temp << "---" << endl;
        }
        /**
        结果为
        ---aaa,---
        ---bbb,---
        ---ccc---
         */
    }

    // 按照指定字符进行字符串分割
    void split3() {
        string data = "   aaa,      bbb, ccc   ";
        istringstream tt(data); // include<ssteam>
        string temp;
        while (getline(tt, temp, ',')) { // 不处理前缀空格和中间多余空格，仅仅按照目标字符分割
            cout << "---" << temp << "---" << endl;
        }
        /**
        结果为
        ---   aaa---
        ---      bbb---
        --- ccc   ---
         */
    }

    // 计算数组的长度
    void charlen(char s[]) {
        char *a = "1234455";
        char b[] = "1234455";
        cout << strlen(a) << endl; // 7
        cout << sizeof(a) << endl; // 8 包含了\0

        int c[] = {1,2,3,4};
        cout << sizeof(c) / sizeof(c[0]) << endl; // 4 需要除以单个元素的长度
    }

};