#include<set>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

struct node_t {
    int id;
    vector <node_t *> links;
    node_t(int id) : id(id) {}
};

int tree_size(node_t *n, vector<node_t *> &counted) {
    if (!n) return 0;
    counted.push_back(n);
    if (!n->id) cout << "0 group" << endl;
    int child_c = 0;
    for (auto it = n->links.begin(); it != n->links.end(); ++it)
        child_c += (find(counted.begin(), counted.end(), *it) == counted.end()) ?
                   tree_size(*it, counted) : 0;
    return 1 + child_c;
}

int main() {
    int parent, child;
    char trashc;
    string trash, line;
    ifstream infile("input");
    vector<string> input;
    vector<node_t *> nodes;
    while (!infile.eof()) {
        if (getline(infile, line)) {
            input.push_back(line);
            stringstream ss(line);
            ss >> parent;
            nodes.push_back(new node_t(parent));
        }
    }
    for (auto it = input.begin(); it != input.end(); ++it) {
        stringstream ss(*it);
        ss >> parent;
        node_t *p, *c;
        for (auto nit = nodes.begin(); nit != nodes.end(); ++nit)
            if ((*nit)->id == parent) p = *nit;
        ss >> trash;
        while (ss >> child) {
            for (auto nit = nodes.begin(); nit != nodes.end(); ++nit)
                if ((*nit)->id == child) c = *nit;
            p->links.push_back(c);
            ss >> trashc;
        }
    } 
    set<vector<node_t *>> groups;
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        vector<node_t *> counted;
        int size = tree_size(*it, counted);
        cout << "ID: " << (*it)->id << " Size: " << size << endl;
        sort(counted.begin(), counted.end());
        groups.insert(counted);
    }
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        delete *it;
    cout << "Group count: " << groups.size() << endl;
    cout << "Node count: " << nodes.size() << endl;
    return 0;
}
