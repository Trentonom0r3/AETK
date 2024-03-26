#include "AETK/AEGP/Core/Base/ItemCollection.hpp"
#include "AETK/AEGP/Core/Items.hpp"

void AE::ItemCollection::append(std::shared_ptr<AE::Item> item)
{
    auto parent = std::dynamic_pointer_cast<AE::FolderItem>(baseItem);
    item->setParentFolder(parent);
}

void AE::ItemCollection::extend(std::vector<std::shared_ptr<AE::Item>> items)
{
    for (auto item : items)
    {
        append(item);
        m_collection.push_back(item);
    }
}

void AE::ItemCollection::insert(size_t index, std::shared_ptr<AE::Item> item)
{
    auto parent = std::dynamic_pointer_cast<AE::FolderItem>(baseItem);
    item->setParentFolder(parent);
    m_collection.insert(m_collection.begin() + index, item);
}

void AE::ItemCollection::remove(std::shared_ptr<AE::Item> item)
{
    m_collection.erase(
        std::remove(m_collection.begin(), m_collection.end(), item),
        m_collection.end());
}

void AE::ItemCollection::pop(size_t index)
{
    auto item = m_collection[index];
    m_collection.erase(m_collection.begin() + index);
    item->deleteItem();
}

void AE::ItemCollection::clear()
{
    for (auto item : m_collection)
    {
        item->deleteItem();
    }
    m_collection.clear();
}

std::vector<std::shared_ptr<AE::Item>> AE::ItemCollection::slice(int start,
                                                                 int end)
{
    std::vector<std::shared_ptr<AE::Item>> newCollection;
    for (int i = start; i < end; i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

std::vector<std::shared_ptr<AE::Item>> AE::ItemCollection::slice(int start)
{
    std::vector<std::shared_ptr<AE::Item>> newCollection;
    for (int i = start; i < m_collection.size(); i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

std::vector<std::shared_ptr<AE::Item>> AE::ItemCollection::createCollection()
{
    auto proj = ProjSuite6().GetProjectByIndex(0);
    auto currentItem = this->baseItem->getItem();
    while (*currentItem.get() != NULL)
    {
        if (*ItemSuite9().GetItemParentFolder(currentItem).get() ==
            *baseItem->getItem().get())
        {
            m_collection.push_back(ItemFactory::createItem(currentItem));
        }
        currentItem = ItemSuite9().GetNextProjItem(proj, currentItem);
    }
    return m_collection;
}
