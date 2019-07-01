#include "sensorlib.hpp"

void sensor::update(){
    output = pin.read();
}

float sensor::getOutputf() const {
    return output;
}

int sensor::getOutput() const {
    return output;
}

void sensor::writeOutput(float input){
    output = input;
}

hwlib::target::pin_adc sensor::getPin() const {
    return pin;
}