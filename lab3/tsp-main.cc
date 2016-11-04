#include "tsp-ga.hh"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cout << "usage: ./tsp-ga population generations keep mutate" << endl;
        exit(1);
    }

    // Assume args are numbers
    int population = atoi(argv[1]);
    int generations = atoi(argv[2]);
    float keep = atof(argv[3]);
    float mutate = atof(argv[4]);

    // Error checking on inputs
    if (population <= 0 || generations <= 0) {
        cout << "input error: population = " << population << " or "
            << "generations = " << generations << " is <= 0" << endl;
        exit(1);
    }
    if (keep < 0 || keep > 1) {
        cout << "input error: keep = " << keep << " is not in range [0,1]" 
            << endl;
        exit(1);
    }
    if (mutate < 0) {
        cout << "input error: mutate = " << mutate << " is negative" << endl;
        exit(1);
    }

    // Seed rng
    srand(time(nullptr));
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

    TSPGenome *g = findAShortPath(points, population, generations,
                                              (int) (keep * population),
                                              (int) (mutate * population));
    vector<int> shortestPath = g->getOrder();
    double shortestLength = g->getCircuitLength();

    cout << "Best order: [";
    for (unsigned int i; i < shortestPath.size(); i++) {
        cout << shortestPath[i];
        if (i < shortestPath.size() - 1)
            cout << " ";
    }
    cout << "]" << endl;
    cout << "Shortest distance: " << shortestLength << endl;

    delete g;
}
