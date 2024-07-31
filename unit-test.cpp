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
static_assert(rectangle(1, 0).same_as(
  O-O
  O-O 
));
static_assert(rectangle(2, 0).same_as(
  O--O
  O--O 
));
static_assert(rectangle(3, 0).same_as(
  O---O
  O---O 
));
static_assert(rectangle(4, 0).same_as(
  O----O
  O----O 
));
static_assert(rectangle(5, 0).same_as(
  O-----O
  O-----O 
));
static_assert(rectangle(6, 0).same_as(
  O------O
  O------O 
));

static_assert(rectangle(0, 0).same_as(
  OO
  OO 
));

constexpr auto tmp = 
  OO 
  OOO
   OO;

