/*****************************************************************//**
 * \file   ItemCollection.hpp
 * \brief  A header file for the ItemCollection class, wrapping all "AEGP_ItemCollectionH" related functions
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef ITEMCOLLECTION_HPP
#define ITEMCOLLECTION_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Collection.hpp"

namespace AE
{
class Item;
class CompItem;
class FootageItem;
class FolderItem;
/**
 * @brief A class representing a collection of items
 * *
 * This class represents a collection of items and provides methods to interact with it.
 * This is used by both Project and FolderItem classes to manage their items.
 * 
 * The goal is to provide a "Pythonic" way to interact with the collection of items, even though it's written in C++.
 * (I'll Later be binding this to Python using pybind11)
 * 
 * Really, You won't be using this class directly, but rather through the Project and FolderItem classes.
 * See Collection.hpp for more detailed documentation.
 */
class ItemCollection : public Collection<std::shared_ptr<Item>>
{
  public:
    ItemCollection() = default;
    ItemCollection(std::shared_ptr<Item> FolderItem) : baseItem(FolderItem)
    {
        m_collection = createCollection();
    }
    ItemCollection(std::vector<std::shared_ptr<Item>> items)
        : Collection(items)
    {
    }
    ~ItemCollection() = default;

    // operator
    std::shared_ptr<Item> operator[](size_t index) override
    {
        return m_collection[index];
    }
    // Provide begin and end iterators for range-based for loops
    auto begin() -> decltype(m_collection.begin())
    {
        return m_collection.begin();
    }

    auto end() -> decltype(m_collection.end()) { return m_collection.end(); }
    void append(std::shared_ptr<Item> item);

    void extend(std::vector<std::shared_ptr<Item>> items) override;

    void insert(size_t index, std::shared_ptr<Item> item) override;

    void remove(std::shared_ptr<Item> item) override;

    void pop(size_t index) override;

    void clear() override;

    std::vector<std::shared_ptr<Item>> slice(int start, int end) override;

    std::vector<std::shared_ptr<Item>> slice(int start) override;

    std::vector<std::shared_ptr<Item>> createCollection();

  private:
    std::shared_ptr<Item> baseItem;
};

} // namespace AE

#endif // ITEMCOLLECTION_HPP
