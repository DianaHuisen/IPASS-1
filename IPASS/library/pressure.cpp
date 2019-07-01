#include "pressure.hpp"

void pressure::update(){
    int temp = 0;
    for(int i = 0; i < 10; i++){
        temp += getPin().read();
    }
    temp = temp / 10;
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

int pressure::getVoltage(){
    return voltage;
}

int pressure::getAtmosphere(){
    return atmosphere;
}

int pressure::getTotalPressure(){
    return totalpressure;
}

int pressure::getPressureDiff(){
    return pressurediff;
}