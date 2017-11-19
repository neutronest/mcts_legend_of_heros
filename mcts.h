#ifndef __MCTS_H_
#define __MCTS_H_

#include <string>
#include <vector>
#include <state.h>

using namespace std;

class mcts_node {
public:
    mcts_node* parent;
    vector<mcts_node*> children; 
    state* game_state;
    int visit_times;
    double q_value ;

    mcts_node();

    bool is_all_expand();

    mcts_node* expand_node();

    mcts_node* get_best_node(int exploaration);

    double default_policy();

    mcts_node* tree_policy();

    void backprop(double reward);

    mcts_node* main_search();
}
#endif