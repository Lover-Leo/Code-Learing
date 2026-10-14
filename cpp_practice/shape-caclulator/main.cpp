#include<iostream>
#include<memory>
#include<vector>
class Shape
{
    public:
        virtual double area() const = 0;
        virtual ~Shape() = default;
};
class Ractangle : public Shape
{
    private:
        double width;
        double height;
    public:
        Ractangle(const double newwidth,const double newheight);
        double area() const override;
};
Ractangle::Ractangle(const double newwidth,const double newheight)
:width(newwidth),height(newheight)
{

}
double Ractangle::area() const
{
    return (height * width);
}
void printArea(const Shape& shape)
{
    std::cout << shape.area() << '\n';
}
int main()
{
    auto first = std::make_unique<Ractangle>(3.0,4.0);
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::move(first));
    std::cout << "first:" << static_cast<bool>(first) << '\n';
    std::cout << "size:" << shapes.size() << '\n';
    printArea(*shapes.at(0));
    return 0;
}