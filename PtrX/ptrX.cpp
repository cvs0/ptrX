#include "ptrX.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>
#include <limits>
#include <string>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <vector> 

MemoryManager::MemoryManager() {
    std::cout << "MemoryManager constructed" << std::endl;
}

MemoryManager::~MemoryManager() {
    std::cout << "MemoryManager destructed" << std::endl;
}

int* MemoryManager::allocateMemory(int size) {
    int* ptr = new (std::nothrow) int[size];
    if (ptr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
    }
    return ptr;
}

void MemoryManager::deallocateMemory(int* ptr) {
    if (ptr != nullptr) {
        delete[] ptr;
        std::cout << "Deallocated memory at address " << static_cast<void*>(ptr) << std::endl;
        ptr = nullptr;
    }
    else {
        std::cerr << "Trying to deallocate a null pointer" << std::endl;
    }
}


bool MemoryManager::writeValue(int* address, int value, int size) {
    if (address != nullptr && size > 0) {
        *address = value;
        return true;
    }
    else {
        std::cerr << "Invalid write operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::readValue(const int* address, int& value, int size) {
    if (address != nullptr && size > 0 && reinterpret_cast<std::uintptr_t>(address) % alignof(int) == 0) {
        value = *address;
        return true;
    }
    else {
        std::cerr << "Invalid read operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else if (size <= 0) {
            std::cerr << "Invalid size." << std::endl;
        }
        else {
            std::cerr << "Unaligned address." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::copyMemory(const int* source, int* destination, int size) {
    if (source != nullptr && destination != nullptr && size > 0) {
        std::memcpy(destination, source, size * sizeof(int));
        return true;
    }
    else {
        std::cerr << "Invalid copy operation: ";
        if (source == nullptr || destination == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::fillMemory(int* address, int value, int size) {
    if (address != nullptr && size > 0) {
        std::fill(address, address + size, value);
        return true;
    }
    else {
        std::cerr << "Invalid fill operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

const int* MemoryManager::findValue(const int* address, int value, int size) {
    if (address != nullptr && size > 0) {
        auto it = std::find(address, address + size, value);
        if (it != address + size) {
            return it;
        }
        else {
            std::cerr << "Value not found in memory." << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid findValue operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return nullptr;
    }
}

bool MemoryManager::compareMemory(const int* address1, const int* address2, int size) {
    if (address1 != nullptr && address2 != nullptr && size > 0) {
        return std::equal(address1, address1 + size, address2);
    }
    else {
        std::cerr << "Invalid compare operation: ";
        if (address1 == nullptr || address2 == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::zeroMemory(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::fill(address, address + size, 0);
        return true;
    }
    else {
        std::cerr << "Invalid zero operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

int* MemoryManager::allocateAndCopy(const int* source, int size) {
    if (source != nullptr && size > 0) {
        int* newPtr = allocateMemory(size);
        if (newPtr != nullptr) {
            std::memcpy(newPtr, source, size * sizeof(int));
            return newPtr;
        }
        else {
            std::cerr << "Memory allocation and copy failed" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid allocateAndCopy operation: ";
        if (source == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return nullptr;
    }
}

const int* MemoryManager::findValue(const int* address, int value, int size) {
    if (address != nullptr && size > 0) {
        return std::find(address, address + size, value);
    }
    else {
        std::cerr << "Invalid findValue operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return nullptr;
    }
}

bool MemoryManager::swapValues(int* address1, int* address2) {
    if (address1 != nullptr && address2 != nullptr) {
        std::swap(*address1, *address2);
        return true;
    }
    else {
        std::cerr << "Invalid swapValues operation: ";
        if (address1 == nullptr || address2 == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::reverseMemory(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::reverse(address, address + size);
        return true;
    }
    else {
        std::cerr << "Invalid reverseMemory operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

bool MemoryManager::shiftMemory(int* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        std::rotate(address, address + shiftCount, address + size);
        return true;
    }
    else {
        std::cerr << "Invalid shiftMemory operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return false;
    }
}

int MemoryManager::calculateChecksum(const int* address, int size) {
    if (address != nullptr && size > 0) {
        int checksum = 0;
        for (int i = 0; i < size; ++i) {
            checksum += address[i];
        }
        return checksum;
    }
    else {
        std::cerr << "Invalid calculateChecksum operation: ";
        if (address == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return 0;
    }
}

int* MemoryManager::allocateAndFill(int value, int size) {
    int* newPtr = allocateMemory(size);
    if (newPtr != nullptr) {
        std::fill(newPtr, newPtr + size, value);
    }
    else {
        std::cerr << "Memory allocation and fill failed" << std::endl;
    }
    return newPtr;
}

bool MemoryManager::compareMemoryWithOffset(const int* address1, const int* address2, int size, int offset) {
    if (address1 != nullptr && address2 != nullptr && size > 0 && offset >= 0 && offset < size) {
        return std::equal(address1 + offset, address1 + size, address2 + offset);
    }
    else {
        std::cerr << "Invalid compareMemoryWithOffset operation." << std::endl;
        return false;
    }
}

const int* MemoryManager::findValueFromEnd(const int* address, int value, int size) {
    if (address != nullptr && size > 0) {
        auto it = std::find(std::make_reverse_iterator(address + size), std::make_reverse_iterator(address), value);
        if (it != std::make_reverse_iterator(address)) {
            return &(*it);
        }
        else {
            std::cerr << "Value not found in memory." << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid findValueFromEnd operation." << std::endl;
        return nullptr;
    }
}

void MemoryManager::initializeMemoryWithRandomValues(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, std::numeric_limits<int>::max());

        for (int i = 0; i < size; ++i) {
            address[i] = distribution(gen);
        }
    }
    else {
        std::cerr << "Invalid initializeMemoryWithRandomValues operation." << std::endl;
    }
}

bool MemoryManager::swapMemoryWithOffset(int* address1, int* address2, int size, int offset) {
    if (address1 != nullptr && address2 != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::swap_ranges(address1 + offset, address1 + size, address2 + offset);
        return true;
    }
    else {
        std::cerr << "Invalid swapMemoryWithOffset operation." << std::endl;
        return false;
    }
}

void MemoryManager::shuffleMemory(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(address, address + size, gen);
    }
    else {
        std::cerr << "Invalid shuffleMemory operation." << std::endl;
    }
}

bool MemoryManager::reverseMemoryWithOffset(int* address, int size, int offset) {
    if (address != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::reverse(address + offset, address + size);
        return true;
    }
    else {
        std::cerr << "Invalid reverseMemoryWithOffset operation." << std::endl;
        return false;
    }
}

int* MemoryManager::resizeAndInitializeMemory(int* ptr, int oldSize, int newSize, int initValue) {
    if (ptr != nullptr && oldSize > 0 && newSize > 0) {
        int* newPtr = new (std::nothrow) int[newSize];
        if (newPtr != nullptr) {
            std::copy(ptr, ptr + std::min(oldSize, newSize), newPtr);
            std::fill(newPtr + oldSize, newPtr + newSize, initValue);
            delete[] ptr;
            return newPtr;
        }
        else {
            std::cerr << "Memory reallocation and initialization failed" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid resizeAndInitializeMemory operation." << std::endl;
        return nullptr;
    }
}

void MemoryManager::shiftMemoryCircular(int* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        std::rotate(address, address + (shiftCount % size + size) % size, address + size);
    }
    else {
        std::cerr << "Invalid shiftMemoryCircular operation." << std::endl;
    }
}

void MemoryManager::deduplicateMemory(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::sort(address, address + size);
        auto last = std::unique(address, address + size);
        std::fill(last, address + size, 0);
    }
    else {
        std::cerr << "Invalid deduplicateMemory operation." << std::endl;
    }
}

bool MemoryManager::copyMemorySubarray(const int* source, int* destination, int sourceStart, int destStart, int count) {
    if (source != nullptr && destination != nullptr && sourceStart >= 0 && destStart >= 0 && count > 0) {
        std::copy(source + sourceStart, source + sourceStart + count, destination + destStart);
        return true;
    }
    else {
        std::cerr << "Invalid copyMemorySubarray operation." << std::endl;
        return false;
    }
}

void MemoryManager::fillMemoryWithIncrementingValues(int* address, int size, int startValue, int increment) {
    if (address != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            address[i] = startValue + i * increment;
        }
    }
    else {
        std::cerr << "Invalid fillMemoryWithIncrementingValues operation." << std::endl;
    }
}

void MemoryManager::interleaveMemory(const int* source1, const int* source2, int* destination, int size) {
    if (source1 != nullptr && source2 != nullptr && destination != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            destination[i * 2] = source1[i];
            destination[i * 2 + 1] = source2[i];
        }
    }
    else {
        std::cerr << "Invalid interleaveMemory operation." << std::endl;
    }
}

void MemoryManager::xorMemory(const int* source1, const int* source2, int* destination, int size) {
    if (source1 != nullptr && source2 != nullptr && destination != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            destination[i] = source1[i] ^ source2[i];
        }
    }
    else {
        std::cerr << "Invalid xorMemory operation." << std::endl;
    }
}

void MemoryManager::moveMemory(int* destination, const int* source, int size) {
    if (destination != nullptr && source != nullptr && size > 0) {
        std::memmove(destination, source, size * sizeof(int));
    }
    else {
        std::cerr << "Invalid moveMemory operation." << std::endl;
    }
}

bool MemoryManager::zeroMemoryWithOffset(int* address, int size, int offset) {
    if (address != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::fill(address + offset, address + size, 0);
        return true;
    }
    else {
        std::cerr << "Invalid zeroMemoryWithOffset operation." << std::endl;
        return false;
    }
}

const int* MemoryManager::searchMemoryPattern(const int* address, const int* pattern, int size, int patternSize) {
    if (address != nullptr && pattern != nullptr && size > 0 && patternSize > 0) {
        return std::search(address, address + size, pattern, pattern + patternSize);
    }
    else {
        std::cerr << "Invalid searchMemoryPattern operation." << std::endl;
        return nullptr;
    }
}

void MemoryManager::swapBytes(int* address, int size) {
    if (address != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            address[i] = ((address[i] << 24) | ((address[i] << 8) & 0xFF0000) |
                ((address[i] >> 8) & 0xFF00) | (address[i] >> 24));
        }
    }
    else {
        std::cerr << "Invalid swapBytes operation." << std::endl;
    }
}

void MemoryManager::printMemoryStatistics(const int* address, int size) {
    if (address != nullptr && size > 0) {
        int minValue = *std::min_element(address, address + size);
        int maxValue = *std::max_element(address, address + size);
        double averageValue = static_cast<double>(std::accumulate(address, address + size, 0)) / size;

        std::cout << "Memory Statistics:" << std::endl;
        std::cout << "  Minimum Value: " << minValue << std::endl;
        std::cout << "  Maximum Value: " << maxValue << std::endl;
        std::cout << "  Average Value: " << std::fixed << std::setprecision(2) << averageValue << std::endl;
    }
    else {
        std::cerr << "Invalid printMemoryStatistics operation." << std::endl;
    }
}

int* MemoryManager::compressMemory(const int* source, int size, int& compressedSize) {
    if (source != nullptr && size > 0) {
        std::vector<int> compressedData;

        for (int i = 0; i < size; ++i) {
            if (i == 0 || source[i] != source[i - 1]) {
                compressedData.push_back(source[i]);
            }
        }

        compressedSize = compressedData.size();
        int* compressedPtr = new (std::nothrow) int[compressedSize];
        if (compressedPtr != nullptr) {
            std::copy(compressedData.begin(), compressedData.end(), compressedPtr);
            return compressedPtr;
        }
        else {
            std::cerr << "Memory allocation for compressed data failed." << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid compressMemory operation." << std::endl;
        return nullptr;
    }
}

int* MemoryManager::decompressMemory(const int* compressedData, int compressedSize, int originalSize) {
    if (compressedData != nullptr && compressedSize > 0 && originalSize > 0) {
        int* decompressedPtr = new (std::nothrow) int[originalSize];
        if (decompressedPtr != nullptr) {
            int currentIndex = 0;
            for (int i = 0; i < compressedSize; ++i) {
                decompressedPtr[currentIndex++] = compressedData[i];
                while (currentIndex < originalSize && compressedData[i] == compressedData[i + 1]) {
                    decompressedPtr[currentIndex++] = compressedData[i];
                }
            }
            return decompressedPtr;
        }
        else {
            std::cerr << "Memory allocation for decompressed data failed." << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid decompressMemory operation." << std::endl;
        return nullptr;
    }
}

void MemoryManager::encryptMemory(int* address, int size, const std::string& key) {
    if (address != nullptr && size > 0 && !key.empty()) {
        std::string binaryKey = "";
        for (char c : key) {
            binaryKey += std::bitset<8>(c).to_string();
        }

        for (int i = 0; i < size; ++i) {
            address[i] ^= static_cast<int>(binaryKey[i % binaryKey.size()] - '0');
        }
    }
    else {
        std::cerr << "Invalid encryptMemory operation." << std::endl;
    }
}

void MemoryManager::decryptMemory(int* address, int size, const std::string& key) {
    if (address != nullptr && size > 0 && !key.empty()) {
        std::string binaryKey = "";
        for (char c : key) {
            binaryKey += std::bitset<8>(c).to_string();
        }

        for (int i = 0; i < size; ++i) {
            address[i] ^= static_cast<int>(binaryKey[i % binaryKey.size()] - '0');
        }
    }
    else {
        std::cerr << "Invalid decryptMemory operation." << std::endl;
    }
}

void MemoryManager::reverseMemoryInRange(int* address, int start, int end) {
    if (address != nullptr && start >= 0 && end < size && start < end) {
        std::reverse(address + start, address + end + 1);
    }
    else {
        std::cerr << "Invalid reverseMemoryInRange operation." << std::endl;
    }
}


void MemoryManager::rotateMemoryLeft(int* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        std::rotate(address, address + shiftCount % size, address + size);
    }
    else {
        std::cerr << "Invalid rotateMemoryLeft operation." << std::endl;
    }
}

void MemoryManager::rotateMemoryRight(int* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        shiftCount = (shiftCount % size + size) % size; // Ensure shiftCount is non-negative
        std::rotate(address, address + size - shiftCount, address + size);
    }
    else {
        std::cerr << "Invalid rotateMemoryRight operation." << std::endl;
    }
}

void MemoryManager::shuffleMemory(int* address, int size) {
    if (address != nullptr && size > 0) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(address, address + size, g);
    }
    else {
        std::cerr << "Invalid shuffleMemory operation." << std::endl;
    }
}

void MemoryManager::uniqueMemory(int* address, int& size) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::unique(address, address + size);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid uniqueMemory operation." << std::endl;
    }
}

void MemoryManager::removeValue(int* address, int& size, int value) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::remove(address, address + size, value);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid removeValue operation." << std::endl;
    }
}

void MemoryManager::removeAllOccurrences(int* address, int& size, int value) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::remove(address, address + size, value);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid removeAllOccurrences operation." << std::endl;
    }
}

void MemoryManager::resizeMemoryWithDefaultValue(int* address, int& size, int newSize, int defaultValue) {
    if (address != nullptr && newSize > 0) {
        if (newSize > size) {
            address = resizeMemory(address, newSize);
            std::fill(address + size, address + newSize, defaultValue);
        }
        else {
            size = newSize;
        }
    }
    else {
        std::cerr << "Invalid resizeMemoryWithDefaultValue operation." << std::endl;
    }
}