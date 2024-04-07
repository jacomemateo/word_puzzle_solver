#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include "word_hunt_solver.h"
using namespace std;

void convert(vector<string>& puz, short num) {
    cout << puz[(num-1)/4][(num-1)%4];
}

int main() {
    vector<string> puzzle_vec = {
        "EOUP",
        "DRTC",
        "BSFA",
        "JGST"
    };


    // WordHuntSolver whs = WordHuntSolver("words.txt", "positions.txt", puzzle_vec);
    WordHuntSolver whs = WordHuntSolver("test_words.txt", "test_positions.txt", puzzle_vec);

    whs.find();

}