#include <iostream>
#include <string>
#include <vector>
using namespace std;
class TravelRoute {
public:
    float travel_cost;
    TravelRoute(float c = 0) { travel_cost = c; }
};
class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;
    float x, y, z;
    bool is_habitable;
    vector<StarSystem*> children;   // child star systems
    vector<TravelRoute> routes;     // routes[i] is the cost to reach children[i]
    StarSystem(int id, string n, int planets, float px, float py, float pz, bool habitable) {
        system_id = id;
        name = n;
        num_planets = planets;
        x = px;
        y = py;
        z = pz;
        is_habitable = habitable;
    }
};
class Galaxy {
    int M;              // max children per node
    StarSystem* root;
    // number of nodes in the subtree of x
    int size(StarSystem* x) const {
        if (x == NULL) return 0;
        int total = 1;
        for (int i = 0; i < x->children.size(); i++)
            total += size(x->children[i]);
        return total;
    }
public:
    // constructor with only M
    Galaxy(int m) {
        M = m;
        root = NULL;
    }
    // overloaded constructor with M and a root
    Galaxy(int m, StarSystem* r) {
        M = m;
        root = r;
    }
    StarSystem* getRoot() const { return root; }
    void addChild(StarSystem* parent, StarSystem* child, float cost) {
        if (parent->children.size() >= M) {
            cout << "Cannot add " << child->name << ", " << parent->name << " is full." << endl;
            return;
        }
        parent->children.push_back(child);
        parent->routes.push_back(TravelRoute(cost));
    }
    // balanced: child subtree sizes differ by at most 1 at every node
    bool is_balanced(StarSystem* x) const {
        if (x == NULL || x->children.empty()) return true;
        int smallest = size(x->children[0]);
        int largest = smallest;
        for (int i = 1; i < x->children.size(); i++) {
            int s = size(x->children[i]);
            if (s < smallest) smallest = s;
            if (s > largest) largest = s;
        }
        if (largest - smallest > 1) return false;
        for (int i = 0; i < x->children.size(); i++)
            if (!is_balanced(x->children[i])) return false;

        return true;
    }
    // count nodes that have no children
    int count_leaves(StarSystem* x) const {
        if (x == NULL) return 0;
        if (x->children.empty()) return 1;
        int count = 0;
        for (int i = 0; i < x->children.size(); i++)
            count += count_leaves(x->children[i]);
        return count;
    }
};
int main() {
    // create 4 star systems
    StarSystem* sol    = new StarSystem(1, "Sol", 8, 0, 0, 0, true);
    StarSystem* alpha  = new StarSystem(2, "Alpha", 3, 4, 1, 2, true);
    StarSystem* sirius = new StarSystem(3, "Sirius", 2, 8, 3, 1, false);
    StarSystem* vega   = new StarSystem(4, "Vega", 5, 25, 9, 4, false);
    // Sol is the root, M = 3
    Galaxy galaxy(3, sol);
    galaxy.addChild(sol, alpha, 4.3);
    galaxy.addChild(sol, sirius, 8.6);
    galaxy.addChild(sol, vega, 25.0);
    cout << "Leaf nodes: " << galaxy.count_leaves(galaxy.getRoot()) << endl;
    if (galaxy.is_balanced(galaxy.getRoot())) cout << "Tree is balanced" << endl;
    else cout << "Tree is NOT balanced" << endl;
    // make one branch bigger so the tree becomes unbalanced
    StarSystem* p1 = new StarSystem(5, "Proxima", 1, 4, 2, 2, true);
    StarSystem* p2 = new StarSystem(6, "Extra", 1, 1, 1, 1, false);
    galaxy.addChild(alpha, p1, 0.2);
    galaxy.addChild(p1, p2, 1.5);
    cout << "After adding more systems:" << endl;
    cout << "Leaf nodes: " << galaxy.count_leaves(galaxy.getRoot()) << endl;
    if (galaxy.is_balanced(galaxy.getRoot())) cout << "Tree is balanced" << endl;
    else cout << "Tree is NOT balanced" << endl;
    return 0;
}