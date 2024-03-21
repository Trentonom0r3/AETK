/*****************************************************************/ /**
                                                                     * \file
                                                                     *AEComp.hpp
                                                                     * \brief  A
                                                                     *header
                                                                     *file for
                                                                     *CompItem
                                                                     *class
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#pragma once

#ifndef AEComp_hpp
#define AEComp_hpp

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Item.hpp"
//in cpp, #include <Layer.hpp>

namespace AE
{
class Layer; // Forward declaration of Layer class
/**
 * \brief A class for representing a composition in After Effects
 *
 * This class represents a composition in After Effects. It inherits from the
 * base class Item.
 */
class CompItem : public Item
{
  public:
    /**
     * \brief Default constructor for CompItem
     */
    CompItem();

    /**
     * \brief Constructor for CompItem that takes an ItemPtr
     *
     * \param item A pointer to an Item object
     */
    CompItem(ItemPtr item) : m_item(item) { m_comp = compFromItem(); }

    /**
     * \brief Constructor for CompItem that takes a CompPtr
     *
     * \param comp A pointer to a Comp object
     */
    CompItem(CompPtr comp) : m_comp(comp) { m_item = itemFromComp(); }

    /**
     * \brief Copy constructor for CompItem
     *
     * \param comp A reference to a CompItem object to be copied
     */
    CompItem(CompItem const &comp) : m_item(comp.m_item)
    {
        m_comp = comp.m_comp;
    }

    /**
     * \brief Get the layers of the composition
     *
     * \return std::vector<Layer> A vector of Layer objects representing the
     * layers in the composition
     */
    std::vector<Layer> layers() const;

    /**
     * \brief Get the layer at the given index
     *
     * \param index The index of the layer to retrieve
     * \return std::shared_ptr<Layer> A shared pointer to the Layer object at
     * the given index
     */
    std::shared_ptr<Layer> layer(int index) const;

    /**
     * \brief Get the layer with the given name
     *
     * \param name The name of the layer to retrieve
     * \return std::shared_ptr<Layer> A shared pointer to the Layer object with
     * the given name
     */
    std::shared_ptr<Layer> layer(std::string name) const;

    /**
     * \brief Add a layer to the composition
     *
     * \param itemToAdd A shared pointer to the Item object to be added as a
     * layer \return std::shared_ptr<Layer> A shared pointer to the newly added
     * Layer object
     */
    std::shared_ptr<Layer> addLayer(std::shared_ptr<Item> itemToAdd);

    /**
     * \brief Remove a layer from the composition
     *
     * \param itemToRemove A shared pointer to the Layer object to be removed
     */
    void removeLayer(std::shared_ptr<Layer> itemToRemove);

    /**
     * \brief Remove a layer from the composition based on its index
     *
     * \param index The index of the layer to be removed
     */
    void removeLayer(int index);

    /**
     * \brief Remove a layer from the composition based on its name
     *
     * \param name The name of the layer to be removed
     */
    void removeLayer(std::string name);

    /**
     * \brief Show or hide layer names in the composition
     *
     * \param show A boolean value indicating whether to show or hide layer
     * names
     */
    void showLayerNames(bool show);

  private:
    CompPtr m_comp; // Pointer to a Comp object
    ItemPtr m_item; // Pointer to an Item object

    /**
     * \brief Get a CompPtr from an ItemPtr
     *
     * \return CompPtr A pointer to a Comp object
     */
    inline CompPtr compFromItem()
    {
        return CompSuite11().GetCompFromItem(m_item);
    }

    /**
     * \brief Get an ItemPtr from a CompPtr
     *
     * \return ItemPtr A pointer to an Item object
     */
    inline ItemPtr itemFromComp()
    {
        return CompSuite11().GetItemFromComp(m_comp);
    }
};
} // namespace AE
#endif /* AEComp_hpp */