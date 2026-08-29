class Vertex {
    
  private:
    double x_coord;
    double y_coord;



  public:
    
    // Constructor.
    Vertex(double x, double y) {
        x_coord = x;
        y_coord = y;
    }

    // Getters and setters.
    double get_x_coordinate { return x_coord; }
    double get_y_coordinate { return y_coord; }
    
    double set_x_coordinate { return x_coord; }
    double set_y_coordinate { return y_coord; }
    
    
    // (Custom) methods.
    void move(double x, double y) { x_coord += x;    y_coord += y; }
}






// In "f(x) = m * x + b" fashion:
// my_line(x) = slope * x + ordinates.
//
class Line {

  private:
    double slope;
    double ordinates;
    
  public:
    
    // Constructors.
	//
	// f(x) = mx + b
    Line(double given_slope, double given_ordinates) {
        slope     = given_slope;
        ordinates = given_ordinates;
    }
	
	// Constructs the line that goes through both vertex1 and vertex2.
    Line(double vertex1, double vertex2) {
        if (vertex_1.get_y_coordinate() == vertex_2.get_y_coordinate()) {	 // it's a horizontal line!
			slope = 0;
			ordinates = vertex_1.get_y_coordinate();                    

		} else if (vertex_1.get_x_coordinate() == vertex_2.get_x_coordinate()) {	// it's a vertical line... we cannot represent it with "f(x) = mx + b" (m's denominator becomes 0 when vertex_1.x = vertex_2.x, but we cannot divide by 0... (slope == inf, ordinates == vertex_1.y == vertex_2.y))
			assert(0 == "ERROR: Cannot represent vertical lines...");
			slope = 0;			// Some random value just so the compiler doesn't complain...
			ordinates = 0;		// Some random value just so the compiler doesn't complain...	

		} else {
			slope       =  (vertex_2.y_coordinate()  -      vertex_1.y_coordinate())  /  (vertex_2.x_coordinate() - vertex_1.x_coordinate());
			ordinates   =   vertex_2.y_coordinate()  -  a * vertex_2.x_coordinate();             // do the math, it checks out :p  ///  vertex_2 and vertex_1 should give the same result here btw              

			// line_formula = Line(a, b);
		}
    }


    // Getters and setters.
    double get_slope()      { return slope;     }
    double get_ordinates()  { return ordinates; }
    
    void set_slope(double given_slope)          {     slope = given_slope;     }
    void set_ordinates(double given_ordinates)  { ordinates = given_ordinates; }
}







class Triangle {

  private:
    Vertex v1;
    Vertex v2;
    Vertex v3;
  

  
  public:

    // Constructor 1:   3 vertices (the region inside them will define our triangle).
    Triangle(Vertex given_v1, Vertex given_v2, Vertex given_v3){
        v1 = given_v1;
        v2 = given_v2;
        v3 = given_v3;
    }
    
    // Constructor 2:   3 lines (the region inside them will define our triangle).
    Triangle(Line line1, Line line2, Line line3){
        //   TODO.
        v1 = LineIntersection(line3, line1);
        v2 = LineIntersection(line1, line2);
        v3 = LineIntersection(line2, line3);
    }
    


    // Getters and setters.
    Vertex get_vertex_1() { return v1; }
    Vertex get_vertex_2() { return v2; } 
    Vertex get_vertex_3() { return v3; }
    
    void set_vertex_1(Vertex given_v1) { v1 = given_v1; }
    void set_vertex_2(Vertex given_v2) { v2 = given_v2; }
    void set_vertex_3(Vertex given_v3) { v3 = given_v3; }
    
    
    
    // (Custom) methods.
    void move(double x, double y) { v1.move(x, y);    v2.move(x, y);    v3.move(x, y); }
    // Triangle scale() {  TODO ; }
}




// Up to here, we have been doing 2D only cuz me lazy e.e  BUT:
//
// For circles, don't do classes...
// do templates, so we can generalise to N dimensions instead :3
