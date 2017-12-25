#include <iostream>
#include<math.h>
using namespace std;
int main() {
    int h = 0;
    for (int i = 107900; i <= (107900+17000); i += 17)
        for (int j = 2; j < i; ++j)
            if (!(i % j)) { h++; break; }
    cout << h << endl;
}