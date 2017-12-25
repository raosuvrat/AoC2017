#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

int build_bridge(vector<pair<int,int>> ports, vector<pair<int,int>> &bridge) {
    pair<int,int> back = bridge.back();
    int length = bridge.size();
    int strength = accumulate(bridge.begin(), bridge.end(), 0, [](auto &a, auto &b){
                                  return a + b.first + b.second; });
    for (auto it = ports.begin(); it != ports.end(); ++it) {
        vector<pair<int,int>> nbridge(bridge), nports(ports);
        if (it->first == back.second) {
            nports.erase(remove(nports.begin(), nports.end(), *it), nports.end());
            nbridge.push_back(*it);
            int nlength = build_bridge(nports, nbridge);
            if (length < nlength) {
                length = nlength;
            }
        } else if (it->second == back.second) {
            nports.erase(remove(nports.begin(), nports.end(), *it), nports.end());
            nbridge.push_back(pair<int,int>(it->second, it->first));
            int nlength = build_bridge(nports, nbridge);
            if (length < nlength) {
                length = nlength;
            }
       }
    }
    if (length == 40) // shrug
        cout << "l: " << length << " s: " << strength << endl;
    return length;
}

int main() {
    ifstream infile("input");
    vector<pair<int,int>> ports;
    while (!infile.eof()) {
        string line;
        if (getline(infile, line)) {
            stringstream ss(line);
            int x, y; char c;
            ss >> x >> c >> y;
            ports.push_back(pair<int,int>(x,y));
        }
    }
    vector<pair<int,int>> mag_ports;
    ports.erase(remove_if(ports.begin(), ports.end(), [&](auto &p){
        if (!p.first) {
            mag_ports.push_back(p);
            return true;
        } else if (!p.second) {
            mag_ports.push_back(pair<int,int>(p.second, p.first));
            return true;
        }
        return false;
    }), ports.end());
    
    for (auto it = mag_ports.begin(); it != mag_ports.end(); ++it) {
        vector<pair<int,int>> bridge(1, *it);
        cout << build_bridge(ports, bridge) << endl;
    }
    
    return 0;
}
