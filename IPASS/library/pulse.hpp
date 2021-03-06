// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef PULSE_HPP
#define PULSE_HPP

/// @file

#include "sensorlib.hpp"

/// \brief
/// A class for pulsesensors
/// \details
/// Contains not only the pin and output variables inherited from the sensor class but also the int previous and int BPM variables
/// Previous refers to the previously measured value in the pin and has no further use
/// BPM refers to heartBeats Per Minute
class pulse : public sensor{
private:
    float previous;
    int BPM;
public:
    /// \brief
    /// Constructor for the pulse subclass
    /// \details
    /// The constructor takes a hwlib::target::pin_adc as input and sets all other variables to 0
    pulse(hwlib::target::pin_adc pin):
        sensor(pin),
        previous(0),
        BPM(0)
    {}

    /// \brief
    /// Updates variables
    /// \details
    /// Updates float output and int previous
    void update() override;

    /// \brief
    /// Checks for pulse
    /// \details
    /// Checks whether theres currently a pulse or not
    bool checkPulse();

    /// \brief
    /// Returns BPM
    /// \details
    /// Returns BPM as an integer to be viewed by the user
    int getBPM() const ;

    /// \brief
    /// Calculates BPM
    /// \details
    /// Calculates BPM by measuring current time, waiting for 5 pulses, and measuring the time again
    /// Afterwards the difference in time is calculated between the 2 time measurements
    /// Lastly calculates the amount of pulses per second, does this times 60 and saves the BPM to int BPM
    void updateBPM();

    /// \brief
    /// Returns output as float
    /// \details
    /// Returns output as float to be used in further calculations
    float getOutputf() const override;

    /// \brief
    /// Returns output as float
    /// \details
    /// Returns output as int to be printed and viewed by the user
    int getOutput() const override;

    /// \brief
    /// Write something to output
    /// \details
    /// Writes a float to output
    void writeOutput(const float & input) override;

    /// \brief
    /// Returns pin
    /// \details
    /// Returns the pin connected to the sensor
    hwlib::target::pin_adc getPin() const override;
};

#endif