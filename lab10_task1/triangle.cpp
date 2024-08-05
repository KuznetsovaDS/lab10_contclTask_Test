#include "triangle.h"
#include <cmath>
#include <iostream>

using namespace std;

Triangle::Triangle(double ax, double ay, double bx, double by, double cx, double cy)
    : a(ax, ay), b(bx, by), c(cx, cy), is_aggregation(false) {}


Triangle::Triangle(Dot* a, Dot* b, Dot* c)
    : a_agg(a), b_agg(b), c_agg(c), is_aggregation(true) {}

void Triangle::printSides() {
    if (is_aggregation) {
        cout << "расстояние a-b " << a_agg->distanceTo(*b_agg) << endl;
        cout << "расстояние b-c " << b_agg->distanceTo(*c_agg) << endl;
        cout << "расстояние c-a " << c_agg->distanceTo(*a_agg) << endl;
    }
    else {
        cout << "расстояние a-b " << a.distanceTo(b) << endl;
        cout << "расстояние b-c " << b.distanceTo(c) << endl;
        cout << "расстояние c-a " << c.distanceTo(a) << endl;
    }
}

double Triangle::perimeter() {
    if (is_aggregation) {
        return a_agg->distanceTo(*b_agg) + b_agg->distanceTo(*c_agg) + c_agg->distanceTo(*a_agg);
    }
    else {
        return a.distanceTo(b) + b.distanceTo(c) + c.distanceTo(a);
    }
}

double Triangle::area() {
    double ab, bc, ca;
    if (is_aggregation) {
        ab = a_agg->distanceTo(*b_agg);
        bc = b_agg->distanceTo(*c_agg);
        ca = c_agg->distanceTo(*a_agg);
    }
    else {
        ab = a.distanceTo(b);
        bc = b.distanceTo(c);
        ca = c.distanceTo(a);
    }

    double s = perimeter() / 2;
    return sqrt(s * (s - ab) * (s - bc) * (s - ca));
}
