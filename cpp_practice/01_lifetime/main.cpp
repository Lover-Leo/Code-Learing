#include<iostream>
#include<string>
class Tracer
{
    private:
        std::string Name;
    public:
        Tracer(const std::string newName);
        ~Tracer();
};
Tracer::Tracer(const std::string newName):Name(newName)
{
    std::cout << "创造" << Name << '\n';
}
Tracer::~Tracer()
{
    std::cout << "销毁" << Name << '\n';
}
int main()
{
    Tracer first{"first"};
    Tracer second{"second"};
    Tracer third{"third"};

    return 0;
}