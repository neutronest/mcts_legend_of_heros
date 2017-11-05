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

    estelle_atk_skill() {
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

class estelle_encourage() : public skill {
public:
    estelle_encourage() {
        this->name = "estelle's encourage: mina, ga-ba-de-gu-da-sai-i-ne!!";
    }

    void apply(player* caster, vector<player*> players) {

        if (castter->cur_ep < 60) {
            cout<<"[WARNING... estelle_encouage has not enough ep]"<<endl;
            return;
        }

        for (auto iter = players.begin();
             iter != players.end();
             iter++) {
            auto player = *iter;
            player->encouraged = 3;
        }
        caster->cur_ep -= 60;
    }
};

class estelle_heal_small() : public skill {
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
        auto player = players[0];
        player->cur_hp = max(player->base_hp, player->cur_hp + 800);
        caster->ep -= 30;
    }
};

class estelle_heal_all() : public skill {

public:
    estelle_heal_all() {
        this->name = "estelle is using "

    }
}