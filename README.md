The `Flags` library provides a convenient way to work with bit flags using enums as indexes. It is based on `std::bitset` and provides an interface adapted for working with enums.

## Requirements

*   C++17
*   CMake 3.28.3 or higher

## Usage

To use the library, the `flags.h` header file must be included.
```cpp
#include "flags.h"
```

## Example

```cpp
enum class MyFlags {
  Flag1,
  Flag2,
  Flag3,
  COUNT
};

utils::Flags<MyFlags> flags;

flags.set(MyFlags::Flag1);
flags.flip(MyFlags::Flag2);

if (flags[MyFlags::Flag1]) {
  // ...
}
```

## Build

CMake is used to build the library.

```bash
cmake -S . -B build
cmake --build build
```

## LICENSE

This project is licensed under the [MIT License](LICENSE).
