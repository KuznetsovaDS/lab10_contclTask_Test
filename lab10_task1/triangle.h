#pragma once

#include "dot.h"
#include <iostream>

using namespace std;

class Triangle {
private:
    Dot a;          
    Dot b;
    Dot c;

    Dot* a_agg;    
    Dot* b_agg;
    Dot* c_agg;
    bool is_aggregation;  

public:
   
    Triangle(double ax, double ay, double bx, double by, double cx, double cy);
        
    Triangle(Dot* a, Dot* b, Dot* c);
       
    void printSides();

    double perimeter();

    double area();
};