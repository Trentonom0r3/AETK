/*****************************************************************/ /**
                                                                     * \file
                                                                     *Item.hpp
                                                                     * \brief  A
                                                                     *header
                                                                     *file for
                                                                     *the Item
                                                                     *class,
                                                                     *wrapping
                                                                     *all
                                                                     *"AEGP_ItemH"
                                                                     *related
                                                                     *functions
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef ITEM_HPP
#define ITEM_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Misc.hpp"

namespace AE
{
class FolderItem;
class CompItem;
class FootageItem;
class ItemCollection;
class Layer;
class LayerCollection;

/**
 * Item class is a wrapper for AEGP_ItemH, and its associated functions
 */
class Item
{
  public:
    Item() : m_item(ItemPtr()), m_itemSuite(ItemSuite9()) {}
    Item(ItemPtr item) : m_item(item), m_itemSuite(ItemSuite9()) {}
    virtual ~Item() = default;

    static std::shared_ptr<Item> activeItem(); /*Gets the Active Item. Typically a CompItem*/

    ItemPtr getItem() const { return m_item; }
    void setItem(ItemPtr item) { m_item = item; }

    virtual AE_ItemType itemType() { return AE_ItemType::NONE; } 
    std::string typeName(); // Returns the type of the item as a string

    bool isSelected(); // Returns true if the item is selected
    void setSelection(bool select, bool deselectOthers = false); // Selects or deselects the item
    // TODO Implement Tis

    bool Missing();
    bool HasProxy();
    bool UsingProxy();
    bool MissingProxy();
    bool HasVideo();
    bool HasAudio();
    bool Still();
    bool HasActiveAudio();

    std::string name(); // Returns the name of the item
    void setName(const std::string &name); // Sets the name of the item

    void setProxyUse(bool useProxy); // Sets the use of proxy for the item

    std::shared_ptr<FolderItem> parentFolder(); // Returns the parent folder of the item
    void setParentFolder(std::shared_ptr<FolderItem> folder); // Sets the parent folder of the item

    double duration(); // Returns the duration of the item in seconds

    double currentTime(); // in seconds 
    void setCurrentTime(double time); // in seconds

    std::string comment(); // Returns the comment of the item
    void setComment(const std::string &comment); // Sets the comment of the item

    AE_Label label(); // Returns the label of the item
    void setLabel(AE_Label label); // Sets the label of the item

    std::tuple<int, int> dimensions(); // Returns the dimensions of the item

    double pixelAspect(); // Returns the pixel aspect ratio of the item

    void deleteItem(); // Deletes the item

  protected:
    ItemPtr m_item;
    ItemSuite9 m_itemSuite;
};

class FolderItem : public Item
{
  public:
    FolderItem() : Item() {}
    FolderItem(ItemPtr item) : Item(item) {}
    static FolderItem create(const std::string &name,
               std::shared_ptr<FolderItem> parentFolder = nullptr);
    AE_ItemType itemType() override { return AE_ItemType::FOLDER; }

    std::shared_ptr<ItemCollection> children();
};

class CompItem : public Item
{
  public:
    CompItem() : Item(), m_compSuite(CompSuite11()) {}
    CompItem(ItemPtr item)
        : Item(item), m_compSuite(CompSuite11()),
          m_comp(m_compSuite.GetCompFromItem(item))
    {
    }
    CompItem(CompPtr comp) : m_comp(comp), m_compSuite(CompSuite11()) {}

    CompPtr getComp() { return m_comp; }
    static CompItem mostRecent();
    static CompItem create(const std::string &name, int width, int height,
                           double pixelAspect, double duration,
                           double frameRate,
                           std::shared_ptr<FolderItem> = nullptr);

    AE_ItemType itemType() override { return AE_ItemType::COMP; }

    bool isFlagSet(AE_CompFlag flag);
    void setFlag(AE_CompFlag flag, bool value);

    std::shared_ptr<LayerCollection> layers();

    std::tuple<short, short> downsampleFactor();
    void setDownsampleFactor(short x, short y);

    ColorVal backgroundColor();
    void setBackgroundColor(ColorVal color);

    // AE_CompFlags, need to separate them
    bool showLayerNameorSourceName();
    void setShowLayerNameorSourceName(bool show);

    bool showBlendModes();
    void setShowBlendModes(bool show);

    double frameRate();
    void setFrameRate(double rate);

  private:
    CompSuite11 m_compSuite;
    CompPtr m_comp;
};

class FootageItem : public Item
{
  public:
    FootageItem() : Item(), m_footageSuite(FootageSuite5()) {}
    FootageItem(ItemPtr item)
        : Item(item), m_footageSuite(FootageSuite5()),
          m_footage(m_footageSuite.getMainFootageFromItem(item))
    {
    }
    static FootageItem create(std::string path, std::string name);
    // ca check on if its a string or vector, folder, list of files, single
    // file, etc.
    static FootageItem createPlaceholder(const std::string &path, int width,
                                         int height, double duration,
                                         AE_Platform plat = AE_Platform::WIN);
    static FootageItem createSolid(const std::string &name, int width,
                                   int height, ColorVal color);

    AE_ItemType itemType() override { return AE_ItemType::FOOTAGE; }

    std::tuple<A_long, A_long> numFiles() ;
    std::string path(int frameNum = 0, int index = 0) ;

    void setProxy(std::shared_ptr<FootageItem> footage);
    void replaceFootage(std::shared_ptr<FootageItem> footage);
    void replaceFromPath(std::string path);

  private:
    FootageSuite5 m_footageSuite;
    FootagePtr m_footage;
};

} // namespace AE

class ItemFactory
{
    public:
    inline static std::shared_ptr<AE::Item> createItem(ItemPtr item) {
        AE_ItemType type = ItemSuite9().GetItemType(item);
        switch (type) {
			case AE_ItemType::FOLDER:
				return std::make_shared<AE::FolderItem>(item);
			case AE_ItemType::COMP:
				return std::make_shared<AE::CompItem>(item);
			case AE_ItemType::FOOTAGE:
				return std::make_shared<AE::FootageItem>(item);
			default:
				return std::make_shared<AE::Item>(item);
                }
    }

};
#endif // ITEM_HPP
