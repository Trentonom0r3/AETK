/*****************************************************************//**
 * \file   AEAllocator.hpp
 * \brief  AEAllocator is a custom allocator that uses the After Effects'
 * Memory Suite to allocate and deallocate memory in standard library containers.
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/
#ifndef AEMEMORY_H
#define AEMEMORY_H

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"


/**
 * \brief AEAllocator is a custom allocator that uses the After Effects' memory
 * suites to allocate and deallocate memory.
 *
 * Doing so allows the user to use the standard library containers with the
 * custom allocator, and the memory will be allocated and deallocated using AE's
 * memory, potentially improving performance and reducing memory fragmentation.
 *
 * \param T The type of the elements to be allocated.
 * \Usage The AEAllocator can be used with the standard library containers, such
 * as std::vector, std::list, and std::map. \Example The following example
 * demonstrates how to use the AEAllocator with a std::vector. #include
 * <AEMemory.h>
 *
 *     template <typename T>
 *     using vector = std::vector<T, AEAllocator<T>>;
 */
template <typename T>
class AEAllocator {
 public:
  // Define type aliases for the allocator traits.
  using value_type = T;
  using pointer = T*;
  using size_type = size_t;

  // Define a default constructor for the allocator.
  AEAllocator() noexcept {}

  // Define a copy constructor for the allocator.
  template <typename U>
  AEAllocator(const AEAllocator<U>&) noexcept {}

  // Define the allocate function, which is used to allocate memory.
  pointer allocate(size_type n) {
    // Calculate the size of the memory to be allocated.
    size_t size = n * sizeof(T);

    // Explicitly handle the conversion, adding a check to ensure no data loss.
    if (size > (std::numeric_limits<AEGP_MemSize>::max)()) {
      throw std::bad_alloc();  // Or any other mechanism to signal the error
    }

    // Use static_cast to convert size to AEGP_MemSize now that we've checked
    // for overflow.
    AEGP_MemSize safeSize = static_cast<AEGP_MemSize>(size);

    MemHandlePtr memHandle =
        MemorySuite1().NewMemHandle("AEAllocator", safeSize, AE_MemFlag::NONE);

    if (!memHandle) {
      throw AEException("Failed to allocate memory handle.");
    }

    void* ptr = nullptr;
    // Inside AEGPCustomAllocator::allocate
    try {
      ptr = MemorySuite1().LockMemHandle(memHandle);  // Assume this returns the
                                                      // locked pointer directly
    } catch (...) {
      MemorySuite1().FreeMemHandle(memHandle);
      throw;  // Re-throw the current exception
              // without having to catch a specific
              // one
    }

    memHandleMap_[static_cast<pointer>(ptr)] = memHandle;
    return static_cast<pointer>(ptr);
  }

  // Define the deallocate function, which is used
  // to deallocate memory.
  void deallocate(pointer p, size_type n) {
    // Find the memory handle associated with the
    // pointer in the memHandleMap.
    auto it = memHandleMap_.find(p);

    // Check if the memory handle is found.
    if (it != memHandleMap_.end()) {
      // Get an instance of the Suites
      MemorySuite1().UnlockMemHandle(it->second);
      MemorySuite1().FreeMemHandle(it->second);

      // Remove the memory handle from the
      // memHandleMap.
      memHandleMap_.erase(it);
    }
  }

 private:
  std::unordered_map<pointer, MemHandlePtr>
      memHandleMap_;  // Store the memory handles
                      // in an unordered_map.
};

// Define the equality operator for two AEGPCustomAllocator objects.
template <typename T, typename U>
bool operator==(const AEAllocator<T>&, const AEAllocator<U>&) {
  return true;
};

// Define the inequality operator for two AEGPCustomAllocator objects.
template <typename T, typename U>
bool operator!=(const AEAllocator<T>&, const AEAllocator<U>&) {
  return false;
};

#endif  // AEMEMORY_H
