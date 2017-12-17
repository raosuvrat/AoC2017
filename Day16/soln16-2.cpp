#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string line ("");
	char temp;
	vector<string> input;
	string prog_line("abcdefghijklmnop");
	fstream infile("input");
	while (!infile.eof()) /*vim:   %s/,/\r/g */
		if (getline(infile, line)) input.push_back(line);
	map<string, string> cache;
	for (int q = 0; q < 1000000000; ++q) {
		// Shortcut: look for a cycle and skip to end of 1000000000 loop :facepalm:
		if (cache.count(prog_line)) {
			prog_line = cache[prog_line];
			continue;
		}
		string start(prog_line);
		for (int i = 0; i < input.size(); ++i) {
			stringstream ss(input[i]);
			char temp, op, pa, pb;
			int xa,xb,r;
			ss >> op;
			switch(op) {
				case 's':
					ss >> r;
					rotate(prog_line.begin(), prog_line.end() - r, prog_line.end());
					break;
				case 'x':
					ss >> xa >> temp >> xb;
					temp = prog_line[xa];
					prog_line[xa] = prog_line[xb];
					prog_line[xb] = temp;
					break;
				case 'p':
					ss >> pa >> temp >> pb; xa = xb = -1;
					for (int j = 0, jl = prog_line.size(); (j<jl)&&(xa==-1||xb==-1); ++j) {
						xa = (prog_line[j] == pa) ? j : xa;
						xb = (prog_line[j] == pb) ? j : xb;
					}
					temp = prog_line[xa];
					prog_line[xa] = prog_line[xb];
					prog_line[xb] = temp;

				default: break;
			}
		}
		cache[start] = prog_line;
	}	

	cout << prog_line << endl;
	return 0;
}
