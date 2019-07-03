// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include "library.hpp"
#include "activate.hpp"

int main(void){
   // Create variables which will be used later on to display systolic and dialostic pressures on oled screen
   auto scl = hwlib::target::pin_oc{hwlib::target::pins::scl};
   auto sda = hwlib::target::pin_oc{hwlib::target::pins::sda};
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   auto oled = hwlib::glcd_oled(i2c_bus, 0x3c);
   auto font = hwlib::font_default_8x8();
   auto display = hwlib::terminal_from(oled, font);

   // Set variables to which the relays for the motor and valve are connected, also close the valve and turn the motor off
   activate valve(hwlib::target::pin_out(hwlib::target::pins::d2));
   valve.write(1);
   activate motor(hwlib::target::pin_out(hwlib::target::pins::d3));
   motor.write(0);

   // Set variables to which the pulsesensor, pressuresensor and button are connected (the pulsesensor is broken and will not be used)
   pulse pulse(hwlib::target::pin_adc(hwlib::target::ad_pins::a2));
   auto button(hwlib::target::pin_in(hwlib::target::pins::d4));
   pressure pressure(hwlib::target::pin_adc(hwlib::target::ad_pins::a3));

   // Create variables in which the measured systolic and dialostic pressure will be stored
   int systolic = 0;
   int diastolic = 0;

   while(button.read()){}

   // Determine relative base pressure in atmosphere and base new measurements off off this one
   pressure.setBase();
   pressure.update();
   hwlib::cout << pressure.getOutput() << " - 365 =" << pressure.getOutput() - 365 << "\n";
   // Turn on motor to start pumping air
   motor.write(1);
   // Update measurements
   pressure.update();
   // Continue pumping air into the cuff until the sensor measures a pressure of 250 mmHg or higher and display measured data on pc
   while(pressure.getPressureDiff() < 250){
      pressure.update();
      hwlib::cout << "Signal: " << pressure.getOutput() << " Milli-Atmosphere: " << pressure.getAtmosphere() <<
       " Pressure: " << pressure.getPressureDiff() << "\n";
   }

   // Turn motor and valve off to allow air to leave cuff and to lower the pressure
   motor.write(0);
   valve.write(0);

   // Push button when bloodflow is heard again instead of relying on pulse sensor
   while(button.read()){}

   // This is what would have been used had the pulse sensor worked
   // while(!pulse.checkPulse()){
   //    valve.write(0);
   //    hwlib::cout << "Signal: " << pressure.getOutput() << " Pressure: " << pressure.getPressureDiff() << "\n";
   // }

   // Update pressure to match current measurements and save them to display systolic pressure later on and to view on pc
   pressure.update();
   hwlib::cout << "SYS Signal: " << pressure.getOutput() << " Pressure: " << pressure.getPressureDiff() << "\n";
   systolic = pressure.getPressureDiff();

   // Push button again when bloodflow isn't heard anymore instead of relying on the pulse sensor
   while(button.read()){}

   // This is again what would have been used had the pulse sensor worked
   // while(!pulse.checkPulse()){
   //    hwlib::cout << "Signal: " << pressure.getOutput() << " Pressure: " << pressure.getPressureDiff() << "\n";
   // }

   // Update pressure to match current measurements and save them to display diastolic pressure later on and to view on pc
   pressure.update();
   hwlib::cout << "DIA Signal: " << pressure.getOutput() << " Pressure: " << pressure.getPressureDiff() << "\n";
   diastolic = pressure.getPressureDiff();

   // Display systolic and diastolic pressure on oled screen
   display.clear();
   display.flush();
   display << "SYS: " << systolic << "\nDIA: " << diastolic;
   display.flush();
}
