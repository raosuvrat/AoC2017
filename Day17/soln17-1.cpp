#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
int main() {
    vector<int> vec;
    vec.push_back(0);
    vec.reserve(2020);
    for (int i = 1; i <= 2017; ++i) {
        rotate(vec.begin(), vec.begin() + 344%vec.size(), vec.end());
        vec.push_back(i);
    }
    auto it = find(vec.begin(), vec.end(), 2017);
    cout << vec[(it - vec.begin() + 1)%vec.size()] << endl;
}
