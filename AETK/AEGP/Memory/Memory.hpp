/*****************************************************************/ /**
                                                                     * \file   Memory.hpp
                                                                     * \brief  AE Memory management systems
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef AE_MEMORY_HPP
#define AE_MEMORY_HPP

#include "AETK/AEGP/Core/Allocator.hpp"
#include "AETK/Common/Common.hpp"

namespace ae
{
// Alias for std::shared_ptr that does not directly incorporate the custom
// allocator,
// but will be used in conjunction with a custom make_shared function.
template <typename T> using shared_ptr = std::shared_ptr<T>;

// A custom make_shared that uses AEGPCustomAllocator to create the object
template <typename T, typename... Args> shared_ptr<T> make_shared(Args &&...args)
{
    // Assuming AEGPCustomAllocator<T> can be default constructed or otherwise
    // obtained
    AEGPCustomAllocator<T> alloc;

    // Using the rebind mechanism to get the correct allocator type
    using alloc_traits = std::allocator_traits<AEGPCustomAllocator<T>>;
    using rebind_alloc = typename alloc_traits::template rebind_alloc<T>;
    rebind_alloc rebound_alloc(alloc);

    // Allocate and construct the object, returning a std::shared_ptr to manage
    // it
    return std::allocate_shared<T>(rebound_alloc, std::forward<Args>(args)...);
}

// Alias for std::unique_ptr that does not directly incorporate the custom
// allocator,
// but will be used in conjunction with a custom make_unique function.

template <typename T> using unique_ptr = std::unique_ptr<T>;

// A custom make_unique that uses AEGPCustomAllocator to create the object

template <typename T> using vector = std::vector<T, AEGPCustomAllocator<T>>;

template <typename Key, typename Value, typename Comparator = std::less<Key>>
using map = std::map<Key, Value, Comparator, AEGPCustomAllocator<std::pair<const Key, Value>>>;

template <typename T> using list = std::list<T, AEGPCustomAllocator<T>>;

template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>

using unordered_map = std::unordered_map<Key, AEGPCustomAllocator<std::pair<const Key, Hash>>>;

template <typename T, typename Comparator = std::less<T>> using set = std::set<T, Comparator, AEGPCustomAllocator<T>>;

template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>

using unordered_set = std::unordered_set<T, Hash, KeyEqual, AEGPCustomAllocator<T>>;
} // namespace ae

#endif // AE_MEMORY_HPP
