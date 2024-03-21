/*****************************************************************/ /**
                                                                     * \file
                                                                     *AEItem.hpp
                                                                     * \brief
                                                                     *After
                                                                     *Effects
                                                                     *Item class
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef AEITEM_HPP
#define AEITEM_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

namespace AE
{

/**
 * \class Item
 * \brief Represents an After Effects item.
 */
class Item
{
  public:
    /**
     * \brief Default constructor.
     */
    Item(){};

    /**
     * \brief Constructor that takes an existing item pointer.
     * \param item The item pointer.
     */
    Item(ItemPtr item) : m_item(item){};

    /**
     * \brief Destructor.
     */
    virtual ~Item(){};

    /**
     * \brief Returns the active item.
     * \return The active item.
     */
    static Item ActiveItem();

    /**
     * \brief Selects the item.
     * \param deselectOthers Flag indicating whether to deselect other items.
     */
    void Select(bool deselectOthers = true);

    /**
     * \brief Deselects the item.
     */
    void Deselect();

    /**
     * \brief Checks if the item is selected.
     * \return True if the item is selected, false otherwise.
     */
    bool IsSelected() const;

    /**
     * \brief Returns the name of the item.
     * \return The name of the item.
     */
    std::string Name() const;

    /**
     * \brief Returns the dimensions of the item.
     * \return A tuple containing the width and height of the item.
     */
    std::tuple<int, int> Dimensions() const;

    /**
     * \brief Returns the width of the item.
     * \return The width of the item.
     */
    int Width() const;

    /**
     * \brief Returns the height of the item.
     * \return The height of the item.
     */
    int Height() const;

    /**
     * \brief Deletes the item.
     */
    void Delete();

    /**
     * \brief Checks if the item is missing.
     * \return True if the item is missing, false otherwise.
     */
    bool Missing() const;

    /**
     * \brief Checks if the item has a proxy.
     * \return True if the item has a proxy, false otherwise.
     */
    bool HasProxy() const;

    /**
     * \brief Checks if the item is using a proxy.
     * \return True if the item is using a proxy, false otherwise.
     */
    bool UsingProxy() const;

    /**
     * \brief Checks if the item is missing a proxy.
     * \return True if the item is missing a proxy, false otherwise.
     */
    bool MissingProxy() const;

    /**
     * \brief Checks if the item has video.
     * \return True if the item has video, false otherwise.
     */
    bool HasVideo() const;

    /**
     * \brief Checks if the item has audio.
     * \return True if the item has audio, false otherwise.
     */
    bool HasAudio() const;

    /**
     * \brief Checks if the item is a still image.
     * \return True if the item is a still image, false otherwise.
     */
    bool Still() const;

    /**
     * \brief Checks if the item has active audio.
     * \return True if the item has active audio, false otherwise.
     */
    bool ActiveAudio() const;

    /**
     * \brief Returns the duration of the item.
     * \return The duration of the item.
     */
    double Duration() const;

    /**
     * \brief Returns the current time of the item.
     * \return The current time of the item.
     */
    double Time() const;

  private:
    ItemPtr m_item;         ///< The item pointer.
    ItemSuite9 m_itemSuite; ///< The item suite.
};

} // namespace AE

#endif /* AEITEM_HPP */