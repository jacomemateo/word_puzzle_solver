#include "tree.h"

class PathTree : public tree {
public:
    void add_word(string word) {
    link_node curr_head = m_head;

    for (size_t i = 0; i < word.size(); ++i) {
        bset& curr_vec = curr_head->get_next();

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

        std::sort(curr_vec.begin(), curr_vec.end(), less_than_key());
    }
    
    curr_head->set_end();
}
};