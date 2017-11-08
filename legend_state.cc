#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#pragma once
#include "state.cc"
#include "player.cc"
#include "skill.cc"

using namespace std;


enum class legend_turn {E, J, L};

class gamer_status {

public:

    string name;
    player* gamer;
    vector<skill*> actions;
    vector<skill*> avaible_actions;
};

class legend_state : public state {

public:

    gamer_status* estelle;
    gamer_status* joshua;
    gamer_status* leon;
    legend_turn cur_turn;
    bool is_over;



    legend_state() {
        
        // init each players
        // estelle
        player* estelle_gamer = new player(2000.0, 200.0, 0.0, 200.0);
        vector<skill*> estelle_skills = {new normal_atk(), 
                                         new estelle_encourage(), 
                                         new estelle_heal_small(), 
                                         new estelle_heal_all(), 
                                         new estelle_shell_all()};
        estelle->name = "estelle";
        estelle->gamer = estelle_gamer;
        estelle->actions = estelle_skills;
        estelle->avaible_actions = {};
        
        // yoshua
        player* joshua_gamer = new player(1800.0, 0.0, 0.0, 300.0);
        vector<skill*> joshua_skills = {
            new normal_atk(),
            new joshua_double_atk(),
            new joshua_smove()
        };
        joshua->name = "joshua";
        joshua->gamer = joshua_gamer;
        joshua->actions = joshua_skills;
        joshua->avaible_actions = {};

        // leon
        player* leon_gamer = new player(20000.0, 0.0, 0.0, 500.0);
        leon->name = "leon";
        leon->gamer = leon_gamer;
        leon->actions = {
            new leon_shadow_atk(),
            new leon_ghostfire_atk(),
            new leon_buff(),
            new leon_deep_shell(),
            new leon_final_move()
        };
        leon->avaible_actions = {};
        cur_turn = legend_turn::E;
        is_over = false;
    }

    bool is_terminal(){

        if (this->estelle->gamer->cur_hp <= 0) {
            return true;
        }
        if (this->joshua->gamer->cur_hp <= 0) {
            return true;
        }
        if (this->leon->gamer->cur_hp <= 0) {
            return true;
        }
        return false;
    }

    void get_avaible_actions(gamer_status* cur_status) {
        cur_status->avaible_actions = {};
        for(auto iter = cur_status->actions.begin();
            iter != cur_status->actions.end();
            iter++) {
            auto p = *iter;
            if (p->is_avaible(cur_status->gamer) == true) {
                cur_status->avaible_actions.push_back(p);
            }
        }
        return;
    }

    void get_next_turn() {

        bool is_estelle_dead = this->estelle->gamer->cur_hp > 0 ? false : true;
        bool is_joshua_dead = this->joshua->gamer->cur_hp > 0 ? false : true;
        bool is_leon_dead = this->leon->gamer->cur_hp > 0 ? false : true;
        

        if (this->cur_turn == legend_turn::E) {

            if(is_joshua_dead == false) {
                this->cur_turn = legend_turn::J;
            } else if (is_leon_dead == false){
                this->cur_turn = legend_turn::L;
            }
        } else if (this->cur_turn == legend_turn::J) {
            if (is_leon_dead == false) {
                this->cur_turn = legend_turn::L;
            } // else means game win
        } else {
            // this->cur_turn == legend_turn::L
            if (is_estelle_dead == false) {
                this->cur_turn = legend_turn::E;
            } else if (is_joshua_dead == false) {
                this->cur_turn = legend_turn::J;
            } // else gamer over
        }

        
    }

    void print_status() {

        

    }

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
        this->get_avaible_actions(cur_status);
        int len_of_avaible_actions = cur_status->avaible_actions.size();
        int r = rand() % len_of_avaible_actions;
        cur_status->avaible_actions[r]->apply(cur_status->gamer, {});

        if (this->is_terminal()) {
            this->is_over = true;
        }

        this->get_next_turn();

        return nullptr;
    }

    bool simulate_default_policy() {

    }   



};

