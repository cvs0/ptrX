#ifndef PTRX_IMPL_H
#define PTRX_IMPL_H

#include "ptrX.h"

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

template <typename T>
bool MemoryManager<T>::logging = false;

/**
 * @brief Constructs a MemoryManager object.
 *
 * @details This constructor initializes a MemoryManager object. If logging is enabled,
 * it prints a message indicating that the MemoryManager has been constructed.
 *
 * @param log If true, logging is enabled, and a construction message is printed.
 */
template <typename T>
inline MemoryManager<T>::MemoryManager(bool log) {
    if (log) {
        std::cout << "MemoryManager constructed" << std::endl;
    }
}

/**
 * @brief Destructs a MemoryManager object.
 *
 * @details This destructor cleans up resources associated with the MemoryManager object.
 * If logging is enabled, it prints a message indicating that the MemoryManager has been destructed.
 */
template <typename T>
inline MemoryManager<T>::~MemoryManager() {
    if (logging) {
        std::cout << "MemoryManager destructed" << std::endl;
    }
}


/**
 * @brief Allocates a block of memory.
 *
 * @details This function allocates a block of memory for an array of elements of type T.
 * The size parameter specifies the number of elements in the array.
 * If the allocation fails, a null pointer is returned, and an error message is printed.
 *
 * @param size The number of elements to allocate space for.
 * @return A pointer to the allocated memory block, or nullptr if allocation fails.
 */
template <typename T>
inline T* MemoryManager<T>::allocateMemory(int size) {
    T* ptr = new (std::nothrow) int[size];
    if (ptr == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
    }
    return ptr;
}

/**
 * @brief Deallocates a block of memory.
 *
 * @details This function frees the memory block pointed to by the given pointer.
 * If logging is enabled, it prints a message indicating the deallocation.
 * If the input pointer is null, an error message is printed.
 *
 * @param ptr A pointer to the memory block to be deallocated.
 */
template <typename T>
inline void MemoryManager<T>::deallocateMemory(T* ptr) {
    if (ptr != nullptr) {
        delete[] ptr;

        if (logging) {
            std::cout << "Deallocated memory at address " << static_cast<void*>(ptr) << std::endl;
        }
        ptr = nullptr;
    }
    else {
        std::cerr << "Trying to deallocate a null pointer" << std::endl;
    }
}

/**
 * @brief Writes a value to the specified memory address.
 *
 * @details This function writes the given value to the memory address pointed to by the provided pointer.
 * The size parameter is the number of elements to be written.
 * If the address is null or the size is less than or equal to 0, the function prints an error message
 * and returns false.
 *
 * @param address A pointer to the memory location where the value will be written.
 * @param value The value to be written to memory.
 * @param size The number of elements to write (usually 1 for a single value).
 * @return True if the write operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::writeValue(T* address, int value, int size) {
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

/**
 * @brief Reads a value from the specified memory address.
 *
 * @details This function reads the value from the memory address pointed to by the provided pointer.
 * The size parameter is the number of elements to be read, and it is used to check for alignment.
 * If the address is null, the size is less than or equal to 0, or the address is not aligned, the function
 * prints an error message and returns false.
 *
 * @param address A pointer to the memory location from which the value will be read.
 * @param value An integer reference to store the read value.
 * @param size The number of elements to read (usually 1 for a single value).
 * @return True if the read operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::readValue(const T* address, int& value, int size) {
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

/**
 * @brief Resizes the allocated memory block pointed to by the provided pointer.
 *
 * @details This function resizes the memory block pointed to by the given pointer to the specified newSize.
 * It allocates a new memory block with the requested size, copies the contents from the original block,
 * and deallocates the original block. If the allocation or copying fails, it prints an error message and returns nullptr.
 *
 * @param ptr A pointer to the memory block to be resized.
 * @param newSize The new size for the memory block.
 * @return A pointer to the resized memory block if the operation is successful, nullptr otherwise.
 */
template <typename T>
inline T* MemoryManager<T>::resizeMemory(T* ptr, int newSize) {
    if (ptr != nullptr && newSize > 0) {
        T* newPtr = new (std::nothrow) int[newSize];
        if (newPtr != nullptr) {
            std::memcpy(newPtr, ptr, std::min(sizeof(int) * newSize, sizeof(int) * sizeof(ptr)));
            delete[] ptr;
            return newPtr;
        }
        else {
            std::cerr << "Memory reallocation failed" << std::endl;
            return nullptr;
        }
    }
    else {
        std::cerr << "Invalid resize operation: ";
        if (ptr == nullptr) {
            std::cerr << "Null pointer." << std::endl;
        }
        else {
            std::cerr << "Invalid size." << std::endl;
        }
        return nullptr;
    }
}

/**
 * @brief Copies the contents of one memory block to another.
 *
 * @details This function copies the contents of the memory block pointed to by the source pointer
 * to the memory block pointed to by the destination pointer. The copy size is determined by the
 * provided size parameter. If either the source or destination pointer is nullptr, or the size is
 * not greater than 0, the function prints an error message and returns false.
 *
 * @param source A pointer to the source memory block.
 * @param destination A pointer to the destination memory block.
 * @param size The size, in number of elements, to be copied from the source to the destination.
 * @return True if the copy operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::copyMemory(const T* source, T* destination, int size) {
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

/**
 * @brief Fills a block of memory with a specified value.
 *
 * @details This function sets the value of each byte in the specified memory block to the provided value.
 * The size parameter determines the number of elements in the memory block. If the address is nullptr
 * or the size is not greater than 0, the function prints an error message and returns false.
 *
 * @param address A pointer to the memory block to be filled.
 * @param value The value to fill the memory block with.
 * @param size The size, in number of elements, of the memory block to be filled.
 * @return True if the fill operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::fillMemory(T* address, int value, int size) {
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

/**
 * @brief Finds the first occurrence of a value in a memory block.
 *
 * @details This function searches for the specified value in the given memory block.
 * If the value is found, a pointer to the first occurrence is returned; otherwise, nullptr is returned.
 * The size parameter determines the number of elements in the memory block.
 * If the address is nullptr or the size is not greater than 0, the function prints an error message and returns nullptr.
 *
 * @param address A pointer to the memory block to be searched.
 * @param value The value to search for in the memory block.
 * @param size The size, in number of elements, of the memory block.
 * @return A pointer to the first occurrence of the value in the memory block, or nullptr if not found.
 */
template <typename T>
inline const T* MemoryManager<T>::findValue(const T* address, int value, int size) {
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

/**
 * @brief Compares two memory blocks for equality.
 *
 * @details This function compares the content of two memory blocks for equality.
 * If the blocks are equal, the function returns true; otherwise, it returns false.
 * The size parameter determines the number of elements in each memory block.
 * If either address1 or address2 is nullptr, or if size is not greater than 0, the function prints an error message and returns false.
 *
 * @param address1 A pointer to the first memory block.
 * @param address2 A pointer to the second memory block.
 * @param size The size, in number of elements, of each memory block.
 * @return True if the memory blocks are equal, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::compareMemory(const T* address1, const T* address2, int size) {
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

/**
 * @brief Sets a block of memory to zero.
 *
 * @details This function sets each byte in the specified memory block to zero.
 * The size parameter determines the number of elements in the memory block.
 * If the address is nullptr or the size is not greater than 0, the function prints an error message and returns false.
 *
 * @param address A pointer to the memory block to be zeroed.
 * @param size The size, in number of elements, of the memory block.
 * @return True if the zero operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::zeroMemory(T* address, int size) {
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

/**
 * @brief Allocates memory and copies the content from a source memory block.
 *
 * @details This function allocates a new memory block of the specified size and copies the content from the source memory block.
 * The size parameter determines the number of elements in both the source and the new memory block.
 * If the source pointer is nullptr or the size is not greater than 0, the function prints an error message and returns nullptr.
 *
 * @param source A pointer to the source memory block.
 * @param size The size, in number of elements, of the source and new memory blocks.
 * @return A pointer to the newly allocated memory block with copied content, or nullptr if the operation fails.
 */
template <typename T>
inline T* MemoryManager<T>::allocateAndCopy(const T* source, int size) {
    if (source != nullptr && size > 0) {
        T* newPtr = allocateMemory(size);
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

/**
 * @brief Swaps the values at two memory addresses.
 *
 * @details This function swaps the values at the specified memory addresses.
 * If either address1 or address2 is nullptr, the function prints an error message and returns false.
 *
 * @param address1 A pointer to the first memory address.
 * @param address2 A pointer to the second memory address.
 * @return true if the values are successfully swapped, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::swapValues(T* address1, T* address2) {
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

/**
 * @brief Reverses the order of elements in the specified memory range.
 *
 * @details This function reverses the order of elements in the memory range starting from the specified address.
 * If the address is nullptr or the size is invalid, the function prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @return true if the memory is successfully reversed, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::reverseMemory(T* address, int size) {
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

/**
 * @brief Shifts the elements in the specified memory range to the right by a given count.
 *
 * @details This function performs a circular shift to the right on the elements in the memory range
 * starting from the specified address. If the address is nullptr or the size is invalid, the function
 * prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @param shiftCount The number of positions to shift the elements to the right.
 * @return true if the memory is successfully shifted, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::shiftMemory(T* address, int size, int shiftCount) {
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

/**
 * @brief Calculates the checksum of the elements in the specified memory range.
 *
 * @details This function calculates the checksum by summing up the elements in the memory range
 * starting from the specified address. If the address is nullptr or the size is invalid, the function
 * prints an error message and returns 0.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @return The calculated checksum.
 */
template <typename T>
inline int MemoryManager<T>::calculateChecksum(const T* address, int size) {
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

/**
 * @brief Allocates memory and fills it with the specified value.
 *
 * @details This function allocates a new block of memory with the specified size and fills it with
 * the specified value. If the memory allocation fails, the function prints an error message and returns nullptr.
 *
 * @param value The value to fill the allocated memory with.
 * @param size The size of the memory block to allocate.
 * @return A pointer to the allocated and filled memory block, or nullptr if allocation fails.
 */
template <typename T>
inline T* MemoryManager<T>::allocateAndFill(int value, int size) {
    T* newPtr = allocateMemory(size);
    if (newPtr != nullptr) {
        std::fill(newPtr, newPtr + size, value);
    }
    else {
        std::cerr << "Memory allocation and fill failed" << std::endl;
    }
    return newPtr;
}

/**
 * @brief Compares two memory ranges with an offset.
 *
 * @details This function compares two memory ranges starting from the specified addresses, considering
 * the offset. If the addresses are not nullptr, the sizes are valid, and the offset is within bounds,
 * the function returns true if the memory ranges are equal, and false otherwise.
 *
 * @param address1 A pointer to the start of the first memory range.
 * @param address2 A pointer to the start of the second memory range.
 * @param size The size of the memory ranges.
 * @param offset The offset indicating where the comparison starts.
 * @return true if the memory ranges are equal, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::compareMemoryWithOffset(const T* address1, const T* address2, int size, int offset) {
    if (address1 != nullptr && address2 != nullptr && size > 0 && offset >= 0 && offset < size) {
        return std::equal(address1 + offset, address1 + size, address2 + offset);
    }
    else {
        std::cerr << "Invalid compareMemoryWithOffset operation." << std::endl;
        return false;
    }
}

/**
 * @brief Finds the last occurrence of a value in the specified memory range.
 *
 * @details This function searches for the last occurrence of the specified value in the memory range
 * starting from the specified address. If the address is not nullptr and the size is valid, the
 * function returns a pointer to the found value, or nullptr if the value is not present.
 *
 * @param address A pointer to the start of the memory range.
 * @param value The value to search for.
 * @param size The size of the memory range.
 * @return A pointer to the last occurrence of the value, or nullptr if not found.
 */
template <typename T>
inline const T* MemoryManager<T>::findValueFromEnd(const T* address, int value, int size) {
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

/**
 * @brief Initializes the specified memory range with random values.
 *
 * @details This function fills the memory range starting from the specified address with random values.
 * If the address is not nullptr and the size is valid, the function uses a random number generator to
 * generate random values for each element in the range.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 */
template <typename T>
inline void MemoryManager<T>::initializeMemoryWithRandomValues(T* address, int size) {
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

/**
 * @brief Swaps portions of memory between two addresses with an offset.
 *
 * @details This function swaps memory ranges starting from the specified addresses, considering the offset.
 * If the addresses are not nullptr, the sizes are valid, and the offset is within bounds, the function swaps
 * the specified portions of memory and returns true. Otherwise, it returns false.
 *
 * @param address1 A pointer to the start of the first memory range.
 * @param address2 A pointer to the start of the second memory range.
 * @param size The size of the memory ranges.
 * @param offset The offset indicating where the swapping starts.
 * @return true if the memory swap is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::swapMemoryWithOffset(T* address1, T* address2, int size, int offset) {
    if (address1 != nullptr && address2 != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::swap_ranges(address1 + offset, address1 + size, address2 + offset);
        return true;
    }
    else {
        std::cerr << "Invalid swapMemoryWithOffset operation." << std::endl;
        return false;
    }
}

/**
 * @brief Shuffles the elements of the specified memory range.
 *
 * @details This function shuffles the elements of the memory range starting from the specified address.
 * If the address is not nullptr and the size is valid, the function uses a random number generator to
 * perform the shuffle.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 */
template <typename T>
inline void MemoryManager<T>::shuffleMemory(T* address, int size) {
    if (address != nullptr && size > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(address, address + size, gen);
    }
    else {
        std::cerr << "Invalid shuffleMemory operation." << std::endl;
    }
}

/**
 * @brief Reverses a portion of memory with an offset.
 *
 * @details This function reverses a portion of the memory range starting from the specified address,
 * considering the offset. If the address is not nullptr, the size is valid, and the offset is within
 * bounds, the function reverses the specified portion of memory and returns true. Otherwise, it returns false.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @param offset The offset indicating where the reversal starts.
 * @return true if the memory reversal is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::reverseMemoryWithOffset(T* address, int size, int offset) {
    if (address != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::reverse(address + offset, address + size);
        return true;
    }
    else {
        std::cerr << "Invalid reverseMemoryWithOffset operation." << std::endl;
        return false;
    }
}

/**
 * @brief Resizes and initializes the memory pointed to by the specified pointer.
 *
 * @details This function resizes the memory block pointed to by the specified pointer to the new size,
 * initializes the existing elements with the values from the original block, and fills the remaining
 * space with the specified initialization value. If the pointer is not nullptr and the sizes are valid,
 * the function performs the resize and initialization, returning the new pointer. If any condition is not met,
 * the function returns nullptr.
 *
 * @param ptr A pointer to the memory block to be resized and initialized.
 * @param oldSize The current size of the memory block.
 * @param newSize The desired new size of the memory block.
 * @param initValue The value used for initializing the new elements.
 * @return A pointer to the resized and initialized memory block, or nullptr if the operation fails.
 */
template <typename T>
inline T* MemoryManager<T>::resizeAndInitializeMemory(T* ptr, int oldSize, int newSize, int initValue) {
    if (ptr != nullptr && oldSize > 0 && newSize > 0) {
        T* newPtr = new (std::nothrow) int[newSize];
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

/**
 * @brief Shifts the elements of the memory range in a circular manner.
 *
 * @details This function shifts the elements of the memory range starting from the specified address
 * in a circular manner based on the specified shift count. If the address is not nullptr and the size is valid,
 * the function performs the circular shift. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @param shiftCount The number of positions to shift the elements.
 */
template <typename T>
inline void MemoryManager<T>::shiftMemoryCircular(T* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        std::rotate(address, address + (shiftCount % size + size) % size, address + size);
    }
    else {
        std::cerr << "Invalid shiftMemoryCircular operation." << std::endl;
    }
}

/**
 * @brief Deduplicates the elements of the memory range.
 *
 * @details This function deduplicates the elements of the memory range starting from the specified address.
 * If the address is not nullptr and the size is valid, the function performs deduplication by sorting the
 * elements and removing duplicates. It fills the remaining space with zeros. If any condition is not met,
 * it prints an error message.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 */
template <typename T>
inline void MemoryManager<T>::deduplicateMemory(T* address, int size) {
    if (address != nullptr && size > 0) {
        std::sort(address, address + size);
        auto last = std::unique(address, address + size);
        std::fill(last, address + size, 0);
    }
    else {
        std::cerr << "Invalid deduplicateMemory operation." << std::endl;
    }
}

/**
 * @brief Copies a subarray from the source memory to the destination memory.
 *
 * @details This function copies a subarray of elements from the source memory starting from the specified
 * source index to the destination memory starting from the specified destination index. If the source and
 * destination pointers are not nullptr and the indices and count are valid, the function performs the copy
 * and returns true. Otherwise, it prints an error message and returns false.
 *
 * @param source A pointer to the source memory.
 * @param destination A pointer to the destination memory.
 * @param sourceStart The starting index in the source memory.
 * @param destStart The starting index in the destination memory.
 * @param count The number of elements to copy.
 * @return true if the copy operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::copyMemorySubarray(const T* source, T* destination, int sourceStart, int destStart, int count) {
    if (source != nullptr && destination != nullptr && sourceStart >= 0 && destStart >= 0 && count > 0) {
        std::copy(source + sourceStart, source + sourceStart + count, destination + destStart);
        return true;
    }
    else {
        std::cerr << "Invalid copyMemorySubarray operation." << std::endl;
        return false;
    }
}

/**
 * @brief Fills the memory with incrementing values starting from a specified value.
 *
 * @details This function fills the specified memory range with incrementing values starting from the specified
 * start value, with each subsequent value incremented by the specified increment. If the address is not nullptr
 * and the size is valid, the function performs the fill operation. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory range.
 * @param size The size of the memory range.
 * @param startValue The starting value for filling the memory.
 * @param increment The increment between consecutive values.
 */
template <typename T>
inline void MemoryManager<T>::fillMemoryWithIncrementingValues(T* address, int size, int startValue, int increment) {
    if (address != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            address[i] = startValue + i * increment;
        }
    }
    else {
        std::cerr << "Invalid fillMemoryWithIncrementingValues operation." << std::endl;
    }
}

/**
 * @brief Interleaves two memory blocks into a destination block.
 *
 * @details This function interleaves the contents of two memory blocks, 'block1' and 'block2', into the destination block
 * starting from the specified 'destAddress'. The size of each block is given by 'size'. The interleaving pattern is such
 * that elements from 'block1' and 'block2' alternate in the destination block.
 *
 * @param destAddress A pointer to the destination memory block.
 * @param block1 A pointer to the first source memory block.
 * @param block2 A pointer to the second source memory block.
 * @param size The size of each memory block.
 */
template <typename T>
inline void MemoryManager<T>::interleaveMemory(T* destAddress, const T* block1, const T* block2, int size) {
    if (destAddress != nullptr && block1 != nullptr && block2 != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            destAddress[i * 2] = block1[i];
            destAddress[i * 2 + 1] = block2[i];
        }
    }
    else {
        std::cerr << "Invalid interleaveMemory operation." << std::endl;
    }
}


/**
 * @brief Interleaves elements from two source memories into a destination memory.
 *
 * @details This function interleaves elements from two source memories into a destination memory. Each element
 * from the first source memory is placed at even indices, and each element from the second source memory is placed
 * at odd indices in the destination memory. If the source1, source2, and destination pointers are not nullptr
 * and the size is valid, the function performs the interleaving. Otherwise, it prints an error message.
 *
 * @param source1 A pointer to the first source memory.
 * @param source2 A pointer to the second source memory.
 * @param destination A pointer to the destination memory.
 * @param size The size of the memory range.
 */
template <typename T>
inline void MemoryManager<T>::fillMemoryWithIncrementingValues(T* address, int size, int startValue, int increment) {
    if (address != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            address[i] = static_cast<T>(startValue + i * increment);
        }
    }
    else {
        std::cerr << "Invalid fillMemoryWithIncrementingValues operation." << std::endl;
    }
}

/**
 * @brief Performs bitwise XOR on elements from two source memories into a destination memory.
 *
 * @details This function performs bitwise XOR on elements from two source memories and stores the result in
 * a destination memory. If the source1, source2, and destination pointers are not nullptr and the size is valid,
 * the function performs the XOR operation. Otherwise, it prints an error message.
 *
 * @param source1 A pointer to the first source memory.
 * @param source2 A pointer to the second source memory.
 * @param destination A pointer to the destination memory.
 * @param size The size of the memory range.
 */
template <typename T>
inline void MemoryManager<T>::xorMemory(const T* source1, const T* source2, T* destination, int size) {
    if (source1 != nullptr && source2 != nullptr && destination != nullptr && size > 0) {
        for (int i = 0; i < size; ++i) {
            destination[i] = source1[i] ^ source2[i];
        }
    }
    else {
        std::cerr << "Invalid xorMemory operation." << std::endl;
    }
}

/**
 * @brief Moves a block of memory from a source address to a destination address.
 *
 * @details This function moves a block of memory from the source address to the destination address using
 * `std::memmove`. If the destination, source, and size are valid, the function performs the memory move.
 * Otherwise, it prints an error message.
 *
 * @param destination A pointer to the destination memory.
 * @param source A pointer to the source memory.
 * @param size The size of the memory block to move.
 */
template <typename T>
inline void MemoryManager<T>::moveMemory(T* destination, const T* source, int size) {
    if (destination != nullptr && source != nullptr && size > 0) {
        std::memmove(destination, source, size * sizeof(int));
    }
    else {
        std::cerr << "Invalid moveMemory operation." << std::endl;
    }
}

/**
 * @brief Sets a block of memory to zero starting from a specified offset.
 *
 * @details This function sets a block of memory to zero starting from a specified offset to the end of the block.
 * If the address is not nullptr and the size and offset are valid, the function performs the zeroing. Otherwise,
 * it prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param offset The offset from which to start zeroing.
 * @return true if the zeroing operation is successful, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::zeroMemoryWithOffset(T* address, int size, int offset) {
    if (address != nullptr && size > 0 && offset >= 0 && offset < size) {
        std::fill(address + offset, address + size, 0);
        return true;
    }
    else {
        std::cerr << "Invalid zeroMemoryWithOffset operation." << std::endl;
        return false;
    }
}

/**
 * @brief Searches for a pattern within a block of memory.
 *
 * @details This function searches for a pattern within a block of memory using `std::search`. If the address,
 * pattern, size, and pattern size are valid, the function returns a pointer to the first occurrence of the pattern.
 * Otherwise, it prints an error message and returns nullptr.
 *
 * @param address A pointer to the start of the memory block.
 * @param pattern A pointer to the pattern to search for.
 * @param size The size of the memory block.
 * @param patternSize The size of the pattern.
 * @return A pointer to the first occurrence of the pattern if found, nullptr otherwise.
 */
template <typename T>
inline const T* MemoryManager<T>::searchMemoryPattern(const T* address, const T* pattern, int size, int patternSize) {
    if (address != nullptr && pattern != nullptr && size > 0 && patternSize > 0) {
        return std::search(address, address + size, pattern, pattern + patternSize);
    }
    else {
        std::cerr << "Invalid searchMemoryPattern operation." << std::endl;
        return nullptr;
    }
}

/**
 * @brief Swaps the byte order of each element in a block of memory.
 *
 * @details This function swaps the byte order of each element in a block of memory. If the address and size
 * are valid, the function performs the byte swapping. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 */
template <typename T>
inline void MemoryManager<T>::swapBytes(T* address, int size) {
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

/**
 * @brief Prints statistics of the memory block.
 *
 * @details This function prints the minimum value, maximum value, and average value of the elements in
 * the memory block. If the address and size are valid, the function calculates and prints the statistics.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 */
template <typename T>
inline void MemoryManager<T>::printMemoryStatistics(const T* address, int size) {
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

/**
 * @brief Compresses a memory block by removing consecutive duplicate elements.
 *
 * @details This function compresses a memory block by removing consecutive duplicate elements.
 * If the source, size, and compressedSize parameters are valid, the function returns a pointer to
 * the compressed memory block along with the size of the compressed block. Otherwise, it prints
 * an error message and returns nullptr.
 *
 * @param source A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param compressedSize A reference to an integer that will be set to the size of the compressed block.
 * @return A pointer to the compressed memory block if successful, nullptr otherwise.
 */
template <typename T>
inline T* MemoryManager<T>::compressMemory(const T* source, int size, int& compressedSize) {
    if (source != nullptr && size > 0) {
        std::vector<int> compressedData;

        for (int i = 0; i < size; ++i) {
            if (i == 0 || source[i] != source[i - 1]) {
                compressedData.push_back(source[i]);
            }
        }

        compressedSize = compressedData.size();
        T* compressedPtr = new (std::nothrow) int[compressedSize];
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

/**
 * @brief Decompresses a memory block by expanding consecutive elements based on counts.
 *
 * @details This function decompresses a memory block by expanding consecutive elements based on counts.
 * If the compressedData, compressedSize, and originalSize parameters are valid, the function returns a pointer
 * to the decompressed memory block. Otherwise, it prints an error message and returns nullptr.
 *
 * @param compressedData A pointer to the start of the compressed memory block.
 * @param compressedSize The size of the compressed memory block.
 * @param originalSize The size of the original (uncompressed) memory block.
 * @return A pointer to the decompressed memory block if successful, nullptr otherwise.
 */
template <typename T>
inline T* MemoryManager<T>::decompressMemory(const T* compressedData, int compressedSize, int originalSize) {
    if (compressedData != nullptr && compressedSize > 0 && originalSize > 0) {
        T* decompressedPtr = new (std::nothrow) int[originalSize];
        if (decompressedPtr != nullptr) {
            int currentIndex = 0;
            int count = 1;

            for (int i = 0; i < compressedSize; ++i) {
                decompressedPtr[currentIndex++] = compressedData[i];

                while (i < compressedSize - 1 && compressedData[i] == compressedData[i + 1] && count < originalSize) {
                    decompressedPtr[currentIndex++] = compressedData[i];
                    ++count;
                    ++i;
                }

                count = 1;
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

/**
 * @brief Encrypts a memory block using XOR with a key.
 *
 * @details This function encrypts a memory block using XOR with a key.
 * If the address, size, and key parameters are valid, the function performs the encryption.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param key The encryption key as a string.
 */
template <typename T>
inline void MemoryManager<T>::encryptMemory(T* address, int size, const std::string& key) {
    if (address != nullptr && size > 0 && !key.empty()) {
        std::vector<int> xorValues;
        for (char c : key) {
            xorValues.push_back(static_cast<int>(c) - '0');
        }

        for (int i = 0; i < size; ++i) {
            address[i] ^= xorValues[i % key.size()];
        }
    }
    else {
        std::cerr << "Invalid encryptMemory operation." << std::endl;
    }
}

/**
 * @brief Decrypts a memory block that was encrypted using XOR with a key.
 *
 * @details This function decrypts a memory block that was encrypted using XOR with a key.
 * If the address, size, and key parameters are valid, the function performs the decryption.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param key The encryption key as a string.
 */
template <typename T>
inline void MemoryManager<T>::decryptMemory(T* address, int size, const std::string& key) {
    if (address != nullptr && size > 0 && !key.empty()) {
        std::vector<int> xorValues;
        for (char c : key) {
            xorValues.push_back(static_cast<int>(c) - '0');
        }

        for (int i = 0; i < size; ++i) {
            address[i] ^= xorValues[i % key.size()];
        }
    }
    else {
        std::cerr << "Invalid decryptMemory operation." << std::endl;
    }
}

/**
 * @brief Reverses a portion of a memory block within a specified range.
 *
 * @details This function reverses a portion of a memory block within a specified range.
 * If the address, start, and end parameters are valid, the function performs the reversal.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param start The starting index of the range to reverse.
 * @param end The ending index of the range to reverse.
 */
template <typename T>
inline void MemoryManager<T>::reverseMemoryInRange(T* address, int start, int end) {
    if (address != nullptr && start >= 0 && end < size && start < end) {
        std::reverse(address + start, address + end + 1);
    }
    else {
        std::cerr << "Invalid reverseMemoryInRange operation." << std::endl;
    }
}

/**
 * @brief Rotates a memory block to the left by a specified number of positions.
 *
 * @details This function rotates a memory block to the left by a specified number of positions.
 * If the address and size parameters are valid, the function performs the rotation.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param shiftCount The number of positions to rotate the memory block to the left.
 */
template <typename T>
inline void MemoryManager<T>::rotateMemoryLeft(T* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        std::rotate(address, address + shiftCount % size, address + size);
    }
    else {
        std::cerr << "Invalid rotateMemoryLeft operation." << std::endl;
    }
}

/**
 * @brief Rotates a memory block to the right by a specified number of positions.
 *
 * @details This function rotates a memory block to the right by a specified number of positions.
 * If the address and size parameters are valid, the function performs the rotation.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param shiftCount The number of positions to rotate the memory block to the right.
 */
template <typename T>
inline void MemoryManager<T>::rotateMemoryRight(T* address, int size, int shiftCount) {
    if (address != nullptr && size > 0) {
        shiftCount = (shiftCount % size + size) % size; // Ensure shiftCount is non-negative
        std::rotate(address, address + size - shiftCount, address + size);
    }
    else {
        std::cerr << "Invalid rotateMemoryRight operation." << std::endl;
    }
}

/**
 * @brief Removes consecutive duplicate values from a sorted memory block.
 *
 * @details This function removes consecutive duplicate values from a sorted memory block.
 * If the address and size parameters are valid, the function performs the removal.
 * The size parameter is updated to reflect the new size of the memory block.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the sorted memory block.
 * @param size The size of the memory block.
 */
template <typename T>
inline void MemoryManager<T>::uniqueMemory(T* address, int& size) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::unique(address, address + size);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid uniqueMemory operation." << std::endl;
    }
}

/**
 * @brief Removes all occurrences of a specified value from a memory block.
 *
 * @details This function removes all occurrences of a specified value from a memory block.
 * If the address and size parameters are valid, the function performs the removal.
 * The size parameter is updated to reflect the new size of the memory block.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param value The value to be removed from the memory block.
 */
template <typename T>
inline void MemoryManager<T>::removeValue(T* address, int& size, int value) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::remove(address, address + size, value);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid removeValue operation." << std::endl;
    }
}

/**
 * @brief Removes all occurrences of a specified value from a memory block.
 *
 * @details This function removes all occurrences of a specified value from a memory block.
 * If the address and size parameters are valid, the function performs the removal.
 * The size parameter is updated to reflect the new size of the memory block.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param value The value to be removed from the memory block.
 */
template <typename T>
inline void MemoryManager<T>::removeAllOccurrences(T* address, int& size, int value) {
    if (address != nullptr && size > 0) {
        auto newEnd = std::remove(address, address + size, value);
        size = std::distance(address, newEnd);
    }
    else {
        std::cerr << "Invalid removeAllOccurrences operation." << std::endl;
    }
}

/**
 * @brief Resizes a memory block and initializes the new elements with a default value.
 *
 * @details This function resizes a memory block and initializes the new elements with a default value.
 * If the address parameter is valid and newSize is greater than the current size,
 * the function resizes the memory block, filling the new elements with the specified defaultValue.
 * If newSize is less than or equal to the current size, the size parameter is updated to newSize.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The current size of the memory block.
 * @param newSize The desired size of the memory block after resizing.
 * @param defaultValue The value used to initialize new elements (if any).
 */
template <typename T>
inline void MemoryManager<T>::resizeMemoryWithDefaultValue(T* address, int& size, int newSize, int defaultValue) {
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

/**
 * @brief Checks if a memory block is null.
 *
 * @details This function checks if a memory block is null.
 *
 * @param address A pointer to the start of the memory block.
 * @return True if the memory block is null, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryNull(const T* address) {
    return (address == nullptr);
}

/**
 * @brief Checks if a memory block is allocated.
 *
 * @details This function checks if a memory block is allocated.
 *
 * @param address A pointer to the start of the memory block.
 * @return True if the memory block is allocated, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryAllocated(const T* address) {
    return (address != nullptr);
}

/**
 * @brief Checks if a memory block is fully initialized with non-zero values.
 *
 * @details This function checks if a memory block is fully initialized with non-zero values.
 * If the address and size parameters are valid, the function performs the check.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is fully initialized, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryInitialized(const T* address, int size) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryInitialized check: Null pointer or invalid size." << std::endl;
        return false;
    }

    return !std::any_of(address, address + size, [](const T& value) { return value == 0; });
}

/**
 * @brief Checks if a memory block is empty.
 *
 * @details This function checks if a memory block is empty by verifying that all elements are zero.
 * If the address and size parameters are valid, the function performs the check.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is empty, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryEmpty(const T* address, int size) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryEmpty check: Null pointer or invalid size." << std::endl;
        return false;
    }

    return std::all_of(address, address + size, [](const T& value) { return value == 0; });
}

/**
 * @brief Checks if a memory block is readable.
 *
 * @details This function checks if a memory block is readable.
 * If the address parameter is valid and size is greater than zero, the function returns true.
 * Otherwise, it prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is readable, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryReadable(const T* address, int size) {
    if (address == nullptr) {
        std::cerr << "Invalid isMemoryReadable check: Null pointer." << std::endl;
        return false;
    }

    if (size <= 0) {
        std::cerr << "Invalid isMemoryReadable check: Invalid size." << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Checks if a memory block is writable.
 *
 * @details This function checks if a memory block is writable.
 * If the address parameter is valid and size is greater than zero, the function returns true.
 * Otherwise, it prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is writable, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryWritable(T* address, int size) {
    if (address == nullptr) {
        std::cerr << "Invalid isMemoryWritable check: Null pointer." << std::endl;
        return false;
    }

    if (size <= 0) {
        std::cerr << "Invalid isMemoryWritable check: Invalid size." << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Swaps adjacent values in a memory block.
 *
 * @details This function swaps adjacent values in a memory block.
 * If the address parameter is valid and size is greater than one, the function performs the swap.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 */
template <typename T>
inline void MemoryManager<T>::swapAdjacentValues(T* address, int size) {
    if (address != nullptr && size > 1) {
        for (int i = 0; i < size - 1; i += 2) {
            std::swap(address[i], address[i + 1]);
        }
    }
    else {
        std::cerr << "Invalid swapAdjacentValues operation." << std::endl;
    }
}

/**
 * @brief Replaces occurrences of a value in a memory block.
 *
 * @details This function replaces occurrences of a specified old value with a new value in a memory block.
 * If the address parameter is valid and size is greater than zero, the function performs the replacement.
 * Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param oldValue The value to be replaced.
 * @param newValue The new value to replace the old value.
 */
template <typename T>
inline void MemoryManager<T>::replaceValue(T* address, int size, int oldValue, int newValue) {
    if (address != nullptr && size > 0) {
        std::replace(address, address + size, oldValue, newValue);
    }
    else {
        std::cerr << "Invalid replaceValue operation." << std::endl;
    }
}

/**
 * @brief Merges two sorted memory blocks into a new sorted block.
 *
 * @details This function merges two sorted memory blocks into a new sorted block.
 * If both input blocks are valid (non-null and non-empty), the function performs the merge.
 * Otherwise, it prints an error message and returns a null pointer.
 *
 * @param block1 A pointer to the first sorted memory block.
 * @param size1 The size of the first memory block.
 * @param block2 A pointer to the second sorted memory block.
 * @param size2 The size of the second memory block.
 * @return A pointer to the newly merged sorted memory block, or nullptr if there are invalid inputs.
 */
template <typename T>
inline T* MemoryManager<T>::mergeSortedMemory(const T* block1, int size1, const T* block2, int size2) {
    if (block1 == nullptr || size1 <= 0 || block2 == nullptr || size2 <= 0) {
        std::cerr << "Invalid mergeSortedMemory operation: Null or empty blocks." << std::endl;
        return nullptr;
    }

    T* mergedBlock = new int[size1 + size2];
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (block1[i] < block2[j]) {
            mergedBlock[k++] = block1[i++];
        }
        else {
            mergedBlock[k++] = block2[j++];
        }
    }

    while (i < size1) {
        mergedBlock[k++] = block1[i++];
    }

    while (j < size2) {
        mergedBlock[k++] = block2[j++];
    }

    return mergedBlock;
}

/**
 * @brief Checks if a memory block is a palindrome.
 *
 * @details This function checks if a memory block is a palindrome.
 * If the address parameter is valid and size is greater than zero, the function performs the check.
 * Otherwise, it prints an error message and returns false.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is a palindrome, false otherwise.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryPalindrome(const T* address, int size) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryPalindrome operation: Null or empty block." << std::endl;
        return false;
    }

    int halfSize = size / 2;
    for (int i = 0; i < halfSize; ++i) {
        if (address[i] != address[size - 1 - i]) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Performs binary search on a sorted memory block.
 *
 * @details This function performs binary search on a sorted memory block to find the target value.
 * If the sortedBlock parameter is valid (non-null and non-empty), the function returns the index of the target value.
 * If the target is not found, it returns -1. If the inputs are invalid, it prints an error message and returns -1.
 *
 * @param sortedBlock A pointer to the sorted memory block.
 * @param size The size of the sorted memory block.
 * @param target The value to search for.
 * @return The index of the target value if found, -1 otherwise.
 */
template <typename T>
inline int MemoryManager<T>::binarySearch(const T* sortedBlock, int size, int target) {
    if (sortedBlock == nullptr || size <= 0) {
        std::cerr << "Invalid binarySearch operation: Null or empty sorted block." << std::endl;
        return -1;
    }

    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (sortedBlock[mid] == target) {
            return mid;
        }
        else if (sortedBlock[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

/**
 * @brief Rotates a specified range of a memory block to the left by a given shift count.
 *
 * @details This function rotates a specified range of a memory block to the left by a given shift count.
 * If the address parameter is valid and the start, end, and shiftCount parameters are within bounds,
 * the function performs the rotation. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param start The start index of the range to rotate.
 * @param end The end index of the range to rotate.
 * @param shiftCount The number of positions to rotate the range to the left.
 */
template <typename T>
inline void MemoryManager<T>::rotateMemoryRangeLeft(T* address, int start, int end, int shiftCount) {
    if (address != nullptr && start >= 0 && end < size && start < end) {
        std::rotate(address + start, address + start + (shiftCount % (end - start + 1)), address + end + 1);
    }
    else {
        std::cerr << "Invalid rotateMemoryRangeLeft operation." << std::endl;
    }
}

/**
 * @brief Rotates a specified range of a memory block to the right by a given shift count.
 *
 * @details This function rotates a specified range of a memory block to the right by a given shift count.
 * If the address parameter is valid and the start, end, and shiftCount parameters are within bounds,
 * the function performs the rotation. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param start The start index of the range to rotate.
 * @param end The end index of the range to rotate.
 * @param shiftCount The number of positions to rotate the range to the right.
 */
template <typename T>
inline void MemoryManager<T>::rotateMemoryRangeRight(T* address, int start, int end, int shiftCount) {
    if (address != nullptr && start >= 0 && end < size && start < end) {
        std::rotate(address + start, address + end - (shiftCount % (end - start + 1)) + 1, address + end + 1);
    }
    else {
        std::cerr << "Invalid rotateMemoryRangeRight operation." << std::endl;
    }
}

/**
 * @brief Swaps adjacent memory ranges in a memory block.
 *
 * @details This function swaps adjacent memory ranges in a memory block.
 * If the address parameter is valid and the range indices are within bounds,
 * the function performs the swap. Otherwise, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param range1Start The start index of the first range to swap.
 * @param range1End The end index of the first range to swap.
 * @param range2Start The start index of the second range to swap.
 * @param range2End The end index of the second range to swap.
 */
template <typename T>
inline void MemoryManager<T>::swapAdjacentMemoryRanges(T* address, int range1Start, int range1End, int range2Start, int range2End) {
    if (address != nullptr && range1Start >= 0 && range1End < size && range1Start < range1End &&
        range2Start >= 0 && range2End < size && range2Start < range2End) {

        std::swap_ranges(address + range1Start, address + range1End + 1, address + range2Start);
    }
    else {
        std::cerr << "Invalid swapAdjacentMemoryRanges operation." << std::endl;
    }
}

/**
 * @brief Performs three-way partitioning on a memory block based on a pivot value.
 *
 * @details This function performs three-way partitioning on a memory block based on a pivot value.
 * If the address parameter is valid and the size is greater than zero, the function partitions the block.
 * It updates the lowerBound and upperBound parameters to indicate the resulting partitions.
 * If the inputs are invalid, it prints an error message.
 *
 * @param address A pointer to the start of the memory block.
 * @param size The size of the memory block.
 * @param pivotValue The pivot value for partitioning.
 * @param lowerBound Reference to the lower bound of the partition with values less than the pivot.
 * @param upperBound Reference to the upper bound of the partition with values greater than the pivot.
 */
template <typename T>
inline void MemoryManager<T>::threeWayPartition(T* address, int size, int pivotValue, int& lowerBound, int& upperBound) {
    if (address != nullptr && size > 0) {
        lowerBound = 0;
        upperBound = size - 1;

        int i = 0;
        while (i <= upperBound) {
            if (address[i] < pivotValue) {
                std::swap(address[i], address[lowerBound]);
                ++lowerBound;
                ++i;
            }
            else if (address[i] > pivotValue) {
                std::swap(address[i], address[upperBound]);
                --upperBound;
            }
            else {
                ++i;
            }
        }
    }
    else {
        std::cerr << "Invalid threeWayPartition operation." << std::endl;
    }
}

/**
 * @brief Computes the union of two sorted memory blocks.
 *
 * @details This function computes the union of two sorted memory blocks, removing duplicate elements.
 * If the input blocks are valid (non-null and sizes greater than zero), the function returns a new memory block
 * containing the union and sets the unionSize parameter to the size of the union. If the inputs are invalid,
 * it prints an error message, sets unionSize to 0, and returns a null pointer.
 *
 * @param block1 A pointer to the first sorted memory block.
 * @param size1 The size of the first memory block.
 * @param block2 A pointer to the second sorted memory block.
 * @param size2 The size of the second memory block.
 * @param unionSize Reference to store the size of the resulting union.
 * @return A pointer to the memory block containing the union, or nullptr if the operation is invalid.
 */
template <typename T>
inline T* MemoryManager<T>::unionSortedMemory(const T* block1, int size1, const T* block2, int size2, int& unionSize) {
    if (block1 == nullptr || block2 == nullptr || size1 <= 0 || size2 <= 0) {
        std::cerr << "Invalid unionSortedMemory operation." << std::endl;
        unionSize = 0;
        return nullptr;
    }

    std::vector<int> result;
    std::merge(block1, block1 + size1, block2, block2 + size2, std::back_inserter(result));
    result.erase(std::unique(result.begin(), result.end()), result.end());

    unionSize = static_cast<int>(result.size());
    T* unionMemory = new int[unionSize];
    std::copy(result.begin(), result.end(), unionMemory);

    return unionMemory;
}

/**
 * @brief Computes the difference of two sorted memory blocks.
 *
 * @details This function computes the difference of two sorted memory blocks, removing common elements.
 * If the input blocks are valid (non-null and sizes greater than zero), the function returns a new memory block
 * containing the difference and sets the differenceSize parameter to the size of the difference.
 * If the inputs are invalid, it prints an error message, sets differenceSize to 0, and returns a null pointer.
 *
 * @param block1 A pointer to the first sorted memory block.
 * @param size1 The size of the first memory block.
 * @param block2 A pointer to the second sorted memory block.
 * @param size2 The size of the second memory block.
 * @param differenceSize Reference to store the size of the resulting difference.
 * @return A pointer to the memory block containing the difference, or nullptr if the operation is invalid.
 */
template <typename T>
inline T* MemoryManager<T>::differenceSortedMemory(const T* block1, int size1, const T* block2, int size2, int& differenceSize) {
    if (block1 == nullptr || block2 == nullptr || size1 <= 0 || size2 <= 0) {
        std::cerr << "Invalid differenceSortedMemory operation." << std::endl;
        differenceSize = 0;
        return nullptr;
    }

    std::vector<int> result;
    std::set_difference(block1, block1 + size1, block2, block2 + size2, std::back_inserter(result));

    differenceSize = static_cast<int>(result.size());
    T* differenceMemory = new int[differenceSize];
    std::copy(result.begin(), result.end(), differenceMemory);

    return differenceMemory;
}

/**
 * @brief Computes the symmetric difference of two sorted memory blocks.
 *
 * @details This function computes the symmetric difference of two sorted memory blocks,
 * removing elements common to both blocks. If the input blocks are valid (non-null and sizes greater than zero),
 * the function returns a new memory block containing the symmetric difference and sets the symDiffSize parameter
 * to the size of the symmetric difference. If the inputs are invalid, it prints an error message,
 * sets symDiffSize to 0, and returns a null pointer.
 *
 * @param block1 A pointer to the first sorted memory block.
 * @param size1 The size of the first memory block.
 * @param block2 A pointer to the second sorted memory block.
 * @param size2 The size of the second memory block.
 * @param symDiffSize Reference to store the size of the resulting symmetric difference.
 * @return A pointer to the memory block containing the symmetric difference, or nullptr if the operation is invalid.
 */
template <typename T>
inline T* MemoryManager<T>::symmetricDifferenceSortedMemory(const T* block1, int size1, const T* block2, int size2, int& symDiffSize) {
    if (block1 == nullptr || block2 == nullptr || size1 <= 0 || size2 <= 0) {
        std::cerr << "Invalid symmetricDifferenceSortedMemory operation." << std::endl;
        symDiffSize = 0;
        return nullptr;
    }

    std::vector<int> result;
    std::set_symmetric_difference(block1, block1 + size1, block2, block2 + size2, std::back_inserter(result));

    symDiffSize = static_cast<int>(result.size());
    T* symDiffMemory = new int[symDiffSize];
    std::copy(result.begin(), result.end(), symDiffMemory);

    return symDiffMemory;
}

/**
 * @brief Checks if a memory block is a subset of another sorted memory block.
 *
 * @details This function checks if the memory block 'potentialSubset' is a subset of the sorted memory block 'set'.
 * If both blocks are valid (non-null and sizes greater than zero), the function returns true if 'potentialSubset'
 * is a subset of 'set'; otherwise, it returns false. If the inputs are invalid, it prints an error message and
 * returns false.
 *
 * @param potentialSubset A pointer to the potential subset memory block.
 * @param subsetSize The size of the potential subset memory block.
 * @param set A pointer to the sorted memory block.
 * @param setSize The size of the sorted memory block.
 * @return True if 'potentialSubset' is a subset of 'set', false otherwise or in case of invalid inputs.
 */
template <typename T>
inline bool MemoryManager<T>::isSubsetSortedMemory(const T* potentialSubset, int subsetSize, const T* set, int setSize) {
    if (potentialSubset == nullptr || subsetSize <= 0 || set == nullptr || setSize <= 0) {
        std::cerr << "Invalid isSubsetSortedMemory operation." << std::endl;
        return false;
    }

    return std::includes(set, set + setSize, potentialSubset, potentialSubset + subsetSize);
}

/**
 * @brief Checks if a memory block is strictly increasing.
 *
 * @details This function checks if the memory block 'address' is strictly increasing.
 * If the block is valid (non-null and size greater than zero), the function returns true if the elements
 * are strictly increasing; otherwise, it returns false. If the input is invalid, it prints an error message
 * and returns false.
 *
 * @param address A pointer to the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is strictly increasing, false otherwise or in case of invalid input.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryStrictlyIncreasing(const T* address, int size) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryStrictlyIncreasing operation." << std::endl;
        return false;
    }

    return std::is_sorted(address, address + size) && std::adjacent_find(address, address + size, std::greater<int>()) == address + size;
}

/**
 * @brief Checks if a memory block is strictly decreasing.
 *
 * @details This function checks if the memory block 'address' is strictly decreasing.
 * If the block is valid (non-null and size greater than zero), the function returns true if the elements
 * are strictly decreasing; otherwise, it returns false. If the input is invalid, it prints an error message
 * and returns false.
 *
 * @param address A pointer to the memory block.
 * @param size The size of the memory block.
 * @return True if the memory block is strictly decreasing, false otherwise or in case of invalid input.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryStrictlyDecreasing(const T* address, int size) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryStrictlyDecreasing operation." << std::endl;
        return false;
    }

    return std::is_sorted(address, address + size, std::greater<int>()) && std::adjacent_find(address, address + size, std::less<int>()) == address + size;
}

/**
 * @brief Checks if a memory block has a plateau.
 *
 * @details This function checks if the memory block 'address' has a plateau,
 * i.e., a contiguous sequence of equal values. If the block is valid (non-null and size greater than zero),
 * the function returns true if there is a plateau, and it sets 'plateauStart' and 'plateauEnd' to the start and end
 * indices of the plateau. If there is no plateau, both indices are set to -1. If the input is invalid, it prints
 * an error message and returns false.
 *
 * @param address A pointer to the memory block.
 * @param size The size of the memory block.
 * @param plateauStart Reference to store the start index of the plateau.
 * @param plateauEnd Reference to store the end index of the plateau.
 * @return True if the memory block has a plateau, false otherwise or in case of invalid input.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryPlateau(const T* address, int size, int& plateauStart, int& plateauEnd) {
    if (address == nullptr || size <= 0) {
        std::cerr << "Invalid isMemoryPlateau operation." << std::endl;
        return false;
    }

    plateauStart = plateauEnd = -1;

    for (int i = 1; i < size; ++i) {
        if (address[i] == address[i - 1]) {
            if (plateauStart == -1) {
                plateauStart = i - 1;
            }
            plateauEnd = i;
        }
        else if (plateauEnd != -1) {
            break;
        }
    }

    return plateauStart != -1 && plateauEnd != -1;
}

/**
 * @brief Checks if a memory block is a subsequence of another memory block.
 *
 * @details This function checks if the memory block 'subsequence' is a subsequence of the memory block 'sequence'.
 * If both blocks are valid (non-null and sizes greater than zero), the function returns true if 'subsequence'
 * is a subsequence of 'sequence'; otherwise, it returns false. If the inputs are invalid, it prints an error message
 * and returns false.
 *
 * @param sequence A pointer to the sequence memory block.
 * @param seqSize The size of the sequence memory block.
 * @param subsequence A pointer to the subsequence memory block.
 * @param subseqSize The size of the subsequence memory block.
 * @return True if 'subsequence' is a subsequence of 'sequence', false otherwise or in case of invalid inputs.
 */
template <typename T>
inline bool MemoryManager<T>::isSubsequence(const T* sequence, int seqSize, const T* subsequence, int subseqSize) {
    if (sequence == nullptr || subsequence == nullptr || seqSize < subseqSize || subseqSize <= 0) {
        std::cerr << "Invalid isSubsequence operation." << std::endl;
        return false;
    }

    return std::search(sequence, sequence + seqSize, subsequence, subsequence + subseqSize) != sequence + seqSize;
}

/**
 * @brief Reverses portions of a memory block based on subblock sizes.
 *
 * @details This function reverses portions of the memory block 'address' based on the given subblock sizes.
 * If the block and subblock size array are valid (non-null and sizes greater than zero), the function performs
 * the reverse operation, preserving the order of subblocks. If the inputs are invalid, it prints an error message
 * and does nothing.
 *
 * @param address A pointer to the memory block.
 * @param size The size of the memory block.
 * @param subblockSizes An array containing the sizes of subblocks to be reversed.
 * @param numSubblocks The number of subblocks.
 */
template <typename T>
inline void MemoryManager<T>::reverseMemoryWithPreservation(T* address, int size, const int* subblockSizes, int numSubblocks) {
    if (address == nullptr || size <= 0 || subblockSizes == nullptr || numSubblocks <= 0) {
        std::cerr << "Invalid reverseMemoryWithPreservation operation." << std::endl;
        return;
    }

    int start = 0;
    for (int i = 0; i < numSubblocks; ++i) {
        int subblockSize = subblockSizes[i];
        if (start + subblockSize <= size) {
            std::reverse(address + start, address + start + subblockSize);
            start += subblockSize;
        }
        else {
            std::cerr << "Invalid subblock size at index " << i << "." << std::endl;
            return;
        }
    }
}

/**
 * @brief Checks if a memory block forms a mountain shape.
 *
 * @details This function checks if the memory block 'address' forms a mountain shape,
 * i.e., has a peak greater than its neighbors. If the block is valid (non-null and size greater than two),
 * the function returns true if a mountain is found, and it sets 'peakIndex' to the index of the peak.
 * If no mountain is found, 'peakIndex' is set to -1. If the input is invalid, it prints an error message
 * and returns false.
 *
 * @param address A pointer to the memory block.
 * @param size The size of the memory block.
 * @param peakIndex Reference to store the index of the peak.
 * @return True if the memory block forms a mountain shape, false otherwise or in case of invalid input.
 */
template <typename T>
inline bool MemoryManager<T>::isMemoryMountain(const T* address, int size, int& peakIndex) {
    if (address == nullptr || size <= 2) {
        std::cerr << "Invalid isMemoryMountain operation." << std::endl;
        return false;
    }

    peakIndex = -1;

    for (int i = 1; i < size - 1; ++i) {
        if (address[i] > address[i - 1] && address[i] > address[i + 1]) {
            peakIndex = i;
            return true;
        }
    }

    return false;
}

#endif // PTRX_IMPL_H