#include "Point.hh"
#include <cmath>


// Default constructor:  initializes the point to (0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}

// Accessors:

double Point::getX() const {
  return x_coord;
}

double Point::getY() const {
  return y_coord;
}

double Point::getZ() const {
  return z_coord;
}

// Other methods 
double Point::distanceTo(const Point &p) const {
    double x_diff = p.getX() - this->getX();
    double y_diff = p.getY() - this->getY();
    double z_diff = p.getZ() - this->getZ();
    double d = sqrt(x_diff * x_diff +
                    y_diff * y_diff +
                    z_diff * z_diff);
    return d;
}
