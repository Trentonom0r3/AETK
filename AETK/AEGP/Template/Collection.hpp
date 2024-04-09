/*****************************************************************/ /**
                                                                     * \file
                                                                     *Collection.hpp
                                                                     * \brief  A
                                                                     *class to
                                                                     *represent
                                                                     *a
                                                                     *collection
                                                                     *of items
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "AETK/AEGP/Core/Core.hpp"

/**
 * \class Collection
 * \brief A class to represent a collection of items.
 *
 * This class provides various methods to manipulate and perform operations on a
 * collection of items. It supports functionalities such as appending,
 * extending, inserting, removing, popping, clearing, reversing, sorting, and
 * more.
 *
 * \tparam T The type of items in the collection.
 */
template <typename T> class Collection
{
  public:
    /**
     * \brief Default constructor.
     */
    Collection() = default;

    /**
     * \brief Constructor that initializes the collection with the given items.
     *
     * \param collection The initial collection of items.
     */
    Collection(tk::vector<T> collection) : m_collection(collection) {}

    /**
     * \brief Destructor.
     */
    ~Collection() = default;

    /**
     * \brief Get the collection of items.
     *
     * \return std::vector<T> The collection of items.
     */
    tk::vector<T> GetCollection() { return m_collection; }

    /**
     * \brief Set the collection of items.
     *
     * \param collection The new collection of items.
     */
    void SetCollection(tk::vector<T> collection) { m_collection = collection; }

    /**
     * \brief Get the size of the collection.
     *
     * \return size_t The size of the collection.
     */
    virtual size_t size() { return m_collection.size(); }

    /**
     * \brief Get the item at the specified index.
     *
     * \param index The index of the item.
     * \return T The item at the specified index.
     */
    virtual T operator[](size_t index) { return m_collection[index]; }

    /**
     * \brief Append an item to the end of the collection.
     *
     * \param item The item to be appended.
     */
    // virtual void append(T item) { m_collection.push_back(item); }

    /**
     * \brief Extend the collection by appending multiple items.
     *
     * \param items The items to be appended.
     */
    virtual void extend(tk::vector<T> items) { m_collection.insert(m_collection.end(), items.begin(), items.end()); }

    /**
     * \brief Insert an item at the specified index.
     *
     * \param index The index at which the item should be inserted.
     * \param item The item to be inserted.
     */
    virtual void insert(size_t index, T item) { m_collection.insert(m_collection.begin() + index, item); }

    /**
     * \brief Remove the first occurrence of an item from the collection.
     *
     * \param item The item to be removed.
     */
    virtual void remove(T item)
    {
        m_collection.erase(std::remove(m_collection.begin(), m_collection.end(), item), m_collection.end());
    }

    /**
     * \brief Remove the item at the specified index.
     *
     * \param index The index of the item to be removed.
     */
    virtual void pop(size_t index) { m_collection.erase(m_collection.begin() + index); }

    /**
     * \brief Clear the collection, removing all items.
     */
    virtual void clear() { m_collection.clear(); }

    /**
     * \brief Get the index of the first occurrence of an item in the
     * collection.
     *
     * \param item The item to search for.
     * \return size_t The index of the item, or -1 if not found.
     */
    virtual size_t index(T item)
    {
        return std::distance(m_collection.begin(), std::find(m_collection.begin(), m_collection.end(), item));
    }

    /**
     * \brief Check if the collection contains a specific item.
     *
     * \param item The item to search for.
     * \return bool True if the item is found, false otherwise.
     */
    virtual bool contains(T item)
    {
        return std::find(m_collection.begin(), m_collection.end(), item) != m_collection.end();
    }

    /**
     * \brief Create a copy of the collection.
     *
     * \return std::vector<T> A copy of the collection.
     */
    virtual tk::vector<T> copy() { return m_collection; }

    /**
     * \brief Get a slice of the collection from the specified start index to
     * the specified end index.
     *
     * \param start The start index of the slice.
     * \param end The end index of the slice.
     * \return std::vector<T> A slice of the collection.
     */
    virtual tk::vector<T> slice(int start, int end)
    {
        return tk::vector<T>(m_collection.begin() + start, m_collection.begin() + end);
    }

    /**
     * \brief Get a slice of the collection from the specified start index to
     * the end of the collection.
     *
     * \param start The start index of the slice.
     * \return std::vector<T> A slice of the collection.
     */
    virtual tk::vector<T> slice(int start) { return tk::vector<T>(m_collection.begin() + start, m_collection.end()); }

    /**
     * \brief Get a slice of the entire collection.
     *
     * \return std::vector<T> A slice of the collection.
     */
    virtual tk::vector<T> slice() { return m_collection; }

    /**
     * \brief Reverse the order of the items in the collection.
     */
    virtual void reverse() { std::reverse(m_collection.begin(), m_collection.end()); }

    /**
     * \brief Sort the items in the collection in ascending order.
     */
    virtual void sort() { std::sort(m_collection.begin(), m_collection.end()); }

    /**
     * \brief Sort the items in the collection using a custom comparison
     * function.
     *
     * \param compare The comparison function to be used for sorting.
     */
    virtual void sort(std::function<bool(T, T)> compare)
    {
        std::sort(m_collection.begin(), m_collection.end(), compare);
    }

  protected:
    tk::vector<T> m_collection; /**< The collection of items. */
};

#endif // COLLECTION_HPP