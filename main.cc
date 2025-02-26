#include <iostream>

#include "flags.h"


ENUM(B,
  a,
  b,
  c,
  d,
  e
)


int main() {
  utils::Flags<enums::B> test;
  test.flip(enums::B::b);

  std::cout << test;

  return 0;
}