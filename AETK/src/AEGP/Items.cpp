#include "AETK/AEGP/Items.hpp"
#include "AETK/AEGP/Layers.hpp"
#include "AETK/AEGP/Template/ItemCollection.hpp"
#include "AETK/AEGP/Template/LayerCollection.hpp"
#include "AETK/AEGP/Util/AssetManager.hpp"
#include "AETK/AEGP/Util/Factories.hpp"

tk::shared_ptr<Item> Item::activeItem()
{
    auto item = ItemSuite().GetActiveItem();
    if (!item)
    {
        return nullptr;
    }
    return ItemFactory::createItem(item);
}

std::string Item::typeName()
{

    auto typeName = ItemSuite().GetTypeName(this->itemType());
    return typeName;
}

bool Item::isSelected()
{
    auto isSelected = ItemSuite().IsItemSelected(m_item);
    return isSelected;
}

void Item::setSelection(bool select, bool deselectOthers)
{
    ItemSuite().SelectItem(m_item, select, deselectOthers);
}

bool Item::Missing()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto missing = flag & AEGP_ItemFlag_MISSING;
    return missing;
}

bool Item::HasProxy()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto hasProxy = flag & AEGP_ItemFlag_HAS_PROXY;
    return hasProxy;
}

bool Item::UsingProxy()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto usingProxy = flag & AEGP_ItemFlag_USING_PROXY;
    return usingProxy;
}

bool Item::MissingProxy()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto usingProxy = flag & AEGP_ItemFlag_MISSING_PROXY;
    return usingProxy;
}

bool Item::HasVideo()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto hasVideo = flag & AEGP_ItemFlag_HAS_VIDEO;
    return hasVideo;
}

bool Item::HasAudio()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto hasAudio = flag & AEGP_ItemFlag_HAS_AUDIO;
    return hasAudio;
}

bool Item::Still()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto still = flag & AEGP_ItemFlag_STILL;
    return still;
}

bool Item::HasActiveAudio()
{
    auto flags = ItemSuite().GetItemFlags(m_item);
    AEGP_ItemFlags flag = static_cast<AEGP_ItemFlags>(flags);
    auto hasActiveAudio = flag & AEGP_ItemFlag_HAS_ACTIVE_AUDIO;
    return hasActiveAudio;
}

std::string Item::name()
{
    auto name = ItemSuite().GetItemName(m_item);
    return name;
}

void Item::setName(const std::string &name)
{
    ItemSuite().SetItemName(m_item, name);
}

void Item::setProxyUse(bool useProxy)
{
    ItemSuite().SetItemUseProxy(m_item, useProxy);
}

tk::shared_ptr<Item> Item::parentFolder()
{
    auto folder = ItemSuite().GetItemParentFolder(m_item);
    return std::make_shared<FolderItem>(folder);
}

void Item::setParentFolder(tk::shared_ptr<Item> folder)
{
    ItemSuite().SetItemParentFolder(m_item, folder->getItem());
}

double Item::duration()
{

    auto duration = ItemSuite().GetItemDuration(m_item).toSeconds();
    return duration;
}

double Item::currentTime()
{
    auto currentTime = ItemSuite().GetItemCurrentTime(m_item).toSeconds();
    return currentTime;
}

void Item::setCurrentTime(double time)
{
    ItemSuite().SetItemCurrentTime(m_item, SecondsToTime(time));
}

std::string Item::comment()
{
    auto comment = ItemSuite().GetItemComment(m_item);
    return comment;
}

void Item::setComment(const std::string &comment)
{
    ItemSuite().SetItemComment(m_item, comment);
}

Label Item::label()
{

    auto label = ItemSuite().GetItemLabel(m_item);
    return label;
}

void Item::setLabel(Label label)
{
    ItemSuite().SetItemLabel(m_item, label);
}

std::tuple<int, int> Item::dimensions()
{
    auto dims = ItemSuite().GetItemDimensions(m_item);
    return dims;
}

double Item::pixelAspect()
{
    auto pixelAspect = RATIO2FLOAT(ItemSuite().GetItemPixelAspectRatio(m_item));
    return pixelAspect;
}

void Item::deleteItem()
{
    ItemSuite().DeleteItem(m_item);
}

FolderItem FolderItem::create(const std::string &name, tk::shared_ptr<Item> parentFolder)
{
    auto folder = ItemSuite().CreateNewFolder(name, parentFolder->getItem());
    return FolderItem(folder);
}

tk::shared_ptr<ItemCollection> FolderItem::children()
{
    if (!m_children) {
		m_children = std::make_shared<ItemCollection>(std::make_shared<FolderItem>(m_item));
	}
    return m_children;
}

CompItem CompItem::mostRecent()
{
    // auto comp = CompSuite().GetMostRecentlyUsedComp();
    return CompItem(CompSuite().GetMostRecentlyUsedComp());
}

CompItem CompItem::create(const std::string &name, int width, int height, double pixelAspect, double duration,
                          double frameRate, tk::shared_ptr<Item> item)
{

    auto comp = CompSuite().CreateComp(item->getItem(), name, width, height, {static_cast<int>(pixelAspect), 1},
                                       SecondsToTime(duration), {static_cast<int>(frameRate), 1});
    return CompItem(comp);
}

// Adjusted layers method implementation
tk::shared_ptr<LayerCollection> CompItem::layers()
{
    if (!m_layerCollection)
    {
        m_layerCollection = std::make_shared<LayerCollection>(m_comp);
    }
    return m_layerCollection;
}

DownsampleFactor CompItem::downsampleFactor()
{
    auto factor = CompSuite().GetCompDownsampleFactor(m_comp);
    return factor;
}

void CompItem::setDownsampleFactor(DownsampleFactor dsf)
{

    CompSuite().SetCompDownsampleFactor(m_comp, dsf);
}

ColorVal CompItem::backgroundColor()
{

    auto color = CompSuite().GetCompBGColor(m_comp);
    return color;
}

void CompItem::setBackgroundColor(ColorVal color)
{

    CompSuite().SetCompBGColor(m_comp, color);
}

bool CompItem::showLayerNameorSourceName()
{

    auto show = CompSuite().GetShowLayerNameOrSourceName(m_comp);
    return show;
}

void CompItem::setShowLayerNameorSourceName(bool show)
{

    CompSuite().SetShowLayerNameOrSourceName(m_comp, show);
}

bool CompItem::showBlendModes()
{
    auto show = CompSuite().GetShowBlendModes(m_comp);
    return show;
}

void CompItem::setShowBlendModes(bool show)
{

    CompSuite().SetShowBlendModes(m_comp, show);
}

double CompItem::frameRate()
{
    auto rate = CompSuite().GetCompFramerate(m_comp);
    return rate;
}

void CompItem::setFrameRate(double rate)
{

    CompSuite().SetCompFrameRate(m_comp, rate);
}

FootageItem FootageItem::create(std::string path, std::string name)
{

    auto footage = AssetManager().import(path, name);

    return FootageItem(footage);
}

FootageItem FootageItem::createPlaceholder(const std::string &path, int width, int height, double duration,
                                           Platform plat)
{

    auto footage = FootageSuite().newPlaceholderFootage(path, width, height, SecondsToTime(duration));
    auto footageItem = FootageSuite().addFootageToProject(footage, NULL);

    return FootageItem(footageItem);
}

FootageItem FootageItem::createSolid(const std::string &name, int width, int height, ColorVal color)
{
    auto footage = FootageSuite().newSolidFootage(name, width, height, color);
    auto footageItem = FootageSuite().addFootageToProject(footage, NULL);
    return FootageItem(footageItem);
}

std::tuple<A_long, A_long> FootageItem::numFiles()
{

    auto numFiles = FootageSuite().getFootageNumFiles(m_footage);
    return numFiles;
}

std::string FootageItem::path(int frameNum, int index)
{
    auto path = FootageSuite().getFootagePath(m_footage, frameNum, index);
    return path;
}

void FootageItem::setProxy(tk::shared_ptr<Item> footage)
{
    FootageSuite().setItemProxyFootage(m_footage, footage->getItem());
}

void FootageItem::replaceFootage(tk::shared_ptr<Item> footage)
{
    FootageSuite().replaceItemMainFootage(m_footage, footage->getItem());
}

void FootageItem::replaceFromPath(std::string path)
{
    auto item = AssetManager().import(path, "");
    FootageSuite().replaceItemMainFootage(m_footage, item);
}
