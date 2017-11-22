//
//  Rule_comparer.hpp
//  Egypt_pub_2grammars
//
//  Created by Christodoulos Aspromallis on 22/08/2017.
//
//

#ifndef Rule_comparer_hpp
#define Rule_comparer_hpp

#include <stdio.h>

//class G_parser;

#include "Grammar_parser.h"

class Rule_comparer{
    
public:
    
    G_parser parser;
    
    bool transitioning;
    bool trans_complete;
    bool un_dist_found;
    int un_dist, curr_bar_undist;
    
    int curr_gr;
    int next_gr;
    
    void combine_rules(vector<int>& seq_t);//the main/central function of the class
    
    struct aug_sect_rule{//augmented sect rules
    
        string sect_name;
        G_parser::rule s_rule;
        int r_len;
        int score;
        string next_sect;//also indirect identifier between same "Sects" in different places..
        int position;//its position in the form..
    };
    
    vector<aug_sect_rule> aug_sect_rules;
    
    vector<G_parser::elem_ID> find_best_rule(vector<int>& seq_t);
    vector<G_parser::elem_ID> best_r;//needs to be global?
    
    //vector<G_parser::elem_ID> aux_cycle;
    
    //bool comb_set_up = 0;
    void setup_combination(vector<int>& seq_t);
    int get_distance_to_goal(vector<int>& seq_t);
    void rewrite_funcs();
    void rewrite_curr_gr_t_g();//till funcs
    void rewrite_next_all();//till funcs
    
    vector<vector<G_parser::elem_ID>> curr_func_chunks;
    vector<vector<G_parser::elem_ID>> next_func_chunks;
    
    void compare_t_g();
    void compare_hist();
    
    vector<vector<G_parser::elem_ID>> construct_lines(vector<vector<G_parser::elem_ID>> func_chunks, int gr_num, int length, int init_curr_bar);
    vector<vector<G_parser::elem_ID>> curr_func_lines;
    //vector<G_parser::elem_ID> curr_func_lines;
    vector<vector<G_parser::elem_ID>> next_func_lines;
    
    int dist;
    int thread;
    void get_goal_point();
    int g_p;
    int length_to_goal;//number of bars until goal
    
    void update_combination(vector<int>& seq_t);
    
    void initiate_aux_cycle();
    
    void project_curr_gr();//projects current (ending) grammar up to goal point
    void project_next_gr();//projects next (upcoming) grammar up to goal point
    
};

#endif /* Rule_comparer_hpp */
