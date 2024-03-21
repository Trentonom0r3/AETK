/*****************************************************************//**
 * \file   AEMemory.hpp
 * \brief  A header file that defines various STL containers using a custom
 * Allocator for After Effects Memory Management.
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef AEMEMORY_HPP
#define AEMEMORY_HPP

#include "AETK/AEGP/Memory/AEAllocator.hpp"

/**
 * \namespace AE
 * \brief Namespace for various pre-defined STL containers using a custom
 * allocator.
 */
namespace AE
{
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
	// Assuming AEAllocator<T> can be default constructed or otherwise obtained
	AEAllocator<T> alloc;

	// Using the rebind mechanism to get the correct allocator type
	using alloc_traits = std::allocator_traits<AEAllocator<T>>;
	using rebind_alloc = typename alloc_traits::template rebind_alloc<T>;
	rebind_alloc rebound_alloc(alloc);

	// Allocate and construct the object, returning a std::unique_ptr to manage
	// it
	return std::allocate_unique<T>(rebound_alloc, std::forward<Args>(args)...);
}
/**
 * \brief Custom make_shared function that uses AEAllocator to create the
 * object. \tparam T The type of the object to be created. \tparam Args The
 * types of the arguments to be passed to the constructor of the object. \param
 * args The arguments to be passed to the constructor of the object. \return
 * std::shared_ptr<T> A shared pointer to the created object.
 *
 * This function creates an object of type T using the AEAllocator<T> allocator
 * and returns a std::shared_ptr<T> to manage the object.
 */
template <typename T, typename... Args>
std::shared_ptr<T> make_shared(Args &&...args)
{
    // Assuming AEAllocator<T> can be default constructed or otherwise obtained
    AEAllocator<T> alloc;

    // Using the rebind mechanism to get the correct allocator type
    using alloc_traits = std::allocator_traits<AEAllocator<T>>;
    using rebind_alloc = typename alloc_traits::template rebind_alloc<T>;
    rebind_alloc rebound_alloc(alloc);

    // Allocate and construct the object, returning a std::shared_ptr to manage
    // it
    return std::allocate_shared<T>(rebound_alloc, std::forward<Args>(args)...);
}

/**
 * \brief Alias for std::vector using AEAllocator.
 * \tparam T The type of the elements in the vector.
 */
template <typename T> using vector = std::vector<T, AEAllocator<T>>;

/**
 * \brief Alias for std::map using AEAllocator.
 * \tparam Key The type of the keys in the map.
 * \tparam Value The type of the values in the map.
 * \tparam Comparator The type of the comparator used to compare keys.
 */
template <typename Key, typename Value, typename Comparator = std::less<Key>>
using map =
    std::map<Key, Value, Comparator, AEAllocator<std::pair<const Key, Value>>>;

/**
 * \brief Alias for std::list using AEAllocator.
 * \tparam T The type of the elements in the list.
 */
template <typename T> using list = std::list<T, AEAllocator<T>>;

/**
 * \brief Alias for std::unordered_map using AEAllocator.
 * \tparam Key The type of the keys in the unordered map.
 * \tparam Hash The type of the hash function used to hash keys.
 * \tparam KeyEqual The type of the key equality function used to compare keys
 * for equality.
 */
template <typename Key, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
using unordered_map =
    std::unordered_map<Key, AEAllocator<std::pair<const Key, Hash>>>;

} // namespace AE

#endif // AEMEMORY_HPP