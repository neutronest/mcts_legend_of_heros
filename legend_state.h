#ifndef __LEGEND_STATE_H_
#define __LEGEND_STATE_H_

#include "state.h"
#include "player.h"
#include "skill.h"

using namespace std;

// to denote estelle, joshua and leon's turn
// E: estelle, J: joshua, L:leon
enum class legend_turn {E, J, L};

// the basic action definite for reinforcement learning
// caster: the initiative side to make the action
// target: the interactive side, may be more then one.
// one action, one skill.
// 
// always be the components of gamer_status 
//
// Example:
// auto ac = new action(leon_gamer, {estelle_gamer, joshua_gamer}, new leon_shadow_atk())
class action {
public:
    player* caster;
    vector<player*> target;
    skill* motion;
    action(player* caster_, vector<player*> target_, skill* motion_);
    action* dcopy();

};

// recording one player's status (for the whole game state)
// name: the player's name, estelle, joshua, or leon
// gamer: the player's basic object 
//        which maintain the orginal and current attribute of player,
//        such as hp, ep, sp, atk...
// actions: the action set that this player can used originally
//          include skill object and target players
//          same skill but different targets can be regard as different acions.
//          only mutable at init, immutable
// available_actions: the available action set in current time, 
//                  some actions (such as magic) have restrict, enough ep, sp etc., 
//                  filtered only by is_available func in skill.cc
//                  mutable and update in each state
class gamer_status {
public:
    string name;
    player* gamer;
    vector<action*> actions;
    vector<action*> available_actions;

    gamer_status* dcopy();
};


class legend_state: public state  {
public:
    gamer_status* estelle = new gamer_status();
    gamer_status* joshua = new gamer_status();
    gamer_status* leon = new gamer_status();
    legend_turn cur_turn = legend_turn::E; // each game starts with estelle's turn.
    bool is_over = false;

    legend_state();

    legend_state* dcopy();

    gamer_status* get_status_by_turn();

    bool is_terminal();

    void set_available_actions(gamer_status* cur_status);

    gamer_status* get_cur_status();

    int get_available_state_limit();

    legend_turn get_next_turn();

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