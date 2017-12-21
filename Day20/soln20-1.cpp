#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct vector_t {
    long long i,j,k;
    vector_t(long long i, long long j, long long k) : i(i), j(j), k(k) {}
};
struct particle_t {
    vector_t p, v, a;
    particle_t(vector_t p, vector_t v, vector_t a) : p(p), v(v), a(a) {}
    long long dist() { return abs(p.i) + abs(p.j) + abs(p.k); }
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
        for (auto it = particles.begin(); it != particles.end(); ++it) {
            it->v.i += it->a.i; it->v.j += it->a.j; it->v.k += it->a.k;
            it->p.i += it->v.i; it->p.j += it->v.j; it->p.k += it->v.k;
        }
    }
    auto closest = particles.begin();
    for (auto it = particles.begin(); it != particles.end(); ++it)
        closest = it->dist() < closest->dist() ? it : closest;
    cout << "Closest particle is #" << closest - particles.begin() << endl;
    
    return 0;
}
