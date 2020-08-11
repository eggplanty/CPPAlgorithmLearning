#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:

    int fun(int l, int r, int cl, int cr, vector<int>& cuts) {
        if (l >= r || cl > cr) return 0;
        if (cr == cl) return r-l;
        double mid = l+(r-l) / 2.0;
        vector<int> v;
        double minval = INT32_MAX;
        for (int i = cl; i <= cr; ++i) {
            if (abs(cuts[i] - mid) < minval) {
                minval = abs(cuts[i] - mid);
                v.clear();
                v.push_back(i);
            }
            else if (abs(cuts[i] - mid) == minval)
                v.push_back(i);
        }

        int maxval = INT32_MAX;
        for (int m : v) {
            maxval = min(maxval, fun(l, cuts[m], cl, m-1, cuts) + fun(cuts[m], r, m+1, cr, cuts) + r-l);
        }
        return maxval;
    }

    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        return fun(0, n, 0, cuts.size()-1, cuts);
    }
};

void f(int* a, int b[2][1]) {
    cout << a[0] << endl;
    cout << b[0][0] << endl;
}

int main() {
    string a = "123";
    a += string(5, ' ');
}