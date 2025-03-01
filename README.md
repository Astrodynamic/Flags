# Flags

## Описание

Библиотека `Flags` предоставляет удобный способ работы с битовыми флагами, используя перечисления (enum) в качестве индексов. Она основана на `std::bitset` и предоставляет интерфейс, адаптированный для работы с перечислениями.

## Требования

*   C++17
*   CMake 3.28.3 или выше

## Использование

Для использования библиотеки необходимо включить заголовочный файл `flags.h`.
```cpp
#include "flags.h"
```

## Пример

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

## Сборка

Для сборки библиотеки используется CMake.

```bash
cmake -S . -B build
cmake --build build
```

## LICENSE

This project is licensed under the [MIT License](LICENSE).
