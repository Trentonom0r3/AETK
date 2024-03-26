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

class Item
{
  public:
    Item() : m_item(nullptr), m_itemSuite(ItemSuite9()) {}
    Item(ItemPtr item) : m_item(item), m_itemSuite(ItemSuite9()) {}
    virtual ~Item() = default;

    static std::shared_ptr<Item> activeItem();

    ItemPtr getItem() const { return m_item; }
    void setItem(ItemPtr item) { m_item = item; }

    virtual AE_ItemType itemType() { return AE_ItemType::NONE; }
    std::string typeName();

    bool isSelected();
    void setSelection(bool select, bool deselectOthers = false);
    // TODO Implement Tis

    bool isFlagSet(AE_ItemFlag flag);
    void setFlag(AE_ItemFlag flag, bool value);

    std::string name();
    void setName(const std::string &name);

    void setProxyUse(bool useProxy);

    std::shared_ptr<FolderItem> parentFolder();
    void setParentFolder(std::shared_ptr<FolderItem> folder);

    double duration();

    double currentTime(); // in seconds
    void setCurrentTime(double time); // in seconds

    std::string comment();
    void setComment(const std::string &comment);

    AE_Label label();
    void setLabel(AE_Label label);

    std::tuple<int, int> dimensions();

    double pixelAspect();

    void deleteItem();

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
