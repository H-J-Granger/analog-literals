/**
 * @file analog_literals.h
 * @author Kuriyama Mirai
 * @brief The main entry of Analog Literals.
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if !defined(ANALOG_LITERALS_ANALOG_LITERALS_H_) || \
    ANALOG_LITERALS_ANALOG_LITERALS_H_ == 0

#ifdef ANALOG_LITERALS_ANALOG_LITERALS_H_
#undef ANALOG_LITERALS_ANALOG_LITERALS_H_
#endif
#define ANALOG_LITERALS_ANALOG_LITERALS_H_ 1

#if !defined(__cplusplus) || __cplusplus < 201103L
#error Analog Literals needs a C++ compiler with >=C++11 standard to run \
  properly.
#endif

#include "analog_types.h"

#define OO ANALOG_LITERALS_OO
#define O ANALOG_LITERALS_O

#define II ANALOG_LITERALS_II
#define I ANALOG_LITERALS_I

#endif  // !defined(ANALOG_LITERALS_ANALOG_LITERALS_H_) || \
        // ANALOG_LITERALS_ANALOG_LITERALS_H_ == 0
