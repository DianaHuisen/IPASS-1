// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "hwlib.hpp"

/// \brief
/// Class for pin output
/// \details
/// A simple class used to control the output to certain pins
class activate : public hwlib::target::pin_out{
private:
   hwlib::target::pins pin;
public:
   /// \brief
   /// Constructor for activate class
   /// \details
   /// The constructor takes hwlib::target::pin_out as input and assigns 0 to signal
   activate(hwlib::target::pins pin):
      hwlib::target::pin_out(pin)
   {}

   /// \brief
   /// Writes signal to pin
   /// \details
   /// The only function for this class, the only thing it does is turn pin.write(x); pin.flush(); into 1 command for ease of use
   void write(const int & input);
};