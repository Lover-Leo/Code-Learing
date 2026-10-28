#include<iostream>
#include<cctype>
//输入一个小写字母，输出其对应的大写字母。例如输入 q[回车] 时，会输出 Q。
int main()
{
    char ch;
    std::cin >> ch;
    std::cout << char(ch-32);
    return 0;
}