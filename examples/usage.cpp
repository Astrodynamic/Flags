#include <iostream>
#include "universal_flags.h"

enum class MyFlags {
  Read,
  Write,
  Exec,
  COUNT
};

int main() {
  using utils::EnumFlags;

  EnumFlags<MyFlags> f;                         // empty
  f.set(MyFlags::Read).set(MyFlags::Write);     // set two
  f.flip(MyFlags::Exec);                        // toggle

  std::cout << "any=" << f.any() << ", count=" << f.count() << "\n";

  // iterate set flags
  for (MyFlags e : f) {
    switch (e) {
      case MyFlags::Read:  std::cout << "Read\n"; break;
      case MyFlags::Write: std::cout << "Write\n"; break;
      case MyFlags::Exec:  std::cout << "Exec\n"; break;
      case MyFlags::COUNT: break;
    }
  }

  // bitwise combine
  auto mask = EnumFlags<MyFlags>::of(MyFlags::Read, MyFlags::Exec);
  auto g = f & mask; // intersection

  std::cout << "g bits: " << g.to_string() << "\n";
  std::cout << "as mask: 0x" << std::hex << g.to_mask<unsigned>() << std::dec << "\n";
}