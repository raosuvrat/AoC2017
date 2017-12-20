#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

void adv_scanners(map<int, vector<bool>> &m, map<int, int> &flips) {
    for (auto it = m.begin(); it != m.end(); ++it) {
        flips[it->first] *= ((it->second.back()) ? -1 : (it->second.front()) ? -1 : 1);
        rotate(it->second.begin(),
               (flips[it->first] > 0 ? it->second.end() - 1 : it->second.begin()+ 1),
               it->second.end());
    }
}

int main() {
    map<int, vector<bool>> layers;
    map<int, int> flips;
    fstream infile("input");
    int depth, range, severity = 0; char c;
    while (infile >> depth >> c >> range) {
        layers[depth] = vector<bool>(range);
        layers[depth][0] = true;
        flips[depth] = -1;
    }
    for (int i = 0; i <= depth; ++i) {
        if (layers.count(i)) {
            if (layers[i][0]) {
                severity += (i*layers[i].size());
            }
        }
        adv_scanners(layers, flips);
    }
    cout << severity << endl;


    return 0;
}
