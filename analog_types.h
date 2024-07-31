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

#include <type_traits>

namespace analog_literals {

// #define ANALOG_LITERALS_DEBUG

template <bool condition, typename type_if_true, typename type_if_false>
using type_if =
    typename std::conditional<condition, type_if_true, type_if_false>::type;

class segment;
class segment_helper;
class rectangle;
class rectangle_helper;
class cuboid;
class cuboid_0_0_0_helper;

enum class signal_t : int {
  no_operation,
  rectangle_reach_end,
  rectangle_add_one_i,
  accept_next_lsh_and_finalize,
  add_one_l,
  build_a_0_0_0_cuboid
};
template <signal_t signal>
class shifter;

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
  constexpr rectangle operator*(segment const& x) const noexcept;
  constexpr rectangle_helper operator-(rectangle const& x) const noexcept;
  constexpr rectangle operator*(segment_helper const& x) const noexcept;

  constexpr cuboid operator+(rectangle const& x) const noexcept;
  constexpr cuboid operator+(segment_helper const& x) const noexcept;

  constexpr rectangle operator<<(
      shifter<signal_t::rectangle_add_one_i> const& x) const noexcept;

  constexpr cuboid_0_0_0_helper operator+(
      cuboid_0_0_0_helper const& x) const noexcept;
  constexpr cuboid operator<<(
      shifter<signal_t::build_a_0_0_0_cuboid> const& x) const noexcept;
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
 public:
  int length, height;

#ifdef ANALOG_LITERALS_DEBUG
 public:
#else
 private:
#endif
  int i_count;

 public:
  explicit constexpr rectangle(int length_ = 0, int height_ = 0,
                               int i_count_ = 0) noexcept
      : length(length_), height(height_), i_count(i_count_) {}
  // constexpr rectangle(segment const& a) noexcept
  //     : length(a.length), height(1), i_count(0) {}

  constexpr int area() const noexcept {
    return this->length * this->height;
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

  // Check if with same length and same height.
  constexpr bool same_as(rectangle const& x) const noexcept {
    return this->length == x.length && this->height == x.height;
  }

  constexpr rectangle operator*(segment const& x) const noexcept;

  constexpr rectangle operator-(segment const& x) const noexcept;

  constexpr cuboid operator-(rectangle const& x) const noexcept;

  constexpr rectangle operator<<(
      shifter<signal_t::rectangle_add_one_i> const& x) const noexcept;
  constexpr rectangle operator<<(
      shifter<signal_t::rectangle_reach_end> const& x) const noexcept;
};

class rectangle_helper {
 public:
  int value;
  explicit constexpr rectangle_helper() noexcept : value(0) {}

  constexpr rectangle operator-(segment const& x) const noexcept;
};

class cuboid {
 public:
  int length, height, depth;

#ifdef ANALOG_LITERALS_DEBUG
 public:
#else
 private:
#endif

  int i_count, l_count;

 public:
  explicit constexpr cuboid(int length_ = 0, int height_ = 0, int depth_ = 0,
                            int i_count_ = 0, int l_count_ = 0) noexcept
      : length(length_),
        height(height_),
        depth(depth_),
        i_count(i_count_),
        l_count(l_count_) {}
  // constexpr rectangle(segment const& a) noexcept
  //     : length(a.length), height(1), i_count(0) {}

  constexpr int volume() const noexcept {
    return this->length * this->height * this->depth;
  }

#if __cplusplus < 20200200L
  constexpr bool operator==(cuboid const& x) const noexcept {
    return this->volume() == x.volume();
  }
  constexpr bool operator!=(cuboid const& x) const noexcept {
    return this->volume() == x.volume();
  }
  constexpr bool operator<(cuboid const& x) const noexcept {
    return this->volume() <= x.volume();
  }
  constexpr bool operator<=(cuboid const& x) const noexcept {
    return this->volume() <= x.volume();
  }
  constexpr bool operator>(cuboid const& x) const noexcept {
    return this->volume() > x.volume();
  }
  constexpr bool operator>=(cuboid const& x) const noexcept {
    return this->volume() >= x.volume();
  }
#else
  constexpr bool operator<=>(cuboid const& x) const noexcept {
    return this->volume() <=> x.volume();
  }
#endif

  // Check if with same length, same height, and same depth.
  constexpr bool same_as(cuboid const& x) const noexcept {
    return this->length == x.length && this->height == x.height &&
           this->depth == x.depth;
  }
  constexpr cuboid operator-(rectangle const& x) const noexcept;
  constexpr cuboid operator-(segment const& x) const noexcept;
};

template <signal_t signal>
class shifter {
 public:
  int value;
  explicit constexpr shifter(int value_ = 0) noexcept : value(value_) {}

  // clang-format off
  
  // These fancy setups can help compiler deduce the functions' return types
  // only using their parameter types.
  
  // template <typename T>
  // constexpr T1 operator<<(T x) const noexcept;
  
  template <typename T>
  constexpr 
      type_if<signal == signal_t::rectangle_reach_end &&
              std::is_same<T, segment>::value,
          shifter<signal_t::rectangle_reach_end>,
          shifter<signal_t::no_operation>
      >
  operator-(T x) const noexcept;

  template <typename T>
  constexpr  
      type_if<signal == signal_t::rectangle_add_one_i &&
              std::is_same<T, segment_helper>::value,
          shifter<signal_t::rectangle_reach_end>,
      type_if<signal == signal_t::rectangle_reach_end &&
              std::is_same<T, segment>::value,
          shifter<signal_t::rectangle_reach_end>,
      type_if<signal == signal_t::rectangle_add_one_i &&
              std::is_same<T, segment>::value,
          shifter<signal_t::rectangle_reach_end>,
          shifter<signal_t::no_operation>
      >>>
  operator*(T x) const noexcept;

  template <typename T>
  constexpr
      type_if<signal == signal_t::rectangle_add_one_i &&
              std::is_same<T, segment>::value,
          shifter<signal_t::rectangle_reach_end>,
      type_if<signal == signal_t::build_a_0_0_0_cuboid &&
              std::is_same<T, segment>::value,
          shifter<signal_t::build_a_0_0_0_cuboid>,
          shifter<signal_t::no_operation>
      >>
  operator+(T x) const noexcept;

  // clang-format on
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
#define ANALOG_LITERALS_OO +(::analog_literals::segment(0))
// Starts and ends a segment with length > 0.
#define ANALOG_LITERALS_O *(::analog_literals::segment(1))

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
 * ===================== Rectangle Literal (height == 0) ======================
 * A rectangle literal with height == 0 is in one of these two format:
 * OO OO , O-O O-O , (O--...) O (O--...) O , and (O--...) - O (O--...) - O.
 * (a) For the first type, it reads +segment(0) + segment(0), simply returns a 
 *     rectangle(0, 0) will work.
 * (b) For the second type, it reads 
 *               *segment(1) - *segment(1) * segment(1) - *segment(1).
 *     We first let the binary * returns a rectangle(1, 0), then introduce a 
 *     helper class rectangle_helper and let the first binary - returns an 
 *     instance of the helper class, then letting the second binary - returns 
 *     the final answer. The introduction of this class is to prevent the 
 *     collision with 1x0x0 cuboid.
 * (c) For the third type, it reads 
 *        *(segment(1)--...) * segment(1) * *(segment(1)--...) * segment(1).
 *     Using the function defined before, it reads
 *                segment(n) * segment_helper(n/2) * segment(1).
 *     We let the first binary * returns rectangle(n, 0) here.
 * (d) For the fourth type, it reads
 *       *(segment(1)--...) - *segment(1) * *(segment(1)--...) - *segment(1).
 *     Using the function defined before, it reads
 *             segment_helper(n/2) - rectangle(n, 0) - segment(1).
 *     We let the first binary - returns rectangle(n+1, 0) here.
 */

// Completes a 0x0 rectangle.
inline constexpr rectangle segment::operator+(segment const& x) const noexcept {
  return rectangle(0, 0);
}

// Starts a 1x0 rectangle.
inline constexpr rectangle segment::operator*(segment const& x) const noexcept {
  return rectangle(x.length, 0);
}
// Completes a 1x0 rectangle, step 1.
inline constexpr rectangle_helper segment::operator-(
    rectangle const& x) const noexcept {
  return rectangle_helper();
}
// Completes a 1x0 rectangle, step 2.
inline constexpr rectangle rectangle_helper::operator-(
    segment const& x) const noexcept {
  return rectangle(1, 0);
}

// Starts a (2k)x0 rectangle.
inline constexpr rectangle segment::operator*(
    segment_helper const& x) const noexcept {
  return rectangle(x.decrement_count * 2, 0);
}
// Completes a (2k)x0 rectangle.
inline constexpr rectangle rectangle::operator*(
    segment const& x) const noexcept {
  return rectangle(this->length, 0);
}

// Starts a (2k+1)x0 rectangle.
inline constexpr rectangle segment_helper::operator-(
    rectangle const& x) const noexcept {
  return rectangle(x.length + 1, 0);
}
// Completes a (2k+1)x0 rectangle.
inline constexpr rectangle rectangle::operator-(
    segment const& x) const noexcept {
  return rectangle(this->length, 0);
}

/**
 * =============== Cuboid Literal (height == 0 && depth == 0) =================
 * A rectangle literal with height == 0 && depth == 0 is in one of these four
 * format: (O--...) O (OO--...) O (O--...) O  ,
 * (O--...) - O OO--... - O O--... - O , O-O OO-O O-O, and OO OOO OO.
 * (a) For the first type, it reads
 *                      *(segment(1)--...) * segment(1) +  \
 *        (segment(0)--...) * segment(1) * (segment(1)--...) * segment(1).
 *     Using functions defined before, it reads segment(n) + rectangle(n, 0).
 *     Letting this binary + returns cuboid(n, 0, 0) does the job.
 * (b) For the second type, it reads
 *            *(segment(1)--...) - *segment(1) + (segment(0)--...) \
 *              - *segment(1) * (segment(1)--...) - *segment(1).
 *     Using functions defined before, it reads 
 *          segment(n) + segment_helper(n/2) - rectangle(0, n) - segment(1).
 *     Letting the first binary + returns cuboid(n, 0, 0) and ignores the rest
 *     does the job.
 * (c) For the third type, it reads
 *                  *segment(1) - *segment(1) + segment(0) \
 *                  - *segment(1) * segment(1) - *segment(1).
 *     Using functions defined before, it reads
 *                rectangle(0, 0) - rectangle(0, 1) - segment(1).
 *     Letting the first binary - returns cuboid(1, 0, 0) and ignores the rest
 *     does the job.
 * (d) For the fourth type, we define OOO as << shift, then swallow the 
 *     +segment(0) after it.
 */

// Completes a (2k)x0x0 cuboid.
inline constexpr cuboid segment::operator+(rectangle const& x) const noexcept {
  return cuboid(x.length, x.height, 0);
}

// Starts a (2k+1)x0x0 cuboid.
inline constexpr cuboid segment::operator+(
    segment_helper const& x) const noexcept {
  return cuboid(this->length, 0, 0);
}
// Completes a (2k+1)x0x0 cuboid, step 1.
inline constexpr cuboid cuboid::operator-(rectangle const& x) const noexcept {
  return *this;
}
// Completes a (2k-1)x0x0 cuboid, step 2.
inline constexpr cuboid cuboid::operator-(segment const& x) const noexcept {
  return *this;
}

// Starts a 1x0x0 cuboid.
inline constexpr cuboid rectangle::operator-(
    rectangle const& x) const noexcept {
  return cuboid(1, 0, 0);
}
// The 1x0x0 cuboid completes with other (2k-1)x0x0 cuboid, as above.

// Starts a 0x0x0 cuboid.
template <>
template <>
inline constexpr shifter<signal_t::build_a_0_0_0_cuboid>
shifter<signal_t::build_a_0_0_0_cuboid>::operator+(segment x) const noexcept {
  return shifter<signal_t::build_a_0_0_0_cuboid>();
}

// Completes a 0x0x0 cuboid.
inline constexpr cuboid segment::operator<<(
    shifter<signal_t::build_a_0_0_0_cuboid> const& x) const noexcept {
  return cuboid(0, 0, 0);
}

// Builds a 0x0x0 cuboid.
#define ANALOG_LITERALS_OOO       \
  << (::analog_literals::shifter< \
      ::analog_literals::signal_t::build_a_0_0_0_cuboid>(0))

/**
 * ===================== Rectangle Literal (height > 0) =======================
 * A rectangle literal with height > 0 is always:
 *    [segment of length k] I ...(2w Is)... I [segment of length k].
 * For convience's sake, we define 'II' as 'I I'.
 * An 'I' is defined as << shift, so the rectangle (with length > 0) will read: 
 *                    segment(n) << shift << ... <<  \ 
 *                shift * segment(1)--... [-/*] segment(1). 
 * A segment(n) shifting a shift will returns a rectangle(n, 0) which counts 'I' 
 * while shifting. The last shift will eat all the unused parts of segment and 
 * tells the rectangle to let its i-count contribute to height.
 * Now let's consider rectangles with length == 0. They will read:
 *          segment(n) << shift << ... << shift + segment(0).
 * Adding a shift::operator+(segment) method simply works.
 */

// Builds a rectangle with length > 0.
#define ANALOG_LITERALS_I         \
  << (::analog_literals::shifter< \
      ::analog_literals::signal_t::rectangle_add_one_i>(0))

// Starts a rectangle with length > 0.
inline constexpr rectangle segment::operator<<(
    shifter<signal_t::rectangle_add_one_i> const& x) const noexcept {
  return rectangle(this->length, 0, 1);
}

// Builds a rectangle with length > 0.
inline constexpr rectangle rectangle::operator<<(
    shifter<signal_t::rectangle_add_one_i> const& x) const noexcept {
  return rectangle(this->length, 0, this->i_count + 1);
}

// Completes a rectangle with length > 0, step 1a.
template <>
template <>
inline constexpr shifter<signal_t::rectangle_reach_end>
shifter<signal_t::rectangle_add_one_i>::operator*(
    segment_helper x) const noexcept {
  return shifter<signal_t::rectangle_reach_end>();
}
// Completes a rectangle with length > 0, step 1b.
template <>
template <>
inline constexpr shifter<signal_t::rectangle_reach_end>
shifter<signal_t::rectangle_add_one_i>::operator*(segment x) const noexcept {
  return shifter<signal_t::rectangle_reach_end>();
}

// Completes a rectangle with length > 0, step 2a.
template <>
template <>
inline constexpr shifter<signal_t::rectangle_reach_end>
shifter<signal_t::rectangle_reach_end>::operator-(segment x) const noexcept {
  return shifter<signal_t::rectangle_reach_end>();
}
// Completes a rectangle with length > 0, step 2b.
template <>
template <>
inline constexpr shifter<signal_t::rectangle_reach_end>
shifter<signal_t::rectangle_reach_end>::operator*(segment x) const noexcept {
  return shifter<signal_t::rectangle_reach_end>();
}

// Completes a rectangle with length == 0, step 1.
template <>
template <>
inline constexpr shifter<signal_t::rectangle_reach_end>
shifter<signal_t::rectangle_add_one_i>::operator+(segment x) const noexcept {
  return shifter<signal_t::rectangle_reach_end>();
}

// Completes a rectangle, final step.
inline constexpr rectangle rectangle::operator<<(
    shifter<signal_t::rectangle_reach_end> const& x) const noexcept {
  return rectangle(this->length, (this->i_count + 1) / 2);
}

// Builds a rectangle with length == 0.
#define ANALOG_LITERALS_II ANALOG_LITERALS_I ANALOG_LITERALS_I

}  // namespace analog_literals

#endif  // #ifndef ANALOG_LITERALS_ANALOG_TYPES_H_
