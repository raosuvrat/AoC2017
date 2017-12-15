#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#define NBANKS 16
using namespace std;

int main() {
	vector<long long> vec_a, vec_b;
	long long a = 679, b = 771, sum=0;
	for (int i = 0; i < 5000000; ) {
		a = (a*16807)%2147483647;
		if (!(a%4)) {
			++i;
			vec_a.push_back(a);
		}
	}
	for (int i = 0; i < 5000000;) {
		b = (b*48271)%2147483647;
		if (!(b%8)) {
			++i;
			vec_b.push_back(b);
		}
	}
	for (int i = 0; i < 5000000; ++i) {
		//cout << vec_a[i] << endl << vec_b[i] <<endl;
		if ((vec_a[i]&0xffff) == (vec_b[i]&0xffff)) sum++;
	}
	cout << sum << endl;
	return 0;
}
