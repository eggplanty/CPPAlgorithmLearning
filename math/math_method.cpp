//
// Created by sen on 2020/6/12.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

class Test {
public:
    vector<int> get_primes(int n) {//埃拉托斯特尼筛法
        vector<bool> is_primes(n + 1, true);
        vector<int> primes;

        for (int i = 2; i < n; i++) {
            if (!is_primes[i]) continue;
            primes.emplace_back(i);
            if (n / i < i) continue; // 防止i*i超出int限制
            // 从 i * i 开始，因为如果 k < i，那么 k * i 在之前就已经被去除过了
            for (int j = i * i; j <= n; j += i) is_primes[j] = false;
        }
        return primes;
    }

    int gcd(int a, int b) { // 最大公约数
        return b == 0 ? a : gcd(b, a % b);
    }

    int lcm(int a, int b) { // 最小公倍数为两数的乘积除以最大公约数。
        return a * b / gcd(a, b);
    }

    int remainder(int x, int a, int M) { // 循环求余法
        // 根据余数运算规则 (x*y) % p = ((x%p) * (y%p)) % p
        // (x+y) % p = ((x%p) + (y%p)) % p
        // 所以 x**a % p = ((x**(a-1) % p)*(x%p))%p = ((x**(a-1) % p) * x) % p
        int rem = 1;
        while (a-- > 0)
            rem = ((rem % M) * x) % M;
        return M;

    }
};