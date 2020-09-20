#ifndef ConvexPolygon_hh
#define ConvexPolygon_hh
#include "Point.hh"

#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <pngwriter.h>

using color = vector <double>;


class ConvexPolygon{
public:

	/**Constructors*/
	ConvexPolygon();
	ConvexPolygon(const vector<Point>& Points);
	
	/**Retorna el vertex i del poligon*/
	const Point& operator[] (int i) const;

	/**Prints the identifier and the vertices of the polygon*/
	void print () const;
	
	/**Returns the area of the polygon*/
	double area () const;
	
	/**Returns the perimeter of the polygon*/
	double perimeter () const;
	
	/**Returns the number of vertices of the polygon*/
	int vertices () const;
	
	/**Returns vertex*/ //canviar el nom per claretat
	vector<Point> SetOfVertices () const;
	
	/**Returns the centroid of the polygon*/
	Point centroid() const;
	
	/**Given two polygon, the first one is updated to their intersection*/
	ConvexPolygon intersection (const ConvexPolygon & p2)const ;
	
	/**Given two polygon, the first one is updated to their union*/
	ConvexPolygon unions (const ConvexPolygon & p2) const; //COM FER PER A QUE NO HO CONFONGUI AMB EL TIPUS UNION

	/**Given a point, the function returns whether or not it is inside the polygon*/
	bool PointInside (const Point & p) const;
	
	/**Given two polygons, returns whether or not the first one is inside the second*/
	bool inside (const ConvexPolygon & p2) const;
	
	/**Sets a new color for the polygon*/
	void setcol (double R, double G, double B);

	/**Prints the color for the polygon*/
	void checkcol () const;

	/**Returns the color of the polygon a vector of size 3**/
	color getcol() const;
	
	/**Returns the bouning box of the given polygons*/
	void bbox (const vector<ConvexPolygon> & polygons);

	
private:
	vector<Point> vertex;
	string name;
	color RGB;	
};

#endif
