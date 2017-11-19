#ifndef __SKILL_H_
#define __SKILL_H_

#include <string>
#include <vector>

#include "player.h"
using namespace std;



class skill {
public:
    string name;
    virtual void apply(player* caster, vector<player*> target) = 0;

    virtual bool is_available(player* caster, vector<player*> target) = 0;
};


class normal_atk : public skill {
public:
    normal_atk();

    void apply(player* caster, vector<player*> target);
    
    bool is_available(player* caster, vector<player*> target);
};

//estelle_heal_small
//estelle_heal_all
//estelle_shell_alls

class estelle_encourage : public skill {
public:

    estelle_encourage();

    void apply(player* caster, vector<player*> target);
    
    bool is_available(player* caster, vector<player*> target);
};


//joshua_double_atk
//joshua_smove


class estelle_heal_small : public skill{
public:
    estelle_heal_small();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);

};

class estelle_heal_all : public skill {
public:
    estelle_heal_all();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class estelle_shell_all : public skill {
public:
    estelle_shell_all();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class joshua_double_atk : public skill {
public:
    joshua_double_atk();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);

};

class joshua_smove : public skill {
public:
    joshua_smove();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

//leon_shadow_atk
//leon_ghostfire_atk
//leon_buff
//leon_deep_shell
//leon_final_move

class leon_shadow_atk : public skill {
public:
    leon_shadow_atk();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class leon_ghostfire_atk : public skill {
public:
    leon_ghostfire_atk();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class leon_buff : public skill {
public:
    leon_buff();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class leon_deep_shell : public skill {
public:
    leon_deep_shell();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};

class leon_final_move : public skill {
public:
    leon_final_move();
    void apply(player* caster, vector<player*> target);
    bool is_available(player* caster, vector<player*> target);
};


#endif
