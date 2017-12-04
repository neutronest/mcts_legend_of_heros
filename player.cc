#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

#include "player.h"

using namespace std;

double player::get_base_hp() {
    return this->base_hp;
}

void player::set_base_hp(double hp) {
    this->base_hp = hp;
    return;
}

double player::get_base_ep() {
    return this->base_ep;
}
void player::set_base_ep(double ep) {
    this->base_ep = ep;
    return;
}

double player::get_base_sp() {
    return this->base_sp;
}
void player::set_base_sp(double sp) {
    this->base_sp = sp;
    return;
}

double player::get_base_atk() {
    return this->base_atk;
}

void player::set_base_atk(double atk) {
    this->base_atk = atk;
    return;
}

player::player(double hp, double ep, double sp, double atk) {
    this->set_base_hp(hp);
    this->set_base_ep(ep);
    this->set_base_sp(sp);
    this->set_base_atk(atk);
    this->cur_hp =  this->get_base_hp();
    this->cur_ep =  this->get_base_ep();
    this->cur_sp =  this->get_base_sp();
    this->cur_atk = this->get_base_atk();
    this->encouraged = 0;
    this->shell = 0;
    this->is_dead = false;
}

player* player::dcopy() {

    player* new_player = new player(0, 0, 0, 0);
    new_player->base_hp = this->base_hp;
    new_player->base_ep = this->base_ep;
    new_player->base_sp = this->base_sp;
    new_player->base_atk = this->base_atk;

    new_player->cur_hp = this->cur_hp;
    new_player->cur_ep = this->cur_ep;
    new_player->cur_sp = this->cur_sp;
    new_player->cur_atk = this->cur_atk;
    new_player->encouraged = this->encouraged;
    new_player->shell = this->shell;
    new_player->is_dead = this->is_dead;
    //cout<<"player'hp: "<<cur_hp<<endl;
    return new_player;
}
    