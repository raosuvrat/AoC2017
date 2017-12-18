#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

struct node_t {
    string name;
    int weight = 0;
    vector<node_t*> children;
    node_t(string name, int weight) : name(name), weight(weight) {}
};

int child_count(node_t *n) {
    int childc = 0;
    for (auto it = n->children.begin(); it != n->children.end(); ++it)
        childc += child_count((*it));
    return n->children.size() + childc;
}

int main() {
	fstream infile("input");
    vector<node_t*> nodes;
    int weight;
    char trashc;
    string name, trash, line, child;
	while(getline(infile, line)) {
        stringstream ss(line);
        ss >> name >> trashc >> weight >> trashc >> trash;
        nodes.push_back(new node_t(name, weight));
    }
    infile = fstream("input");
    while (getline(infile, line)) {
        stringstream ss(line);
        ss >> name >> trashc >> weight >> trashc >> trash; ss.get();
        node_t *p, *c;
        while (getline(ss, child, ',')) {
            for (auto it = nodes.begin(); it != nodes.end(); ++it) {
                if ((*it)->name == child) c = *it;
                if ((*it)->name == name) p = *it;
            }
            p->children.push_back(c);
            ss.get();
        }
    }
    int lidx = 0;
    for (int i = 0; i < nodes.size(); ++i) {
        int c = child_count(nodes[i]);
        lidx = (c > child_count(nodes[lidx])) ? i : lidx;
    }
    cout << nodes[lidx]->name << " children: " << child_count(nodes[lidx]) << endl;
    for (int i = 0; i < nodes.size(); ++i)
        delete nodes[i];
	return 0;
}
