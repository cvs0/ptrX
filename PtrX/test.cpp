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
