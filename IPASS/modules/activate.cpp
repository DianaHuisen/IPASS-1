// Copyright Daniel van Eijk-Bos 2019-2021
// Distributed under the Boost Software License, Version 1.0
// (See accompanying file license.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

/// @file

#include "activate.hpp"

void activate::write(const int & input){
    pin.write(input);
    pin.flush();
}