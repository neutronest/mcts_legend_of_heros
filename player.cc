#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

class player {
private:
    double base_hp;
    double base_ep; // or sp
    double base_sp;
    double base_atk;


    
public:
    double cur_hp;
    double cur_ep;
    double cur_sp;
    double cur_atk;
    int encouraged;
    int shell;

    double get_base_hp() {
        return this->base_hp;
    }
    void set_base_hp(double hp) {
        this->base_hp = hp;
        return;
    }

    double get_base_ep() {
        return this->base_ep;
    }
    void set_base_ep(double ep) {
        this->base_ep = ep;
        return;
    }

    double get_base_sp() {
        return this->base_sp;
    }
    void set_base_sp(double sp) {
        this->base_sp = sp;
        return;
    }

    double get_base_atk() {
        return this->base_atk;
    }

    void set_base_atk(double atk) {
        this->base_atk = atk;
        return;
    }
    
};
    