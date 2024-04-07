#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

int main() {
    fstream dictonary_file;

    dictonary_file.open( RES_DIR + "dictionary.txt"s , ios::in);
    if(!dictonary_file.is_open()) {
        cerr << "Error opening dictionary file." << endl;
        return -1;
    }

    fstream new_dict;
    new_dict.open( RES_DIR + "z_words.txt"s , ios::out);
    if(!new_dict.is_open()) {
        cerr << "Error opening new file." << endl;
        return -1;
    }


    string word;
    while(getline(dictonary_file, word)) {
        if(word.size() <= 8 && word.size() >= 3 && regex_match(word, std::regex("^[A-Za-z]+$"))) {
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            new_dict << word << '\n';
        }
    }
    
    dictonary_file.close();
    new_dict.close();
}
