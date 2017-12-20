#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream infile("input");
    string line;
    vector<string> grid;
    while (!infile.eof())
        if (getline(infile, line)) grid.push_back(line);
    
    int y = 0, x = 0, y_mom = 1, x_mom = 0;
    for (int i = 0; i < grid[0].size(); ++i)
        if (grid[0][i] != ' ') { x = i; break; }

    while (true) {
        if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size()) break;
        switch (grid[y][x]) {
            case '|':
            case '-': x += x_mom; y += y_mom; break;
            case '+':
                if (y_mom) {
                    x_mom = (grid[y][x-1] == ' ') ? 1 : -1; y_mom = 0; x += x_mom;
                } else {
                    y_mom = (grid[y-1][x] == ' ') ? 1 : -1; x_mom = 0; y += y_mom;
                }
                break;
            default:
                cout << "Encountered: " << grid[y][x] << endl;
                y += y_mom; x += x_mom; break;
        }
    }

    return 0;
}
