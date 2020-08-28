#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:

    string reverseLeftWords(string s, int n) {
        auto reverse = [] (string &str, int i , int j) {
            while(i < j) swap(str[i++], str[j--]);
        };
        reverse(s, 0, n-1);
        reverse(s, n, s.size() - 1);
        reverse(s, 0, s.size());
        return s;
    }
};

int main() {
    Solution().reverseLeftWords("123456", 3);
}