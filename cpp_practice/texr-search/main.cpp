#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<fstream>
#include<set>
#include<cctype>
std::string normalizeWord(std::string word)
{
    std::string result;
    for(unsigned char ch:word)
    {
        if(std::isalnum(ch))
        {
            result += static_cast<char>(std::tolower(ch));
        }
    }
    return result;
}
int main()
{
    std::ifstream file("text.txt");
    std::string line;
    std::string word;
    std::map<std::string,int> counts;
    std::map<std::string,std::set<int>> locations;
    int lineNumber = 0;
    while(std::getline(file,line))
    {
        ++lineNumber;
        std::istringstream input(line);
        while(input >> word)
        {
            if(!word.empty())
            {
                locations[word].insert(lineNumber);
                ++counts[word];
            }
        }
    }
    std::string query;
    do
    {
        std::cout << "Entry a word:";
        if(!(std::cin >> query))
        {
            std::cerr << "Failed to entry a word\n";
            return 1;
        }
        if(query == "quit")
        {
            break;
        }
        else
        {
            query = normalizeWord(query);
            auto it = counts.find(query);
            if(it != counts.end())
            {
                std::cout << it->first << ":" << it->second << '\n';
                std::cout << "line:";
                for(int number:locations.at(query))
                {
                    std::cout << number << ' ';
                }
                std::cout << '\n';
            }
            else
            {
                std::cout << "Not Found\n";
            }
        }
    }while(query != "quit");
    return 0;
}