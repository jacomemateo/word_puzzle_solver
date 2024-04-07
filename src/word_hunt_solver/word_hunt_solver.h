#pragma once
#include <stdexcept>
#include "tree.h"

struct found_match {
    vector<shared_ptr<TrieNode<char>>>& current;
    bool found;
    bool end;
};

class WordHuntSolver {
public:
    WordHuntSolver(string dictionary_path, string paths_file, vector<string> puzzle_vec);

    void recuse_paths(string& current_word, vector<string>& found_words, vector<shared_ptr<TrieNode<short>>>& current,  vector<shared_ptr<TrieNode<char>>>& current_nigga);
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


void WordHuntSolver::recuse_paths(string& current_word, vector<string>& found_words, vector<shared_ptr<TrieNode<short>>>& current_path_vec, vector<shared_ptr<TrieNode<char>>>& current_char_vec) {
    
    // Iterate over
    for (const auto& path_vec : current_path_vec) {
        short index = path_vec->m_data;
        char current_letter =  m_puzzle_vec[(index-1)/4][(index-1)%4];

        bool exists = false;
        bool end_char = true;

        // cout << "iterating thru node: " << index  << "\tSize of current_char_vec " << current_char_vec.size() << endl;

        // Check if the letter exists in the current path
        for(auto& trie_char_node : current_char_vec) {
            // cout << '\'' << trie_char_node->get_data() << '\'' << " ?= " << '\'' << current_letter << '\'' << endl;
            if( trie_char_node->get_data() == current_letter ) {
                end_char = trie_char_node->get_end();
                exists = true;
            
                current_char_vec = trie_char_node->get_next();
                break;
            }
        }

        if(exists) {
            current_word += current_letter;
            recuse_paths(current_word, found_words, path_vec->get_next(), current_char_vec );
        }

        if(path_vec->get_end() && end_char) {
            found_words.push_back(current_word);
            current_word = "";
            current_char_vec =  m_alphabet_tree.m_head->get_next();
        }
    }
}

void WordHuntSolver::find() {
    vector<string> found_words;
    string current_word;

    auto m = m_alphabet_tree.m_head->get_next();

    recuse_paths(current_word, found_words, m_path_tree.m_head->get_next(), m );

    for(auto word : found_words) {
        cout << word << endl;
    }
}