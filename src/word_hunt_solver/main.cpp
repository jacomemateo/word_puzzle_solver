#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include "word_hunt_solver.h"
using namespace std;

int main() {
    set<string> puzzle_vec = {
        "EOUP",
        "DRTC",
        "BSFA",
        "JGAT"
    };

    fstream dict_file;
    dict_file.open( OUTPUT_DIR + "clean_words.txt"s , ios::in);
    if(!dict_file.is_open()) {
        cerr << "Error opening dict file." << endl;
        return -1;
    } 

    tree<char> alphabet_tree;
    alphabet_tree.add_word("GOATED");
    alphabet_tree.add_word("GOAT");

    cout << alphabet_tree << endl;

    tree<int> path_tree;
    path_tree.add_word( {1} );
    path_tree.add_word( {1, 2} );
    path_tree.add_word( {16, 12, 8, 4} );

    // for()

    cout << path_tree << endl;
}