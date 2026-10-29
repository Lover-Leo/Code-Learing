#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
//输入一个不小于 100 且小于 1000，同时包括小数点后一位的一个浮点数，
//例如 123.4 ，要求把这个数字翻转过来，变成 4.321 并输出。
int main()
{
    string a;
    cin >> a;
    reverse(a.begin(),a.end());
    std::cout << a << '\n';
    return 0;
}