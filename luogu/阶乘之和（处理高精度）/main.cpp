#include <iostream>

//用高精度计算出 S=1!+2!+3!+⋯+n!（n≤50）。

int main() {
    int n;
    std::cin >> n;

    // 低位在前，每个数组元素保存一位十进制数字。
    int factorial[100] = {};  // 当前阶乘
    int total[100] = {};      // 阶乘总和

    factorial[0] = 1;  // 初始值为 1

    for (int i = 1; i <= n; i++) {
        // 第一步：当前阶乘乘以 i。
        int carry = 0;

        for (int j = 0; j < 100; j++) {
            int value = factorial[j] * i + carry;

            factorial[j] = value % 10;  // 当前位
            carry = value / 10;        // 向高位进位
        }

        // 第二步：把当前阶乘加入总和。
        carry = 0;

        for (int j = 0; j < 100; j++) {
            int value = total[j] + factorial[j] + carry;

            total[j] = value % 10;
            carry = value / 10;
        }
    }

    // 找到最高的非零位，避免输出前导零。
    int highest = 99;

    while (highest > 0 && total[highest] == 0) {
        highest--;
    }

    // 从高位向低位输出。
    for (int j = highest; j >= 0; j--) {
        std::cout << total[j];
    }

    std::cout << '\n';
    return 0;
}