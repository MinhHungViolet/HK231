#include <iostream>
#include <math.h>
using namespace std;
class Point
{
private:
    double x, y;

public:
    Point()
    {
        /*  
         * Set zero x-y coordinate
         */
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        /*  
         * Set x and y coordinates to the given values
         */
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        /*  
         * Set the x coordinate to the given value
         */
        this->x = x;
    }

    void setY(double y)
    {
        /*  
         * Set the y coordinate to the given value
         */
        this->y = y;
    }

    double getX() const
    {
        /*  
         * Return the x coordinate
         */
        return x;
    }

    double getY() const
    {
        /*  
         * Return the y coordinate
         */
        return y;
    }

    double distanceToPoint(const Point& pointA) const
    {
        /*  
         * Calculate the distance from this point to point A in the coordinate plane
         */
        double dx = x - pointA.x;
        double dy = y - pointA.y;
        return sqrt(dx * dx + dy * dy);
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        center = Point();
        radius = 0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    Circle(const Circle &circle)
    {
        /*  
         * Copy constructor that creates a new Circle object with the same center and radius as the given Circle object
         */
        center = circle.center;
        radius = circle.radius;
    }
    
    void setCenter(Point point)
    {
        /*  
         * Set the center point to the given point
         */
        center = point;
    }

    void setRadius(double radius)
    {
        /*  
         * Set the radius to the given value
         */
        this->radius = radius;
    }

    Point getCenter() const
    {
        /*  
         * Return the center point
         */
        return center;
    }

    double getRadius() const
    {
        /*  
         * Return the radius
         */
        return radius;
    }
    
    void printCircle() const
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", center.getX(), center.getY(), radius);
    }
    
    double area() const
    {
        /*  
         * Calculate the area of the circle
         */
        return M_PI * radius * radius;
    }

    double circumference() const
    {
        /*  
         * Calculate the circumference of the circle
         */
        return 2 * M_PI * radius;
    }

    bool contains(const Point& point) const
    {
        /*  
         * Check if the circle contains the given point
         */
        double distance = center.distanceToPoint(point);
        return distance <= radius;
    }
};