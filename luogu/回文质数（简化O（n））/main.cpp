#include <iostream>
#include <vector>
#include <algorithm>

/*# P1217 [USACO1.5] 回文质数 Prime Palindromes

## 题目描述

因为 $151$ 既是一个质数又是一个回文数（从左到右和从右到左是看一样的），所以 $151$ 是回文质数。

写一个程序来找出范围 $[a,b] (5 \le a < b \le 100,000,000)$（一亿）间的所有回文质数。

## 输入格式

第一行输入两个正整数 $a$ 和 $b$。

## 输出格式

输出一个回文质数的列表，一行一个。

## 输入输出样例 #1

### 输入 #1

```
5 500

```

### 输出 #1

```
5
7
11
101
131
151
181
191
313
353
373
383

```

## 说明/提示

提示 1: 找出所有的回文数再判断它们是不是质数（素数）.

提示 2: 要产生正确的回文数，你可能需要几个像下面这样的循环。

产生长度为 $5$ 的回文数：*/
bool isPrime(int n) {
    if (n < 2) {
        return false;
    }

    if (n % 2 == 0) {
        return n == 2;
    }

    // 偶数已经排除，只检查奇数因数。
    for (int d = 3; d <= n / d; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }

    return true;
}

// 生成奇数位回文数。
// 12 → 121，123 → 12321
int makePalindrome(int prefix) {
    int result = prefix;
    int tail = prefix / 10;

    while (tail > 0) {
        result = result * 10 + tail % 10;
        tail /= 10;
    }

    return result;
}

int main() {
    int a, b;
    std::cin >> a >> b;

    std::vector<int> answer;

    // 单独处理偶数位回文质数 11。
    if (a <= 11 && 11 <= b) {
        answer.push_back(11);
    }

    // b ≤ 1亿，奇数位回文数最多只需要考虑7位。
    for (int prefix = 1; prefix <= 9999; prefix++) {
        int num = makePalindrome(prefix);

        if (num > b) {
            break;
        }

        if (num >= a && isPrime(num)) {
            answer.push_back(num);
        }
    }

    // 因为11是单独加入的，最后统一排序。
    std::sort(answer.begin(), answer.end());

    for (int num : answer) {
        std::cout << num << '\n';
    }

    return 0;
}
