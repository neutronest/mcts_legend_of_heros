#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "state.h"

using namespace std;

const vector<int> all_states = {1, -1, 2, -2};
const int MAX_ROUND_NUM = 100;

class nim_state :  public state {

public:

    int cur_value;
    int cur_round_idx;
    vector<string> state_history;


    nim_state(int round_idx);
    
    nim_state* gen_next_state();
    int get_state_limit();
    int get_available_state_limit();
    string get_encoding();
    bool is_terminal();
    double get_reward();
    void pprint();
};


nim_state::nim_state(int round_idx) {
    this->cur_round_idx = round_idx;
    
}

nim_state* nim_state::gen_next_state()  {
    // random
    int r = rand() % (this->get_available_state_limit());
    nim_state* new_state = new nim_state(0);
    new_state->cur_value = this->cur_value + all_states[r];
    new_state->cur_round_idx = this->cur_round_idx + 1;
    cout<<"new_state: idx/value: "<<new_state->cur_round_idx<<" / "<<new_state->cur_value<<endl;
    new_state->state_history = this->state_history; // copy by value
    new_state->state_history.push_back(to_string(all_states[r]));
    return new_state;
}

int nim_state::get_state_limit() {
    return all_states.size();
}

int nim_state::get_available_state_limit() {
    return all_states.size();
}

string nim_state::get_encoding() {
    return to_string(cur_value);
}

bool nim_state::is_terminal() {
    if (this->cur_round_idx >= MAX_ROUND_NUM) {
        return true;
    }
    return false;
}

double nim_state::get_reward() {
    return - abs(1 - this->cur_value);
}

void nim_state::pprint() {
    cout<<"value: "<<this->cur_value<<" round: "<<this->cur_round_idx<<" history: ";
    cout<<"[";
    for (auto iter=this->state_history.begin();
              iter != this->state_history.end();
              iter++) {
        cout<<*iter<<" ,";
    }
    cout<<"]\n";
    return;
}

bool nim_state::is_boss_turn() {
    return false;
}