//
// Created by sen on 2020/6/12.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
#include <set>

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

/**
 * 405. 数字转换为十六进制数
 * 给定一个整数，编写一个算法将这个数转换为十六进制数。对于负整数，我们通常使用 补码运算 方法。
 * 十六进制中所有字母(a-f)都必须是小写。
 * 十六进制字符串中不能包含多余的前导零。如果要转化的数为0，那么以单个字符'0'来表示；对于其他情况，十六进制字符串中的第一个字符将不会是0字符。 
 * 给定的数确保在32位有符号整数范围内。
 * 不能使用任何由库提供的将数字直接转换或格式化为十六进制的方法。
 */
class Solution3 {
public:
    string toHex(int num) {
        if (num == 0) return "0";
        string ans;
        vector<char> map  = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        unsigned int nn = num; // 考虑补码运算，将带符号int转成无符号int，-1的无符号int为ffffffff，负数补码运算为除符号位外取反然后加1
        while (nn!=0) {
            ans+=map[nn & 0xf]; // 16进制可以理解为与f取与
            nn >>= 4; // 每次向右移动四位
        }
        reverse(ans.begin(), ans.end()); // 字符串反向
        return ans;

        for (int i = 31; i >= 0; i--)
            cout << ((num >> i) & 1); // 打印二进制值
    }
};

/**
 * 168. Excel表列名称
 * 给定一个正整数，返回它在 Excel 表中相对应的列名称。
 * 例如
 *     1 -> A
 *     2 -> B
 *     3 -> C
 */
class Solution4 {
public:
    string convertToTitle(int n) {
        string ans;
        while (n != 0) {
            n--; // 由于是从1开始而不是从0开始的，所以要先--
            ans = char('A' + n % 26) + ans; // 不能在这里用(n-1) % 26 来做，因为从1开始会对n/=26同样产生影响
            n /= 26;
        }
        return ans;
    }
};

/**
 * 172. 阶乘后的零
 * 给定一个整数 n，返回 n! 结果尾数中零的数量。
 *
 * 尾部的 0 由 2 * 5 得来，2 的数量明显多于 5 的数量，因此只要统计有多少个 5 即可
 */
class Solution5 {
public:
    int trailingZeroes(int n) { // 处理尾数为0等问题，分解为2，5来考虑
        return n == 0 ? 0 : n / 5 + trailingZeroes(n / 5); // 统计的是1-n中所有和5有关的数中5的出现次数之和
    }
};


/**
 * 67. 二进制求和
 * 给你两个二进制字符串，返回它们的和（用二进制表示）。
 * 输入为 非空 字符串且只包含数字 1 和 0。
 *
 * 这题核心在于如何处理进位
 */
class Solution6 {
public:
    string addBinary(string a, string b) {
        int i = a.size()-1, j = b.size()-1, t = 0; // 从后向前遍历相加，t用来处理进位
        string ans;
        while (t == 1 || i >= 0 || j >= 0) { // t==1用来处理最高位进位的情况
            if (i >= 0 && a[i--] == '1')
                t++;
            if (j >= 0 && b[j--] == '1')
                t++;
            ans = char('0' + t % 2) + ans;
            t /= 2; // 进位处理
        }
        return ans;
    }
};

/**
 * 415. 字符串相加
 * 给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。
 *
 * 和6一样，核心关键在于处理进位
 */
class Solution7 {
public:
    string addStrings(string num1, string num2) {
        int i = num1.size()-1, j = num2.size()-1, t = 0;
        string ans;
        while (t > 0 || i >= 0 || j >= 0) {
            if (i >= 0)
                t += num1[i--] - '0';
            if (j >= 0)
                t += num2[j--] - '0';
            ans = char('0' + t % 10) + ans;
            t /= 10; // t用作进位处理
        }
        return ans;
    }
};

/**
 * 462. 最少移动次数使数组元素相等 II
 * 给定一个非空整数数组，找到使所有数组元素相等所需的最小移动数，其中每次移动可将选定的一个元素加1或减1。 您可以假设数组的长度最多为10000。
 *
 * 这是个典型的相遇问题，移动距离最小的方式是所有元素都移动到中位数。理由如下：
 * 设 m 为中位数。a 和 b 是 m 两边的两个元素，且 b > a。要使 a 和 b 相等，它们总共移动的次数为 b - a，这个值等于 (b - m) + (m - a)，也就是把这两个数移动到中位数的移动次数。
 * 设数组长度为 N，则可以找到 N/2 对 a 和 b 的组合，使它们都移动到 m 的位置。
 */
class Solution8 {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size()-1, cnt = 0;
        while (i < j)
            cnt += nums[j--] - nums[i++]; // 移动到中位数
        return cnt;
    }
};

/**
 * 462. 最少移动次数使数组元素相等 II
 * 上题的一种更快的方法，快速选择找中位数，第N/2大的数，时间复杂度为O(N)
 */
class Solution9 {
public:

    int partition(int l, int h, vector<int> &nums) {
        int i = l, j = h-1, q = nums[h];
        while (i <= j) {
            while (i <= j && nums[i] < q) i++;
            while (i <= j && nums[j] > q) j--;
            if (i <= j) swap(nums[i++], nums[j--]);
        }
        swap(nums[i], nums[h]);
        return i;
    }

    int findKthSmallest(vector<int> nums, int k) {
        int i = 0, j = nums.size()-1;
        while (i <= j) {
            int t = partition(i, j, nums);

            if (t == k) return nums[k];
            if (t < k) i = t+1;
            else j = t-1;
        }
        return 0;
    }

    int minMoves2(vector<int>& nums) {
        int median = findKthSmallest(nums, nums.size() / 2);
        int cnt = 0;
        for (auto n : nums)
            cnt += abs(n - median);
        return cnt;
    }
};

/**
 * 169. 多数元素
 * 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 [ n/2 ] 的元素。
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 *
 * 先排序，中间的数一定出现次数超过n/2
 */
class Solution10 {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

/**
 * 169. 多数元素
 * 上题的另一种解法
 * 使用 cnt 来统计一个元素出现的次数，当遍历到的元素和统计元素不相等时，令 cnt--。如果前面查找了 i 个元素，且 cnt == 0，说明前 i 个元
 * 素没有 majority，或者有 majority，但是出现的次数少于 i / 2，因为如果多于 i / 2 的话 cnt 就一定不会为 0。此时剩下的 n - i 个元素
 * 中，majority 的数目依然多于 (n - i) / 2，因此继续查找就能找出 majority。
 */
class Solution11 {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, majority = nums[0];
        for (auto n : nums) {
            majority = cnt == 0 ? n : majority;
            cnt = majority == n ? cnt+1 : cnt-1;
        }
        return majority;
    }
};

/**
 * 326. 3的幂
 * 给定一个整数，写一个函数来判断它是否是 3 的幂次方。
 * 可以直接用一个很大的3的幂来取余，从而判断
 */
class Solution12 {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};

/**
 * 367. 有效的完全平方数
 * 给定一个正整数 num，编写一个函数，如果 num 是一个完全平方数，则返回 True，否则返回 False。
 * 说明：不要使用任何内置的库函数，如  sqrt。
 *
 * 典型的二分查找题
 */
class Solution13 {
public:
    bool isPerfectSquare(int num) {
        if (num == 1) return true;
        int i = 1, j = num/2; // 注意下起始点，i从1开始可以避免0除的错误
        while (i <= j) {
            int m = (j-i) / 2 + i;
            if (num / m == m && num % m == 0) return true;
            if (num / m >= m) i = m+1;
            else j = m-1;
        }
        return false;
    }
};

/**
 * 367. 有效的完全平方数
 * 高级方法
 * 平方序列：1,4,9,16,..
 * 间隔：3,5,7,...
 * 间隔为等差数列，使用这个特性可以得到从 1 开始的平方序列。
 */
class Solution14 {
public:
    bool isPerfectSquare(int num) {
        int t = 1;
        while (num > 0) {
            num -= t;
            t += 2;
        }
        return num == 0;
    }
};

/**
 * 238. 除自身以外数组的乘积
 * 给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。
 *
 * 关键点在于用一个变量存储不断变化的临时值，这是经常用到的技巧
 */
class Solution15 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans(nums.size(), 1);

        // 从前向后，从后向前两次循环找到除了当前值之外所有值的乘积
        int prev = nums[0], after = nums[nums.size()-1]; // 用两个变量分别存储当前值之前和之后的所有值的乘积
        for (int i = 1; i < nums.size(); i++) {
            ans[i] = prev;
            prev *= nums[i];
        }

        for (int j = nums.size()-2; j>=0; j--) {
            ans[j] *= after;
            after *= nums[j];
        }

        return ans;
    }
};

/**
 * 628. 三个数的最大乘积
 * 给定一个整型数组，在数组中找出由三个数组成的最大乘积，并输出这个乘积。
 *
 * 思路为找出三个最大的数乘积或者两个最小的数和一个最大的数的乘积
 */
class Solution16 {
public:
    int maximumProduct(vector<int>& nums) {
        int m1=INT32_MIN, m2=INT32_MIN, m3=INT32_MIN;// m1>m2>m3
        int s1=INT32_MAX, s2=INT32_MAX; //s1<s2

        for (auto n : nums) {
            if (n > m1) {
                m3 = m2;
                m2 = m1;
                m1 = n;
            }
            else if (n > m2) {
                m3 = m2;
                m2 = n;
            }
            else if (n > m3)
                m3 = n;

            if (n < s1) {
                s2 = s1;
                s1 = n;
            }
            else if (n < s2)
                s2 = n;
        }
        return max(m1*m2*m3, s1*s2*m1);
    }
};


/**
 * 剑指 Offer 20. 表示数值的字符串
 * 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"0123"都表示数值，但"12e"、"1a3.14"、"1.2.3"、"+-5"、"-1E-16"及"12e+5.4"都不是。
 *
 * 典型的有限状态机题
 */
class Solution17 {
public:

    bool isNumber(string s) {
        vector<map<char, int>> vm = {
                {{'b', 0}, {'s', 1}, {'d', 2}, {'.', 4}},
                {{'.', 4}, {'d', 2}},
                {{'d', 2}, {'.', 3}, {'b', 8}, {'e', 5}},
                {{'d', 3}, {'e', 5}, {'b', 8}},
                {{'d', 3}},
                {{'s', 6}, {'d', 7}},
                {{'d', 7}},
                {{'d', 7}, {'b', 8}},
                {{'b', 8}}
        };
        set<int> st = {2,3,7,8};
        int p = 0;
        for (auto c: s) {
            char k;
            if (c >= '0' && c <= '9') k = 'd';
            else if (c==' ') k = 'b';
            else if (c == '.') k = '.';
            else if (c == 'e') k = 'e';
            else if (c == '+' || c== '-') k = 's';
            else return false;
            if (vm[p].count(k) <= 0) return false;
            p = vm[p][k];
        }
        return st.count(p) > 0;
    }
};


/**
 * 剑指 Offer 43. 1～n整数中1出现的次数
 * 输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
 * 例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。
 *
 * 这是一道找规律的题
 * 将数据按照cur位置分成high和low两部分，进而计算cur==1时的数量
 */
class Solution18 {
public:
    int countDigitOne(int n) {
        long high = n / 10, cur = n % 10, low = 0, digital = 1, res = 0;
        while (high != 0 || cur != 0) {  // 当 high 和 cur 同时为 0 时，说明已经越过最高位，因此跳出
            if (cur == 0) res += high * digital;  //
            else if (cur == 1) res += high *digital + low + 1;
            else res += (high+1) * digital;
            low += cur * digital; // 将 cur 加入 low ，组成下轮 low
            cur = high % 10; // 下轮 cur 是本轮 high 的最低位
            high = high/10; // 将本轮 high 最低位删除，得到下轮 high
            digital *= 10; // 位因子每轮 × 10
        }
        return res;
    }
};


/**
 * 剑指 Offer 44. 数字序列中某一位的数字
 * 数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
 * 请写一个函数，求任意第n位对应的数字。
 *
 * 还是找规律题，
 * 先确定第n为属于哪个数值范围，然后确定属于哪个数值，最后确定属于那位数
 */
class Solution19 {
public:
    int findNthDigit(int n) {
        long start = 1, digit = 1, count = 9;
        while (n > count) { // 说明n在该数位的数值范围内
            n = n - count;
            digit++;
            start*=10;
            count = 9*start*digit;
        }
        int num = start+(n-1)/digit; // 确定属于该数值范围内的某个数字
        return to_string(num)[(n-1)%digit] - '0';// 确定属于该数字的位数
    }
};


/**
 * 剑指 Offer 62. 圆圈中最后剩下的数字
 * 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
 *
 * 约瑟夫环问题
 * https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/javajie-jue-yue-se-fu-huan-wen-ti-gao-su-ni-wei-sh/
 */
class Solution20 {
public:
    int lastRemaining(int n, int m) {
        int ans = 0;
        for (int i = 2;i <= n; ++i)
            ans = (ans+m) % i;
        return ans;
    }
};


/**
 * 剑指 Offer 66. 构建乘积数组
 * 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。
 *
 * 从上下三角矩阵的角度来考虑
 */
class Solution21 {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int> dp(n, 1);
        for(int i = 1; i < n; ++i)
            dp[i] = dp[i-1]*a[i-1];

        int tmp = 1;
        for (int i = n-2; i >= 0; --i) {
            tmp *= a[i+1];
            dp[i] *= tmp;
        }
        return dp;
    }
};