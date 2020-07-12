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

    // 快速幂的二分实现
    double fastPow(double x, int n) {
        if (x == 0) return 0; // 防止n<0时1/x出错
        long ln = n;
        if (ln < 0) x = 1 / x, ln = -ln; // n有可能为INT32_MAX，取负数超出下界
        double res = 1.0;
        // https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof/solution/mian-shi-ti-16-shu-zhi-de-zheng-shu-ci-fang-kuai-s/
        // 根据二分推导，可通过循环 x = x^2操作，每次把幂从 n 降至 n//2 ，直至将幂降为 0
        // 设 res=1，则初始状态为x^n = x^n * res，在循环二分的过程中，每当n为奇数时，则将多出的一项乘到res上，最终得到x^n = x^0 * res = res， 返回res即可
        while (ln) { // 核心是这个循环
            if (ln & 1) res *= x; // 必然会走到n==1，将之间没乘的x一次乘完
            x *= x;
            ln /= 2;
        }
        return res;
    }

};