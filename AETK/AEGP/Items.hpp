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

#include <AETK/AEGP/Core/Core.hpp>

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
    Item() : m_item(ItemPtr()) {}
    Item(ItemPtr item) : m_item(item) {}
    virtual ~Item() = default;

    static tk::shared_ptr<Item> activeItem(); /*Gets the Active Item. Typically a CompItem*/

    ItemPtr getItem() const { return m_item; }
    void setItem(ItemPtr item) { m_item = item; }

    virtual ItemType itemType() { return ItemType::NONE; }
    std::string typeName(); // Returns the type of the item as a string

    bool isSelected();                                           // Returns true if the item is selected
    void setSelection(bool select, bool deselectOthers = false); // Selects or deselects the item
    // TODO Implement Tis

    bool Missing();        // Returns true if the item is missing
    bool HasProxy();       // Returns true if the item has a proxy
    bool UsingProxy();     // Returns true if the item is using a proxy
    bool MissingProxy();   // Returns true if the item is missing a proxy
    bool HasVideo();       // Returns true if the item has video
    bool HasAudio();       // Returns true if the item has audio
    bool Still();          // Returns true if the item is a still
    bool HasActiveAudio(); // Returns true if the item has active audio

    std::string name();                    // Returns the name of the item
    void setName(const std::string &name); // Sets the name of the item

    void setProxyUse(bool useProxy); // Sets the use of proxy for the item

    tk::shared_ptr<Item> parentFolder();               // Returns the parent folder of the item
    void setParentFolder(tk::shared_ptr<Item> folder); // Sets the parent folder of the item

    double duration(); // Returns the duration of the item in seconds

    double currentTime();             // in seconds
    void setCurrentTime(double time); // in seconds

    std::string comment();                       // Returns the comment of the item
    void setComment(const std::string &comment); // Sets the comment of the item

    Label label();              // Returns the label of the item
    void setLabel(Label label); // Sets the label of the item

    std::tuple<int, int> dimensions(); // Returns the dimensions of the item

    double pixelAspect(); // Returns the pixel aspect ratio of the item

    void deleteItem(); // Deletes the item

  protected:
    ItemPtr m_item;
};

class FolderItem : public Item
{
  public:
    FolderItem() : Item() {}
    FolderItem(ItemPtr item) : Item(item) {}
    static FolderItem create(const std::string &name, tk::shared_ptr<Item> parentFolder = nullptr);
    ItemType itemType() override { return ItemType::FOLDER; }

    tk::shared_ptr<ItemCollection> children(); // Returns the children of the folder

    private:
        tk::shared_ptr<ItemCollection> m_children;
};

class CompItem : public Item
{
  public:
    CompItem() : Item() {}
    CompItem(ItemPtr item) : Item(item), m_comp(CompSuite().GetCompFromItem(item)) {}
    CompItem(CompPtr comp) : m_comp(comp), Item(CompSuite().GetItemFromComp(comp)) {}

    CompPtr getComp() { return m_comp; }
    static CompItem mostRecent(); // Returns the most recent comp
    static CompItem create(const std::string &name, int width, int height, double pixelAspect, double duration,
                           double frameRate, tk::shared_ptr<Item> parent = nullptr); // Creates a new comp

    ItemType itemType() override { return ItemType::COMP; }

    bool isFlagSet(CompFlag flag);           // Returns true if the flag is set
    void setFlag(CompFlag flag, bool value); // Sets the flag

    tk::shared_ptr<LayerCollection> layers();

    DownsampleFactor downsampleFactor();            // Returns the downsample factor
    void setDownsampleFactor(DownsampleFactor dsf); // Sets the downsample factor

    ColorVal backgroundColor();              // Returns the background color of the comp
    void setBackgroundColor(ColorVal color); // Sets the background color of the comp

    // AE_CompFlags, need to separate them
    bool showLayerNameorSourceName();             // Returns true if the layer name or source name is shown
    void setShowLayerNameorSourceName(bool show); // Sets the show layer name or source name

    bool showBlendModes();             // Returns true if the blend modes are shown
    void setShowBlendModes(bool show); // Sets the show blend modes

    double frameRate();             // Returns the frame rate of the comp
    void setFrameRate(double rate); // Sets the frame rate of the comp

  private:
    CompPtr m_comp;
    tk::shared_ptr<LayerCollection> m_layerCollection;
};

class FootageItem : public Item
{
  public:
    FootageItem() : Item() {}
    FootageItem(ItemPtr item) : Item(item), m_footage(FootageSuite().getMainFootageFromItem(item)) {}
    static FootageItem create(std::string path, std::string name);
    // ca check on if its a string or vector, folder, list of files, single
    // file, etc.
    static FootageItem createPlaceholder(const std::string &path, int width, int height, double duration,
                                         Platform plat = Platform::WIN); // Creates a placeholder footage
    static FootageItem createSolid(const std::string &name, int width, int height, ColorVal color); // Creates a solid

    ItemType itemType() override { return ItemType::FOOTAGE; }

    std::tuple<A_long, A_long> numFiles();             // Returns the number of files
    std::string path(int frameNum = 0, int index = 0); // Returns the path of the footage

    void setProxy(tk::shared_ptr<Item> footage);       // Sets the proxy of the footage
    void replaceFootage(tk::shared_ptr<Item> footage); // Replaces the footage
    void replaceFromPath(std::string path);            // Replaces the footage from a path

  private:
    FootagePtr m_footage;
};


#endif // ITEM_HPP
