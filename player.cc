#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#include "skill.cc"

using namespace std;

class player {
private:
    int base_hp;
    int base_ep; // or sp
    int base_sp;

    vector<skill*> skills = {};
    
public:
    int cur_hp;
    int cur_ep;
    int cur_sp;
    int cur_atk;
    int encouraged;

    int get_base_hp() {
        return this->base_hp;
    }
    void set_base_hp(int hp) {
        this->base_hp = hp;
        return;
    }

    int get_base_ep() {
        return this->base_ep;
    }
    void set_base_ep(int ep) {
        this->base_ep = ep;
        return;
    }

    int get_base_sp() {
        return this->base_sp;
    }
    void set_base_sp(int sp) {
        this->base_sp = sp;
    }

    vector<skill*> get_skills() {
        return this->skills;
    }
    
    void set_skills(vector<skill*> skills) {
        this->skills = skills;
    }

    
};
    