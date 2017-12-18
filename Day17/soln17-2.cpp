#include<vector>
#include<iostream>
#include<algorithm>
#define STEPS 344
using namespace std;
int main() {
    int result;
    for (int pos = 0, i = 1; i <= 50000000; ++i, pos = (pos+STEPS)%i)
        if (!(pos++)) result = i;
    cout << result << endl;
    return 0;
}
