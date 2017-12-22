#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct vector_t {
    long long i,j,k;
    vector_t(long long i, long long j, long long k) : i(i), j(j), k(k) {}
    long long dist() const { return abs(i) + abs(j) + abs(k); }
    bool operator<(const vector_t &v) {
        return dist() < v.dist();
    }
    bool operator==(const vector_t &v) {
        return i == v.i && j == v.j && k == v.k;
    }
};
struct particle_t {
    vector_t p, v, a;
    particle_t(vector_t p, vector_t v, vector_t a) : p(p), v(v), a(a) {}
    void step() { 
        v.i += a.i; v.j += a.j; v.k += a.k;
        p.i += v.i; p.j += v.j; p.k += v.k;
    }
};
int main() {
    ifstream infile("input");
    vector<particle_t> particles;
    while (!infile.eof()) {
        string line;
        if (getline(infile,line)) {
            stringstream ss(line);
            char c; int i, j, k;
            vector<vector_t> vin;
            for (int q = 0; q < 3; ++q) {
                ss.ignore(256, '<');
                ss >> i >> c >> j >> c >> k;
                vin.push_back(vector_t(i, j ,k));
            }
            particles.push_back(particle_t(vin[0], vin[1], vin[2]));
        }
    }
    for (int tick = 0; tick < 10000; ++tick) {
        vector<vector_t> positions, kill;
        for_each(particles.begin(), particles.end(), [&](auto &p){
            p.step();
            positions.push_back(p.p);
        });
        for_each(positions.begin(), positions.end(), [&](auto &p){
            if (count(positions.begin(), positions.end(), p) > 1)
                kill.push_back(p);
        });
        sort(kill.begin(), kill.end());
        kill.erase(unique(kill.begin(), kill.end()), kill.end());
        auto new_end = remove_if(particles.begin(), particles.end(), [&](auto &p){
            return (find(kill.begin(), kill.end(), p.p) != kill.end());
        });
        particles.erase(new_end, particles.end());
    }
    cout << "Particles left: " << particles.size() << endl;
    
    return 0;
}
