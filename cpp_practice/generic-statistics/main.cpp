#include<iostream>
#include<vector>
#include<stdexcept>
#include<numeric>
#include<algorithm>
#include<iterator>
#include<optional>
template<typename T>
concept Number = std::integral<T> || std::floating_point<T>;
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
template<typename T,typename Predicate>
std::vector<T> filter(
    const std::vector<T>& values,
    Predicate predicate
)
{
    std::vector<T> result;
    std::copy_if(
        values.begin(),
        values.end(),
        std::back_inserter(result),
        predicate
    );
    return result;
}
template<Number T>
class Statistics
{
    private:
        std::vector<T> values;
    public:
        void add(T value)
        {
            values.push_back(value);
        }
        double mean() const
        {
            return average(values);
        }
        template<typename Predicate>
        std::vector<T> select(Predicate predicate) const
        {
            return filter(values,predicate);
        };
        std::optional<double> tryMean() const
        {
            if (values.empty())
            {
                return std::nullopt;
            }

            return average(values);
        }
        template<typename Operation>
        std::vector<T> transformed(Operation operation) const
        {
            std::vector<T> result;
            std::transform(
                values.begin(),values.end(),
                std::back_inserter(result),
                operation);
            return result;
        }
};
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
    std::vector <double> selected;
    selected = filter(values,[threshold](double value)
{
    return value > threshold;
});
    for(const auto& se:selected)
    {
        std::cout << se << '\n';
    }
    selected = filter(values,[](double value)
{
    return value < 0.0;
});
    for(const auto& se:selected)
    {
        std::cout << se << '\n';
    }
    Statistics<int> counts;
    counts.add(2);
    counts.add(3);
    std::cout << counts.mean() << '\n';

    Statistics<double> measurements;
    measurements.add(1.5);
    measurements.add(2.0);
    measurements.add(3.25);
    std::cout << measurements.mean() << '\n';
    auto selectedMeasurements = measurements.select(
    [](double value)
    {
        return value > 1.8;
    });
    for(const auto& se:selectedMeasurements)
    {
        std::cout << se << '\n';
    }
    auto result = measurements.tryMean();
    if (result.has_value())
    {
        std::cout << *result << '\n';
    }
    else
    {
        std::cout << "No data\n";
    }
    Statistics<double> emptyStats;
    result = emptyStats.tryMean();
    if(result.has_value())
    {
        std::cout << *result << '\n';
    }
    else
        std::cout << "No data\n";
    auto doubled = measurements.transformed([](double value)
    {
        return value * 2.0;
    });
    for(const auto& dou:doubled)
    {
        std::cout << dou << '\n';
    }
    return 0;
}