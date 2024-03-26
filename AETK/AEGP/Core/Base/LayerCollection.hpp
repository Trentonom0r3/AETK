/*****************************************************************//**
 * \file   LayerCollection.hpp
 * \brief  LayerCollection class declaration
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef LAYERCOLLECTION_HPP
#define LAYERCOLLECTION_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Collection.hpp"

namespace AE
{
class CompItem;
class Layer;
class Item;
/**
 * @brief A class representing a collection of Layers
 * *
 * This class represents a collection of Layers and provides methods to interact
 * with it. This is used by CompItem class to manage its layers.
 *
 * The goal is to provide a "Pythonic" way to interact with the collection of
 * items, even though it's written in C++. (I'll Later be binding this to Python
 * using pybind11)
 *
 * Really, You won't be using this class directly, but rather through the
 * CompItem class. See Collection.hpp for more detailed
 * documentation.
 */
class LayerCollection : public Collection<std::shared_ptr<Layer>>
{
  public:
    LayerCollection() = default;
    LayerCollection(CompPtr comp) : baseComp(comp)
    {
        m_collection = createCollection();
    }
    LayerCollection(std::vector<std::shared_ptr<Layer>> layers) : Collection(layers) {}
    ~LayerCollection() = default;

    // operator
    //std::shared_ptr<Layer> operator[](size_t index) override { return m_collection[index]; }
    //    virtual size_t size() { return m_collection.size(); }
    size_t size() override { return m_collection.size(); }
    /**
     * \brief Get an iterator pointing to the beginning of the collection.
     *
     * \return auto An iterator pointing to the beginning of the collection.
     */
    // Provide begin and end iterators for range-based for loops
    auto begin() -> decltype(m_collection.begin())
    {
        return m_collection.begin();
    }

    auto end() -> decltype(m_collection.end()) { return m_collection.end(); }
   
    void append(std::shared_ptr<Item> item);

    void extend(std::vector<std::shared_ptr<Layer>> layers) override;

    void insert(size_t index, std::shared_ptr<Layer> layer) override;

    void remove(std::shared_ptr<Layer> layer) override;

    void pop(size_t index) override;

    void clear() override;

    std::vector<std::shared_ptr<Layer>> copy() override { return m_collection; }

    std::vector<std::shared_ptr<Layer>> slice(int start, int end) override;

    std::vector<std::shared_ptr<Layer>> slice(int start) override;
    std::vector<std::shared_ptr<Layer>> slice() override { return m_collection; }

    void reverse() override;

    void sort(std::function<bool(std::shared_ptr<Layer>, std::shared_ptr<Layer>)> compare);

    std::vector<std::shared_ptr<Layer>> createCollection();

  protected:
    CompPtr baseComp;
};

} // namespace AE

#endif // LAYERCOLLECTION_HPP
