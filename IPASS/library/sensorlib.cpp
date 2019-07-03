// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

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

void sensor::writeOutput(const float & input){
    output = input;
}

hwlib::target::pin_adc sensor::getPin() const {
    return pin;
}