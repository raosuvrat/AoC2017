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
    int mul = 0;
    string op, arg1, arg2;
    map<string, long long> regfile;
    for (long long i = 0; i >= 0 && i < input.size(); ++i){
        stringstream ss(input[i]);
        ss >> op >> arg1 >> arg2;
        if (!regfile.count(arg1)) regfile[arg1] = 0;
        if (op == "set") {
            regfile[arg1] = isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "sub") {
            regfile[arg1] -= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "mul") { mul++;
            regfile[arg1] *= isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str());
        } if (op == "jnz") {
            if ((isalpha(arg1[0]) ? regfile[arg1] : atoi(arg1.c_str())) != 0)
            i += (isalpha(arg2[0]) ? regfile[arg2] : atoi(arg2.c_str()))-1;
        }
    }
    cout << mul << endl;
    return 0;
}
