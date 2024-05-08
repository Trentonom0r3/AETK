#include "AETK/AEGP/Template/LayerCollection.hpp"
#include "AETK/AEGP/Items.hpp"
#include "AETK/AEGP/Layers.hpp"

//    tk::shared_ptr<CompItem> baseComp;
void LayerCollection::append(tk::shared_ptr<Item> item)
{
    if (!LayerSuite().IsAddLayerValid(item->getItem(), baseComp))
    {
        return;
    }
    LayerPtr layer = LayerSuite().AddLayer(item->getItem(), baseComp);
    m_collection.push_back(std::make_shared<Layer>(layer));
}

void LayerCollection::extend(tk::vector<tk::shared_ptr<Layer>> layers)
{
    for (auto layer : layers)
    {
        append(layer->sourceItem());
        m_collection.push_back(layer);
    }
}

void LayerCollection::insert(size_t index, tk::shared_ptr<Layer> layer)
{
    if (!LayerSuite().IsAddLayerValid(layer->sourceItem()->getItem(), baseComp) == false)
    {
        return;
    }
    auto newLayer = LayerSuite().AddLayer(layer->sourceItem()->getItem(), baseComp);
    m_collection.insert(m_collection.begin() + index, std::make_shared<Layer>(newLayer));
}

void LayerCollection::remove(tk::shared_ptr<Layer> layer)
{
    LayerSuite().DeleteLayer(layer->getLayer());
    m_collection.erase(std::remove(m_collection.begin(), m_collection.end(), layer), m_collection.end());
}

void LayerCollection::pop(size_t index)
{
    LayerSuite().DeleteLayer(m_collection[index]->getLayer());
    m_collection.erase(m_collection.begin() + index);
}

void LayerCollection::clear()
{
    for (auto layer : m_collection)
    {
        LayerSuite().DeleteLayer(layer->getLayer());
    }
    m_collection.clear();
}

tk::vector<tk::shared_ptr<Layer>> LayerCollection::slice(int start, int end)
{
    tk::vector<tk::shared_ptr<Layer>> newCollection;
    for (int i = start; i < end; i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

tk::vector<tk::shared_ptr<Layer>> LayerCollection::slice(int start)
{
    tk::vector<tk::shared_ptr<Layer>> newCollection;
    for (int i = start; i < m_collection.size(); i++)
    {
        newCollection.push_back(m_collection[i]);
    }
    return newCollection;
}

void LayerCollection::reverse()
{
    for (int i = 0; i < m_collection.size(); i++)
    {
        LayerSuite().ReorderLayer(m_collection[i]->getLayer(), static_cast<int>(m_collection.size()) - i);
    }
    std::reverse(m_collection.begin(), m_collection.end());
}

void LayerCollection::sort(std::function<bool(tk::shared_ptr<Layer>, tk::shared_ptr<Layer>)> compare)
{
    // std::sort(m_collection.begin(), m_collection.end(), compare);
    for (int i = 0; i < m_collection.size(); i++)
    {
        for (int j = i + 1; j < m_collection.size(); j++)
        {
            if (compare(m_collection[i], m_collection[j]))
            {
                LayerSuite().ReorderLayer(m_collection[i]->getLayer(), j);
                std::swap(m_collection[i], m_collection[j]);
            }
        }
    }
}

void LayerCollection::createCollection()
{
    int numLayers = LayerSuite().GetCompNumLayers(baseComp);
    for (int i = 0; i < numLayers; i++)
    {
        m_collection.push_back(std::make_shared<Layer>(LayerSuite().GetCompLayerByIndex(baseComp, i)));
    }
}

tk::vector<tk::shared_ptr<Layer>> LayerCollection::find(const std::function<bool(tk::shared_ptr<Layer>)> &predicate)
{
    tk::vector<tk::shared_ptr<Layer>> newCollection;
    for (auto layer : m_collection)
    {
        if (predicate(layer))
        {
			newCollection.push_back(layer);
		}
	}
	return newCollection;
}
