#include "ConvexPolygon.hh"

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <stdlib.h>

#include <algorithm>
#include <pngwriter.h>
using namespace std;

using color = vector <double>;

//Comparator to sort points by angle to min_x
struct Comparator {
	Point P0;
	bool operator () (const Point& p1, const Point& p2)const{
		return not P0.leftof(p1, p2);
	}
};

//Returns the index of the Point with the minimum x coordinate from a vector
static int min_x (const vector<Point>& Points){
	double minX = Points[0].getX();
	int index=0;
	int n = Points.size();
	for (int i = 1; i<n ; i++) {
		if 	(Points[i].getX()<minX or 
			(Points[i].getX()==minX and Points[i].getY()<Points[index].getY())) {
			minX=Points[i].getX();
			index=i;
		}
	}
	return index;
}

//Comparator to sort points according to their coordinates
static bool comp (const Point& p1, const Point& p2){
	if (p1.getY() != p2.getY()) return p1.getY() < p2.getY();
	else return p1.getX() < p2.getX();
}

//Deletes a certain point from a vector
static void DeleteFromArray (int i , vector<Point>& NewPoints){
	int n = NewPoints.size();
	for (int k = i; k<n-1 ; k++){
		swap(NewPoints[k], NewPoints[k+1]);
	}
	NewPoints.pop_back();
}

//Deletes repeated point from vector
static void DeleteRepeated (vector<Point>& NewPoints){
	sort (NewPoints.begin(), NewPoints.end(), comp);
	int n = NewPoints.size();
	for (int i = 0; i<n-1; i++){
		if (NewPoints[i] == NewPoints[i+1]) {
			DeleteFromArray (i+1, NewPoints);
			n--;
			i--;
		}
	}	
}

//Given a polygon with multiple aligned vertices per edge, it deletes those points
static void DeleteAligned(vector<Point>& NewPoints){
	int n = NewPoints.size();
	for (int i = 0; i<n-2; i++){
		if (NewPoints[i].slope(NewPoints[i+1])==NewPoints[i].slope(NewPoints[i+2])) {
			DeleteFromArray (i+1, NewPoints);
			n--;
			i--;
		}
	}	
}

//Implementation of the convexhull
static vector<Point> ConvexHull(const vector<Point>& Points){
	vector<Point> NewPoints = Points;
	int n = NewPoints.size();
	if (n==0) return NewPoints;
	DeleteRepeated(NewPoints);
	int index = min_x(NewPoints);
	swap(NewPoints[0], NewPoints[index]);
	Comparator c = {NewPoints[0]};
	sort (NewPoints.begin()+1, NewPoints.end() , c);
	n = NewPoints.size();
	if (n <= 3) return NewPoints;
	vector<Point> polygon = {NewPoints[0], NewPoints[1], NewPoints[2]};
	for (int i = 3; i < n; i++){
		int j = polygon.size()-2;
		while (polygon[j].leftof(polygon[j+1], NewPoints[i]) and j>=0){
			polygon.pop_back();
			j--;
		}
		polygon.push_back(NewPoints[i]);
	}
	DeleteAligned(NewPoints);	
	return polygon;
}

/**Retorna el vertex i del poligon*/
const Point& ConvexPolygon::operator[] (int i) const{
		return vertex[i];
}


/**Constructor*/
ConvexPolygon::ConvexPolygon(){}
/**Constructor*/
ConvexPolygon::ConvexPolygon(const vector<Point>& points){
	vertex = ConvexHull(points);
	RGB={0, 0, 0};	
}

/**Prints the identifier and the vertices of the polygon*/
void ConvexPolygon::print () const{
	for (Point p : vertex) {
		p.printPoint();
	}
	cout << endl;
}

/**Returns the number of vertices of the polygon*/
int ConvexPolygon::vertices () const {
	int size = vertex.size();
	return size;
}

/**Returns the area of the polygon (Shoelace formula)*/
//Precondicio: vertex.size-1 >= 3
double ConvexPolygon::area () const {
	double area=0;
	int n = vertex.size();
	if (n <= 2) return area;
	//INTRODUIR SORTIDA D'ERROR if(n<3) return 0;
	for (int i = 0; i<n-1; i++){
		area+=vertex[i].getX()*vertex[i+1].getY();
		area-=vertex[i+1].getX()*vertex[i].getY();
	}
	area+=vertex[n-1].getX()*vertex[0].getY();
	area-=vertex[0].getX()*vertex[n-1].getY();
	return area/2;
}

/**Returns the perimeter of the polygon*/

double ConvexPolygon::perimeter () const {
	int n = vertex.size();
	double perimeter = 0;
	for(int i = 1; i<n; i++){
		perimeter += vertex[i].distance(vertex[i-1]);
	}
	if (n > 2) perimeter += vertex[n-1].distance(vertex[0]);
	return perimeter;
}

/**Returns the vertices of the polygon*/
vector<Point> ConvexPolygon::SetOfVertices () const{
	return vertex;
}

/**Returns the centroid of the polygon*/
Point ConvexPolygon::centroid() const{
	double cx=0;
	double cy=0;
	int n = vertex.size();
	for (int i = 0; i<n-1; i++){
		cx+=(vertex[i].getX()+vertex[i+1].getX())*(vertex[i].getX()*vertex[i+1].getY()-vertex[i+1].getX()*vertex[i].getY());
		cy+=(vertex[i].getY()+vertex[i+1].getY())*(vertex[i].getX()*vertex[i].getY()-vertex[i+1].getX()*vertex[i].getY());
	}
	cx+=(vertex[n-1].getX()+vertex[0].getX())*(vertex[n-1].getX()*vertex[0].getY()-vertex[0].getX()*vertex[n-1].getY());
	cy+=(vertex[n-1].getY()+vertex[0].getY())*(vertex[n-1].getX()*vertex[0].getY()-vertex[0].getX()*vertex[n-1].getY());
	return Point(cx/(6*(this->area())), cy/(6*(this->area())));
}

//Given two segments (two points per segment) pushes their intersection into the vector points
static void SegIntersec (const Point& p1, const Point& p2, const Point& q1, const Point& q2, vector<Point>& points){
	Point v = p2 - p1;
	Point u = q2 - q1;
	if (v.getX()==0 or u.getX()==0){
		if ((v.getX()==0) xor (u.getX()==0)){
			if (v.getX()==0){
				double k = (p1.getX()-q1.getX())/u.getX();
				if (k>=0 and k<=1){
					Point p(q1+u*k);
					double kp = (p.getY()-p1.getY())/v.getY();
					if(kp>=0 and kp<=1) points.push_back(p);
				}
			}else{
				double k = (q1.getX()-p1.getX())/v.getX();
				if (k>=0 and k<=1){
					Point p(p1+v*k);
					double kp = (p.getY()-q1.getY())/u.getY();
					if(kp>=0 and kp<=1) points.push_back(p);
				}
			}
		}
	}else {
		double mv = v.getY()/v.getX();
		double mu = u.getY()/u.getX();
		if (mv != mu){ 
			double kp=(p1.getY()+mv*(q1.getX()-p1.getX()) - q1.getY())/(u.getY()-mv*u.getX());
			double k= (q1.getX()+kp*u.getX()-p1.getX())/v.getX();
			Point inter(q1 + u*kp);
			if (k<=1 and k>=0 and kp<=1 and kp>=0){
				points.push_back(inter);
			}
		}
	}
}

//Given two polygon, the first one is updated to their intersection
ConvexPolygon ConvexPolygon::intersection (const ConvexPolygon & p2)const{
	int n1 = vertex.size();
	int n2 = p2.vertices();
	vector<Point> points;
	for (Point p : vertex){
		if (p2.PointInside(p)) {
			points.push_back(p) ;
		}
	}
	for (Point p :p2.SetOfVertices()){
		if (this->PointInside(p)) {
			points.push_back(p) ;
		}
	}
	for (int i = 0; i<n1; i++){
		for (int j = 0; j<n2; j++){
			SegIntersec(vertex[i], vertex[(i+1)%n1], p2[j], p2[(j+1)%n2], points);
		}
	}
	return ConvexPolygon(points);
}

/**Given two polygon, the first one is updated to their union*/
ConvexPolygon ConvexPolygon::unions (const ConvexPolygon & p2)  const{
	vector<Point> unio = vertex;
	for (Point p : p2.SetOfVertices()) unio.push_back(p); 
	return ConvexHull(unio);
}


/**Given a point, the function returns whether or not it is inside the polygon*/
bool ConvexPolygon::PointInside (const Point & p) const{ 
	int n = vertex.size();
	if (n < 3) return false;
	for (int i = 0; i<n-1; i++){
		if(vertex[i].leftof(vertex[i+1], p)) return false;
	}
	if (vertex[n-1].leftof(vertex[0], p)) return false;
	return true;
}

/**Given two polygons, returns whether or not the first one is inside the second*/
/*I consider that a polygon cannot be inside a polygon of less than 3 vertices*/
bool ConvexPolygon::inside (const ConvexPolygon & p2) const{
	if (p2.vertices() < 3) return false;
	for (Point p : vertex){
		if (not p2.PointInside(p)) return false;
	}
	return true;
}

/**Sets a new color for the polygon*/
/**Precondition: R, G, B ∈ [0, 1]*/
void ConvexPolygon::setcol (double R, double G, double B){
	RGB={R, G, B};
}

/**Sets a new color for the polygon*/
/**Precondition: R, G, B ∈ [0, 1]*/
void ConvexPolygon::checkcol () const{
	for (double c : RGB) cout << c << " ";
	cout << endl;
}

//Returns the color of a polygon
color ConvexPolygon::getcol () const{
	return RGB;
}


/**Returns the bounding box of the given polygons*/
void ConvexPolygon::bbox (const vector<ConvexPolygon> & polygons){
	double minX = 0, maxX = 0;
	double minY = 0, maxY = 0;
	bool first = true;
	for (ConvexPolygon poly : polygons){
		for (Point p : poly.SetOfVertices()){
			    if (p.getX()<minX or first) {
			     	minX = p.getX();
			    }
			    if (p.getX()>maxX or first) {
					maxX = p.getX();
				}
			   	if (p.getY()<minY or first) {
			   		minY = p.getY();
			   	}
			   	if (p.getY()>maxY or first) {
			   		maxY = p.getY();
			   	}
				first = false;
		}
	}
	Point LL(minX, minY); /**Lower Left corner*/
	Point LR(maxX, minY); /**Lower Right corner*/
	Point UR(maxX, maxY); /**Upper Right corner*/
	Point UL(minX, maxY); /**Upper Left corner*/

	vector<Point> vertex = {LL, LR, UR, UL};
	ConvexPolygon bbox(vertex);
	*this = bbox;
}