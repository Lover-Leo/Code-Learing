#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
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
    while(std::getline(file,line))
    {
        ++lineNumber;
        std::istringstream input(line);
        std::string name;
        std::string extra;
        double value{};
        if(!(input >> name >> value))
        {
            std::cerr << "Failed to read data.\n";
            continue;
        }
        if(input >> extra)
        {
            std::cout << "There is extra data.\n";
        }
        else
        {
            std::cout << name << ':' << value << '\n';
        }
    }
    return 0;
}