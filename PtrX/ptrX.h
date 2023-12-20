#ifndef PTRX_H
#define PTRX_H
#define DEBUG_MODE

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iterator>

template <typename T>
class MemoryManager {
public:
    // Memory Management
    MemoryManager(bool log);
    ~MemoryManager();
    T* allocateMemory(int size);
    void deallocateMemory(T* ptr);

    // Basic Memory Operations
    bool writeValue(T* address, int value, int size);
    bool readValue(const T* address, int& value, int size);
    bool copyMemory(const T* source, T* destination, int size);
    bool fillMemory(T* address, int value, int size);
    T* resizeMemory(T* ptr, int newSize);

    // Memory Comparison and Manipulation
    bool compareMemory(const T* address1, const T* address2, int size);
    bool zeroMemory(T* address, int size);
    T* allocateAndCopy(const T* source, int size);
    const T* findValue(const T* address, int value, int size);
    bool swapValues(T* address1, T* address2);
    bool reverseMemory(T* address, int size);
    bool shiftMemory(T* address, int size, int shiftCount);
    int calculateChecksum(const T* address, int size);
    T* allocateAndFill(int value, int size);
    bool compareMemoryWithOffset(const T* address1, const T* address2, int size, int offset);
    const T* findValueFromEnd(const T* address, int value, int size);

    // Additional Memory Operations
    void initializeMemoryWithRandomValues(T* address, int size);
    bool swapMemoryWithOffset(T* address1, T* address2, int size, int offset);
    void shuffleMemory(T* address, int size);
    bool reverseMemoryWithOffset(T* address, int size, int offset);
    T* resizeAndInitializeMemory(T* ptr, int oldSize, int newSize, int initValue);
    void shiftMemoryCircular(T* address, int size, int shiftCount);
    void deduplicateMemory(T* address, int size);
    bool copyMemorySubarray(const T* source, T* destination, int sourceStart, int destStart, int count);
    void fillMemoryWithIncrementingValues(T* address, int size, int startValue, int increment);
    void interleaveMemory(T* destAddress, const T* block1, const T* block2, int size);
    void xorMemory(const T* source1, const T* source2, T* destination, int size);
    void moveMemory(T* destination, const T* source, int size);
    bool zeroMemoryWithOffset(T* address, int size, int offset);
    const T* searchMemoryPattern(const T* address, const T* pattern, int size, int patternSize);

    // Advanced Memory Operations
    void swapBytes(T* address, int size);
    void printMemoryStatistics(const T* address, int size);
    T* compressMemory(const T* source, int size, int& compressedSize);
    T* decompressMemory(const T* compressedData, int compressedSize, int originalSize);
    void encryptMemory(T* address, int size, const std::string& key);
    void decryptMemory(T* address, int size, const std::string& key);

    // Memory Range Operations
    void reverseMemoryInRange(T* address, int start, int end);
    void rotateMemoryLeft(T* address, int size, int shiftCount);
    void rotateMemoryRight(T* address, int size, int shiftCount);

    // Memory Set Operations
    void uniqueMemory(T* address, int& size);
    void removeValue(T* address, int& size, int value);
    void removeAllOccurrences(T* address, int& size, int value);
    void resizeMemoryWithDefaultValue(T* address, int& size, int newSize, int defaultValue);

    // Memory Checks
    bool isMemoryNull(const T* address);
    bool isMemoryAllocated(const T* address);
    bool isMemoryInitialized(const T* address, int size);
    bool isMemoryEmpty(const T* address, int size);
    bool isMemoryReadable(const T* address, int size);
    bool isMemoryWritable(T* address, int size);

    // Advanced Memory Operations

    void swapAdjacentValues(T* address, int size);

    void replaceValue(T* address, int size, int oldValue, int newValue);

    T* mergeSortedMemory(const T* block1, int size1, const T* block2, int size2);

    bool isMemoryPalindrome(const T* address, int size);

    int binarySearch(const T* sortedBlock, int size, int key);

    void rotateMemoryRangeLeft(T* address, int start, int end, int shiftCount);

    void rotateMemoryRangeRight(T* address, int start, int end, int shiftCount);

    void swapAdjacentMemoryRanges(T* address, int range1Start, int range1End, int range2Start, int range2End);

    void threeWayPartition(T* address, int size, int pivotValue, int& lowerBound, int& upperBound);

    T* unionSortedMemory(const T* block1, int size1, const T* block2, int size2, int& unionSize);

    T* differenceSortedMemory(const T* block1, int size1, const T* block2, int size2, int& differenceSize);

    T* symmetricDifferenceSortedMemory(const T* block1, int size1, const T* block2, int size2, int& symDiffSize);

    bool isSubsetSortedMemory(const T* potentialSubset, int subsetSize, const T* set, int setSize);

    bool isMemoryStrictlyIncreasing(const T* address, int size);

    bool isMemoryStrictlyDecreasing(const T* address, int size);

    bool isMemoryPlateau(const T* address, int size, int& plateauStart, int& plateauEnd);

    bool isSubsequence(const T* sequence, int seqSize, const T* subsequence, int subseqSize);

    void reverseMemoryWithPreservation(T* address, int size, const int* subblockSizes, int numSubblocks);

    bool isMemoryMountain(const T* address, int size, int& peakIndex);


private:
    int size;
    static bool logging;
};

#include "ptrX_impl.h"

#endif // PTRX_H
