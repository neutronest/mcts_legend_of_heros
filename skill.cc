#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#include "player.cc"

using namespace std;

class skill {

public:
    string name;
    virtual void apply(player* caster, vector<player*> players) = 0;
};


class normal_atk : public skill {

    normal_atk() {
        this->name = "normal atk.";
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
    }
};

class estelle_encourage: public skill {
public:
    estelle_encourage() {
        this->name = "estelle's encourage: mina, ga-ba-de-gu-da-sai-i-ne!!";
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
};

class estelle_heal_small: public skill {
public:
    estelle_heal_small() {
        this->name = "estelle is using small healing!";
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
};

class estelle_heal_all: public skill {

public:
    estelle_heal_all() {
        this->name = "estelle is using all healing!";
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
};

class estelle_shell_all : public skill {
public:
    estelle_shell_all() {
        this->name = "estelle is using shell all!";
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
};

///////////////////
// Joshua
//////////////////

class joshua_double_atk : public skill {
public:
    joshua_double_atk() {
        this->name = "joshua is using double atk!";
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
            p->cur_hp = fmin(0, p->cur_hp - 2 * caster->cur_atk);
            
        }
        // caster add sp back
        caster->cur_sp  = fmax(200, caster->cur_sp + 20);
        return;
    }
};

class joshua_smove : public skill {
public:
    joshua_smove() {
        this->name = "joshua is using S-move!";
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

};


//
class leon_shadow_atk : public skill {

public:
    leon_shadow_atk() {
        this->name = "leon is using shaodow atk";
    }

    void apply(player* caster, vector<player*> players) {

        if (players.size() != 1) {

            cout<<"leon_shadow_atk but target must be only one!"<<endl;
            return;
        }

        auto p = players[0];
        p->cur_hp = fmax(0, p->cur_hp - 1.6 * caster->cur_atk);
    }
};

class leon_ghostfire_atk : public skill {

public:
    leon_ghostfire_atk() {
        this->name = "leon is using ghostfire atk";
    }

    void apply(player* caster, vector<player*> players) {
        
        for (auto iter = players.begin();
             iter != players.end();
             iter++) {
            auto p = *iter;
            p->cur_hp = fmax(0, p->cur_hp - 0.8 * caster->cur_atk);
        }
    }
};


class leon_buff : public skill {

public:
    leon_buff() {
        this->name = "leon is using buff";
    }

    void apply(player* caster, vector<player*> players) {
        caster->encouraged = 3;
    }
};

class leon_deep_shell : public skill {

public:
    leon_deep_shell() {
        this->name = "leon is using deep shell";
    }

    void apply(player* caster, vector<player*> players){
        caster->shell = 2;
    }
};

class leon_final_move : public skill {
public:
    leon_final_move() {
        this->name = "leon is using final move!!";
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
};
