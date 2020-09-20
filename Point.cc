#include "Point.hh"

#include <iostream>
#include <cmath>
using namespace std;

/**Constructor*/
Point::Point (double temp_x, double temp_y):
	x(temp_x) , y(temp_y) {}

/**Returns the slope of the line connecting two points*/
double Point::slope (const Point& p) const {
	double Xvariation = p.getX() - x;
	double Yvariation = p.getY() - y;
	return Yvariation/Xvariation;
}

/*Returns true if p2 is at the left of the segment that goes through p1 and this*/
bool Point::leftof(const Point& p1, const Point& p2) const{
	return (p1.getX() - x)*(p2.getY() - y) > (p1.getY()-y)*(p2.getX()-x);
}

/**Print the x and y coordinates of the point*/
void Point::printPoint () const{
	cout << x << " " << y << " ";
}

/**Returns the x coordinate of the point*/
double Point::getX () const{
	return x;
}

/**Returns the y coordinate of the point*/
double Point::getY () const{
	return y;
}

/**Returns the distance between two given points*/
double Point::distance (const Point & p2) const{
	double dist;
	double Xvariation = p2.getX () - x;
	double Yvariation = p2.getY () - y;
	
	dist = sqrt (Xvariation * Xvariation + Yvariation * Yvariation );
	return dist;
}

Point Point::operator- (const Point & p2) const{
	double newx = x - p2.getX();
	double newy = y - p2.getY();
	return Point(newx, newy);
}

Point Point::operator+ (const Point & p2) const{
	double newx = x + p2.getX();
	double newy = y + p2.getY();
	return Point(newx, newy);
}

Point Point::operator* (double i) const{
	double newx = x*i;
	double newy = y*i;
	return Point(newx, newy);
}

bool Point::operator== (const Point & p2) const{
	return abs(x-p2.getX())<1e-12 and abs(y-p2.getY())<1e-12;
}

bool Point::operator!= (const Point & p2) const{
	return not operator==(p2);
}

