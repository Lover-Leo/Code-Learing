#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<variant>
#include<vector>
#include<map>
#include<numeric>
enum class PraseErrorCode
{
    InvalidRecord,
    ExtraField
};
struct PraseError
{
    PraseErrorCode code;
    std::string message;
};
struct Measurement
{
    std::string name;
    double value;
};
struct AnalysisResult
{
    std::map<std::string, std::vector<double>> groups;
    int invalidCount{};
    int extraCount{};
};
using PraseResult = std::variant<Measurement,PraseError>;
PraseResult PraseMeasurement(const std::string& line)
{
    std::istringstream input(line);
    std::string name;
    std::string extra;
    double value;
    Measurement record;
    if(!(input >> name >> value))
    {
        return PraseError{PraseErrorCode::InvalidRecord,
            "Failed to read the file.\n"};
    }
    if(input >> extra)
    {
        return PraseError{PraseErrorCode::ExtraField,
            "There is extra data.\n"};
    }
    else
    {
        record.name = name;
        record.value = value;
        return record;
    }
}
void writeReport(
    std::ostream& output,
    const std::map<std::string,std::vector<double>>& groups)
{
    for(const auto& [name,value]:groups)
    {
        double total = std::accumulate(
            value.begin(),value.end(),0.0);
        double mean = total/value.size();
        output << name << ':' << "count:"
            << value.size() << ','
            << "mean:" << mean << '\n';
    }
}
AnalysisResult analyze(std::istream& input)
{
    AnalysisResult analysis;
    std::string line;

    while (std::getline(input, line))
    {
        auto result = PraseMeasurement(line);
        if(auto* record = std::get_if<Measurement>(&result))
        {
            analysis.groups[record->name].push_back(record->value);
        }
        else
        {
            const auto& error = std::get<PraseError>(result);
            switch(error.code)
            {
                case PraseErrorCode::ExtraField:
                {
                    analysis.extraCount += 1;
                    break;
                }
                case PraseErrorCode::InvalidRecord:
                {
                    analysis.invalidCount += 1;
                    break;
                }
            }
        }
    }
    return analysis;
}
int main()
{
    std::ifstream file("measurements.txt");
    if(!file)
    {
        std::cerr << "Failed to open.\n";
        return 1;
    }
    AnalysisResult analysis = analyze(file);
    writeReport(std::cout,analysis.groups);
    std::ofstream report("report.txt");
    if(!report)
    {
        std::cerr << "Failed to open the file.\n";
    }
    writeReport(report,analysis.groups);
    std::map<std::string, std::vector<double>> testGroups
    {
        {"sensorA", {20.0, 30.0}}
    };
    std::ostringstream output;
    writeReport(output,testGroups);
    std::cout << std::boolalpha
          << (output.str() == "sensorA:count:2,mean:25\n")
          << '\n';
    std::cout << "Invalid records: " << analysis.invalidCount << '\n';
    std::cout << "Extra fields: " << analysis.extraCount << '\n';
    return 0;
}