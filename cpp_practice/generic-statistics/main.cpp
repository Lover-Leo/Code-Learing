#include<iostream>
#include<vector>
#include<stdexcept>
#include<numeric>
#include<algorithm>
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
template<typename T>
double average(const std::vector<T>& numbers)
{
    if(numbers.empty())
    {
        throw std::invalid_argument("Don't be empty\n");
    }
    double aver = std::accumulate(
        numbers.begin(),numbers.end(),0.0)/numbers.size();
    return aver;
}
template<typename T>
T maximum(const std::vector<T>& numbers)
{
     if(numbers.empty())
    {
        throw std::invalid_argument("Don't be empty\n");
    }
    auto it = std::max_element(numbers.begin(),numbers.end());
    return (*it);
}
int main()
{
    try
    {
        std::cout << average(std::vector<int> {2,3}) <<'\n';
        std::cout << average(std::vector<double> {1.5,2.0,3.25}) << '\n';
        std::cout << maximum(std::vector<double> {1.5,2.0,3.25}) << '\n';
        std::cout << maximum(std::vector<int> {-8,-3,-10}) << '\n';
        std::cout << maximum(std::vector<int> {});
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::vector<double> values {1.5,2.0,3.25,4.0};
    double threshold = 2.0;
    std::cout << std::count_if(
        values.begin(),values.end(),
        [threshold](double value)
        {
            return value > threshold;
        }
    ) << '\n';
    std::vector<double> selected;
    std::copy_if(
        values.begin(),values.end(),
        std::back_inserter(selected),
        [threshold](double value)
        {
            return value > threshold;
        }
    );
    std::sort(
    selected.begin(),
    selected.end(),
    [](double a, double b)
    {
        return a > b;
    });
    for(const auto& se:selected)
    {
        std::cout << se << '\n';
    }
    if (selected.empty())
{
    std::cout << "No matching values\n";
}
else
{
    std::cout << "Average: " << average(selected) << '\n';
}
    return 0;
}