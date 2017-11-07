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


class gamer_status {

public:

    string name;
    player* gamer;
    vector<skill*> actions;
    vector<skill*> aviable_actions;
};

class legend_state : public state {

public:

    gamer_status* estelle;
    gamer_status* joshua;
    gamer_status* leon;



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
        estelle->aviable_actions = {};
        
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
        joshua->aviable_actions = {};

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
        leon->aviable_actions = {};
    }

};

