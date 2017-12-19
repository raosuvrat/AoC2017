#include<map>
#include<fstream>
#include<vector>
#include<queue>
#include<sstream>
#include<iostream>
using namespace std;

struct Machine {
	Machine *partner;
	vector<string> rom;
	queue<long long> out; int sent = 0;
	int pc = 0, id;
	map<string, long long> regfile;
	Machine(vector<string> input, int id) : rom(input), id(id) { regfile["p"] = id; }
	bool step() {
		string op, arg1, arg2;
		stringstream ss(rom[pc]);
		ss >> op >> arg1 >> arg2;
		if (!regfile.count(arg1)) regfile[arg1] = 0;
        if (op == "snd") {
            out.push(regfile[arg1]); ++sent;
        } if (op == "set") {
            regfile[arg1] = isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "add") {
            regfile[arg1] += isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "mul") {
            regfile[arg1] *= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "mod") {
            regfile[arg1] %= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "rcv") {
			if (partner->out.empty()) return false;
			regfile[arg1] = partner->out.front(); partner->out.pop();
        } if (op == "jgz") {
            if ((isalpha(arg1[0]) ? regfile[arg1] : atoi(arg1.c_str())) > 0)
                pc += (isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str()))-1;
        }
		++pc;
		return (pc >= 0 && pc < rom.size());
	}
};

int main() {
    fstream infile("input");
    vector<string> input;
    while (!infile.eof()){
        string s("");
        if(getline(infile, s)) input.push_back(s);
    }
	Machine a(input, 0), b(input, 1);
	a.partner = &b; b.partner = &a;
	while (a.step() || b.step());
	cout << "a sent: " << a.sent << " b sent: " << b.sent << endl;
    return 0;
}
