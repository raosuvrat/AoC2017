#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

string knot_hash(string);

int main() {
    int count = 0;
    string input("hfdlxzhv");
    for (int i = 0; i < 128; ++i) {
        string hash = knot_hash(input + "-" + to_string(i));
        for (int j = 0; j < 32; ++j) {
            unsigned char byte = (hash[j] >= 'A') ?
                                   (hash[j] >= 'a') ? (hash[j] - 'a' + 10) : (hash[j] - 'A' + 10) :
                                 (hash[j] - '0');
            count += bitset<8>(byte).count();
        }
    }
    cout << "Used grid count: " << count << endl;
    return 0;
}

string knot_hash(string key) {
    char c;
    vector<int> input, vec, dense(16);
    for (int i = 0; i < key.size(); ++i)
        input.push_back((int)key[i]);
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
    stringstream ret;
    for (int i = 0; i < dense.size(); ++i)
        ret << setfill('0') << setw(2) << hex << dense[i];
    return ret.str();
}


