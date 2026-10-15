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
    if(newwidth <= 0 || newheight <= 0)
    {
        throw std::invalid_argument("Width and Height must be positive\n");
    }
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
    std::vector<double> widths{3.0,-1.0,0.0,5.0};
    std::vector<std::unique_ptr<Shape>> shapes;
    for(const auto& wid:widths)
    {
        double height = 4.0;
        try
        {
            shapes.emplace_back(std::make_unique<Ractangle>(wid,height));
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    std::cout << shapes.size() << '\n';
    for(const auto& shape:shapes)
    {
        printArea(*shape);
    }
    return 0;
}