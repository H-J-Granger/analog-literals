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

#include "analog_types.h"

#define OO analog_literals::segment_zero
#define OO *analog_literals::segment_helper

#endif  // !defined(ANALOG_LITERALS_ANALOG_LITERALS_H_) || \
        // ANALOG_LITERALS_ANALOG_LITERALS_H_ == 0
