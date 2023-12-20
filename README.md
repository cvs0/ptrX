# ptrX

ptrX is a C++ library designed to simplify and enhance memory management using pointers.

## Overview

The ptrX library provides a set of utility functions for efficient and safe manipulation of memory using pointers in C++. Whether you need to allocate and deallocate memory, perform read and write operations, or execute advanced memory manipulations, ptrX has you covered.

## Features

- **Memory Allocation and Deallocation:** Easily allocate and deallocate memory using safe and error-checked functions.

- **Read and Write Operations:** Safely read and write values at memory locations, with extensive error handling.

- **Memory Manipulation:** Perform various memory manipulation operations, such as copying, filling, resizing, and more.

- **Advanced Functions:** Execute advanced memory operations, including encryption, decryption, memory searching, and pattern matching.

- **Utility Checks:** Ensure the safety and validity of memory operations with a range of utility checks.

## Getting Started

To start using ptrX, include the `ptrX.h` header file in your C++ project. The library is designed to be simple to integrate and use.

```cpp
#include "ptrX.h"
#include <iostream>

int main() {
    MemoryManager<int> memoryManager(true);

    int* data = memoryManager.allocateMemory(10);

    memoryManager.writeValue(data, 42, 10);
    int value;
    memoryManager.readValue(data, value, 1);

    memoryManager.deallocateMemory(data);

    return 0;
}
```

## Documentation

For detailed information on each function and how to use them, refer to the documentation.

## Contributions

Contributions are welcome! If you have ideas for improvements or new features, feel free to open an issue or submit a pull request.

## License

ptrX is released under the [MIT License](LICENSE).
