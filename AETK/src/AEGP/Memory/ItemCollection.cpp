#include "AETK/AEGP/Template/ItemCollection.hpp"
#include "AETK/AEGP/Items.hpp"
#include "AETK/AEGP/Util/Factories.hpp"

void ItemCollection::append(tk::shared_ptr<Item> item)
{
    auto parent = std::dynamic_pointer_cast<FolderItem>(baseItem);
    item->setParentFolder(parent);
}

void ItemCollection::extend(tk::vector<tk::shared_ptr<Item>> items)
{
    for (auto item : items)
    {
        append(item);
        m_collection.push_back(item);
    }
}

void ItemCollection::insert(size_t index, tk::shared_ptr<Item> item)
{
    auto parent = std::dynamic_pointer_cast<FolderItem>(baseItem);
    item->setParentFolder(parent);
    m_collection.insert(m_collection.begin() + index, item);
}

void ItemCollection::remove(tk::shared_ptr<Item> item)
{
    m_collection.erase(std::remove(m_collection.begin(), m_collection.end(), item), m_collection.end());
}

void ItemCollection::pop(size_t index)
{
    auto item = m_collection[index];
    m_collection.erase(m_collection.begin() + index);
    item->deleteItem();
}

void ItemCollection::clear()
{
    for (auto item : m_collection)
    {
        item->deleteItem();
    }
    m_collection.clear();
}

tk::vector<tk::shared_ptr<Item>> ItemCollection::slice(int start, int end)
{
    tk::vector<tk::shared_ptr<Item>> newCollection;
    for (int i = start; i < end; i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

tk::vector<tk::shared_ptr<Item>> ItemCollection::slice(int start)
{
    tk::vector<tk::shared_ptr<Item>> newCollection;
    for (int i = start; i < m_collection.size(); i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

void ItemCollection::createCollection()
{
    auto proj = ProjSuite().GetProjectByIndex(0);
    auto currentItem = this->baseItem->getItem();
    while (&currentItem != NULL)
    {
        if (ItemSuite().GetItemParentFolder(currentItem) == baseItem->getItem())
        {
            m_collection.push_back(ItemFactory::createItem(currentItem));
        }
        currentItem = ItemSuite().GetNextProjItem(proj, currentItem);
    }
}

tk::vector<tk::shared_ptr<Item>> ItemCollection::find(const std::function<bool(tk::shared_ptr<Item>)> &predicate)
{
    tk::vector<tk::shared_ptr<Item>> foundItems;
    for (auto item : m_collection)
    {
        if (predicate(item))
        {
			foundItems.push_back(item);
		}
	}
	return foundItems;
}
