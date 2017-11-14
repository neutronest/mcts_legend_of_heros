#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class state {

public:

    /*
    state() {
        cout<<"...hahaha\n";
        return;
    }

    virtual ~state() {

    }
    */

    virtual state* gen_next_state() = 0;
    virtual int get_state_limit() = 0;
    virtual int get_available_state_limit() = 0;
    virtual string get_encoding() = 0;
    virtual bool is_terminal() = 0;
    virtual double get_reward() = 0;
    virtual void pprint() = 0;
    virtual bool is_boss_turn() = 0;


    /*
    virtual state gen_next_state() const {

        state s;
        cout<<"warning: called get_next_state by the trait!\n";
        return s;
    }

    virtual int get_state_limit() {

        cout<<"warning: called get_state_limit by the trait!\n";
        return -1;    
    }

    virtual int get_available_state_limit() {
        cout<<"warning: called get_available_state_limit by the trait!\n";
        return -1;
        
    }

    virtual string get_encoding() {
        cout<<"warning: called get_encoding by the trait!\n";
        return "";
    }

    virtual bool is_terminal() {
        cout<<"warning: called is_terminal by the trait!\n";
        return false;
    }

    virtual double get_reward() {
        cout<<"warning: called get_reward by the trait!\n";
        return 0.0;
    }

    virtual void pprint()  {
        cout<<"warning: called pprint by the trait!\n";
        return;
    }
    */
};
