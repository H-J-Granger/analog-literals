#include "analog_literals.h"

// clang-format off

using namespace analog_literals;

static_assert(OO == segment(0));
static_assert(O-O == segment(1));
static_assert(O--O == segment(2));
static_assert(O---O == segment(3));
static_assert(O----O == segment(4));
static_assert(O-----O == segment(5));

static_assert(rectangle(0, 0).same_as(
  OO
  OO 
));
static_assert(rectangle(0, 1).same_as(
  OO
  II
  OO 
));
static_assert(rectangle(0, 2).same_as(
  OO
  II
  II
  OO 
));
static_assert(rectangle(0, 3).same_as(
  OO
  II
  II
  II
  OO 
));

// static_assert(
//   O-O I 
// );

// #define test O-O I
// test;

// static_assert(
//   OO
//   II
//   II
//   OO == rectangle(0, 2)
// );