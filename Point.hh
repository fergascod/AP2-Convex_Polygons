#ifndef Point_hh
#define Point_hh

class Point{
public:
	 
	/**Constructor*/
	Point (double temp_x, double temp_y);
	
	/**Returns the vector from this to p*/
	Point vector_to(const Point& p) const ; 

	bool leftof (const Point& p1, const Point& p2) const;

	/**Returns the slope of the line connecting two points*/
	double slope (const Point& p) const ;
	
	/**Escriu les coordenades del punt*/
	void printPoint () const;
	
	/**Returns the x coordinate of the point*/
	double getX () const;
	
	/**Returns the y coordinate of the point*/
	double getY () const;

	/**Returns the distance between two given points*/
	double distance (const Point & p2) const;

	//Sum of the coordinates of two points
	Point operator+ (const Point & p2) const;

	//Substraction of the coordinates of two points
	Point operator- (const Point & p2) const;

	//Multiplies the coordinates of a point by i
	Point operator* (double i) const;

	//Returns true if two points are equal
	bool operator== (const Point & p2) const;

	//Returns true if two points are different 
	bool operator!= (const Point & p2) const;

	
private:
	double x, y;
	
};

#endif
