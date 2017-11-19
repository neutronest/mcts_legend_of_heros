#ifndef __LEGEND_STATE_H_
#define __LEGEND_STATE_H_

#include "state.h"
#include "player.h"
#include "skill.h"

using namespace std;

enum class legend_turn {E, J, L};

class action {
public:
    player* caster;
    vector<player*> target;
    skill* motion;
    action(player* caster_, vector<player*> target_, skill* motion_);

};

class gamer_status {
public:
    string name;
    player* gamer;
    vector<action*> actions;
    vector<action*> avaible_actions;

};

class legend_state: public state  {
public:
    gamer_status* estelle = new gamer_status();
    gamer_status* joshua = new gamer_status();
    gamer_status* leon = new gamer_status();
    legend_turn cur_turn = legend_turn::E; // each game starts with estelle's turn.
    bool is_over = false;

    legend_state();

    gamer_status* get_status_by_turn();

    bool is_terminal();

    void set_available_actions(gamer_status* cur_status);

    gamer_status* get_cur_status();

    int get_available_state_limit();

    legend_turn gen_next_turn();

    void check_alive();

    void print_status();

    legend_state* gen_next_state();

    void pprint_state();

    bool simulate_default_policy();

    int get_state_limit();

    string get_gamer_encoding(player* gamer);

    string get_encoding();

    double get_reward();

    bool is_boss_turn();

    void pprint();
};

#endif