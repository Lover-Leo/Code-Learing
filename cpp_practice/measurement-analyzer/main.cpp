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
struct Diagnostic
{
    int lineNumber;
    PraseError error;
};
struct AnalysisResult
{
    std::map<std::string, std::vector<double>> groups;
    int invalidCount{};
    int extraCount{};
    std::vector<Diagnostic> diagnostic;
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
            "Failed to read the file."};
    }
    if(input >> extra)
    {
        return PraseError{PraseErrorCode::ExtraField,
            "There is extra data."};
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
    int lineNumber = 0;
    while (std::getline(input, line))
    {
        lineNumber++;
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
            analysis.diagnostic.push_back(
                Diagnostic{lineNumber,error}
            );
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
    for(const auto& Diag:analysis.diagnostic)
    {
        std::cerr << "Line" << Diag.lineNumber
            << ':' << Diag.error.message << '\n';
    }
    writeReport(std::cout,analysis.groups);
    std::ofstream report("report.txt");
    if(!report)
    {
        std::cerr << "Failed to open the file.\n";
    }
    writeReport(report,analysis.groups);

    //测试部分1
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
    std::istringstream testInput(
        "sensorA 20\n"
        "sensorB wrong\n"
        "sensorC 18 extra\n"
        "sensorA 30\n"
    );

    auto tested = analyze(testInput);

    std::map<std::string, std::vector<double>> expectedGroups{
        {"sensorA", {20.0, 30.0}}
    };

    bool passed = tested.groups == expectedGroups
            && tested.invalidCount == 1
            && tested.extraCount == 1;

    std::cout << std::boolalpha
            << "Analyze test: " << passed << '\n';

    //测试部分2
    std::istringstream emptyInput("");
    auto emptyResult = analyze(emptyInput);

    bool emptyPassed = emptyResult.groups.empty()
                    && emptyResult.diagnostic.empty()
                    && emptyResult.invalidCount == 0
                    && emptyResult.extraCount == 0;

    std::cout << std::boolalpha
            << "Empty input test: " << emptyPassed << '\n';
    return 0;
}