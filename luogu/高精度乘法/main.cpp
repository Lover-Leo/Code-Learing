#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string a, b;
    std::cin >> a >> b;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());

    std::vector<char> factor_1;
    std::vector<char> factor_2;

    for (char ch : a)
    {
        factor_1.push_back(ch);
    }

    for (char ch : b)
    {
        factor_2.push_back(ch);
    }

    int n = static_cast<int>(factor_1.size());
    int m = static_cast<int>(factor_2.size());

    std::vector<int> result(n + m, 0);

    // 每一位分别相乘，累加到对应位置
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            result[i + j] += (factor_1[i] - '0')
                           * (factor_2[j] - '0');
        }
    }

    // 从低位到高位处理进位
    for (int i = 0; i < n + m - 1; i++)
    {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int highest = n + m - 1;

    while (highest > 0 && result[highest] == 0)
    {
        highest--;
    }

    for (int i = highest; i >= 0; i--)
    {
        std::cout << result[i];
    }

    std::cout << '\n';
    return 0;
}