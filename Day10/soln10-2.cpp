#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    fstream infile("input");
    char c;
    vector<int> input, vec, dense(16);
    while (infile >> c)
        input.push_back((int)c);
    for (int i = 0; i < 256; ++i) vec.push_back(i);
    vector<int> suffix = {17,31,73,47,23};
    input.reserve(input.size() + suffix.size());
    input.insert(input.end(), suffix.begin(), suffix.end());

    for (int h = 0, pos = 0, skip = 0; h < 64; ++h) {
        for (int i = 0, l = input.size(); i < l; ++i) {
            int len = input[i];
            for (int j = 0; j < len/2; ++j)
                swap(vec[(pos+j)%vec.size()], vec[(pos-j+len-1)%vec.size()]);
            pos += len + skip++;
            pos %= vec.size();
        }
    }
    for (int i = 0; i < vec.size(); ++i) {
        if (!(i%16))
            dense[i/16] = vec[i];
        else
            dense[i/16] ^= vec[i];
    }
    for (int i = 0; i < 16; ++i)
        cout << setfill('0') << setw(2) << hex << dense[i];
    cout << endl;

    return 0;
}
