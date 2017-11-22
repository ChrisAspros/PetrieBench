//
//  Logger.hpp
//  Egypt_pub_2grammars
//
//  Created by Christodoulos Aspromallis on 21/09/2017.
//
//

#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include "ofxMidiOut.h"


class Logger{
    
public:

    void setup();
    void update();
    
    void gather_all_elements();
  
    
    bool tracked_randomised; //0 for tracked 1 for randomised
    
    //tracking state
    bool room1;
    bool room2;
    vector<string> new_read;
    vector<string> previous_read;
    
    //transition stage
    bool transitioning;
    bool transition_entered;
    bool transition_complete;
    int curr_gr;
    int next_gr;
    
    //music decisions
    //rules - rewrites
    
    //?????
    //logger.curr_func_chunks = r_comp.curr_func_chunks;
    //logger.next_func_chunks = r_comp.next_func_chunks;

    
};


#endif /* Logger_hpp */
