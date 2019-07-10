// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "pressure.hpp"

void pressure::update(){
    // Calculates average over 10 measurements
    int temp = 0;
    for(int i = 0; i < 10; i++){
        temp += getPin().read();
    }
    temp = temp / 10;
    // Calculates and writes corresponding data to variables
    writeOutput(temp - base);
    voltage = getOutput() / 5.25;
    atmosphere = voltage / 70 * 1000;
    totalpressure = voltage / 70 * 760;
    pressurediff = totalpressure - 760;
}

void pressure::setBase(){
    update();
    base = getOutput() - 365;
}

int pressure::getVoltage() const {
    return voltage;
}

int pressure::getAtmosphere() const {
    return atmosphere;
}

int pressure::getTotalPressure() const {
    return totalpressure;
}

int pressure::getPressureDiff() const {
    return pressurediff;
}

float pressure::getOutputf() const {
    return output;
}

int pressure::getOutput() const {
    return output;
}

void pressure::writeOutput(const float & input){
    output = input;
}

hwlib::target::pin_adc pressure::getPin() const {
    return pin;
}