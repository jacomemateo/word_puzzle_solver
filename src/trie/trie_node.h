#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;


template <typename T>
class TrieNode : public std::enable_shared_from_this<TrieNode<T>> {
public:
    friend class WordHuntSolver;

    TrieNode(); // Default constructor
    explicit TrieNode(T data, shared_ptr<TrieNode<T>> prev = nullptr); // Constructor with data and previous node

    void add_child(T data); // Add a child node with the given data
    void set_end(); // Mark the node as the end of a word
    bool get_end() const; // Check if the node is the end of a word

    T get_data() const;
    int get_child_size() const; // Get the number of children
    shared_ptr<TrieNode<T>> get_child(size_t i) const; // Get the child node at index i
    shared_ptr<TrieNode<T>> get_prev() const; // Get the previous node
    vector<shared_ptr<TrieNode<T>>>& get_next(); // Get the vector of child nodes

    friend ostream& operator<<(ostream& stream, const TrieNode<T>& node) {
        string output;
        node.recursive_traversal(output, "", node.m_next_nodes);

        stream << output;
        return stream;
    }

private:
    void recursive_traversal(string& output, string prev, const vector<shared_ptr<TrieNode<T>>>& current) const; // Helper function for traversal

    T m_data;
    shared_ptr<TrieNode<T>> m_prev;
    vector<shared_ptr<TrieNode<T>>> m_next_nodes;
    bool m_end_of_word;
};


template<typename T>
TrieNode<T>::TrieNode() : m_data(T()), m_prev(nullptr), m_end_of_word(false) {}

template<typename T>
TrieNode<T>::TrieNode(T data, shared_ptr<TrieNode<T>> prev) : m_data(data), m_prev(prev), m_end_of_word(false) {}

template<typename T>
void TrieNode<T>::add_child(T data) {
    auto child = make_shared<TrieNode<T>>(data, this->shared_from_this());
    m_next_nodes.push_back(child);
}

template<typename T>
void TrieNode<T>::set_end() {
    m_end_of_word = true;
}

template<typename T>
bool TrieNode<T>::get_end() const {
    return m_end_of_word;
}

template<typename T>
void TrieNode<T>::recursive_traversal(string& output, string prev, const vector<shared_ptr<TrieNode<T>>>& current) const {
    if (current.empty()) {
        output += "EMPTY\n";
        return;
    }

    for (const auto& child : current) {
        output += "\"" + prev.substr(0, prev.size()-1) + "\" -> \"" + prev + std::to_string(child->m_data) + "\"\n";

        if (child->get_end()) {
            output += '\"' + prev + to_string(child->m_data) + "\"[shape=circle, style=filled, fillcolor=Gray]\n";
        }

        if (!child->m_next_nodes.empty()) {
            recursive_traversal(output, prev + to_string(child->m_data) + ' ', child->m_next_nodes);
        }
    }
}

template<>
void TrieNode<char>::recursive_traversal(string& output, string prev, const vector<shared_ptr<TrieNode<char>>>& current) const {
    if (current.empty()) {
        output += "EMPTY\n";
        return;
    }

    for (const auto& child : current) {
        output += "\"" + prev + "\" -> \"" + prev + child->m_data + "\"\n";

        if (child->get_end()) {
            output += '\"' + prev + child->m_data + "\"[shape=circle, style=filled, fillcolor=Gray]\n";
        }

        if (!child->m_next_nodes.empty()) {
            recursive_traversal(output, prev + child->m_data, child->m_next_nodes);
        }
    }
}

template<typename T>
vector<shared_ptr<TrieNode<T>>>& TrieNode<T>::get_next() {
    return m_next_nodes;
}

template<typename T>
T TrieNode<T>::get_data() const {
    return m_data;
}

template<typename T>
int TrieNode<T>::get_child_size() const {
    return m_next_nodes.size();
}

template<typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::get_child(size_t i) const {
    if (i < m_next_nodes.size())
        return m_next_nodes[i];
    return nullptr; // Handle out-of-range index
}

template<typename T>
shared_ptr<TrieNode<T>> TrieNode<T>::get_prev() const {
    return m_prev;
}
