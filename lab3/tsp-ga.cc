#include "tsp-ga.hh"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
using namespace std;

/* ========== Member Functions ========== */

// Constructor that initializes the order vector to be some random 
// order of points and the circuitLength to be equal to dummyLength.
TSPGenome::TSPGenome(int numPoints) {
   this->order.resize(numPoints);
   // Initialize to 0, 1, 2, ..., numPoints - 1
   std::iota(this->order.begin(), this->order.end(), 0);
   std::random_shuffle(this->order.begin(), this->order.end());
   this->circuitLength = this->DUMMY_LENGTH;
}

// Constructor that initializes the order vector with the passed-in vector.
TSPGenome::TSPGenome(const vector<int> &order) {
    this->order = order;
    this->circuitLength = this->DUMMY_LENGTH;
}


// Gets genome's current visit order.
vector<int> TSPGenome::getOrder() const {
    return this->order;
}


// Gets genome's current circuit length.
double TSPGenome::getCircuitLength() const {
    return this->circuitLength;
}


// Computes circuit length from traversing the passed-in points in the 
// order specified by this object.
void TSPGenome::computeCircuitLength(const vector<Point> &points) {
    double length = 0;
    for (unsigned int i = 0; i < this->order.size(); i++) {
        int next;
        if (i == this->order.size() - 1)
            next = 0;
        else
            next = i + 1;

        length += points[this->order[i]].distanceTo(points[this->order[next]]);
    }
    
    // Update length.
    this->circuitLength = length;
}


// "Mutates" the genome by swapping two randomly-selected values in the order 
// vector.
void TSPGenome::mutate() {
    // If we have less than 2 elements, we can't mutate 
    if (this->order.size() < 2)
        return;

    int rand1 = rand() % this->order.size();
    int rand2 = rand() % this->order.size();
    while (rand2 == rand1) {
        rand2 = rand() % this->order.size();
    }

    assert(rand1 != rand2);
    swap(order[rand1], order[rand2]);
}

/* ========== Nonmember Functions ========== */

// Generate an offspring genome by crosslinking the order vectors of 
// two existing genomes. We assume that these genomes are made of unique
// elements.
TSPGenome *crosslink(const TSPGenome &g1, const TSPGenome &g2) {
    // Sizes should be equal (same circuit length)
    vector<int> g1Order = g1.getOrder();
    assert(g1Order.size() == g2.getOrder().size());

    unsigned int N = g1Order.size();
    vector<int> offspring;
    int offspringEnd = rand() % N;

    // Don't make two calls to g1.getOrder() here to make sure iterators
    // are consistent ****
    std::copy(g1Order.begin(), g1Order.begin() + offspringEnd, 
              std::back_inserter(offspring));
    set<int> offspringSet(offspring.begin(), offspring.begin() + offspringEnd);

    for (int num : g2.getOrder()) {
        if (!offspringSet.count(num)) {
            // If num is not already included
            offspring.push_back(num);
        }
    }

    assert(offspring.size() == N);
    return new TSPGenome(offspring);
}


// Returns true if g1 has a shorter circuit length than g2, false otherwise.
bool isShorterPath(const TSPGenome *g1, const TSPGenome *g2) {
    return g1->getCircuitLength() < g2->getCircuitLength();
}


// Finds a short path (not shortest).
TSPGenome *findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations) {
    assert(populationSize > 0);

    // Generate an initial population of random genomes. Use array of pointers
    // so we can easily update the lengths (g->computeCircuitLength())
    vector<TSPGenome *> genomes(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        genomes[i] = new TSPGenome(points.size());
    }

    for (int gen = 0; gen < numGenerations; ++gen) {
        // Compute circuit length for each genome
        for (TSPGenome *g : genomes) {
            g->computeCircuitLength(points);
        }

        // Sort genomes by circuit length
        std::sort(genomes.begin(), genomes.end(), isShorterPath);

        // Print stuff to see what's going on
        if (gen % 10 == 0) {
            cout << "Generation " << gen << ": shortest path is "
                 << genomes[0]->getCircuitLength() << endl;
        }

        // Replace our "unfit" members by breeding the "fit" members. That is,
        // use the top N genomes to replace the other genomes.
        for (int i = keepPopulation; i < populationSize; ++i) {
            int fit1 = rand() % keepPopulation;
            int fit2 = rand() % keepPopulation;
            while (fit2 == fit1) {
                fit2 = rand() % keepPopulation;
            }

            genomes[i] = crosslink(*genomes[fit1], *genomes[fit2]);
        }

        // Mutate the population
        for (int i = 0; i < numMutations; ++i) {
            // Don't mutate the best solution
            int randI = 1 + rand() % (populationSize - 1);
            genomes[randI]->mutate();
        }
    }

    // Free memory
    for (unsigned int i = 1; i < genomes.size(); i++)
        delete genomes[i];

    return genomes[0];
}
