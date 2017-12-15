#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	vector<int> mem;
    int count, cursor;
	ifstream infile("input");
	while (infile >> cursor) mem.push_back(cursor);
	for (cursor = 0, count = 0; cursor >= 0 && cursor < mem.size(); ++count){
		int move = mem[cursor];
		if (move >= 3)
			mem[cursor]--;
		else
			mem[cursor]++;
		cursor+=move;

	}

	cout << count << endl;
	return 0;
}
