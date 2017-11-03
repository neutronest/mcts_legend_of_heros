#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#include "state.cc"

using namespace std;

class mcts_node {

public:



    mcts_node* parent;
    vector<mcts_node*> children; 
    state game_state;

    int visit_times;
    double q_value = 0.0;


    // Methods
    bool is_all_expand() {

        int state_limit = this->game_state.get_available_state_limit();
        if (this->children.size() == state_limit) {
            return true;
        }
        return false;
    }

    /***
    expand a new node from target node;
    choice a new action randomly action
    */
    mcts_node* expand_node() {
        
        vector<string> child_state_encodings;
        
        for (auto child = this->children.begin(); child != this->children.end(); child++) {
            child_state_encodings.push_back( (*child)->game_state.get_encoding());
        }

        state new_state = this->game_state.gen_next_state();
        while (std::find(child_state_encodings.begin(), 
            child_state_encodings.end(),
            new_state.get_encoding()) != child_state_encodings.end() ) {
            // 
            new_state = this->game_state.gen_next_state();
        }

        mcts_node* node = new mcts_node();
        node->parent = this;
        node->children = {};
        node->game_state = new_state;
        node->visit_times = 0;
        node->q_value = 0.0;
        return node;
    }


    /***
    Use UCB algorithm
    */
    mcts_node* get_best_child(int is_exploration) {

        mcts_node* best_node = nullptr;
        double max_score = - 9999.0;
        double c = 0.0;
        if (is_exploration) {
            c = 1.0 / sqrt(2);
        }
        
        for (auto iter = this->children.begin(); 
                  iter != this->children.end();
                  iter++) {
            mcts_node* cur_node = *iter;
            // caculate the exploition and exploration value
            double exploit_value = cur_node->q_value / cur_node->visit_times;
            double explore_value = c * sqrt(2 * log2(this->visit_times) / cur_node->visit_times);
            double ucb_score = exploit_value + explore_value;
            if (best_node == nullptr) {
                best_node = cur_node;
                max_score = ucb_score;
                continue;
            }
            // TODO
            // if found multi numbers of best score
            // mast choose one randomly.
            if (max_score < ucb_score) {
                best_node = cur_node;
                max_score = ucb_score;
            }   
        }
        return best_node;
    }


    double default_policy() {


        auto cur_state = this->game_state;
        while (cur_state.is_terminal() == false) {
            cur_state = cur_state.gen_next_state();
        }
        return cur_state.get_reward();
    }


    mcts_node* tree_policy(mcts_node* node) {
        // selection and expansion
        while (node->game_state.is_terminal() == false) {

            if (node->is_all_expand()) {
                node = node->get_best_child(0);
            } else {
                // expand a new node
                auto new_node = node->expand_node();
                return new_node;
            }
        }
        return node;
    }

    mcts_node* main_search() {

        return nullptr;
    }

};

int main() {



    return 1;

}