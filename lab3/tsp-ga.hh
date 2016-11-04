#include "Point.hh"
#include <vector> 
using namespace std;

// Represents on possible solution to a Traveling Salesman Problem. Used 
// to solve TSP with genetic algorithms.
class TSPGenome {

private:
    vector<int> order;
    double circuitLength;
    static const int DUMMY_LENGTH = 1e9;

public:
    // Constructors 
    TSPGenome() {}
    TSPGenome(int numPoints);
    TSPGenome(const vector<int> &order);
          

    // Destructor 
    ~TSPGenome() {}

    // Accessor methods 
    vector<int> getOrder() const;
    double getCircuitLength() const;

    // Other methods 
    void computeCircuitLength(const vector<Point> &points);
    void mutate();
};

// Other functions
TSPGenome *crosslink(const TSPGenome &g1, const TSPGenome &g2);
bool isShorterPath(const TSPGenome *g1, const TSPGenome *g2);
TSPGenome *findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations);
