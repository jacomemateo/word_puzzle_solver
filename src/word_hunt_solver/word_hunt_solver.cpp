#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include "tree.h"
using namespace std;


int main() {
    set<string> puzzle_vec = {
        "EOUP",
        "DRTS",
        "BSFE",
        "JGAO"
    };

    fstream dict_file;
    dict_file.open( RES_DIR + "z_words.txt"s , ios::in);
    if(!dict_file.is_open()) {
        cerr << "Error opening dict file." << endl;
        return -1;
    } 

    fstream save_file;
    save_file.open( RES_DIR + "save.txt"s , ios::out);
    if(!save_file.is_open()) {
        cerr << "Error opening new file." << endl;
        return -1;
    }


    tree<char, string> alphabet_tree;
    alphabet_tree.add_word("GOATED");
    alphabet_tree.add_word("GOAT");

    // string line;
    // while(getline(dict_file, line)) {
    //     tree.add_word(line);
    // }

    // cout << alphabet_tree << endl;

    tree<short, vector<short>> path_tree;
    path_tree.add_word( {1} );
    path_tree.add_word( {1, 2} );
    path_tree.add_word( {1, 3} );
    path_tree.add_word( {1, 4} );
    path_tree.add_word( {1, 4, 5} );
    path_tree.add_word( {1, 2, 3, 4} );
    path_tree.add_word( {4, 2, 3, 4} );
    path_tree.add_word( {14, 12, 13, 4} );

    // cout << path_tree << endl;
}