#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Abstract base class for concrete Shape classes
class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Concrete Shape classes
class Circle : public Shape
{
public:
    explicit Circle(double radius) : m_Radius(radius) {}

    void draw() const override
    {
        cout << "Drawing a circle with radius " << m_Radius << endl;
    }

private:
    double m_Radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(double width, double height) : m_Width(width), m_Height(height) {}

    void draw() const override
    {
        cout << "Drawing a rectangle with width " << m_Width << " and height " << m_Height << endl;
    }

private:
    double m_Width;
    double m_Height;
};

class Triangle : public Shape
{
public:
    Triangle(double side1, double side2, double side3) : m_Side1(side1), m_Side2(side2), m_Side3(side3) {}

    void draw() const override
    {
        cout << "Drawing a triangle with sides " << m_Side1 << ", " << m_Side2 << ", and " << m_Side3 << endl;
    }

private:
    double m_Side1;
    double m_Side2;
    double m_Side3;
};

class CompositeShape : public Shape
{
public:
    void addShape(Shape& shape)
    {
        m_shapes.push_back(&shape);
    }

    void removeShape(Shape& shape)
    {
        for(auto it=m_shapes.begin();it!=m_shapes.end();it++)
        {
            if (&shape==*it)
            {
                m_shapes.erase(it);
                break;
            }
        }
    }

    void draw() const override
    {
        for(const auto& shape : m_shapes)
        {
            shape->draw();
        }
    }
private:
    vector<Shape*> m_shapes;
};

int main()
{
    Circle c(5);
    Rectangle r(10, 20);
    Triangle t(3, 4, 5);

    CompositeShape cs;
    cs.addShape(c);
    cs.addShape(r);
    cs.addShape(t);
    
    cs.draw();

    cs.removeShape(r);

    cs.draw();

    return 0;
}
