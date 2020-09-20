CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include
PNG = -L $(HOME)/libs/lib -l PNGwriter -l png

all: main.exe

main.exe: Point.o ConvexPolygon.o main.o
	$(CXX) $^ -o $@ $(PNG)

clean:
	rm -f main.exe *.o *.png *.txt

	
main.o: Point.hh ConvexPolygon.hh main.cc

ConvexPolygon.o: ConvexPolygon.hh Point.hh ConvexPolygon.cc

Point.o: Point.hh Point.cc 


