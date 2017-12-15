#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<sstream>

using namespace std;

int main() {
	int highest = 0;
	map<string, int> reg;
	fstream infile("input");
	vector<string> input;
	while(!infile.eof()) {
		string line("");
		if (getline(infile, line)) input.push_back(line);
	}
	for (int i = 0; i < input.size(); ++i)
		reg[input[i].substr(0,input[i].find(" "))] = 0;
	for (int i = 0; i < input.size(); ++i) {
		stringstream ss(input[i]);
		string r, com, blank, r2, op;
		int cond, val;
		ss >> r >> com >> val >> blank >> r2 >> op >> cond;
		int mul = (com == "inc") ? 1 : -1;

		if (op == "<")
			if (reg[r2] < cond) reg[r] += mul*val;
		if (op == "<=")
			if (reg[r2] <= cond) reg[r] += mul*val;
		if (op == ">")
			if (reg[r2] > cond) reg[r] += mul*val;
		if (op == ">=")
			if (reg[r2] >= cond) reg[r] += mul*val;
		if (op == "!=")
			if (reg[r2] != cond) reg[r] += mul*val;
		if (op == "==")
			if (reg[r2] == cond) reg[r] += mul*val;

		highest = (reg[r2] > highest) ? reg[r2] : highest;
	}

	for (auto it = reg.begin(); it != reg.end(); ++it)
		cout << it->first << ": " << it->second << endl; 
	cout << "Highest: " << highest << endl;
    return 0;
}
