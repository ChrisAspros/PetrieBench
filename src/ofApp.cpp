//  ofApp.cpp

#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(false);//unlocks the refresh rate from my monitor sync//https://forum.openframeworks.cc/t/is-the-glfw-limit-the-framerate-at-60hz/17632

    //this is from the merged branch
    
    //ofSetWindowShape(575, 800);
    ofSetWindowPosition(1700, -300);//(708, 0);
    
    //run_ID = rand();;
    tracked_randomised = 0;//0 is tracked, is randomised 1
    
    //midiOut.openPort(0);
    
    //sleep(5);
    //ofSleepMillis(1000);//seems to make it a bit more stable?
    
    frame_sp1 = 40;
    frame_sp2 = 40;
    
    frame_sp = frame_sp1;
    
    ofSetFrameRate(frame_sp); // for egypt 40?// for blues was 60 // 1 frame : 1 tick

    //gr_pop must preceed blues.setup() in order to feed initiate_cycle() in blues.setup
    blues.seq.r_comp.parser.gr_pop = 0;
    blues.seq.r_comp.parser.gr_changed = 1;//true means it doesn't need to change now..
    blues.setup();
    
    //only to accept "b" (after gr1 - "a" non-pressed) or "a" (after gr2 - "b" non-pressed) and start from top
    play_gr1 = !blues.seq.r_comp.parser.gr_pop;
    show_gr1 = play_gr1;
    play_gr2 = blues.seq.r_comp.parser.gr_pop;
    show_gr2 = play_gr2;
    show_p_e_input = 1; //to show "GR_*" from start..
    
    show_trans = 0;
    
    OSC.setup();
    
    //ofSleepMillis(1000);
    
    //cout << "set up" << endl << endl << endl;
    
    openSans.load("/Users/christodoulosaspromallis/Documents/UCL/PhD_Y_3/OF/of_v0.9.8_osx_release/apps/myApps/PetrieBench/bin/data/open-sans/OpenSans-Regular.ttf", 19.5);
    
    //gr_pop
    
    
    //arrow shape
    arrow.addVertex(0, 0);
    arrow.addVertex(0, 23);
    arrow.addVertex(-8, 15);
    arrow.addVertex(0, 23);
    arrow.addVertex(8, 15);
    arrow.addVertex(0, 23);
}


void ofApp::update(){
    
    //if (!speed_done) update_speed();
    //update_speed();
    
    //sleep(10); //debug plays only 1 note with this in..(??)
    //ofSleepMillis();//??
    //seq.update();
    
    //stop blues updates when:
    //string s = curr_cycle[t[3]].name;
    //if (goal_reached && (s=="i" || s=="i6" || s=="i7")) break;

    blues.update();
    
    /*
    for (int i=0; i<blues.seq.r_comp.parser.all_gr.size(); i++){
        
        cout << "end_times " << i << ": ";
        for (int j=0; j<blues.seq.r_comp.parser.all_gr[i].end_times.size(); j++){
            
            cout << blues.seq.r_comp.parser.all_gr[i].end_times[j] << ", ";
        }
        cout << endl;
    }
     */
    
    if (!tracked_randomised){//0 is tracked, is randomised 1)
    
        /*
        tracking_repl_A_B();
        if(blues.seq.only_on("beat", blues.t)) ;OSC.update();
         */
    }
    else {
    
        //clock_input();
    }
    
    
    
    
    //updating OSC on every beat only (no more needed for now..)
    if(blues.seq.only_on("beat", blues.t)){
        
        //OSC.update();
        logger.update();
        blues.ending = OSC._ending;
        blues.goal_reached = OSC._goal_reached;
        
        //allowing to draw P(rediction) E(ngine) input indication
        if (blues.ending){ show_p_e_input = 1; show_recovery = 1; }
        if (blues.goal_reached) show_p_e_input = 1;
        
        //cout << "ending: " << ending << ", g_r: " << goal_reached << endl;
    }
    
    blues.seq.r_comp.parser.transitioning = transitioning;
    blues.seq.r_comp.trans_complete = trans_complete;
    
    //if (ofApp_is_stopped) blues.seq.stop_all_MIDI();
    
    /*
     # - For compensation - #
     getTimeNow(do this first)
     do actions
     work out how much time elapsed
     sleep for period - elapsed
     ---
     */
    
    //failed try to not alter the lib files..
    /*
    GLFWwindow* = w_p;
    glfwSetWindowCloseCallback(w_p, stop_all_midi_2());
    
    //glfwCreateWindow
     */
}

void ofApp::update_speed(){

    //control smoothness of speeding up / slowing down
    if (!(speeding_smoothener % 20)){
    
        if (speedup){
        
            frame_sp ++;
            ofSetFrameRate(frame_sp);
            if (frame_sp == frame_sp2) speedup = 0;
        }
        
        if (slowdown){
        
            frame_sp --;
            ofSetFrameRate(frame_sp);
            if (frame_sp == frame_sp1) slowdown = 0;
        }
        
        speeding_smoothener = 0;
    }
    
    speeding_smoothener++;
}

/*
 make last chord (if v7 and previous == "fin" be also "fin"
 a bit more of testing (all cases once at last..)
 backup (HDD, git, upload)
 connect with prediction engine
 make vid
 make pp
 rehearse
 */


void ofApp::draw(){

    //ofColor(0);
    ofBackground(0);
    
    
    //PREDICTION ENGINE STATE FRAME
    ofSetColor(255);
    openSans.drawString("PREDICTION ENGINE STATE:", ofGetWidth()/2 - 157, 30);
    ofSetColor(110);
    ofSetLineWidth(2.5);
    ofNoFill();
    ofDrawRectangle(140, 40, 300, 120);
    
    string p_e_input; //input from prediction engine
    
    if (show_p_e_input){
    
        //Draw transitioning & stages
        if (show_trans) {
            
            ofSetColor(0, 255, 0);
            string aux_str;
            aux_str = "TRANSITIONING stage: " + stage_num + "\n" + to_string(blues.seq.r_comp.dist);
            //openSans.drawString("TRANSITIONING stage: " + stage_num, 215, 130);
            openSans.drawString(aux_str, 200, 150);
        }
        
        //Draw abrupt transitions
        if (show_gr1) {
            
            ofSetColor(0, 255, 0);
            openSans.drawString("GR_1", 215, 110);
        }
        if (show_gr2) {
            
            ofSetColor(0, 255, 0);
            openSans.drawString("GR_2", 215, 110);
        }
        
        if (blues.ending) {
        
            ofSetColor(0, 255, 0);
            openSans.drawString("ENDING", 215, 110);
        }
        else if (show_recovery) {
            
            ofSetColor(255, 0, 0);
            openSans.drawString("RECOVERING", 215, 110);
        }
        if (blues.goal_reached) {
            
            ofSetColor(30, 144, 255);
            openSans.drawString("\n\nGOAL_REACHED", 215, 110);
        }
    
    }
    
     openSans.drawString(p_e_input, 215, 110);
    
    
    //CYCLE STATE FRAME
    ofSetColor(255);
    openSans.drawString("CYCLE STATE:", ofGetWidth()/2 - 80, 190);
    ofSetColor(110);
    ofSetLineWidth(2.5);
    ofNoFill();
    ofDrawRectangle(4, 200, 567, 540);
    
    
    //DRAW CYCLE STATES
    string chord_str;
    
    for (int i=0; i<blues.seq.r_comp.parser.all_gr[blues.seq.r_comp.parser.gr_pop].form_length; i++){
     
        chord_str = blues.seq.r_comp.parser.curr_cycle[i].name;
        
        bool last_cad_time;
        
        //coloured special non-terminals
        if (chord_str=="cad"){
            
            ofSetColor(0, 255, 0);
            last_cad_time = 1;
        }
        else if (chord_str=="rec") ofSetColor(255, 0, 0);
        else if (chord_str=="fin") ofSetColor(30, 144, 255);
        else ofSetColor(255);
        
        /*
        //show "fin" instead of v7 at end..
        if (blues.t[3]!=11 && chord_str == "v7" && i==11){// && last_cad_time && (blues.ending || blues.goal_reached) && blues.seq.r_comp.parser.cad_updated){
        
            chord_str = "fin";
            ofSetColor(30, 144, 255);
        }
         */
        
        for (int j=0; j<i/4; j++) chord_str = "\n\n" + chord_str;
        openSans.drawString(chord_str, ((i%4)+1)*135-95, 240);
    }
    
    
    //DRAW A B A C as form indicators
    ofSetColor(102, 102, 0);
    string barline;
    
    for (int i=0; i<4; i++){
        
        //barline = "|";
        if (i==0 || i==2) barline = "A";
        else if (i==1) barline = "B";
        else if (i==3) barline = "C";
        
        //for (int j=0; j<i/5; j++) barline = "\n\n" + barline;
        openSans.drawString (barline, 10, 240+i*138);//, ((i%5)+1)*135-130, 240);
    }
    
    
    //ARROW
    ofSetColor(255, 222, 0);
    ofSetLineWidth(2.5);
    
    //openSans.drawString(ofToString(blues.t[3]), 50, 50);
    
    ofPushMatrix();
    ofTranslate(49, 190);
    
    for (int j=0; j<blues.t[3]/4; j++) ofTranslate(0, 69);//pushing down every 4 chords
    ofTranslate(((blues.t[3]%4))*133, 0);//pushing right every chord
    
    arrow.draw();
    ofPopMatrix();
}


void ofApp::tracking_repl_A_B(){

    //abrupt grammar change UI
    if (OSC.room1) {
        
        if (play_gr2){
            
            blues.seq.r_comp.parser.gr_changed = !blues.seq.r_comp.parser.gr_changed;
            slowdown = 1;
        }
        
        //blues.seq.r_comp.parser.gr_pop = 0;
        show_gr1 = 1;
        show_gr2 = 0;
        play_gr1 = 1;
        play_gr2 = 0;
        
        show_p_e_input = 1;//to allow showing
    }
    if (OSC.room2) {
        
        if (play_gr1){
            
            blues.seq.r_comp.parser.gr_changed = !blues.seq.r_comp.parser.gr_changed;
            speedup = 1;
        }
        
        //blues.seq.r_comp.parser.gr_pop = 1;
        show_gr2 = 1;
        show_gr1 = 0;
        play_gr2 = 1;
        play_gr1 = 0;
        
        show_p_e_input = 1;
    }
}


void ofApp::keyPressed(int key){

    //transition and changes UI
    //transition
    
    if (key == 's' || key == 'S'){
    
        frame_sp ++;
        ofSetFrameRate(frame_sp);
    }
    
    if ((key == 't' || key == 'T') && !transitioning) {
        
        transitioning = 1;
        show_trans = 1;
        stage_num = "1";
        trans_stage = 1;
        
        blues.seq.r_comp.parser.comb_setup = 0;
        
        //blues.seq.r_comp.parser.gr_pop = 0;
        show_gr1 = 1;
        show_gr2 = 0;
        
        show_p_e_input = 1;//to allow showing
    }
    //stages (press 2 to 5 - 5 is end of transition..)
    if (key == '2' && (blues.seq.r_comp.parser.transitioning || show_trans)) stage_num = "2"; trans_stage = 2;
    if (key == '3' && (transitioning || show_trans)) stage_num = "3"; trans_stage = 3;
    if (key == '4' && (transitioning || show_trans)) stage_num = "4"; trans_stage = 4;
    if (key == '5' && (transitioning || show_trans)){
        
        transitioning = !transitioning;
        trans_complete = 1;
        stage_num = "0";
        trans_stage = 0;
        show_trans = 0;
    }
    
    
    //abrupt grammar change UI
    if (key == 'a' || key == 'A') {
        
        if (play_gr2){
            
            blues.seq.r_comp.parser.gr_changed = !blues.seq.r_comp.parser.gr_changed;
            slowdown = 1;
        }
        
        //blues.seq.r_comp.parser.gr_pop = 0;
        show_gr1 = 1;
        show_gr2 = 0;
        play_gr1 = 1;
        play_gr2 = 0;
        
        show_p_e_input = 1;//to allow showing
    }
    if (key == 'b' || key == 'B') {
        
        if (play_gr1){
        
            blues.seq.r_comp.parser.gr_changed = !blues.seq.r_comp.parser.gr_changed;
            speedup = 1;
        }
        
        //blues.seq.r_comp.parser.gr_pop = 1;
        show_gr2 = 1;
        show_gr1 = 0;
        play_gr2 = 1;
        play_gr1 = 0;
        
        show_p_e_input = 1;
    }
    
    if (key == 'e' || key == 'E') {
        
        blues.ending = 1;
        show_p_e_input = 1;
    }
    if (key == 'r' || key == 'R') {
     
        blues.ending = 0;
        show_recovery = 1;
    }
    if (key == 'g' || key == 'G'){
     
        blues.goal_reached = 1;
        show_p_e_input = 1;
    }
    if (key == 's' || key == 'S') blues.seq.stop_all_MIDI();
}


void ofApp::keyReleased(int key){

    if (key == 's' || key == 'S'){
    
        frame_sp = 50;
        ofSetFrameRate(frame_sp);
    }
}


void ofApp::pass_log_values(){

    //in a paper write what we want for this and the next study run
        //now bad transitions (unintelligent), next getter, intelligent
        //now repetitive (within a style?)
        //next 
    //che to buy these books - tell Dawn to buy..
    
    //in a questionnaire..!!
        //think evaluation write-up, what answers do we need for the questionnaire to be able to tell us..
    //this has 2 styles.. and transitions
        //how abrupt is it, and why??
        //on a scale 1 to 10 is this abrupt..
        //control orchestration
            //we watn the grammar to move from one to the other..
            //similarity of orchestrations..
        //melodic..
    //all of them find it repetitive but they don't see it as a bad thing
    //
    //to what extent is repetition part of a style!!!!
    //styles that are closely to each other...!!!
        //different but not so different.. so that we don't get as much abruptnes..
    //
    
    //check what a nice python log is..
    
    /*
    //clock (in logger)
        //how long does transition/recover take etc..
        //descritise time in some way..
            //assume
     
        start
        generate ID
            compare for uniqueness
            appear screen
            goes in questionnaiere
        get current time -> T (baseline time)
        start logging
            (use prepared logger class?)
        find difference between times.. current time - actual time etc..
        stop button
        commit the log.. (use 'touch' to say one psecific time..)
        have a button for deleting the log..
     
     
    keep MIDI file, AUDIO file, log file..
     
    //run_ID (in logger)
     
     
    //tracked VS randomised
    logger.tracked_randomised = tracked_randomised; //0 for tracked 1 for randomised
    
    //tracking state
    logger.room1 = OSC.room1;
    logger.room2 = OSC.room2;
    logger.new_read = OSC.new_read;
    logger.previous_read = OSC.previous_read;
    
    //transition stage
    logger.transitioning = transitioning;
    logger.transition_entered = transition_entered;
    logger.transition_complete = transition_complete;
    logger.curr_gr = r_comp.curr_gr;
    logger.next_gr = r_comp.next_gr;
    
    //music decisions
        //rules - rewrites
    
    logger.curr_func_chunks = r_comp.curr_func_chunks;
    logger.next_func_chunks = r_comp.next_func_chunks;
    
    //scores
    //choices (from current andnext gr)
    
    //context awareness
    
    //final cycle choices.. - states!!
     */
}


void ofApp::stop_all_midi_2(){
    
    cout << "stopping midi..!!" << endl;
}
