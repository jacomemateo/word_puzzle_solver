#pragma once
#include <stdexcept>
#include "tree.h"

struct found_match {
    vector<shared_ptr<TrieNode<char>>>& current;
    bool found;
};

class WordHuntSolver {
public:
    WordHuntSolver(string dictionary_path, string paths_file, vector<string> puzzle_vec);

    void recuse_paths(string& current_word, vector<string>& found_words, const vector<shared_ptr<TrieNode<short>>>& current,  vector<shared_ptr<TrieNode<char>>>& current_nigga);
    found_match recuse_dict(char puzzle_letter, vector<shared_ptr<TrieNode<char>>>& current);
    void find();

private:
    tree<char> m_alphabet_tree;
    tree<short> m_path_tree;
    vector<string> m_puzzle_vec;
};

WordHuntSolver::WordHuntSolver(string dictionary_path, string paths_path, vector<string> puzzle_vec) {
    m_puzzle_vec = puzzle_vec;

    if(dictionary_path.empty() || paths_path.empty()) {
        throw invalid_argument("Error invalid file.");
    }

    fstream dict_file;
    dict_file.open( OUTPUT_DIR + dictionary_path , ios::in);
    if(!dict_file.is_open()) {
        throw invalid_argument("Error opening dict file.");
    }

    fstream paths_file;
    paths_file.open( OUTPUT_DIR + paths_path , ios::in);
    if(!paths_file.is_open()) {
        throw invalid_argument("Error opening paths file.");
    }

    m_alphabet_tree = tree<char>();
    m_path_tree = tree<short>();

    string line;
    while(getline(dict_file, line)) {
        m_alphabet_tree.add_word(line);
    }

    while(getline(paths_file, line)) {
        vector<short> temp_vec;

        short start_pos = 0;
        short size = 0;

        for(int i=0; i<line.size(); i++) {
            if(line[i] == ' ') {
                size = i-start_pos;

                short num = atoi( line.substr(start_pos, size).c_str() );
                temp_vec.push_back(num);

                start_pos = i+1;
            }

        }

        m_path_tree.add_word(temp_vec);
    }
}

found_match WordHuntSolver::recuse_dict(char puzzle_letter, vector<shared_ptr<TrieNode<char>>>& current) {
    for(auto& c : current) {
        if( c->get_data() == puzzle_letter ) {
            return found_match {
                c->get_next(),
                true
            };
        }
    }

    return found_match {
        current,
        false
    };
}

void WordHuntSolver::recuse_paths(string& current_word, vector<string>& found_words, const vector<shared_ptr<TrieNode<short>>>& current, vector<shared_ptr<TrieNode<char>>>& current_nigga) {
    for (const auto& child : current) {
        short index = child->m_data;
        char puzzle_letter =  m_puzzle_vec[(index-1)/4][(index-1)%4];

        found_match found = recuse_dict(puzzle_letter, current_nigga);

        if ( found.found ) {
            current_word += puzzle_letter;
            recuse_paths(current_word, found_words, child->m_next_nodes, found.current);
        } else {
            current_word = "";
        }
        // current_nigga = m_alphabet_tree.m_head->get_next();
        // return;

        if(child->get_end()) {
            found_words.push_back(current_word);
            current_word = "";
        }

    }
}

void WordHuntSolver::find() {
    vector<string> found_words;
    string current_word;

    recuse_paths(current_word, found_words, m_path_tree.m_head->get_next(), m_alphabet_tree.m_head->get_next() );

    for(auto word : found_words) {
        cout << word << endl;
    }
}