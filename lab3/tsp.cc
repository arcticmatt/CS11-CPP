// @mattlim

#include "Point.hh"
#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

/*
 * Takes
 * - a vector of points
 * - the order in which those points are visited
 * and computes the total length of the path when the points are traveled in
 * the specified order. Note that we calculate length of a ROUND trip.
 */
double circuitLength(const vector<Point> &points, const vector<int> &order) {
    double length = 0;
    for (unsigned int i = 0; i < order.size(); i++) {
        int next;
        if (i == order.size() - 1)
            next = 0;
        else
            next = i + 1;

        length += points[order[i]].distanceTo(points[order[next]]);
    }
    return length;
}

/*
 * Solves the TSP by brute force.
 *
 * Takes
 * - a vector of points
 * and returns a vector that specifies the order to visit all the points in a
 * single round trip, visiting each point once, to ensure that the trip is
 * as short as possible.
 */
vector<int> findShortestPath(const vector<Point> &points) {
    double shortestLength = INT_MAX;
    vector<int> orderPerm(points.size());
    // Initialize to 0, 1, 2, ..., N - 1
    std::iota(orderPerm.begin(), orderPerm.end(), 0);
    vector<int> shortestPath = orderPerm;

    do {
        double permLength = circuitLength(points, orderPerm);
        if (permLength < shortestLength) {
            shortestPath = orderPerm;
            shortestLength = permLength;
        }
    }
    while (std::next_permutation(orderPerm.begin(), orderPerm.end()));

    return shortestPath;
}

int main() {
    unsigned int num_points;
    cout << "How many points? ";
    cin >> num_points;

    vector<Point> points(num_points);
    double x, y, z;
    for (unsigned int i = 0; i < num_points; i++) {
        cout << "Point " << i << ": ";
        cin >> x >> y >> z;
        Point p(x, y, z);
        points[i] = p;
    }

    vector<int> shortestPath = findShortestPath(points);
    double shortestLength = circuitLength(points, shortestPath);

    cout << "Best order: [";
    for (unsigned int i; i < shortestPath.size(); i++) {
        cout << shortestPath[i];
        if (i < shortestPath.size() - 1)
            cout << " ";
    }
    cout << "]" << endl;
    cout << "Shortest distance: " << shortestLength << endl;
}
