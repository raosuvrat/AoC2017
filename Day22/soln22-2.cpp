#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

int main() {
    char grid[25][25];
    ifstream infile("input");
    for (int i = 0; i < 25; ++i)
        for (int j = 0; j < 25; ++j)
            infile >> grid[i][j];

    enum direction_t {NORTH,EAST,SOUTH,WEST};
    direction_t d = NORTH;
    map<pair<int,int>, char> infinitegrid;
    int x = 12, y = 12, infected = 0;
    for (int i = 0; i < 10000000; ++i) {
        char *cur;
        if (x < 0 || x >= 25 || y < 0 || y >= 25) {
            if (!infinitegrid.count(pair<int,int>(y,x)))
                infinitegrid[pair<int,int>(y,x)] = '.';
            cur = &infinitegrid[pair<int,int>(y,x)];
        } else {
            cur = &grid[y][x];
        }
        if (*cur == '#') {
            *cur = 'F';
            switch (d) {
                case NORTH: x++; d = EAST; break;
                case EAST: y++; d = SOUTH; break;
                case SOUTH: x--; d = WEST; break;
                case WEST: y--; d = NORTH; break;
            }
        } else if (*cur == '.'){
            *cur = 'W';
            switch (d) {
                case NORTH: x--; d = WEST; break;
                case EAST: y--; d = NORTH; break;
                case SOUTH: x++; d = EAST; break;
                case WEST: y++; d = SOUTH; break;
            }
        } else if (*cur == 'F') {
            *cur = '.';
            switch (d) {
                case NORTH: y++; d = SOUTH; break;
                case EAST: x--; d = WEST; break;
                case SOUTH: y--; d = NORTH; break;
                case WEST: x++; d = EAST; break;
            }
        } else if (*cur == 'W') {
            *cur = '#';
            infected++;
            switch (d) {
                case NORTH: y--; break;
                case EAST: x++; break;
                case SOUTH: y++; break;
                case WEST: x--; break;
            }
        }
    }
    cout << "infected:" << infected << endl;
    return 0;
}
