#ifndef __PLAYER_H_
#define __PLAYER_H_

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
    bool is_dead;
    int encouraged;
    int shell;

    double get_base_hp();
    void set_base_hp();

    double get_base_ep();
    void set_base_ep();

    double get_base_sp();
    void set_base_sp();

    double get_base_atk();
    void set_base_atk();

    player(int hp, int ep, int sp, int atk);
};

#endif