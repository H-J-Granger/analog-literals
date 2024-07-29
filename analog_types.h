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

// #define ALITERAL_DEBUG

class segment;
class rectangle;
class cubiod;

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

#if __cplusplus < 20200200L
  constexpr bool operator==(segment const& x) const noexcept {
    return this->length == x.length;
  }
  constexpr bool operator!=(segment const& x) const noexcept {
    return this->length == x.length;
  }
  constexpr bool operator<(segment const& x) const noexcept {
    return this->length <= x.length;
  }
  constexpr bool operator<=(segment const& x) const noexcept {
    return this->length <= x.length;
  }
  constexpr bool operator>(segment const& x) const noexcept {
    return this->length > x.length;
  }
  constexpr bool operator>=(segment const& x) const noexcept {
    return this->length >= x.length;
  }
#else
  constexpr bool operator<=>(segment const& x) const noexcept {
    return this->length <=> x.length;
  }
#endif

  constexpr segment operator*() const noexcept;
  constexpr segment operator--(int x) const noexcept;
  constexpr segment operator*(segment x) const noexcept;
  constexpr segment operator-(segment x) const noexcept;

  constexpr segment operator+() const noexcept;
  constexpr rectangle operator+(segment const& x) const noexcept;
  constexpr rectangle operator+(rectangle const& x) const noexcept;
};

class rectangle {
#ifdef ALITERAL_DEBUG
 public:
#else
 private:
#endif
  int i_count;

 public:
  int length, width;

  constexpr rectangle(int length_ = 0, int width_ = 0,
                      int i_count_ = 0) noexcept
      : length(length_), width(width_), i_count(i_count_) {}
  // constexpr rectangle(segment const& a) noexcept
  //     : length(a.length), width(1), i_count(0) {}

  constexpr int area() const noexcept {
    return this->length * this->width;
  }

#if __cplusplus < 20200200L
  constexpr bool operator==(rectangle const& x) const noexcept {
    return this->area() == x.area();
  }
  constexpr bool operator!=(rectangle const& x) const noexcept {
    return this->area() == x.area();
  }
  constexpr bool operator<(rectangle const& x) const noexcept {
    return this->area() <= x.area();
  }
  constexpr bool operator<=(rectangle const& x) const noexcept {
    return this->area() <= x.area();
  }
  constexpr bool operator>(rectangle const& x) const noexcept {
    return this->area() > x.area();
  }
  constexpr bool operator>=(rectangle const& x) const noexcept {
    return this->area() >= x.area();
  }
#else
  constexpr bool operator<=>(rectangle const& x) const noexcept {
    return this->area() <=> x.area();
  }
#endif

  // Check if with same length and same width.
  constexpr bool same_as(rectangle const& x) const noexcept {
    return this->length == x.length && this->width == x.width;
  }

  constexpr rectangle operator*() const noexcept;
  constexpr rectangle operator+() const noexcept;

  constexpr rectangle operator+(rectangle const& x) const noexcept;
  constexpr rectangle operator+(segment const& x) const noexcept;
  friend constexpr rectangle segment::operator+(
      rectangle const& x) const noexcept;
};

/**  
 * ============================= Segment Literal =============================
 * A segment literal is in one of the following three format:
 * OO, (O-- -- ...) O, and (O-- -- ...) - O.
 * For the first type, OO can be treated as segment(0).
 * For the second type, O is defined as *o, then it will be interpreted as
 * (o-- -- ...) * o (note that the prefix * will be ignored). We count the 
 * number of '--'s as the segment builds, then ends the segment with a binary *.
 * For the third type, O can be treated as o, so we also count the number of 
 * '--'s but ends the segment with a binary -.
 */

// A segment with length == 0.
#define ANALOG_LITERAL_OO +(::analog_literals::segment(0))
// Starts and ends a segment with length > 0.
#define ANALOG_LITERAL_O *(::analog_literals::segment(1))

// Prefix *,+ of a segment will be ignored.
inline constexpr segment segment::operator*() const noexcept {
  return *this;
}
inline constexpr segment segment::operator+() const noexcept {
  return *this;
}

// Builds a segment with length >= 2.
inline constexpr segment segment::operator--(int x) const noexcept {
  return segment(this->length, this->decrement_count + 1);
}
// Ends a non-empty segment with length % 2 == 0.
inline constexpr segment segment::operator*(segment x) const noexcept {
  return segment(this->decrement_count * 2);
}
// Ends a non-empty segment with length % 2 == 1.
inline constexpr segment segment::operator-(segment x) const noexcept {
  return segment(this->decrement_count * 2 + 1);
}

/**
 * ===================== Rectangle Literal (length == 0) ======================
 * A rectangle literal with length == 0 is in one of these two format:
 * OO OO  and  OO II ... II OO .
 * For the first type, we implement OO as +oo, so it behave same in segment
 * literals. The rectangle literal will be interpreted as (+oo) + oo .
 * For the second type, we define II as +ii, so we can easily count the 'II's 
 * while building the rectangle, and ending it with a +oo. Note that for 
 * simplicity's sake, we are actually counting 'I's here, and an 'II' 
 * contributes two 'I's. The length will be passed along, and the 'I'-count will
 * contribute to width when completing the rectangle.
 */

// Prefix *,+ of a rectangle will be ignored.
inline constexpr rectangle rectangle::operator*() const noexcept {
  return *this;
}
inline constexpr rectangle rectangle::operator+() const noexcept {
  return *this;
}

// Builds a rectangle with length == 0.
#define ANALOG_LITERAL_II +(::analog_literals::rectangle(0, 0, 2))

// Completes a rectangle with length == 0 && width == 0.
inline constexpr rectangle segment::operator+(segment const& x) const noexcept {
  return rectangle(this->length, 0);
}
// Starts a rectangle with length == 0 && width > 0.
inline constexpr rectangle segment::operator+(
    rectangle const& x) const noexcept {
  return rectangle(this->length, 0, x.i_count);
}
// Builds a rectangle with length == 0 && width > 0.
inline constexpr rectangle rectangle::operator+(
    rectangle const& x) const noexcept {
  return rectangle(this->length, 0, this->i_count + x.i_count);
}
// Completes a rectangle with length == 0 && width > 0.
inline constexpr rectangle rectangle::operator+(
    segment const& x) const noexcept {
  return rectangle(this->length, this->i_count / 2);
}

}  // namespace analog_literals

#endif  // #ifndef ANALOG_LITERALS_ANALOG_TYPES_H_
