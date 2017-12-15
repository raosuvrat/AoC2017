#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#define NBANKS 16
using namespace std;

int largest(int *arr) {
	int ret = 0;
	for (int i = 0; i < NBANKS; ++i)
		ret = (arr[i] > arr[ret]) ? i : ret;
	return ret;
}
void print(int *arr) {
	for (int i = 0; i < NBANKS; ++i)
		cout << arr[i] << " ";
	cout << endl;
}

int main() {
	vector<vector<int>> mem;
	int lidx, store,count=0;
	int banks[NBANKS] = {2,8,8,5,4,2,3,1,5,5,1,2,15,13,5,14};
	print(banks);
	mem.push_back(vector<int>(banks,banks+sizeof(banks)/sizeof(banks[0])));
	while (++count) {
		lidx = largest(banks);
		store = banks[lidx];
		banks[lidx] = 0;
		while (store--)
			banks[(++lidx)%NBANKS] += 1;
		int incount = 0;
		for (int i = 0; i < mem.size(); ++i) {
			if (mem[i] == vector<int>(banks,banks+sizeof(banks)/sizeof(banks[0])))
				incount++;
		}
		if (incount ==2 ) {
			cout <<count << endl;
			return 0;
		}
		mem.push_back(vector<int>(banks,banks+sizeof(banks)/sizeof(banks[0])));
	}
	return 0;
}
