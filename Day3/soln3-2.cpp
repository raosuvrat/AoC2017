#include <iostream>
#include <iomanip>
#define DIM 17
using namespace std;

int main() {
	int **mem = new int*[DIM], OFFSET = DIM/2;
	for (int i = 0; i < DIM; ++i)
		mem[i] = new int[DIM]();
	auto localsum = [&](int x, int y) {
		return mem[x][y-1]+mem[x][y+1]+
			   mem[x-1][y]+mem[x+1][y]+
			   mem[x-1][y-1]+mem[x-1][y+1]+
			   mem[x+1][y-1]+mem[x+1][y+1];
	};

	for (int x,y,ring = 0; ring < 6; ++ring) {
		if (!ring) { mem[OFFSET][OFFSET] = 1; continue; }
		x = OFFSET+ring;
		y = x-1;
		mem[x][y] = localsum(x,y);
		for (;y > OFFSET-ring; --y) mem[x][y] = localsum(x,y);
		for (;x > OFFSET-ring; --x) mem[x][y] = localsum(x,y);
		for (;y < OFFSET+ring; ++y) mem[x][y] = localsum(x,y);
		for (;x <=OFFSET+ring; ++x) mem[x][y] = localsum(x,y);
	}

	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j)
			cout << setw(10) << mem[j][i] << " ";
		cout << endl << endl;
	}
	for (int i = 0; i < DIM; ++i)
		delete[] mem[i];
	delete mem;
	return 0;
}
