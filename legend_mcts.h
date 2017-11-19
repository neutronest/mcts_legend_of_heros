#ifndef __LEGEND_MCTS_H_
#define __LEGEND_MCTS_H_

#include <vector>
#include "state.h"

class legend_mcts {

public:
    legend_mcts* parent;
    std::vector<legend_mcts*> children; 
    state* game_state;
    int visit_times;
    double q_value;

    legend_mcts();

    bool is_all_expand();

    legend_mcts* expand_node();

    legend_mcts* get_best_child(int is_exploration);

    double default_policy();

    legend_mcts* tree_policy();

    void backprop(double reward);

    legend_mcts* main_search(int computation_budge);
};


#endif