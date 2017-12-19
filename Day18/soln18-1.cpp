#include<map>
#include<fstream>
#include<vector>
#include<sstream>
#include<iostream>

using namespace std;
int main() {
    fstream infile("input");
    vector<string> input;
    while (!infile.eof()){
        string s("");
        if(getline(infile, s)) input.push_back(s);
    }
    string op, arg1, arg2; long long lastsound = 0;
    map<string, long long> regfile;
    for (long long i = 0; i < input.size(); ++i) {
        cout << input[i] << endl;
        stringstream ss(input[i]);
        ss >> op >> arg1 >> arg2;
        if (!regfile.count(arg1)) regfile[arg1] = 0;
        if (op == "snd") {
            lastsound = regfile[arg1];
            cout << "playing sound f: " << regfile[arg1] << endl;
        } if (op == "set") {
            regfile[arg1] = isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());

        } if (op == "add") {
            regfile[arg1] += isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "mul") {
            regfile[arg1] *= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "mod") {
            regfile[arg1] %= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "rcv") {
            if (regfile[arg1]) {cout << "recovered: " << lastsound << endl; return 0;}
        } if (op == "jgz") {
            if (regfile[arg1] > 0) i += (isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str()))-1;

        }
        for (auto it = regfile.begin(); it != regfile.end(); ++it)
            cout << it->first << " <-> " << it->second << endl;
    }
    return 0;
}
