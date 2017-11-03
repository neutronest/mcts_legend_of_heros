#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class state {

public:

    virtual state gen_next_state();

    virtual int get_state_limit();

    virtual int get_available_state_limit();

    virtual string get_encoding();

    virtual bool is_terminal();

    virtual double get_reward();
    


};