#include<iostream>
#include<vector>
template<typename T>
T sum(const std::vector<T>& numbers)
{
    T total{};
    for(const auto& num:numbers)
    {
        total += num;
    }
    return total;
}
int main()
{
    std::vector<int> counts{2, 3, 5};
    std::vector<double> measurements{1.5, 2.0, 3.25};
    std::cout << sum(counts) << '\n';        // T 推断为 int
    std::cout << sum(measurements) << '\n';  // T 推断为 double
    return 0;
}