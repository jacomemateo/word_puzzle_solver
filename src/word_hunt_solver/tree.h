#pragma once
#include "trie_node.h"

template<typename T>
struct less_than_key
{
    inline bool operator() (const shared_ptr<TrieNode<T>>& struct1, const shared_ptr<TrieNode<T>>& struct2)
    {
        return (struct1->get_data() < struct2->get_data());
    }
};

template<typename T, typename nigga>
class tree {
public:
    tree();

    void add_word(const nigga& line);
    friend ostream& operator<<(ostream& stream, const tree<T, nigga>& tree) {
        stream << *(tree.m_head);
        return stream;
    }
    
private:
    shared_ptr<TrieNode<T>> m_head;
};

#include "tree.h"

template<typename T, typename nigga>
tree<T, nigga>::tree() {
    m_head = make_shared<TrieNode<T>>();
}

template<>
void tree<char, string>::add_word(const string& word) {
    shared_ptr<TrieNode<char>> curr_head = m_head;

    for (size_t i = 0; i < word.size(); ++i) {
        vector<shared_ptr<TrieNode<char>>>& curr_vec = curr_head->get_next();

        bool found = false;
        size_t found_index = 0;

        for (size_t j = 0; j < curr_vec.size(); ++j) {
            if (curr_vec[j]->get_data() == word[i]) {
                found = true;
                found_index = j;
                break;
            }
        }

        if (!found) {
            curr_head->add_child(word[i]);
            curr_head = curr_head->get_child(curr_head->get_next().size() - 1);
        } else {
            curr_head = curr_vec[found_index];
        }

        std::sort(curr_vec.begin(), curr_vec.end(), less_than_key<char>());
    }
    
    curr_head->set_end();
}

template<>
void tree< short, vector<short> >::add_word(const vector<short>& word) {
    shared_ptr<TrieNode<short>> curr_head = m_head;

    for (size_t i = 0; i < word.size(); ++i) {
        vector<shared_ptr<TrieNode<short>>>& curr_vec = curr_head->get_next();

        bool found = false;
        size_t found_index = 0;

        for (size_t j = 0; j < curr_vec.size(); ++j) {
            if (curr_vec[j]->get_data() == word[i]) {
                found = true;
                found_index = j;
                break;
            }
        }

        if (!found) {
            curr_head->add_child(word[i]);
            curr_head = curr_head->get_child(curr_head->get_next().size() - 1);
        } else {
            curr_head = curr_vec[found_index];
        }

        std::sort(curr_vec.begin(), curr_vec.end(), less_than_key<short>());

        // curr_head->set_end();
    }
}