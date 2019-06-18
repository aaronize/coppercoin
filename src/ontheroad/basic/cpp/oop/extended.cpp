#include <iostream>

using namespace std;

// 
class Shape
{
    public:
        void setWidth(int w);
        void setHeight(int h);
    
    protected:
        int width;
        int height;
};

void Shape::setWidth(int w)
{
    width = w;
}
void Shape::setHeight(int h)
{
    height = h;
}

// 
class PaintCost
{
    public:
        int getCost(int area);
};

int PaintCost::getCost(int area)
{
    return area * 70;
}

class Rectangle: public Shape, public PaintCost
{
    public:
        int getArea()
        {
            return (width * height);
        }
};

int main(void)
{
    Rectangle rect;
    int area;

    rect.setWidth(5);
    rect.setHeight(7);

    area = rect.getArea();

    cout << "Total area: " << rect.getArea() << endl;

    cout << "Tatal paint cost: $" << rect.getCost(area) << endl;

    return 0;
}
