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

// #define ANALOG_LITERAL_DEBUG

class segment;
class segment_helper;
class rectangle;
class rectangle_helper;
class cubiod;

class segment {
 public:
  int length;

  explicit constexpr segment(int length_ = 0) noexcept : length(length_) {}

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
  constexpr segment_helper operator--(int x) const noexcept;
  constexpr segment operator-(segment const& x) const noexcept;

  constexpr segment operator+() const noexcept;
  constexpr rectangle operator+(segment const& x) const noexcept;
  constexpr rectangle operator+(rectangle const& x) const noexcept;

  constexpr rectangle operator*(segment_helper const& x) const noexcept;
  constexpr rectangle_helper operator*(
      rectangle_helper const& x) const noexcept;
  constexpr rectangle operator*(segment const& x) const noexcept;
  constexpr rectangle operator-(rectangle const& x) const noexcept;
};

class segment_helper {
 public:
  int decrement_count;

  explicit constexpr segment_helper(int decrement_count_ = 0) noexcept
      : decrement_count(decrement_count_) {}

  constexpr segment_helper operator*() const noexcept;
  constexpr segment_helper operator--(int x) const noexcept;
  constexpr segment operator-(segment const& x) const noexcept;
  constexpr segment operator*(segment const& x) const noexcept;

  constexpr rectangle operator-(rectangle const& x) const noexcept;
};

class rectangle {
#ifdef ANALOG_LITERAL_DEBUG
 public:
#else
 private:
#endif
  int ii_count;

 public:
  int length, width;

  explicit constexpr rectangle(int length_ = 0, int width_ = 0,
                               int ii_count_ = 0) noexcept
      : length(length_), width(width_), ii_count(ii_count_) {}
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

  constexpr rectangle operator*(segment const& x) const noexcept;

  constexpr rectangle operator-(segment const& x) const noexcept;
};

class rectangle_helper {
 public:
  int length, i_count;

  explicit constexpr rectangle_helper(int length_ = 0,
                                      int i_count_ = 0) noexcept
      : length(length_), i_count(i_count_){};

  constexpr rectangle_helper operator*(
      rectangle_helper const& x) const noexcept;
  constexpr rectangle operator*(segment_helper const& x) const noexcept;
  constexpr rectangle operator*(segment const& x) const noexcept;
};

/**  
 * ============================= Segment Literal =============================
 * A segment literal is in one of the following three format:
 * OO, (O-- -- ...) O, and (O-- -- ...) - O.
 * (a) For the first type, OO can be treated as segment(0).
 * (b) For the second type, O is defined as *o, then it will be interpreted as
 *     (o-- -- ...) * o (note that the prefix * will be ignored). We count the 
 *     number of '--'s as the segment builds, then ends the segment with a 
 *     binary *.
 * (c) For the third type, O can be treated as o, so we also count the number of 
 *     '--'s but ends the segment with a binary -. Note that the O - O is 
 *     treated differently, since the counting of '--'s is maintained by a 
 *     helper class segment_helper.
 */

// A segment with length == 0.
#define ANALOG_LITERAL_OO +(::analog_literals::segment(0))
// Starts and ends a segment with length > 0.
#define ANALOG_LITERAL_O *(::analog_literals::segment(1))

// Prefix *,+ of a segment/segment_helper will be ignored.
inline constexpr segment segment::operator*() const noexcept {
  return *this;
}
inline constexpr segment segment::operator+() const noexcept {
  return *this;
}
inline constexpr segment_helper segment_helper::operator*() const noexcept {
  return *this;
}

// Completes a segment with length == 1.
inline constexpr segment segment::operator-(segment const& x) const noexcept {
  return segment(1);
}

// Starts a segment with length >= 2.
inline constexpr segment_helper segment::operator--(int x) const noexcept {
  return segment_helper(1);
}
// Builds a segment with length >= 2.
inline constexpr segment_helper segment_helper::operator--(
    int x) const noexcept {
  return segment_helper(this->decrement_count + 1);
}
// Completes a segment with odd length >= 2.
inline constexpr segment segment_helper::operator-(
    segment const& x) const noexcept {
  return segment(this->decrement_count * 2 + 1);
}
// Completes a segment with even length >= 2.
inline constexpr segment segment_helper::operator*(
    segment const& x) const noexcept {
  return segment(this->decrement_count * 2);
}

/**
 * ===================== Rectangle Literal (length == 0) ======================
 * A rectangle literal with length == 0 is in one of these two format:
 * OO OO  and  OO II ... II OO .
 * (a) For the first type, we implement OO as +oo, so it behave same in segment
 *     literals. The rectangle literal will be interpreted as (+oo) + oo .
 * (b) For the second type, we define II as +ii, so we can easily count the 
 *     'II's while building the rectangle, and ending it with a +oo. The length 
 *     will be passed along, and the 'II'-count will contribute to width when 
 *     completing the rectangle.
 */

// Prefix *,+ of a rectangle will be ignored.
inline constexpr rectangle rectangle::operator*() const noexcept {
  return *this;
}
inline constexpr rectangle rectangle::operator+() const noexcept {
  return *this;
}

// Builds a rectangle with length == 0.
#define ANALOG_LITERAL_II +(::analog_literals::rectangle(0, 0, 1))

// Completes a rectangle with width == 0.
inline constexpr rectangle segment::operator+(segment const& x) const noexcept {
  return rectangle(this->length, 0);
}
// Starts a rectangle with width > 0.
inline constexpr rectangle segment::operator+(
    rectangle const& x) const noexcept {
  return rectangle(this->length, 0, x.ii_count);
}
// Builds a rectangle with width > 0.
inline constexpr rectangle rectangle::operator+(
    rectangle const& x) const noexcept {
  return rectangle(this->length, 0, this->ii_count + x.ii_count);
}
// Completes a rectangle with width > 0.
inline constexpr rectangle rectangle::operator+(
    segment const& x) const noexcept {
  return rectangle(this->length, this->ii_count);
}

/**
 * ============ Rectangle Literal (with non-zero even length) =================
 * A rectangle literal of this kind is in one of these two format:
 * O-...-O O-...-O  and  O-...-O I ... I O-...-O .
 * (a) For the first type, it reads *(o--...) * o * (o--...) * o.
 *     Having a part being API of a segment literal, it has to be
 *     segment(n) * (o--...) * o. Therefore, segment * segment_helper will 
 *     returns a rectangle.
 * (b) For the second type, it reads *(o--...) * o * i * ... * i * (o--...) * o,
 *     i.e. segment(n) * i ... i * (o--...) * o. We count the number of 'I's
 *     as we build the rectangle.
 */

// Builds a rectangle with length > 0.
#define ANALOG_LITERAL_I *(::analog_literals::rectangle_helper(0, 1))

// A rectangle will ignore the * o after it, where o is a segment.
inline constexpr rectangle rectangle::operator*(
    segment const& x) const noexcept {
  return *this;
}

// Completes a rectangle with width == 0.
inline constexpr rectangle segment::operator*(
    segment_helper const& x) const noexcept {
  return rectangle(x.decrement_count * 2, 0);
}

// Starts a rectangle with width > 0.
inline constexpr rectangle_helper segment::operator*(
    rectangle_helper const& x) const noexcept {
  return rectangle_helper(this->length, x.i_count);
}
// Builds a rectangle with width > 0.
inline constexpr rectangle_helper rectangle_helper::operator*(
    rectangle_helper const& x) const noexcept {
  return rectangle_helper(this->length, this->i_count + x.i_count);
}
// Completes a rectangle with width > 0.
inline constexpr rectangle rectangle_helper::operator*(
    segment_helper const& x) const noexcept {
  return rectangle(this->length, this->i_count / 2);
}

/**
 * ================= Rectangle Literal (with odd length) ======================
 * A rectangle literal of this kind is in one of these four format:
 * O-...-O O-...-O , O-...-O I ... I O-...-O , O-O O-O , and O-O I ... I O-O.
 * (a) For the first type, it reads *(o--...) - (*o) * (o--...) - (*o).
 *     Using functions defined before, it calculates 
 *         segment_helper(n/2) - rectangle(n, 0) - segment(1).
 *     The rectangle will use 2 * decrement_count of the segment_helper before 
 *     it as its length and add 1 to its length when subtracting segment(1).
 * (b) For the second type, it reads:
 *             *(o--...) - (*o) * i * ... * i * (o--...) - (*o).
 *     Using functions defined before, it calculates 
 *         segment_helper(n/2) - rectangle(1, i_cnt/2) - segment(1).
 *     The operator- method described in (a) also works well in this situation.
 * (c) For the third type, it reads (*o) - (*o) * o - (*o).
 *     
 * (c) For the fourth type, it reads (*o) - (*o) * i * ... * i * o - (*o).
 */

// Completes a rectangle with odd length, step 1.
inline constexpr rectangle segment_helper::operator-(
    rectangle const& x) const noexcept {
  return rectangle(this->decrement_count * 2, x.width);
}

// Completes a rectangle with odd length, step 2.
inline constexpr rectangle rectangle::operator-(
    segment const& x) const noexcept {
  return rectangle(this->length + 1, this->width);
}

// Starts a rectangle with length == 1 && width == 0, step 1.
inline constexpr rectangle segment::operator*(segment const& x) const noexcept {
  return rectangle(0, 0);
}
// Starts a rectangle with length == 1 && width > 0, step 1.
inline constexpr rectangle rectangle_helper::operator*(
    segment const& x) const noexcept {
  return rectangle(this->length, this->i_count / 2);
}
// Starts a rectangle with length == 1, step 2.
inline constexpr rectangle segment::operator-(
    rectangle const& x) const noexcept {
  return rectangle(0, x.width);
}

}  // namespace analog_literals

#endif  // #ifndef ANALOG_LITERALS_ANALOG_TYPES_H_
