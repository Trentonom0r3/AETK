/*****************************************************************/ /**
                                                                     * \file   Allocator.hpp
                                                                     * \brief
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "AETK/Common/Common.hpp"

// Define a custom allocator class called AEGPCustomAllocator.
template <typename T> class AEGPCustomAllocator
{
  public:
    // Define type aliases for the allocator traits.
    using value_type = T;
    using pointer = T *;
    using size_type = size_t;

    // Define a default constructor for the allocator.
    AEGPCustomAllocator() noexcept {}

    // Define a copy constructor for the allocator.
    template <typename U> AEGPCustomAllocator(const AEGPCustomAllocator<U> &) noexcept {}

    // Define the allocate function, which is used to allocate memory.
    pointer allocate(size_type n)
    {
        // Calculate the size of the memory to be allocated.
        size_t size = n * sizeof(T);

        // Explicitly handle the conversion, adding a check to ensure no data loss.
        if (size > (std::numeric_limits<AEGP_MemSize>::max)())
        {
            throw std::bad_alloc(); // Or any other mechanism to signal the error
        }

        AEGP_MemHandle memHandle = nullptr;
        auto &suiteManager = SuiteManager::GetInstance();
        auto *pluginID = suiteManager.GetPluginID();

        // Use static_cast to convert size to AEGP_MemSize now that we've checked
        // for overflow.
        AEGP_MemSize safeSize = static_cast<AEGP_MemSize>(size);

        suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_NewMemHandle(*pluginID, "Custom Allocator Memory", safeSize,
                                                                         AEGP_MemFlag_CLEAR, &memHandle);

        if (!memHandle)
        {
            throw std::exception("Failed to allocate memory handle.");
        }

        void *ptr = nullptr;
        A_Err err = suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_LockMemHandle(memHandle, &ptr);
        if (err != A_Err_NONE || !ptr)
        {
            suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(memHandle);
            throw std::exception("Failed to lock memory handle.");
        }

        memHandleMap_[static_cast<pointer>(ptr)] = memHandle;
        return static_cast<pointer>(ptr);
    }

    // Define the deallocate function, which is used to deallocate memory.
    void deallocate(pointer p, size_type n)
    {
        // Find the memory handle associated with the pointer in the memHandleMap.
        auto it = memHandleMap_.find(p);

        // Check if the memory handle is found.
        if (it != memHandleMap_.end())
        {
            // Get an instance of the SuiteManager.
            auto &suiteManager = SuiteManager::GetInstance();

            // Use the AEGP Memory Suite functions AEGP_UnlockMemHandle and
            // AEGP_FreeMemHandle to unlock and free the memory handle.
            suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_UnlockMemHandle(it->second);
            suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(it->second);

            // Remove the memory handle from the memHandleMap.
            memHandleMap_.erase(it);
        }
    }

  private:
    std::unordered_map<pointer, AEGP_MemHandle> memHandleMap_; // Store the memory handles in an unordered_map.
};

// Define the equality operator for two AEGPCustomAllocator objects.
template <typename T, typename U> bool operator==(const AEGPCustomAllocator<T> &, const AEGPCustomAllocator<U> &)
{
    return true;
}

// Define the inequality operator for two AEGPCustomAllocator objects.
template <typename T, typename U> bool operator!=(const AEGPCustomAllocator<T> &, const AEGPCustomAllocator<U> &)
{
    return false;
}

#endif // ALLOCATOR_HPP
