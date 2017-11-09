#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#pragma once
#include "player.cc"

using namespace std;




class skill {

public:
    string name;

    virtual void apply(player* caster, vector<player*> players) = 0;

    virtual bool is_avaible(player* caster) = 0;
};


class normal_atk : public skill {
public:
    normal_atk() {
        this->name = "普通攻击！";
    }

    void apply(player* caster, vector<player*> players) {

        if (players.size() != 1) {
            cout<<"[WARNING..normal atk must be only one]"<<endl;
            return;
        }
        
        auto p = players[0];
        if (p->shell > 0) {
            p->shell -= 1;
            return;
        }
        p->cur_hp = fmax(0, p->cur_hp - caster->cur_atk);
        caster->cur_sp = fmin(200, caster->cur_sp+10);
    }

    bool is_avaible(player* caster) {
        return true;
    }
};

class estelle_encourage: public skill {
public:
    estelle_encourage() {
        this->name = "大家加油啊！";
    }

    void apply(player* caster, vector<player*> players) {

        if (caster->cur_ep < 60) {
            cout<<"[WARNING... estelle_encouage has not enough ep]"<<endl;
            return;
        }

        for (auto iter = players.begin();
             iter != players.end();
             iter++) {
            auto p = *iter;
            p->encouraged = 3;
        }
        caster->cur_ep = fmax(0, caster->cur_ep - 60);
    }


    bool is_avaible(player* caster) {
        if (caster->cur_ep < 60) {
            return false;
        }
        return true;
    }
};

class estelle_heal_small: public skill {
public:
    estelle_heal_small() {
        this->name = "小回复！";
    }

    void apply(player* caster, vector<player*> players) {
        if (players.size() != 1) {
            cout<<"[WARNING.. the players'num of es's heal small must be only one]"<<endl;
            return;
        }
        if (caster->cur_ep < 30) {
            cout<<"[WARNING..estelle_heal_small but ep < 30]"<<endl;
            return;
        }
        player* p = players[0];
        p->cur_hp = fmin(p->get_base_hp(), p->cur_hp + 1200);
        caster->cur_ep -= 30;
    }

    
    bool is_avaible(player* caster) {
        if (caster->cur_ep < 30) {
            return false;
        }
        return true;
    }
};

class estelle_heal_all: public skill {

public:
    estelle_heal_all() {
        this->name = "风之愈！";
    }

    void apply(player* caster, vector<player*> players)  {

        if (caster->cur_ep < 60) {
            cout<<"[WARNING..estelle_heal_all but ep < 60]"<<endl;
            return;
        }

        for(auto iter = players.begin();
            iter != players.end();
            iter++) {
            auto p = *iter;
            p->cur_hp = fmax(p->get_base_hp(), p->cur_hp + 1500);
        }
        caster->cur_ep -= 60;
    }


    bool is_avaible(player* caster) {
        if (caster->cur_ep < 60) {
            return false;
        }
        return true;
    }
};

class estelle_shell_all : public skill {
public:
    estelle_shell_all() {
        this->name = "大地之墙！";
    }

    void apply(player* caster, vector<player*> players) {

        if (caster->cur_ep < 80) {
            cout<<"[WARNING... estelle_shell_all but ep < 80]"<<endl;
        }

        for(auto iter = players.begin();
            iter != players.end();
            iter++) {
            auto p = *iter;
            p->shell = 1;
        }
        caster->cur_ep = fmax(0, caster->cur_ep - 80);
    }


    bool is_avaible(player* caster) {
        if (caster->cur_ep < 80) {
            return false;
        }
        return true;
    }
};

///////////////////
// Joshua
//////////////////

class joshua_double_atk : public skill {
public:
    joshua_double_atk() {
        this->name = "双连击！";
    }

    void apply(player* caster, vector<player*> players) {
        if (caster->cur_sp < 30) {
            cout<<"[WARNING... joshua_double_atk but sp < 30]"<<endl;
            return;
        }

        if (players.size() != 1) {
            cout<<"[WARNING... joshua_double_atk but enemy must be only one]"<<endl;
            return;
        }
        auto p = players[0];

        if (p->shell > 0) {
            p->shell -= 1;
        } else {
            p->cur_hp = fmax(0, p->cur_hp - 2 * caster->cur_atk);
            
        }
        // caster add sp back
        caster->cur_sp  = fmin(200, caster->cur_sp + 20);
        return;
    }


    bool is_avaible(player* caster) {

        if (caster->cur_sp < 30) {
            return false;
        }
        return true;
    }
};

class joshua_smove : public skill {
public:
    joshua_smove() {
        this->name = "秘技-幻影奇袭！";
    }

    void apply(player* caster, vector<player*> players) {

        if (caster->cur_sp < 100) {
            cout<<"[WARNING... joshua_smove but sp must >= 100]"<<endl;
        }

        for (auto iter = players.begin();
             iter != players.end();
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


    bool is_avaible(player* caster) {
        
        if (caster->cur_sp < 100) {
            return false;
        }
        return true;
    }
};


//
class leon_shadow_atk : public skill {

public:
    leon_shadow_atk() {
        this->name = "暗影剑！";
    }

    void apply(player* caster, vector<player*> players) {

        if (players.size() != 1) {

            cout<<"leon_shadow_atk but target must be only one!"<<endl;
            return;
        }

        auto p = players[0];
        p->cur_hp = fmax(0, p->cur_hp - 1.6 * caster->cur_atk);
    }


    bool is_avaible(player* caster) {
        return true;
    }
};

class leon_ghostfire_atk : public skill {

public:
    leon_ghostfire_atk() {
        this->name = "鬼炎斩！";
    }

    void apply(player* caster, vector<player*> players) {
        
        for (auto iter = players.begin();
             iter != players.end();
             iter++) {
            auto p = *iter;
            p->cur_hp = fmax(0, p->cur_hp - 0.8 * caster->cur_atk);
        }
    }


    bool is_avaible(player* caster) {
        return true;
    }
};


class leon_buff : public skill {

public:
    leon_buff() {
        this->name = "修罗之怒！";
    }

    void apply(player* caster, vector<player*> players) {
        caster->encouraged = 3;
    }


    bool is_avaible(player* caster) {
        return true;
    }
};

class leon_deep_shell : public skill {

public:
    leon_deep_shell() {
        this->name = "大地之障·改";
    }

    void apply(player* caster, vector<player*> players){
        caster->shell = 2;
    }


    bool is_avaible(player* caster) {
        return true;
    }
};

class leon_final_move : public skill {
public:
    leon_final_move() {
        this->name = "S-冥皇击！";
    }

    void apply(player* caster, vector<player*> players) {

        for (auto iter = players.begin();
             iter != players.end();
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


    bool is_avaible(player* caster) {
        return true;
    }
};
