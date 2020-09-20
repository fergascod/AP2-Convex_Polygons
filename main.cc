#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <pngwriter.h>

using namespace std;
using color = vector <double>;

#include "Point.hh"
#include "ConvexPolygon.hh"


/*-----------------------Header files-------------------------------------------------------------
------------------------------------------------------------------------------------------------*/


//ERROR HANDLING
void error(int i){
	if (i == 0){
		cout << "error: undefined polygon identifier" << endl;
	}else if(i == 1){
		cout << "error: wrong number of arguments" << endl;	
	}else if(i == 2){
		cout << "error: not an even number of parameters"<< endl;
	}else if(i == 3){
		cout << "error: a polygon identifier is required" << endl;
	}else if(i == 4){
		cout << "error: not a file" << endl;
	}else if (i == 5){
		cout << "error: color parameters should be in range [0, 1]" << endl;
	}else if (i == 6){
		cout << "error: a file is required" << endl;
	}
}

//Creates a new polygon
void New_Polygon (map<string, ConvexPolygon>& Pols, istringstream& line){
	string name;
	line >> name;
	double x, y;
	vector <Point> points;
	while (line >> x){
		if (line.good()) {
			line >> y;
			points.push_back(Point(x, y));
		}else{
			error(2);
			return;
		}
	}
	ConvexPolygon NewPolygon (points);
	Pols[name]=NewPolygon;
	cout << "ok"<< endl;
}

//Prints a polygon
void Poly_print (map<string, ConvexPolygon>& Pols, istringstream& line){
	string name;
	if (line.good()){
		line >> name;
		if (Pols.end() != Pols.find(name)){
			cout << name <<" ";
			Pols[name].print();
		}else {
			error(0);
			return;
		}
	} else {
		error(1);		
		return;
	}
}


//Prints the area of a polygon
void Poly_area (map<string, ConvexPolygon>& Pols, istringstream& line){
	if (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)) cout << abs(Pols[name].area())<< endl;
		else {
			cout << "error: undefined polygon identifier " << "\""<< name << "\"" << endl;
			return;
		}
	} else {
		error(1);		
		return;
	}
}

//Prints the perimeter of a polygon
void Poly_perimeter (map<string, ConvexPolygon>& Pols, istringstream& line){
	string name;
	if (line.good()) {
		line >> name;
		if (Pols.end() != Pols.find(name)) {
			cout << Pols[name].perimeter() << endl;
		}
		else {
			error(0);
			return;
		}
	} else {
		error(3);
		return;
	}
}

//Prints the number of vertices of a polygon
void Poly_vertices (map<string, ConvexPolygon>& Pols, istringstream& line){
	if (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)) cout << Pols[name].vertices() << endl;
		else {
			error(0);
			return;
		}
	} else {
		error(1);		
		return;
	}
}

//Prints the centroid of a polygon
void Poly_centroid (map<string, ConvexPolygon>& Pols, istringstream& line){
	string name;
	if (line.good()) {
		line >> name;
		if (Pols.end() != Pols.find(name)) {
			Pols[name].centroid().printPoint();
			cout << endl;
		} else {
			error(0);
			return;
		}
	}else error(3);
}

//Prints all the IDs of the polygons
void Poly_list (map<string, ConvexPolygon>& Pols){
	for (auto polygon : Pols) cout << polygon.first <<" ";
	cout << endl;
}

//Creates a file with the info of a sequence of polygons
void Poly_output(map<string, ConvexPolygon>& Pols, istringstream& line){
	string file;
	line >> file;
	ofstream myfile;
	myfile.open(file);
	string name;
	while (line >> name){
		myfile << name;
		for (Point p : Pols[name].SetOfVertices()){
			myfile << " " << p.getX() << " " << p.getY();
		}
		myfile << endl;
	}
	myfile.close();
	cout << "ok" << endl;
}

//Saves the info of the polygons in a file
void Poly_input(map<string, ConvexPolygon>& Pols, istringstream& line){
	string file;
	if (line.good()){
		line >> file;
		ifstream myfile (file);
		if (not myfile){
			error(4);
		}else {
			string polygon;
			while (getline(myfile, polygon)){
				istringstream iss (polygon);
				string name;
				iss >> name;
				double x, y;
				vector<Point> points;
				while (iss >> x >> y){
					points.push_back(Point(x, y));
				}
				Pols.insert ({name, ConvexPolygon(points)});
			}
			cout << "ok" << endl;
		}
	} else error(6);
}

//sets  a new color for a polygon
void Poly_setcol(map<string, ConvexPolygon>& Pols, istringstream& line){
	if (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)){
			double R, G, B;
			line >> R  >> G >> B;
			if (R>1 or R<0 or G>1 or G<0 or B>1 or B<0){
				error(5);
			}else{
				Pols[name].setcol(R, G, B);
				cout << "ok" << endl;
			}
		} else {
			error(0);
			return;
		}
	} else error(3);
}

//Prints the color of a polygon
void Poly_checkcol(map<string, ConvexPolygon>& Pols, istringstream& line){
	if (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)){
			Pols[name].checkcol();
		} else {
			error(0);
			return;
		}
	} else error(1);}

//Prints whether or not a polygon is inside another polygon
void Poly_inside (map<string, ConvexPolygon>& Pols, istringstream& line){
	string first;
	if (line.good()){
		string first;
		line >> first;
		if (line.good()){
			string second;
			line >> second;
			if (Pols.end() != Pols.find(first) and Pols.end() != Pols.find(second)){
				if (Pols[first].inside(Pols[second])) cout << "yes" << endl;
				else cout << "no" << endl;
			}else {
				error(0);
				return;
			}
		}else error(1);	
	}else error(1);
}

//Prints whether or not a point is inside a polygon
void Poly_Point_inside (map<string, ConvexPolygon>& Pols, istringstream& line){
	double x, y;
	string name;
	line >> x >> y;
	if (line.good()){
		line >> name;
		if (Pols.end() != Pols.find(name)){
			Point p(x, y);
				if (Pols[name].PointInside(p)) cout << "yes" << endl;
				else cout << "no" << endl;
		}
	}else error(1);
}

//Creates a new polygon with the intersection of two polygons
void Poly_intersection (map<string, ConvexPolygon>& Pols, istringstream& line){
	string first, second, third;
	if (line.good()) {
		line >> first;
			if (line.good()) {
				line >> second;
				if(line.good()){
					line>> third;
					if (Pols.end() != Pols.find(third) and Pols.end() != Pols.find(second)){
						Pols[first] = Pols[second].intersection(Pols[third]);
						cout << "ok" << endl;
					}else {
						error(0);
						return;
					}
				} else{
					if (Pols.end() != Pols.find(second) and Pols.end() != Pols.find(first)){
						Pols[first] = Pols[second].intersection(Pols[first]);
						cout << "ok" << endl;
					}else {
						error(0);
						return;
					}
				}
			} else error(1);
	} else error(1);	
}

//Creates a new polygon with the union of two polygons
void Poly_union (map<string, ConvexPolygon>& Pols, istringstream& line){
	string first, second, third;
	if (line.good()) {
		line >> first;
			if (line.good()) {
				line >> second;
				if(line.good()){
					line>> third;
					if (Pols.end() != Pols.find(third) and Pols.end() != Pols.find(second)){
						Pols[first] = Pols[second].unions(Pols[third]);
						cout << "ok" << endl;
					}else {
						error(0);
						return;
					}
				} else{
					if (Pols.end() != Pols.find(second) and Pols.end() != Pols.find(first)){
						Pols[first] = Pols[second].unions(Pols[first]);
						cout << "ok" << endl;
					}else {
						error(0);
						return;
					}
				}
			} else error(1);
	} else error(1);	
}

//Creates the bounding box of a sequence of polygons
void Poly_bbox (map<string, ConvexPolygon>& Pols, istringstream& line){
	vector<ConvexPolygon> polygons(0);
	string name1;
	line >> name1;
	while (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)) {
			polygons.push_back(Pols[name]);
		} else {
			error(0);
			return;
		}
	}
	Pols[name1].bbox(polygons);
	cout << "ok" << endl;
}

//Draws a sequence of polygons into png file
void Poly_draw (map<string, ConvexPolygon>& Pols, istringstream& line){
	vector<ConvexPolygon> polygons(0);
	string FileName;
	line >> FileName;
	pngwriter png (500, 500, 1.0, FileName.c_str());
	while (line.good()){
		string name;
		line >> name;
		if (Pols.end() != Pols.find(name)) polygons.push_back(Pols[name]);
		else {
			error(0);
			return;
		}
	}
	ConvexPolygon BBOXFORDRAW;
	BBOXFORDRAW.bbox(polygons);
	double costat= max (abs(BBOXFORDRAW.SetOfVertices()[0].getY()-BBOXFORDRAW.SetOfVertices()[1].getY()), abs(BBOXFORDRAW.SetOfVertices()[1].getX()-BBOXFORDRAW.SetOfVertices()[2].getX()));
	double scale = 497/costat;
	Point LL = BBOXFORDRAW.SetOfVertices()[0];
	for (ConvexPolygon cp : polygons){
		int n = cp.vertices();
		for (int i = 0; i<n-1; i++){
			int xfrom = (cp[i].getX()- LL.getX())*scale+2;
			int yfrom = (cp[i].getY()- LL.getY())*scale+2;
			int xto = (cp[i+1].getX()- LL.getX())*scale+2;
			int yto = (cp[i+1].getY()- LL.getY())*scale+2;
			png.line (xfrom, yfrom, xto, yto, cp.getcol()[0], cp.getcol()[1], cp.getcol()[2]);
		}
		if (n>1){
			int xfrom = (cp[0].getX()- LL.getX())*scale+2;
			int yfrom = (cp[0].getY()- LL.getY())*scale+2;
			int xto = (cp[n-1].getX()- LL.getX())*scale+2;
			int yto = (cp[n-1].getY()- LL.getY())*scale+2;
			png.line (xfrom , yfrom, xto, yto, cp.getcol()[0], cp.getcol()[1], cp.getcol()[2]);
		}
		if(n==1){
			int x = (cp[0].getX()- LL.getX())*scale+2;
			int y = (cp[0].getY()- LL.getY())*scale+2;
			png.filledcircle(x, y, 2, cp.getcol()[0], cp.getcol()[1], cp.getcol()[2]);
		}
	}
	png.close();
	cout << "ok" << endl;
}



/*------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------*/

int main (){
	cout.setf(ios::fixed);
	cout.precision (3);

	map<string, ConvexPolygon> Pols;
	string newline;
	while (getline(cin, newline)){
		istringstream iss (newline);
		string action;
		iss >> action;

		     if (action == "polygon")					New_Polygon(Pols, iss);                                
		else if (action == "print") 					Poly_print(Pols, iss);
		else if (action == "area") 						Poly_area(Pols, iss);
		else if (action == "perimeter") 				Poly_perimeter(Pols, iss);
		else if (action == "vertices")					Poly_vertices(Pols, iss);
		else if (action == "centroid")					Poly_centroid(Pols, iss);
		else if (action == "list")						Poly_list(Pols);
		else if (action == "save")						Poly_output (Pols, iss);
		else if (action == "load")						Poly_input(Pols, iss);
		else if (action == "setcol")					Poly_setcol(Pols, iss);
		else if (action == "checkcol")					Poly_checkcol(Pols, iss);
		else if (action == "draw")						Poly_draw(Pols, iss);
		else if (action == "intersection")				Poly_intersection (Pols, iss);
		else if (action == "union")						Poly_union(Pols, iss);
		else if (action == "inside")					Poly_inside(Pols, iss);
		else if (action == "point_inside")				Poly_Point_inside(Pols, iss);
		else if (action == "bbox")						Poly_bbox(Pols, iss);
		else if (action == "#")							cout << "#" << endl;
		else if (action == "");
		else if (action == "exit")                      return 0;
		else 											cout << "error: invalid command" << " \"" << action << "\"" << endl;
	}
}
