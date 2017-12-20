#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
using namespace std;


int main() {
    ifstream infile("input");
    map<int, pair<int,int>> layers;
    char c;
    int depth, range, delay = -1;
    while (infile >> depth >> c >> range)
        layers[depth] = pair<int, int>(0, range-1);
    bool caught = true; 
    while (caught) {
        ++delay;
        caught = false;
        for (auto it = layers.begin(); it != layers.end(); ++it)
            it->second.first = 0;
        
        for (int i = 0; i <= depth; ++i) {
            if (layers.count(i)) {
                if (!((layers[i].first++ + i + delay) % (2*layers[i].second))) {
                    caught = true;
                    break;
                }
            }
        }
    }
    cout << "Delay needed: " << delay << endl;
    return 0;
}
