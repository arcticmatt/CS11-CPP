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
    double x, y, z;

    cout << "Point 1: ";
    cin >> x >> y >> z;
    Point a(x, y, z);

    cout << "Point 2: ";
    cin >> x >> y >> z;
    Point b(x, y, z);
    
    cout << "Point 3: ";
    cin >> x >> y >> z;
    Point c(x, y, z);

    double area = computeArea(a, b, c);

    cout << "Area is: " << area << endl;
}
