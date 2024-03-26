#include "AETK/AEGP/Core/Items.hpp"
#include "AETK/AEGP/Core/Layer.hpp"
#include "AETK/AEGP/Core/Base/ItemCollection.hpp"
#include "AETK/AEGP/Core/Base/LayerCollection.hpp"

std::shared_ptr<AE::Item> AE::Item::activeItem()
{
    auto item = ItemSuite9().GetActiveItem();
    return ItemFactory::createItem(item);
}

std::string AE::Item::typeName() 
{
    return m_itemSuite.GetTypeName(this->itemType());
}

bool AE::Item::isSelected() 
{
    return m_itemSuite.IsItemSelected(m_item);
}

void AE::Item::setSelection(bool select, bool deselectOthers) {
    m_itemSuite.SelectItem(m_item, select, deselectOthers);
}

std::string AE::Item::name() 
{
    return m_itemSuite.GetItemName(m_item);
}

void AE::Item::setName(const std::string &name) {
    m_itemSuite.SetItemName(m_item, name.c_str());
}

void AE::Item::setProxyUse(bool useProxy) {
    m_itemSuite.SetItemUseProxy(m_item, useProxy);
}

std::shared_ptr<AE::FolderItem> AE::Item::parentFolder() 
{
    auto folder = m_itemSuite.GetItemParentFolder(m_item);
	return std::make_shared<FolderItem>(folder);
}

void AE::Item::setParentFolder(std::shared_ptr<AE::FolderItem> folder)
{
    m_itemSuite.SetItemParentFolder(m_item, folder->getItem());
}

double AE::Item::duration() 
{
	return TimeToSeconds(m_itemSuite.GetItemDuration(m_item));
}

double AE::Item::currentTime() 
{
    return TimeToSeconds(m_itemSuite.GetItemCurrentTime(m_item));
}

void AE::Item::setCurrentTime(double time) {
    m_itemSuite.SetItemCurrentTime(m_item, SecondsToTime(time));
}

std::string AE::Item::comment() 
{
    return m_itemSuite.GetItemComment(m_item);
}

void AE::Item::setComment(const std::string &comment) {
    m_itemSuite.SetItemComment(m_item, comment);
}

AE_Label AE::Item::label() {
    return m_itemSuite.GetItemLabel(m_item);
}

void AE::Item::setLabel(AE_Label label) {
    m_itemSuite.SetItemLabel(m_item, label);
}

std::tuple<int, int> AE::Item::dimensions() 
{
    auto dims = m_itemSuite.GetItemDimensions(m_item);
    return dims;
}

double AE::Item::pixelAspect() 
{
    return RATIO2FLOAT(m_itemSuite.GetItemPixelAspectRatio(m_item));
}

void AE::Item::deleteItem() {
    m_itemSuite.DeleteItem(m_item);
}


AE::FolderItem AE::FolderItem::create(const std::string &name,
                                  std::shared_ptr<FolderItem> parentFolder)
{
    auto folder = ItemSuite9().CreateNewFolder(name, parentFolder->getItem());
    return FolderItem(folder);
}

std::shared_ptr<AE::ItemCollection> AE::FolderItem::children()
{
    std::shared_ptr<Item> item = std::make_shared<Item>(m_item);
	return std::make_shared<ItemCollection>(item);
}

AE::CompItem AE::CompItem::mostRecent()
{
    auto item = CompSuite11().GetMostRecentlyUsedComp();
    return CompItem(item);
}

AE::CompItem AE::CompItem::create(const std::string &name, int width, int height,
                              double pixelAspect, double duration,
                              double frameRate, std::shared_ptr<FolderItem> item)
{
    auto comp = CompSuite11().CreateComp(item->getItem(), name, width, height,
                                         {static_cast<int>(pixelAspect), 1},
                                         SecondsToTime(duration),
                                         {static_cast<int>(frameRate), 1});
	return CompItem(comp);
}

// Adjusted layers method implementation
std::shared_ptr<AE::LayerCollection> AE::CompItem::layers()
{
    return std::make_shared<LayerCollection>(m_comp);
}

std::tuple<short, short> AE::CompItem::downsampleFactor() 
{
    auto factor = CompSuite11().GetCompDownsampleFactor(m_comp);
    return factor;
}

void AE::CompItem::setDownsampleFactor(short x, short y) {
    CompSuite11().SetCompDownsampleFactor(m_comp, std::make_tuple(x, y));
}

ColorVal AE::CompItem::backgroundColor() 
{
    return CompSuite11().GetCompBGColor(m_comp);
}

void AE::CompItem::setBackgroundColor(ColorVal color) {
    CompSuite11().SetCompBGColor(m_comp, color);
}

bool AE::CompItem::showLayerNameorSourceName() 
{
    return CompSuite11().GetShowLayerNameOrSourceName(m_comp);
}

void AE::CompItem::setShowLayerNameorSourceName(bool show) {
    CompSuite11().SetShowLayerNameOrSourceName(m_comp, show);
}

bool AE::CompItem::showBlendModes() 
{
    return CompSuite11().GetShowBlendModes(m_comp);
}

void AE::CompItem::setShowBlendModes(bool show) {
    CompSuite11().SetShowBlendModes(m_comp, show);
}

double AE::CompItem::frameRate() 
{
    return CompSuite11().GetCompFramerate(m_comp);
}

void AE::CompItem::setFrameRate(double rate) {
    CompSuite11().SetCompFrameRate(m_comp, rate);
}


AE::FootageItem AE::FootageItem::create(std::string path, std::string name)
{
    auto item = AssetManager().import(path, name);
    return FootageItem(item);
}

AE::FootageItem AE::FootageItem::createPlaceholder(const std::string &path,
                                               int width, int height,
                                               double duration,
                                               AE_Platform plat)
{
    auto footage = FootageSuite5().newPlaceholderFootage(path, width, height,
        													SecondsToTime(duration));
	auto footageItem = FootageSuite5().addFootageToProject(footage, NULL);
	return FootageItem(footageItem);
}

AE::FootageItem AE::FootageItem::createSolid(const std::string &name, int width,
                                         int height, ColorVal color)
{
    auto footage = FootageSuite5().newSolidFootage(name, width, height, color);
    auto footageItem = FootageSuite5().addFootageToProject(footage, NULL);
    return FootageItem(footageItem);
}

std::tuple<A_long, A_long> AE::FootageItem::numFiles() 
{
    return m_footageSuite.getFootageNumFiles(m_footage);
}

std::string AE::FootageItem::path(int frameNum, int index) 
{
    return m_footageSuite.getFootagePath(m_footage, frameNum, index);
}

void AE::FootageItem::setProxy(std::shared_ptr<FootageItem> footage) {
    m_footageSuite.setItemProxyFootage(m_footage, footage->getItem());
}

void AE::FootageItem::replaceFootage(std::shared_ptr<FootageItem> footage) {
    m_footageSuite.replaceItemMainFootage(m_footage, footage->getItem());
}

void AE::FootageItem::replaceFromPath(std::string path) {
    auto item = AssetManager().import(path);
    m_footageSuite.replaceItemMainFootage(m_footage, item);
}
