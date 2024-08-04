#include "dot.h"
#include "triangle.h"
#include <iostream>

using namespace std;

int main() {
    system("chcp 1251");

    cout << "���������� " << endl;
    Triangle t1(0, 0, 0, 4, 4, 0);
    t1.printSides();
    cout << "�������� " << t1.perimeter() << endl;
    cout << "������� " << t1.area() << endl;

    cout << "\n��������� " << endl;
    Dot a(0, 0);
    Dot b(0, 4);
    Dot c(4, 0);
    Triangle t2(&a, &b, &c);
    t2.printSides();
    cout << "�������� " << t2.perimeter() << endl;
    cout << "������� " << t2.area() << endl;

    return 0;
}