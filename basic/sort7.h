//
// Created by XBB-PC on 2020/7/11.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

class MySort {
protected:
    vector<vector<int>> test_cases = {
            {},
            {1, 2, 3},
            {6, 5, 4, 3, 2, 1},
            {5, 4, 3, 2, 6, 76, 43, 6, 1, 3},
            {3, 6, 87, 43, 76, 0, 43, 56, 4, 67, 56, 77, 88, 65}
    };

    vector<vector<int>> test_answer = {
            {},
            {1, 2, 3},
            {1, 2, 3, 4, 5, 6},
            {1, 2, 3, 3, 4, 5, 6, 6, 43, 76},
            {0, 3, 4, 6, 43, 43, 56, 56, 65, 67, 76, 77, 87, 88}
    };

    bool match(vector<int> &a, vector<int> &b) {
        if (a.size() != b.size())
            return false;

        for (int i = 0; i < a.size(); ++i)
            if (a[i] != b[i])
                return false;
        return true;
    }


    virtual void sort(vector<int> &q) = 0;

public:

    void run() {

        for (int i = 0; i < test_cases.size(); ++i) {
            vector<int> v = test_cases[i];
            cout << "origin: ";
            for (auto vv : v) cout << vv << " ";
            cout << endl;

            sort(v);

            cout << "sort: ";
            for (auto vv : v) cout << vv << " ";
            string result = match(v, test_answer[i]) ? "[OK]" : "[X]";
            cout << result << endl;
        }
    }
};