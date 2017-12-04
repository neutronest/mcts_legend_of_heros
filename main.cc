#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <ctime>
#include <unistd.h>

#include "state.h"
#include "player.h"
#include "skill.h"
#include "legend_state.h"
#include "legend_mcts.h"

using namespace std;


int main() {


        /*
        cout<<"start"<<endl;
        
        
        int hero_win_num = 0;
        int boss_win_num = 0;
        int avg_depth = 0;
        srand((unsigned)time(0));     
        for (int epoch = 0; epoch < 1000; epoch ++) {
            legend_state* cur_state = new legend_state();  
            while (cur_state->is_over == false) {
                cur_state->pprint_state();
                cout<<cur_state->get_encoding()<<endl;
                cur_state = cur_state->gen_next_state();
                avg_depth += 1;
                //usleep(3 * 1000000);
            }
            cur_state->pprint_state();
            cout<<"leon' final hp"<<cur_state->leon->gamer->cur_hp<<endl<<endl<<endl;
            if (cur_state->leon->gamer->cur_hp <= 0) {
                hero_win_num += 1;
            } else {
                boss_win_num += 1;
            }
        }
        cout<<"hero_win: "<<hero_win_num<<" boss_win: "<<boss_win_num<<endl;
        cout<<"avg depth"<<(avg_depth / 1000)<<endl;
        */
        legend_state* root_state = new legend_state();
        root_state->start();

        legend_mcts* root = new legend_mcts();
        root->q_value = 0.0;
        root->visit_times = 0;
        root->game_state = root_state;
        root->children = {};
        int epoches = 100;
        int computation_budge = 100;
    
        auto best_node = root;
        for (auto epoch=0; epoch < epoches; epoch++) {
            cout<<"epoch "<<epoch<<endl;
            
            best_node = best_node->main_search(computation_budge);
            cout<<"*** current best step: ";
            best_node->game_state->pprint();
            //cout<<"nullptr?"<<endl;
            if (best_node == nullptr) {
                cout<<"woc.."<<endl;
            }
            cout<<"hehe.."<<best_node->q_value<<endl;
            best_node->game_state->pprint();
        }
    
        return 1;
    
    }