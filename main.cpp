#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int v) : val(v), next(NULL) {}
};

int main() {
    vector<int> a = {1,2,3,4};
    vector<int> b(a.begin(), a.end());
    swap(a[0], a[2]);
    a.insert(a.begin(), 111);
    a.erase(a.begin());
    cout<< a[0] << a[1] << a[2] <<a[3] <<endl;
}
