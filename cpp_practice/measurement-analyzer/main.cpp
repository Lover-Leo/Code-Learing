#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<variant>
#include<vector>
#include<map>
#include<numeric>
struct Measurement
{
    std::string name;
    double value;
};
using PraseResult = std::variant<Measurement,std::string>;
PraseResult PraseMeasurement(const std::string& line)
{
    std::istringstream input(line);
    std::string name;
    std::string extra;
    double value;
    Measurement record;
    if(!(input >> name >> value))
    {
        return "Failed to read.\n";
    }
    if(input >> extra)
    {
        return "There is extra data.\n";
    }
    else
    {
        record.name = name;
        record.value = value;
        return record;
    }
}
int main()
{
    std::ifstream file("measurements.txt");
    if(!file)
    {
        std::cerr << "Failed to open.\n";
        return 1;
    }
    std::string line;
    int lineNumber = 0;
    std::map<std::string,std::vector<double>> groups;
    while(std::getline(file,line))
    {
        ++lineNumber;
        auto result = PraseMeasurement(line);
        if(auto* record = std::get_if<Measurement>(&result))
        {
            std::cout << record->name << ':' << record->value << '\n';
            records.push_back(*record);
            groups[record->name].push_back(record->value);
        }
        else
        {
            std::cerr << "line:" << lineNumber << ':'
                << std::get<std::string>(result);
        }
    }
    for(const auto& [name,value]:groups)
    {
        double total = std::accumulate(
            value.begin(),value.end(),0.0);
        double mean = total/value.size();
        std::cout << name << ':' << "count:"
            << value.size() << ','
            << "mean:" << mean << '\n';
    }
    return 0;
}