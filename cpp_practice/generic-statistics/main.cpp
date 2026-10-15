#include<iostream>
#include<vector>
#include<stdexcept>
#include<numeric>
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
    double aver = std::accumulate(numbers.begin(),numbers.end(),0.0)/numbers.size();
    return aver;
}
int main()
{
    std::vector<int> counts{2, 3, 5};
    std::vector<double> measurements{1.5, 2.0, 3.25};
    std::cout << sum(counts) << '\n';        // T 推断为 int
    std::cout << sum(measurements) << '\n';  // T 推断为 double
    try
    {
        std::cout << average(std::vector<int> {2,3}) <<'\n';
        std::cout << average(std::vector<double> {1.5,2.0,3.25}) << '\n';
        std::cout << average(std::vector<int> {}) << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}