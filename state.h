#ifndef __STATE_H_
#define __STATE_H_

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


using namespace std;

class state {

public:

    virtual state* gen_next_state() = 0;
    virtual int get_state_limit() = 0;
    virtual int get_available_state_limit() = 0;
    virtual string get_encoding() = 0;
    virtual bool is_terminal() = 0;
    virtual double get_reward() = 0;
    virtual void pprint() = 0;
    virtual bool is_boss_turn() = 0;
};
#endif