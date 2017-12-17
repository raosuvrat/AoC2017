#include <string>
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    fstream in("input");
    string input("");
    getline(in, input); 
    cout << input << endl;
    bool garbage = false;
    int score = 0, depth = 1, garbc = 0;
    for (auto it = input.begin(); it != input.end(); ++it) {
        switch (*it) {
            case '!': ++it; break;
            case '<': if (!garbage) garbage = true; else ++garbc; break;
            case '>': if (garbage) garbage = false; else --garbc; break;
            case '}': if (!garbage) --depth; else ++garbc; break;
            case '{': if (!garbage) score += depth++; else ++garbc; break;
            default: if (garbage) ++garbc;
        }
    }
    cout << "Score: " << score << endl
         << "Garb. count: " << garbc << endl;
    return 0;
}
