#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    fstream infile("input");
    int in; char c;
    vector<int> vec, input;
    while (infile >> in) { input.push_back(in); infile >> c; }
    for (int i = 0; i < 256; ++i) vec.push_back(i);

    for (int i = 0, pos = 0, skip = 0, l = input.size(); i < l; ++i) {
        int len = input[i];
        for (int i = 0; i < 256; ++i)
            cout << vec[i] << " ";
        cout << " len: " << len << " pos: " << pos << " sk: " << skip << endl;
        for (int j = 0; j < len/2; ++j)
            swap(vec[(pos+j)%vec.size()], vec[(pos-j+len-1)%vec.size()]);
        pos += len + skip++;
        pos %= vec.size();
    }
    cout << "Product: " << vec[0]*vec[1] << endl; 
    return 0;
}
