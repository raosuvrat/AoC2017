#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<map>
#include<math.h>

using namespace std;

string flip_sq(string in) {
    int dim = in.size() % 3 ? 2 : 3;
    for (int i = 0; i < dim; ++i)
        reverse(in.begin() + i*dim, in.begin() + dim + i*dim);
    return in;
}

string rotate_sq(string in) {
    return (in.size() % 3) ? string {in[2],in[0],in[3],in[1]} : 
           string {in[6],in[3],in[0],in[7],in[4],in[1],in[8],in[5],in[2]};
}

int main() {
    ifstream infile("input");
    map<string, string> rules;
    while (!infile.eof()) {
        string line;
        if (getline(infile, line)) {
            line.erase(
                remove_if(line.begin(), line.end(), [](auto p){ return p=='/';}),
                line.end());
            string lval = line.substr(0, line.find(" => ")),
                   rval = line.substr(line.find(" => ")+4);
            rules[lval] = rval;
        }
    }

    string grid(".#...####");
    
    for (int loop = 0; loop < 18; ++loop) {
        string newgrid;
        vector<string> new_subcells;
        if (!((int)sqrt(grid.size()) % 2)) {
            for (int i = 0; i < sqrt(grid.size())/2; ++i) {
                for (int j = 0; j < sqrt(grid.size())/2; ++j) {
                    string subcell = grid.substr(j*2 + 2*i*sqrt(grid.size()), 2) +
                                     grid.substr(j*2 + 2*i*sqrt(grid.size()) + sqrt(grid.size()), 2);
                    for (int k = 0, l; k < 256 && !rules.count(subcell); ++k) {
                        subcell = rotate_sq(subcell);
                        for (int l = 0; l < 2 && !rules.count(subcell); ++l)
                            subcell = flip_sq(subcell);
                    }
                    new_subcells.push_back(rules[subcell]);
                }
            }
            for (int i = 0; i < new_subcells.size(); i += sqrt(new_subcells.size())) {
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(0,3);
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(3,3);
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(6,3);
            }
        } else {
            for (int i = 0; i < sqrt(grid.size())/3; ++i) {
                for (int j = 0; j < sqrt(grid.size())/3; ++j) {
                    string subcell = grid.substr(j*3 + 3*i*sqrt(grid.size()), 3) +
                                     grid.substr(j*3 + 3*i*sqrt(grid.size()) + sqrt(grid.size()), 3) +
                                     grid.substr(j*3 + 3*i*sqrt(grid.size()) + 2*sqrt(grid.size()), 3);
                    for (int k = 0, l; k < 256 && !rules.count(subcell); ++k) {
                        subcell = rotate_sq(subcell);
                        for (int l = 0; l < 2 && !rules.count(subcell); ++l)
                            subcell = flip_sq(subcell);
                    }
                    new_subcells.push_back(rules[subcell]);
                }
            }
            for (int i = 0; i < new_subcells.size(); i += sqrt(new_subcells.size())) {
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(0,4);
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(4,4);
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(8,4);
                for (int j = 0; j < sqrt(new_subcells.size()); ++j)
                    newgrid += new_subcells[i+j].substr(12,4);
            }
        }
        grid = newgrid;

    }
    cout << "Final grid: " << grid << endl 
         << " Size: " << grid.size() << " Dim: " << sqrt(grid.size())
         << " On count: " << count(grid.begin(), grid.end(), '#') << endl;
    return 0;
}
