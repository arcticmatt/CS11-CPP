#include "Point.hh"
#include <cmath>
#include <iostream>
using namespace std;

/* 
 * Computes area using Heron's formula.
 */
double computeArea(Point &a, Point &b, Point &c) {
    // Get side lengths
    double s1 = a.distanceTo(b);
    double s2 = b.distanceTo(c);
    double s3 = c.distanceTo(a);
    double semiperimeter = (s1 + s2 + s3) / 2.0;
    double area = sqrt(semiperimeter * 
                       (semiperimeter - s1) * 
                       (semiperimeter - s2) * 
                       (semiperimeter - s3));
    return area;
}

int main() {
    double x1, y1, z1, x2, y2, z2, x3, y3, z3;

    cout << "Point 1: ";
    cin >> x1 >> y1 >> z1;
    cout << "Point 2: ";
    cin >> x2 >> y2 >> z2;
    cout << "Point 3: ";
    cin >> x3 >> y3 >> z3;

    Point a(x1, y1, z1);
    Point b(x2, y2, z2);
    Point c(x3, y3, z3);
    double area = computeArea(a, b, c);

    cout << "Area is: " << area << endl;
}
