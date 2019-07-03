// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef SENSORLIB_HPP
#define SENSORLIB_HPP

/// @file

#include "hwlib.hpp"

/// \brief
/// Sensor class that connects a pin to a dataset
/// \details
/// The sensor class consists of a hwlib::target::pin_adc and an float
/// The data from the pin is stored in the float
class sensor{
private:
   hwlib::target::pin_adc pin;
   float output;
public:
   /// \brief
   /// Constructor for sensor class
   /// \details
   /// Takes an hwlib::target::pin_adc input and sets output to 0
   sensor(hwlib::target::pin_adc pin):
      pin(pin),
      output(0)
   {}

   /// \brief
   /// Updates output
   /// \details
   /// Reads input from the associated pin and writes it to output
   virtual void update();

   /// \brief
   /// Returns output as float
   /// \details
   /// Returns output as float to be used in further calculations
   float getOutputf() const;

   /// \brief
   /// Returns output as float
   /// \details
   /// Returns output as int to be printed and viewed by the user
   int getOutput() const;

   /// \brief
   /// Write something to output
   /// \details
   /// Writes a float to output
   void writeOutput(const float & input);

   /// \brief
   /// Returns pin
   /// \details
   /// Returns the pin connected to the sensor
   hwlib::target::pin_adc getPin() const;
};

#endif