/**
 * @file analog_literals_off.h
 * @author Kuriyama Mirai
 * @brief Undefines the macro of Analog Literals, allowing user to use O, I, and
 * L in their code. The user can include analog_literals.h again to redefine 
 * them.
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if defined(ANALOG_LITERALS_ANALOG_LITERALS_H_) && \
    ANALOG_LITERALS_ANALOG_LITERALS_H_ == 1

#undef ANALOG_LITERALS_ANALOG_LITERALS_H_
#define ANALOG_LITERALS_ANALOG_LITERALS_H_ 0

#undef O
#undef I
#undef L

#endif  // defined(ANALOG_LITERALS_ANALOG_LITERALS_H_) && \
        // ANALOG_LITERALS_ANALOG_LITERALS_H_ == 1
