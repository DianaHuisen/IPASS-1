#include "pulse.hpp"

void pulse::update(){
    previous = getOutputf();
    writeOutput(getPin().read());
}

bool pulse::checkPulse(){
    // 4095 Is the magic number which the sensor returns when it senses a pulse
    // When a pulse is heard it takes a moment before the pulse ends, to avoid counting the same pulse twice
    // the function compares the current output what was previously measured
    update();
    if(getOutput() == 4095 && getOutputf() > previous){
        return true;
    }
    return false;
}

int pulse::getBPM(){
    return BPM;
}

void pulse::updateBPM(){
    // First timestamp
    int time1 = hwlib::now_us();
    // Wait until a pulse is heard 5 times
    for(int i = 0; i < 5; i++){
        while(!checkPulse()){

        }
    }
    // Second timestamp
    int time2 = hwlib::now_us();
    // Calculate difference and convert so seconds
    int time = (time2 - time1) / 1000000;
    // Timer output / 5 = Beats Per Second
    int BPS = time / 5;
    // Beats per second * 60 = Beats Per Minute (BPM)
    BPM = BPS * 60;
}