#include <vector>
using namespace std;
class Dumb {

private:
    vector<int> v;

public:
    // Constructors 
    Dumb() {}
    Dumb(vector<int> vec);

    // Destructor 
    ~Dumb() {}

    // Accessor methods 
    vector<int>& getV();
};
