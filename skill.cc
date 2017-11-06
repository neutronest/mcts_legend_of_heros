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

class estelle_atk: public skill {
public:

    estelle_atk() {
        this->name = "estelle's normal attack."; 
    }

    void apply(player* caster, vector<player*> players) {
        
        if (players.size() != 1) {
            cout<<"[WARNING.. the players'num of es normal atk must be only one]"<<endl;
            return;
        }
        players[0]->cur_hp = min(0, players[0]->cur_hp-200);
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
        caster->cur_ep -= 60;
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
        p->cur_hp = max(p->get_base_hp(), p->cur_hp + 1200);
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
            p->cur_hp = max(p->get_base_hp(), p->cur_hp + 1500);
        }
        caster->cur_ep -= 60;
    }
};

class estelle_shell_all() : public skill {
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
        caster->cur_ep -= 80;
    }
};

///////////////////
// Joshua
//////////////////

class joshua_atk : public skill {
public:
    joshua_atk() {
        this->name = "josuha is using atk!";
    }
    void apply(player* caster, vector<player*> players) {
        
        for (auto iter = players.begin();
             iter != players.end();
             iter++) {
            
            auto p = *iter;
            p->cur_hp = min(0, p->cur_hp - 300);
        } 
    }
};

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
            cout<<"[WARNING... josuhua_double_atk but enemy must be only one]"<<endl;
            return;
        }
        auto p = players[0];
        p->cur_hp = min(0, p->cur_hp - 2 * caster->cur_atk);
        // caster add sp back
        caster->cur_sp  = max(200, caster->cur_sp + 20);
        return;
    }
};



