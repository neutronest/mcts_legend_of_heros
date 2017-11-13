#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#pragma once
#include "legend_state.cc"

using namespace std;

class legend_mcts {

    legend_mcts* parent;
    vector<legend_mcts*> children; 
    state* game_state;
    int visit_times;
    double q_value;

    legend_mcts() {
        this->parent = nullptr;
        this->children = {};
        this->game_state = nullptr;
        this->visit_times = 0;
        this->q_value = 0.0;
    }

    bool is_all_expand() {
        
        if (this->game_state == nullptr) {
            cout<<"[WARNING... legend_mcts,is_all_expand: game_state is nullptr]"<<endl;
            return false;
        }

        int cur_avaible_action_num = this->game_state->get_available_state_limit();
        return false;
    }

    legend_mcts* expand_node() {


        return nullptr;
    }

    legend_mcts* get_best_child(int exploration) {


        return nullptr;
    }

    double default_policy() {


        return 0.0;
    }

    void backup(double reward) {

        return;
    }

    legend_mcts* main_policy(int computate_budge) {


        return nullptr;
    }



}