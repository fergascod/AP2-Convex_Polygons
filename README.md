# `POLYGON` CALCULATOR	

1st of April 2019



#### **MAKEFILE**

- To compile our polygon calculator we have to run the command $make on the SHELL.

  `$ make`

- In order to run the calculator, you have to execute the main.exe file created during the compilation process.

  `$./main.exe`

- In the Makefile I have implemented the clean rule so that all *.png and *.txt files are removed when make clean is executed.  So, when running the draw command or saving and loading files, take that into account. To execute this rule run the command line:

  `$ make clean`

In order for the compilation process to be successful you have to modify the Makefile that compiles the project, which is given to you along with the code of all the other files. The PNG flag indicates where the compiler has to look for the PNGwriter library (that was used for the draw function), so you have to modify its information according to the directory where you downloaded it.





#### **CLASSES**

To implement the different functions in this program, I've created two new classes: Point and ConvexPolygon.



#### **COMMANDS**

This Polygon calculator allows for the use of the following commands:
- polygon: given a polygon ID and an even number of coordinates in the plane, the smallest convex polygon containing all of them will be created, the word "ok" will be printed onto the terminal. An error will be produced if the number of coordinates is not even.

- print: given a polygon ID this command will print the identifier followed by the coordinates of all the vertices.

- area*: given a polygon ID this command will print its area.

- perimeter: given a polygon ID this command will print its area. For a polygon with two vertices, the length of the segment will be given.

- vertices: given a polygon ID this command will print its number of vertices. 

- centroid*: given a polygon ID this command will print its centroid.

- list: this command will print the ID of all polygons that have been created.

- save: given a file name and a sequence of polygon IDs, a text file containing all the polygons (one per line) will be created.

- load: given a file name, all of the polygons in it will be saved so they can be used.

- setcol: given a polygon ID and three real numbers in range [0, 1], the polygon's RGB color will be updated to the given values. An error will be generated if the values are not in range [0, 1].

- draw: given a file name and a sequence of polygon IDs, a png file with the given polygons drawn will be created.

- intersection: This command may receive two or three parameters. When receiving two parameters `p1`and `p2`, `p1`should be updated to the intersection of the original `p1` and `p2`. When receiving three parameters `p1`, `p2` and `p3`, `p1`should be updated to the intersection of `p2` and `p3`.

- union: just as the intersection command, but with the convex union of polygons.

- inside: given two polygons, prints "yes" if the first polygon is inside the second one, it prints "no" otherwise. 

- bbox

  

For all commands if the given IDs do not correspond to a polygon an error will be printed onto the terminal.

Alongside with the other required commands, I have also implemented:
- checkcol: Given a polygon identifier, this command prints the polygon's current color.
- point_inside: Given the x and y coordinates and a polygon identifier, it prints yes if the point represented by the coordinates is inside the polygon, it prints no, otherwise.
- exit: running this command, will allow you to quit the polygon calculator (just like ctrl+Z)

**Both of the formulas used to compute the area and the centroid of a polygon can be found in this site:*
*https://en.wikipedia.org/wiki/Centroid#Of_a_polygon*



#### TEST CASES

An example of the use of my polygon calculator:

```
    polygon p1 1 3 4 3 3 1 5 0 0 0 
    print p1
    polygon p2 0 5 4 3 3 1 5 9 8 3
    print p3
    point_inside 1 1 p1
    inside p1 p2
    intersection p3 p1 p2
    setcol p3 1 0 0
    union p4 p1 p2
    area p4
    perimeter p3
    setcol p4 0 0 1
    # El convex hull es molt complicat
    draw image.png p1 p2 p3 p4
    quit
    exit


```

The output of these command lines should be:

```
    ok
    p1 0.000 0.000 5.000 0.000 1.000 3.000 4.000 3.000 
    ok
    error: undefined polygon identifier
    no
    no
    ok
    ok
    ok
    15.000
    3.867
    ok
    #
    ok
    error: invalid command "quit"

```



And `image.png` should be the same as Test_case in the folder.

