#include<numeric>
#include<iostream>
#include<map>

int main() {
    enum state_t { A, B, C, D, E, F };
    state_t state = A;
    std::map<int,int> tape;
    for (int i = 0, cursor = 0; i < 12399302; ++i) {
        switch (state) {
            case A:
                if (!tape[cursor]) {
                    tape[cursor] = 1; ++cursor; state = B;
                } else {
                    tape[cursor] = 0; ++cursor; state = C;
                } break;
            case B:
                if (!tape[cursor]) {
                    tape[cursor] = 0; --cursor; state = A;
                } else {
                    tape[cursor] = 0; ++cursor; state = D;
                } break;
            case C:
                if (!tape[cursor]) {
                    tape[cursor] = 1; ++cursor; state = D;
                } else {
                    tape[cursor] = 1; ++cursor; state = A;
                } break;
            case D:
                if (!tape[cursor]) {
                    tape[cursor] = 1; --cursor; state = E;
                } else {
                    tape[cursor] = 0; --cursor; state = D;
                } break;
            case E:
                if (!tape[cursor]) {
                    tape[cursor] = 1; ++cursor; state = F;
                } else {
                    tape[cursor] = 1; --cursor; state = B;
                } break;
            case F:
                if (!tape[cursor]) {
                    tape[cursor] = 1; ++cursor; state = A;
                } else {
                    tape[cursor] = 1; ++cursor; state = E;
                } break;
            }
    }
    std::cout << "Checksum: " 
              << std::accumulate(tape.begin(), tape.end(), 0, [](auto &a, auto &b){return a+b.second;})
              << std::endl;
}
