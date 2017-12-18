#include<math.h>
#include<fstream>
#include<iostream>
using namespace std;

int main() {
    fstream infile("input");
    string dir;
    double x = 0, y = 0, max = 0;
    while (infile >> dir) {
        if (dir == "n") y++;
        if (dir == "nw") { x -= .5; y += .5; }
        if (dir == "ne") { x += .5; y += .5; }
        if (dir == "se") { x += .5; y -= .5; }
        if (dir == "sw") { x -= .5; y -= .5; }
        if (dir == "s") y--;
        int d = abs(x) > abs(y) ? 2*abs(x) : (abs(x)+abs(y));
        max = (d > max) ? d : max;
    }
    cout << (abs(x) > abs(y) ? 2*abs(x) : (abs(x)+abs(y))) << endl;
    cout << "x: " << x << " y: " << y << " max: " << max << endl;
    return 0;
}
