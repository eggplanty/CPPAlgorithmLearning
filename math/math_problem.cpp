//
// Created by sen on 2020/6/12.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

/**
 * 素数分解
 * 每一个数都可以分解成素数的乘积，例如 84 = 2^2 * 3^1 * 5^0 * 7^1 * 11^0 * 13^0 * 17^0 * …
 *
 * 整除
 * 令 x = 2^m0 * 3^m1 * 5^m2 * 7^m3 * 11^m4 * …
 * 令 y = 2^n0 * 3^n1 * 5^n2 * 7^n3 * 11^n4 * …
 * 如果 x 整除 y（y mod x == 0），则对于所有 i，mi <= ni。也就是对应的素数的幂保持大小关系。
 *
 * 最大公约数最小公倍数
 * x 和 y 的最大公约数为：gcd(x,y) = 2^min(m0,n0) * 3^min(m1,n1) * 5^min(m2,n2) * ...
 * x 和 y 的最小公倍数为：lcm(x,y) = 2^max(m0,n0) * 3^max(m1,n1) * 5^max(m2,n2) * ...
 */

/**
 * 204. 计数质数
 * 统计所有小于非负整数 n 的质数的数量。
 */
class Solution {
public:

    vector<int> get_primes(int n) { //埃拉托斯特尼筛法
        vector<bool> is_primes(n+1, true);
        vector<int> primes;

        for (int i = 2; i < n; i++) {
            if (!is_primes[i]) continue;
            primes.emplace_back(i);
            if (n/i < i) continue; // 防止i*i超出int限制
            // 从 i * i 开始，因为如果 k < i，那么 k * i 在之前就已经被去除过了
            for (int j = i*i; j <= n; j+=i) is_primes[j] = false;
        }
        return primes;
    }

    int countPrimes(int n) {
        return get_primes(n).size();
    }
};

/**
 * 504. 七进制数
 * 给定一个整数，将其转化为7进制，并以字符串形式输出。
 */
class Solution2 {
public:
    // 递归解法
    string convertToBase7(int num) {
        if (num < 0) return "-" + convertToBase7(-1 * num);
        if (num < 7) return to_string(num);
        return convertToBase7(num/7) + to_string(num%7);
    }

    // 常规解法
    string convertToBase77(int num) {
        if (num == 0) return "0";

        string s = "", ff = "";
        if (num < 0) {
            num *= -1;
            ff = "-";
        }
        while (num != 0) { // 7进制就是循环对7取余
            s = to_string(num % 7) + s;
            num /= 7;
        }
        return ff + s;
    }
};