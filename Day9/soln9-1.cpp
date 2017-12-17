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
    int groups = 0, score = 0, depth = 1;
    for (auto it = input.begin(); it != input.end(); ++it) {
        switch (*it) {
            case '!': ++it; break;
            case '<': garbage = true; break;
            case '>': garbage = false; break;
            case '}': if (!garbage) --depth; break;
            case '{': if (!garbage) { score += depth++; groups++; } break;
        }
    }
    cout << "Group count: " << groups << endl;
    cout << "Score: " << score << endl;
    return 0;
}
