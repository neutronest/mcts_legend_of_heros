#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <ctime>
#include <unistd.h>

#include "state.h"
#include "player.h"
#include "skill.h"
#include "legend_state.h"

using namespace std;

//////////
// action
//////////
action::action(player* caster_, vector<player*> target_, skill* motion_) {
    this->caster = caster_;
    this->target = target_;
    this->motion = motion_;
}

action* action::dcopy() {

    player* caster_ = this->caster->dcopy();
    vector<player*> target_ = {};
    for (auto iter = this->target.begin();
              iter != this->target.end();
              iter++) {

        auto p = *iter;
        target_.push_back(p->dcopy());
    }
    // skill shared!!!
    skill* motion_ = this->motion;
    
    action* new_action = new action(caster_, target_, motion_);
    return new_action;

}

///////////////////
//// gamer_status
///////////////////

gamer_status* gamer_status::dcopy() {


    gamer_status* new_status = new gamer_status();
    new_status->name = this->name;
    new_status->gamer = this->gamer->dcopy();
    new_status->actions = {};
    for (auto iter = this->actions.begin();
              iter != this->actions.end();
              iter++) {
                  
        auto action = *iter;
        new_status->actions.push_back(action->dcopy());          
    }
    new_status->available_actions = {};
    return new_status;
}


////////////////
// legend_state
////////////////

void legend_state::start() {

    player* estelle_gamer = new player(2000.0, 400.0, 0.0, 200.0);
    player* joshua_gamer = new player(1800.0, 0.0, 0.0, 300.0);
    player* leon_gamer = new player(20000.0, 0.0, 0.0, 500.0);
    this->init(estelle_gamer, joshua_gamer, leon_gamer, legend_turn::E);
    return;
}

void legend_state::init(player* estelle_gamer, player* joshua_gamer, player* leon_gamer, legend_turn turn) {
    
    // init each players
    //

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
    estelle->available_actions = {};
    // joshua
    vector<action*> joshua_actions = {
        new action(joshua_gamer, {leon_gamer}, new normal_atk()),
        new action(joshua_gamer, {leon_gamer}, new joshua_double_atk()),
        new action(joshua_gamer, {leon_gamer}, new joshua_smove())

    };
    joshua->name = "约修亚";
    joshua->gamer = joshua_gamer;
    joshua->actions = joshua_actions;
    joshua->available_actions = {};

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
    leon->available_actions = {};


    this->cur_turn = turn;
    auto cur_status = this->get_cur_status();
    this->set_available_actions(cur_status);

    is_over = false;
}

legend_state* legend_state::dcopy(){
    
    player* estelle_gamer = this->estelle->gamer->dcopy();
    player* joshua_gamer = this->joshua->gamer->dcopy();
    player* leon_gamer = this->leon->gamer->dcopy();
    legend_turn next_turn = this->get_next_turn();

    legend_state* next_state = new legend_state();
    next_state->init(estelle_gamer, joshua_gamer, leon_gamer, next_turn);
    return next_state;
       
}

bool legend_state::is_terminal(){

    if (this->estelle->gamer->is_dead && this->joshua->gamer->is_dead) {
        return true;
    }
    if (this->leon->gamer->is_dead) {
        return true;
    }
    return false;
}

void legend_state::set_available_actions(gamer_status* cur_status) {

    cur_status->available_actions = {};
    for(auto iter = cur_status->actions.begin();
        iter != cur_status->actions.end();
        iter++) {
        auto action_ = *iter;
        if (action_->motion->is_available(cur_status->gamer, action_->target) == true) {
            cur_status->available_actions.push_back(action_);
        }
    }
    if (cur_status->available_actions.size() == 0) {
        cout<<"[WARNING... Not Available acions found!!!!]"<<endl;
        action* bottom_action = new action(cur_status->gamer, {}, new bottom_move());
        cur_status->available_actions.push_back(bottom_action);
    }
    return;
}

gamer_status* legend_state::get_cur_status() {
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


int legend_state::get_available_state_limit() {
    
    gamer_status* cur_status = this->get_cur_status();
    return cur_status->available_actions.size();
}

legend_turn legend_state::get_next_turn() {

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
    return legend_turn::L;

    
}

void legend_state::check_alive() {
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



legend_state* legend_state::gen_next_state() {

    // TODO
    this->pprint_state();
    
    gamer_status* cur_status = this->get_cur_status();        
    if (cur_status->gamer->encouraged > 0) {
        cur_status->gamer->cur_atk = 1.5 * cur_status->gamer->get_base_atk();
        cur_status->gamer->encouraged -= 1;
    }
    cout<<cur_status->name<<"'s turn: "<<endl;
    int len_of_available_actions = cur_status->available_actions.size();
    int r = rand() % len_of_available_actions;
    action* cur_action = cur_status->available_actions[r];
    cur_action->motion->apply(cur_action->caster, cur_action->target);
    cout<<cur_status->name<<"使用了 "<<cur_action->motion->name<<" ..."<<endl;
    cout<<"----------"<<endl;
    
    this->check_alive();        
    if (this->is_terminal()) {
        this->is_over = true;
        cout<<"游戏结束!!!!"<<endl;
        return this;
    }

    legend_state* next_state = this->dcopy();        
    next_state->cur_turn = this->get_next_turn();
    next_state->set_available_actions(next_state->get_cur_status());
    return next_state;

}

bool legend_state::simulate_default_policy() {

    return false;
}   

int legend_state::get_state_limit() {
    return -1;
}

// encoding the state's information to string
// can distinguish diff state's by their encoding result
// encoding format:
//   E-HP2000|EP200|SP0|Sh1|En1|J-JP1800|EP0|SP200|Sh1|En1|L-...
string legend_state::get_gamer_encoding(player* gamer) {

    string hp = to_string(int(gamer->cur_hp));
    string ep = to_string(int(gamer->cur_ep));
    string sp = to_string(int(gamer->cur_sp));
    string sh = to_string(int(gamer->shell));
    string en = to_string(int(gamer->encouraged));
    string res = "";
    res = "HP" + hp + "|EP" + ep + "|SP" + sp + "|Sh" + sh + "|En" + en;
    return res;
}



string legend_state::get_encoding() {
    
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
double legend_state::get_reward() {
    return - abs(0 - this->leon->gamer->cur_hp);
}


bool legend_state::is_boss_turn() {
    if (this->cur_turn == legend_turn::L) {
        return true;
    }
    return false;
}

void legend_state::pprint() {
    this->pprint_state();
}

void legend_state::print_status() {
}


void legend_state::pprint_state() {
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
