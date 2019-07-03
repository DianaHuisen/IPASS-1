#ifndef PRESSURE_HPP
#define PRESSURE_HPP

/// @file

#include "sensorlib.hpp"

/// \brief
/// A class for pressuresensors
/// \details
/// A subclass of the class sensor named pressure, this subclass is designed to be used solely for pressure sensors
/// The data recieved from the pin is initially stored in the same output variable as the sensor class,
/// but is later also converted to other usefull data: the voltage (in mV), measured atmosphere (in mAtm),
/// 2 versions of the measured pressure (in mmHg) and a float base on which future measurements and calculations are based
class pressure : public sensor{
private:
    float voltage;
    float atmosphere;
    float totalpressure;
    float pressurediff;
public:
    int base;
   /// \brief
   /// Constructor for the pressure subclass
   /// \details
   /// The contructor takes a hwlib::target::pin_adc input and sets all other values to 0
    pressure(hwlib::target::pin_adc pin):
        sensor(pin),
        voltage(0),
        atmosphere(0),
        totalpressure(0),
        pressurediff(0),
        base(0)
    {}

    /// \brief
    /// Updates variables
    /// \details
    /// Reads the input from the pin 10 times and stores the average in output
    /// Afterwards converts output with the help of float base into the other desired variables:
    /// voltage, output / 5.25 (in mV);
    /// atmosphere, voltage / 70 * 1000 (in mAtm);
    /// totalpressure, voltage / 70 * 760 (in mmHg);
    /// pressurediff, totalpressure - 760 (in mmHg);
    /// The difference between totalpressure and pressurediff is that totalpressure is the total of the measured pressure
    /// including the basic pressure of 760mmHg which is everywhere, presurediff is the difference between the regular pressure
    /// and the measured pressure and also the pressure people look at when talking about bloodpressure
    void update() override;

    /// \brief
    /// Defines base pressure
    /// \details
    /// Measures the outside pressure and saves it to float base, this is used in update() to calculate
    /// differences between standard outside pressure and present outside pressure to avoid any measuring errors this would normally cause
    void setBase();

    /// \brief
    /// Returns voltage in mV
    /// \details
    /// Returns the voltage calculated in update() as an integer so it can be viewed by users
    int getVoltage();

    /// \brief
    /// Returns atmosphere in mAtm
    /// \details
    /// Returns the atmosphere calculated in update() as an integer so it can be viewed by users
    int getAtmosphere();

    /// \brief
    /// Returns total measured pressure
    /// \details
    /// Returns the pressure calculated in update() as an integer so it can be viewed by users
    int getTotalPressure();

    /// \brief
    /// Returns the pressure difference
    /// \details
    /// Returns the pressure difference between the outside pressure and pressure in the cuff
    /// calculated in update() as an integer so it can be viewed by users
    int getPressureDiff();
};

#endif