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

static_assert(rectangle(2, 0).same_as(
  O--O
  O--O
));
static_assert(rectangle(2, 1).same_as(
  O--O
  I  I
  O--O
));
static_assert(rectangle(2, 2).same_as(
  O--O
  I  I
  I  I
  O--O
));
static_assert(rectangle(2, 3).same_as(
  O--O
  I  I
  I  I
  I  I
  O--O
));

constexpr int a = (O---O O---O).width;
constexpr int b = (O---O O---O).width;

static_assert(rectangle(5, 0).same_as(
  O-----O
  O-----O
));
static_assert(rectangle(5, 2).same_as(
  O-----O 
  I     I 
  I     I
  O-----O
));

static_assert(rectangle(1, 0).same_as(
  O-O
  O-O
));
static_assert(rectangle(1, 1).same_as(
  O-O
  I I
  O-O
));
static_assert(rectangle(1, 2).same_as(
  O-O
  I I
  I I
  O-O
));