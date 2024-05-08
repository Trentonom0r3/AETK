/*****************************************************************/ /**
                                                                     * \file   LayerCollection.hpp
                                                                     * \brief  LayerCollection class declaration
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   March 2024
                                                                     *********************************************************************/

#ifndef LAYERCOLLECTION_HPP
#define LAYERCOLLECTION_HPP

#include "AETK/AEGP/Core/Core.hpp"
#include "AETK/AEGP/Template/Collection.hpp"

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
class LayerCollection : public Collection<tk::shared_ptr<Layer>>
{
  public:
    LayerCollection() = default;
    LayerCollection(CompPtr comp) : baseComp(comp) {createCollection(); }
    LayerCollection(tk::vector<tk::shared_ptr<Layer>> layers) : Collection(layers), baseComp(CompPtr()) {}
    ~LayerCollection() = default;


    tk::shared_ptr<Layer> createTextLayer(const std::string &text, ColorVal color = {1, 1, 1, 1});

    // operator
    // tk::shared_ptr<Layer> operator[](size_t index) override { return m_collection[index]; }
    //    virtual size_t size() { return m_collection.size(); }
    size_t size() override { return m_collection.size(); }
    /**
     * \brief Get an iterator pointing to the beginning of the collection.
     *
     * \return auto An iterator pointing to the beginning of the collection.
     */
    // Provide begin and end iterators for range-based for loops
    auto begin() -> decltype(m_collection.begin()) { return m_collection.begin(); }

    auto end() -> decltype(m_collection.end()) { return m_collection.end(); }

    void append(tk::shared_ptr<Item> item);

    void extend(tk::vector<tk::shared_ptr<Layer>> layers) override;

    void insert(size_t index, tk::shared_ptr<Layer> layer) override;

    void remove(tk::shared_ptr<Layer> layer) override;

    void pop(size_t index) override;

    void clear() override;

    tk::vector<tk::shared_ptr<Layer>> copy() override { return m_collection; }

    tk::vector<tk::shared_ptr<Layer>> slice(int start, int end) override;

    tk::vector<tk::shared_ptr<Layer>> slice(int start) override;
    tk::vector<tk::shared_ptr<Layer>> slice() override { return m_collection; }

    void reverse() override;

    void sort(std::function<bool(tk::shared_ptr<Layer>, tk::shared_ptr<Layer>)> compare);

    void createCollection();

    tk::vector<tk::shared_ptr<Layer>> find(const std::function<bool(tk::shared_ptr<Layer>)> &predicate);

  protected:
    CompPtr baseComp;
};

#endif // LAYERCOLLECTION_HPP
