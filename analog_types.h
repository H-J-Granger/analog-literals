/**
 * @file analog_types.h
 * @author Kuriyama Mirai
 * @brief 
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ANALOG_LITERALS_ANALOG_TYPES_H_
#define ANALOG_LITERALS_ANALOG_TYPES_H_

namespace analog_literals {

#define ALITERAL_DEBUG

class segment {
#ifdef ALITERAL_DEBUG
 public:
#else
 private:
#endif
  int decrement_count;

 public:
  int length;

  constexpr segment(int length_ = 0, int decrement_count_ = 0) noexcept
      : length(length_), decrement_count(decrement_count_) {}

  constexpr operator int() const noexcept {
    return this->length;
  }

  constexpr segment operator*() const noexcept {
    return *this;
  }
  constexpr segment operator--(int x) const noexcept {
    return segment(this->length, this->decrement_count + 1);
  }
  constexpr segment operator*(segment x) const noexcept {
    // When performing ((*a)-- -- -- ...) * a, returning 2*n, where n is the
    // number of --.
    return segment(this->decrement_count * 2);
  }
  constexpr segment operator-(segment x) const noexcept {
    // When performing ((*a)-- -- -- ...) - (*a), returning 2*n+1, where n is
    // the number of --.
    return segment(this->decrement_count * 2 + 1);
  }
};

constexpr segment segment_zero = segment(0);
constexpr segment segment_helper = segment(0);

}  // namespace analog_literals

#endif  // #ifndef ANALOG_LITERALS_ANALOG_TYPES_H_