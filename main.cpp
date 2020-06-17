#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int v) : val(v), next(NULL) {}
};

int main() {
    vector<ListNode*> ans(10, new ListNode(-1));
}
