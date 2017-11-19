#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <ctime>
#include <unistd.h>


#pragma once
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

    action(player* caster_, vector<player*> target_, skill* motion_) {
        this->caster = caster_;
        this->target = target_;
        this->motion = motion_;
    }
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
// avaible_actions: the avaible action set in current time, 
//                  some actions (such as magic) have restrict, enough ep, sp etc., 
//                  filtered only by is_avaible func in skill.cc
//                  mutable and update in each state
class gamer_status {

public:

    string name;
    player* gamer;
    vector<action*> actions;
    vector<action*> avaible_actions;
};

class legend_state : public state {

public:

    gamer_status* estelle = new gamer_status();
    gamer_status* joshua = new gamer_status();
    gamer_status* leon = new gamer_status();
    legend_turn cur_turn = legend_turn::E; // each game starts with estelle's turn.
    bool is_over = false;


    legend_state() {
        
        // init each players
        //
      
        player* estelle_gamer = new player(2000.0, 400.0, 0.0, 200.0);
        player* joshua_gamer = new player(1800.0, 0.0, 0.0, 300.0);
        player* leon_gamer = new player(10000.0, 0.0, 0.0, 500.0);

        vector<action*> estelle_actions = {
            new action(estelle_gamer, {leon_gamer}, new normal_atk()),
            new action(estelle_gamer, {estelle_gamer, joshua_gamer}, new estelle_encourage()),
            new action(estelle_gamer, {estelle_gamer}, new estelle_heal_small()),
            new action(estelle_gamer, {joshua_gamer}, new estelle_heal_small()),
            new action(estelle_gamer, {estelle_gamer, joshua_gamer}, new estelle_heal_all()),
            new action(estelle_gamer, {estelle_gamer, joshua_gamer}, new estelle_shell_all())
        };
        estelle->name = "艾丝蒂尔";
        estelle->gamer = estelle_gamer;
        estelle->actions = estelle_actions;
        estelle->avaible_actions = {};
        // joshua
        vector<action*> joshua_actions = {
            new action(joshua_gamer, {leon_gamer}, new normal_atk()),
            new action(joshua_gamer, {leon_gamer}, new joshua_double_atk()),
            new action(joshua_gamer, {leon_gamer}, new joshua_smove())

        };
        joshua->name = "约修亚";
        joshua->gamer = joshua_gamer;
        joshua->actions = joshua_actions;
        joshua->avaible_actions = {};

        // leon
        vector<action*> leon_actions = {
            new action(leon_gamer, {estelle_gamer}, new normal_atk()),
            new action(leon_gamer, {joshua_gamer}, new normal_atk()),
            new action(leon_gamer, {estelle_gamer}, new leon_shadow_atk()),
            new action(leon_gamer, {joshua_gamer}, new leon_shadow_atk()),
            new action(leon_gamer, {estelle_gamer, joshua_gamer}, new leon_ghostfire_atk()),
            new action(leon_gamer, {leon_gamer}, new leon_buff()),
            new action(leon_gamer, {leon_gamer}, new leon_deep_shell()),
            new action(leon_gamer, {estelle_gamer, joshua_gamer}, new leon_final_move())

        };
        leon->name = "剑帝";
        leon->gamer = leon_gamer;
        leon->actions = leon_actions;
        leon->avaible_actions = {};


        this->cur_turn = legend_turn::E;
        auto cur_status = this->get_status_by_turn();
        this->set_avaible_actions(cur_status);

        is_over = false;
    }

    gamer_status* get_status_by_turn() {
        
        gamer_status* cur_status = nullptr;        
        if (this->cur_turn == legend_turn::E) {
            cur_status = this->estelle;
        } else if (this->cur_turn == legend_turn::J) {
            cur_status = this->joshua;
        } else {
            cur_status = this->leon;
        } 
        return cur_status;
           
    }

    bool is_terminal(){

        if (this->estelle->gamer->is_dead && this->joshua->gamer->is_dead) {
            return true;
        }
        if (this->leon->gamer->is_dead) {
            return true;
        }
        return false;
    }

    void set_avaible_actions(gamer_status* cur_status) {

        cur_status->avaible_actions = {};
        for(auto iter = cur_status->actions.begin();
            iter != cur_status->actions.end();
            iter++) {
            auto action_ = *iter;
            if (action_->motion->is_avaible(cur_status->gamer, action_->target) == true) {
                cur_status->avaible_actions.push_back(action_);
            }
        }
        if (cur_status->avaible_actions.size() == 0) {
            cout<<"[WARNING... Not Avaible acions found!!!!]"<<endl;
            action* bottom_action = new action(cur_status->gamer, {}, new bottom_move());
            cur_status->avaible_actions.push_back(bottom_action);
        }
        return;
    }

    gamer_status* get_cur_status() {
        gamer_status* cur_status = nullptr;
        if (this->cur_turn == legend_turn::E) {
            cur_status = this->estelle;
        } else if (this->cur_turn == legend_turn::J) {
            cur_status = this->joshua;
        } else {
            cur_status = this->leon;
        }

        return cur_status;
    }


    int get_available_state_limit() {
        
        gamer_status* cur_status = this->get_cur_status();
        return cur_status->avaible_actions.size();
    }

    legend_turn get_next_turn() {

        bool is_estelle_dead = this->estelle->gamer->cur_hp > 0 ? false : true;
        bool is_joshua_dead = this->joshua->gamer->cur_hp > 0 ? false : true;
        bool is_leon_dead = this->leon->gamer->cur_hp > 0 ? false : true;
        

        if (this->cur_turn == legend_turn::E) {

            if(is_joshua_dead == false) {
                return legend_turn::J;
            } else if (is_leon_dead == false){
                return legend_turn::L;
            }
        } else if (this->cur_turn == legend_turn::J) {
            if (is_leon_dead == false) {
                return legend_turn::L;
            } // else means game win
        } else {
            // this->cur_turn == legend_turn::L
            if (is_estelle_dead == false) {
                return legend_turn::E;
            } else if (is_joshua_dead == false) {
                return legend_turn::J;
            } // else gamer over
        }

        
    }

    void check_alive() {
        if (this->estelle->gamer->cur_hp <= 0) {
            this->estelle->gamer->is_dead = true;
        }
        if (this->joshua->gamer->cur_hp <= 0) {
            this->joshua->gamer->is_dead = true;
        }
        if (this->leon->gamer->cur_hp <= 0) {
            this->leon->gamer->is_dead = true;
        }
    }

    void print_status() {

        

    }

    legend_state* gen_next_state() {

        

        gamer_status* cur_status = this->get_status_by_turn();        
        if (cur_status->gamer->encouraged > 0) {
            cur_status->gamer->cur_atk = 1.5 * cur_status->gamer->get_base_atk();
            cur_status->gamer->encouraged -= 1;
        }
        cout<<cur_status->name<<"'s turn: "<<endl;
        int len_of_avaible_actions = cur_status->avaible_actions.size();
        int r = rand() % len_of_avaible_actions;
        action* cur_action = cur_status->avaible_actions[r];
        cur_action->motion->apply(cur_action->caster, cur_action->target);
        cout<<cur_status->name<<"使用了 "<<cur_action->motion->name<<" ..."<<endl;
        cout<<"----------"<<endl;
        
        this->check_alive();        
        if (this->is_terminal()) {
            this->is_over = true;
            cout<<"游戏结束!!!!"<<endl;
            return this;
        }

        legend_state* next_state = new legend_state(*this);        
        next_state->cur_turn = this->get_next_turn();
        next_state->set_avaible_actions(next_state->get_status_by_turn());
        return next_state;

    }
    /*
    legend_state* gen_next_state() {
        
        gamer_status* cur_status = nullptr;
        if (this->cur_turn == legend_turn::E) {
            cur_status = this->estelle;
        } else if (this->cur_turn == legend_turn::J) {
            cur_status = this->joshua;
        } else {
            cur_status = this->leon;
        }

        if (cur_status->gamer->encouraged > 0) {
            cur_status->gamer->cur_atk = 1.5 * cur_status->gamer->get_base_atk();
            cur_status->gamer->encouraged -= 1;
        }


        cout<<cur_status->name<<"'s turn: "<<endl;
        this->set_avaible_actions(cur_status);
        int len_of_avaible_actions = cur_status->avaible_actions.size();
        
        int r = rand() % len_of_avaible_actions;
        action* cur_action = cur_status->avaible_actions[r];
        cur_action->motion->apply(cur_action->caster, cur_action->target);
        cout<<cur_status->name<<"使用了 "<<cur_action->motion->name<<" ..."<<endl;

        if (this->is_terminal()) {
            this->is_over = true;
            cout<<"游戏结束!!!!"<<endl;
        }

        this->get_next_turn();

        cout<<"----------"<<endl;
        return this;
    }
    */

    void pprint_state() {
        // print information of each player
        // foramt:
        // estelle- HP-1000 MP-1000 joshua- 
        int estelle_hp = this->estelle->gamer->cur_hp;
        int estelle_ep = this->estelle->gamer->cur_ep;
        int joshua_hp = this->joshua->gamer->cur_hp;
        int joshua_sp = this->joshua->gamer->cur_sp;
        int leon_hp = this->leon->gamer->cur_hp;
        cout<<"艾丝蒂尔- HP:"<<estelle_hp<<" EP: "<<estelle_ep;
        cout<<"约修亚- HP:"<<joshua_hp<<" SP: "<<joshua_sp;
        cout<<"剑帝- HP:"<<leon_hp<<endl;

    }

    bool simulate_default_policy() {

        return false;
    }   

    int get_state_limit() {
        return -1;
    }

    // encoding the state's information to string
    // can distinguish diff state's by their encoding result
    // encoding format:
    //   E-HP2000|EP200|SP0|Sh1|En1|J-JP1800|EP0|SP200|Sh1|En1|L-...
    string get_gamer_encoding(player* gamer) {

        string hp = to_string(int(gamer->cur_hp));
        string ep = to_string(int(gamer->cur_ep));
        string sp = to_string(int(gamer->cur_sp));
        string sh = to_string(int(gamer->shell));
        string en = to_string(int(gamer->encouraged));
        string res = "";
        res = "HP" + hp + "|EP" + ep + "|SP" + sp + "|Sh" + sh + "|En" + en;
        return res;
    }



    string get_encoding() {
        
        player* estelle_gamer = this->estelle->gamer;
        player* joshua_gamer = this->joshua->gamer;
        player* leon_gamer = this->leon->gamer;

        string estelle_encode = this->get_gamer_encoding(estelle_gamer);
        string joshua_encode = this->get_gamer_encoding(joshua_gamer);
        string leon_encode = this->get_gamer_encoding(leon_gamer);
        string encode_str = "|E-" + estelle_encode + "|J-" + joshua_encode + "|L-" + leon_encode;
        return encode_str;
    }


    // reward = -| 0 - leon->cur_hp()) / 1000.0|
    // for example, if player debeat the boss, then reward = -|-0 - 0| = 0
    // if player failed but boss 5000 hp left, then reward = - |-5000/1000| = -5
    // reward's range: [-20, 0]
    double get_reward() {
        return - abs(0 - this->leon->gamer->cur_hp);
    }


    bool is_boss_turn() {
        if (this->cur_turn == legend_turn::L) {
            return true;
        }
        return false;
    }

    void pprint() {
        this->pprint_state();
    }
};



int main() {

    cout<<"start"<<endl;
    
    
    int hero_win_num = 0;
    int boss_win_num = 0;
    int avg_depth = 0;
    srand((unsigned)time(0));     
    for (int epoch = 0; epoch < 1000; epoch ++) {
        legend_state* cur_state = new legend_state();  
        while (cur_state->is_over == false) {
            cur_state->pprint_state();
            cout<<cur_state->get_encoding()<<endl;
            cur_state = cur_state->gen_next_state();
            avg_depth += 1;
            //usleep(3 * 1000000);
        }
        cur_state->pprint_state();
        cout<<"leon' final hp"<<cur_state->leon->gamer->cur_hp<<endl<<endl<<endl;
        if (cur_state->leon->gamer->cur_hp <= 0) {
            hero_win_num += 1;
        } else {
            boss_win_num += 1;
        }
    }
    cout<<"hero_win: "<<hero_win_num<<" boss_win: "<<boss_win_num<<endl;
    cout<<"avg depth"<<(avg_depth / 1000)<<endl;


}

