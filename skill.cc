#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#include "skill.h"
#include "player.h"

using namespace std;



// bottom_move
bottom_move::bottom_move() {
    this->name = "什么也不干!";
}

void bottom_move::apply(player* caster, vector<player*> target) {

}

bool bottom_move::is_available(player* caster, vector<player*> target) {
    return true;
}

//normal_atk
normal_atk::normal_atk() {
    this->name = "普通攻击！";
}

void normal_atk::apply(player* caster, vector<player*> target) {

    if (target.size() != 1) {
        cout<<"[WARNING..normal atk must be only one]"<<endl;
        return;
    }
    
    auto p = target[0];
    if (p->shell > 0) {
        p->shell -= 1;
        return;
    }
    p->cur_hp = fmax(0, p->cur_hp - caster->cur_atk);
    caster->cur_sp = fmin(200, caster->cur_sp+10);
}

bool normal_atk::is_available(player* caster, vector<player*> target) {
    auto p = target[0];
    if (p->is_dead == true) {
        return false;
    }
    return true;
}

estelle_encourage::estelle_encourage() {
    this->name = "大家加油啊！";
}

void estelle_encourage::apply(player* caster, vector<player*> target) {

    if (caster->cur_ep < 60) {
        cout<<"[WARNING... estelle_encouage has not enough ep]"<<endl;
        return;
    }

    for (auto iter = target.begin();
         iter != target.end();
         iter++) {
        auto p = *iter;
        p->encouraged = 3;
    }
    caster->cur_ep = fmax(0, caster->cur_ep - 60);
}


bool estelle_encourage::is_available(player* caster, vector<player*> target) {
    if (caster->cur_ep < 60) {
        return false;
    }
    return true;
}

estelle_heal_small::estelle_heal_small() {
    this->name = "小回复！";
}

void estelle_heal_small::apply(player* caster, vector<player*> target) {
    if (target.size() != 1) {
        cout<<"[WARNING.. the target'num of es's heal small must be only one]"<<endl;
        return;
    }
    if (caster->cur_ep < 30) {
        cout<<"[WARNING..estelle_heal_small but ep < 30]"<<endl;
        return;
    }
    player* p = target[0];
    p->cur_hp = fmin(p->get_base_hp(), p->cur_hp + 1200);
    caster->cur_ep -= 30;
}


bool estelle_heal_small::is_available(player* caster, vector<player*> target) {
    if (caster->cur_ep < 30 || target[0]->is_dead == true) {
        return false;
    }
    return true;
}

// estelle_heal_all
estelle_heal_all::estelle_heal_all() {
    this->name = "风之愈！";
}

void estelle_heal_all::apply(player* caster, vector<player*> target)  {

    if (caster->cur_ep < 60) {
        cout<<"[WARNING..estelle_heal_all but ep < 60]"<<endl;
        return;
    }

    for(auto iter = target.begin();
        iter != target.end();
        iter++) {
        auto p = *iter;
        p->cur_hp = fmin(p->get_base_hp(), p->cur_hp + 1500);
    }
    caster->cur_ep -= 60;
}


bool estelle_heal_all::is_available(player* caster, vector<player*> target) {
    if (caster->cur_ep < 60) {
        return false;
    }
    return true;
}


// estelle_shell_all
estelle_shell_all::estelle_shell_all() {
    this->name = "大地之墙！";
}

void estelle_shell_all::apply(player* caster, vector<player*> target) {

    if (caster->cur_ep < 80) {
        cout<<"[WARNING... estelle_shell_all but ep < 80]"<<endl;
    }

    for(auto iter = target.begin();
        iter != target.end();
        iter++) {
        auto p = *iter;
        p->shell = 1;
    }
    caster->cur_ep = fmax(0, caster->cur_ep - 80);
}


bool estelle_shell_all::is_available(player* caster, vector<player*> target) {
    if (caster->cur_ep < 80) {
        return false;
    }
    return true;
}
///////////////////
// Joshua
//////////////////
joshua_double_atk::joshua_double_atk() {
    this->name = "双连击！";
}

void joshua_double_atk::apply(player* caster, vector<player*> target) {
    if (caster->cur_sp < 30) {
        cout<<"[WARNING... joshua_double_atk but sp < 30]"<<endl;
        return;
    }

    if (target.size() != 1) {
        cout<<"[WARNING... joshua_double_atk but enemy must be only one]"<<endl;
        return;
    }
    auto p = target[0];

    if (p->shell > 0) {
        p->shell -= 1;
    } else {
        p->cur_hp = fmax(0, p->cur_hp - 2 * caster->cur_atk);
        
    }
    // caster add sp back
    caster->cur_sp = fmax(0, caster->cur_sp - 30);
    caster->cur_sp  = fmin(200, caster->cur_sp + 20);
    return;
}


bool joshua_double_atk::is_available(player* caster, vector<player*> target) {

    if (caster->cur_sp < 30) {
        return false;
    }
    return true;
}

////////////////
/// joshua_smove
/////////////////
joshua_smove::joshua_smove() {
    this->name = "秘技-幻影奇袭！";
}

void joshua_smove::apply(player* caster, vector<player*> target) {

    if (caster->cur_sp < 100) {
        cout<<"[WARNING... joshua_smove but sp must >= 100]"<<endl;
    }

    for (auto iter = target.begin();
         iter != target.end();
         iter++) {
        auto p = *iter;
        if (p->shell > 0) {
            p->shell -= 1;
        } else {
            p->cur_hp = fmax(0, p->cur_hp - 8 * caster->cur_atk);
            
        }
    }
    caster->cur_sp = 30;
    return;
}


bool joshua_smove::is_available(player* caster, vector<player*> target) {
    
    if (caster->cur_sp < 100) {
        return false;
    }
    return true;
}


///////////////////
// leon_shadow_atk
//////////////////
leon_shadow_atk::leon_shadow_atk() {
    this->name = "暗影剑！";
}

void leon_shadow_atk::apply(player* caster, vector<player*> target) {

    if (target.size() != 1) {

        cout<<"leon_shadow_atk but target must be only one!"<<endl;
        return;
    }

    auto p = target[0];
    p->cur_hp = fmax(0, p->cur_hp - 1.6 * caster->cur_atk);
}


bool leon_shadow_atk::is_available(player* caster, vector<player*> target) {
    if (target[0]->is_dead == true) {
        return false;
    }
    return true;
}

/////////////////////
// leon_ghostfire_atk
//////////////////////
leon_ghostfire_atk::leon_ghostfire_atk() {
    this->name = "鬼炎斩！";
}

void leon_ghostfire_atk::apply(player* caster, vector<player*> target) {
    
    for (auto iter = target.begin();
         iter != target.end();
         iter++) {
        auto p = *iter;
        p->cur_hp = fmax(0, p->cur_hp - 0.8 * caster->cur_atk);
    }
}


bool leon_ghostfire_atk::is_available(player* caster, vector<player*> target) {
    return true;
}

///////////
// leon_buff
////////////
leon_buff::leon_buff() {
    this->name = "修罗之怒！";
}

void leon_buff::apply(player* caster, vector<player*> target) {
    caster->encouraged = 3;
}


bool leon_buff::is_available(player* caster, vector<player*> target) {
    return true;
}

leon_deep_shell::leon_deep_shell() {
    this->name = "大地之障·改";
}

void leon_deep_shell::apply(player* caster, vector<player*> target){
    caster->shell = 2;
}


bool leon_deep_shell::is_available(player* caster, vector<player*> target) {
    return true;
}

leon_final_move::leon_final_move() {
    this->name = "S-冥皇击！";
}

void leon_final_move::apply(player* caster, vector<player*> target) {

    for (auto iter = target.begin();
         iter != target.end();
         iter++) {
        
        auto p = *iter;
        if (p->shell > 0) {
            p->shell -= 1;
        } else {
            p->cur_hp = fmax(0, p->cur_hp - 2.4 * caster->cur_atk);
        }
    }
    return;
}


bool leon_final_move::is_available(player* caster, vector<player*> target) {
    return true;
}
