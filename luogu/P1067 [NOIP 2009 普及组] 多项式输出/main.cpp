#include <iostream>
#include <vector>
#include <string>

int main()
{
    int n;
    std::cin >> n;

    std::vector<int> num(n + 1);
    std::string ans;

    for (int i = 0; i < n + 1; i++)
    {
        std::cin >> num[i];
    }

    int j = n;

    for (int i = 0; i < n + 1; i++)
    {
        if (num[i] == 0)
        {
            j--;
            continue;
        }

        // 正数且前面已有项，才添加加号
        if (num[i] > 0 && !ans.empty())
        {
            ans += '+';
        }

        // 常数项完整保留；非常数项省略系数中的数字 1
        if (j == 0 || (num[i] != 1 && num[i] != -1))
        {
            ans += std::to_string(num[i]);
        }
        else if (num[i] == -1)
        {
            ans += '-';
        }

        if (j > 1)
        {
            ans += "x^";
            ans += std::to_string(j);
        }
        else if (j == 1)
        {
            ans += 'x';
        }

        j--;
    }

    // 所有系数都是 0
    if (ans.empty())
    {
        ans = "0";
    }

    std::cout << ans << '\n';
    return 0;
}