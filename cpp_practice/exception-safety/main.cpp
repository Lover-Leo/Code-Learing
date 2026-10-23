#include<iostream>
#include<vector>
#include<stdexcept>
void updated(std::vector<int>& values)
{
    auto tempary = values;
    tempary.push_back(30);
    throw std::runtime_error("更新失败");
    tempary.push_back(40);
    tempary.swap(values);
}
int main()
{
    std::vector<int> values{10,20};
    try
    {
        updated(values);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    for(const auto& value:values)
    {
        std::cout << value << '\n';
    }
    return 0;
}