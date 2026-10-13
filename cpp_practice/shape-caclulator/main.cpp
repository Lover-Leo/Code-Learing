#include<iostream>
class Shape
{
    public:
        virtual double area() const
        {
            return 0.0;
        }
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
    Ractangle rectangle{3.0,4.0};
    printArea(rectangle);
    return 0;
}