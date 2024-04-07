#pragma once
#include <concepts>
#include "trie_node.h"

template<typename T>
concept arithmetic = std::integral<T>; // Inculdes char!

template<typename T>
struct tree_traits {
    using container_type = std::vector<T>;
};

template<>
struct tree_traits<char> {
    using container_type = std::string;
};

template<typename T>
struct less_than_key
{
    inline bool operator() (const shared_ptr<TrieNode<T>>& struct1, const shared_ptr<TrieNode<T>>& struct2)
    {
        return (struct1->get_data() < struct2->get_data());
    }
};

template<typename T>
requires arithmetic<T>
class tree {
public:
    friend class WordHuntSolver;
    tree();

    void add_word(const tree_traits<T>::container_type & line);
    friend ostream& operator<<(ostream& stream, const tree<T>& tree) {
        stream << *(tree.m_head);
        return stream;
    }
    
private:
    shared_ptr<TrieNode<T>> m_head;
};

#include "tree.h"

template<typename T>
requires arithmetic<T>
tree<T>::tree() {
    m_head = make_shared<TrieNode<T>>();
}

template<>
void tree<char>::add_word(const tree_traits<char>::container_type& word) {
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

template<typename T>
requires arithmetic<T>
void tree<T>::add_word(const tree_traits<T>::container_type & word) {
    shared_ptr<TrieNode<T>> curr_head = m_head;

    for (size_t i = 0; i < word.size(); ++i) {
        vector<shared_ptr<TrieNode<T>>>& curr_vec = curr_head->get_next();

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

        std::sort(curr_vec.begin(), curr_vec.end(), less_than_key<T>());

    }

    curr_head->set_end();
}