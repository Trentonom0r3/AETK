#include "AETK/AEGP/Core/Base/LayerCollection.hpp"
#include "AETK/AEGP/Core/Layer.hpp"
#include "AETK/AEGP/Core/Items.hpp"


//    std::shared_ptr<CompItem> baseComp;
void AE::LayerCollection::append(std::shared_ptr<AE::Item> item) {
    if (isLayerValid(item->getItem(), baseComp))
    {
        return;
    }
    LayerPtr layer = LayerSuite9().AddLayer(item->getItem(), baseComp);
    m_collection.push_back(std::make_shared<Layer>(layer));
}


void AE::LayerCollection::extend(std::vector<std::shared_ptr<AE::Layer>> layers) {
    for (auto layer : layers)
    {
		append(layer->sourceItem());
        m_collection.push_back(layer);
	}
}

void AE::LayerCollection::insert(size_t index, std::shared_ptr<AE::Layer> layer) {
    if (LayerSuite9().IsAddLayerValid(layer->sourceItem()->getItem(), baseComp) ==
        false)
    {
		return;
	}
	auto newLayer = LayerSuite9().AddLayer(layer->sourceItem()->getItem(), baseComp);
	m_collection.insert(m_collection.begin() + index, std::make_shared<Layer>(newLayer));
}

void AE::LayerCollection::remove(std::shared_ptr<AE::Layer> layer) {
	LayerSuite9().DeleteLayer(layer->getLayer());
	m_collection.erase(std::remove(m_collection.begin(), m_collection.end(), layer), m_collection.end());
}

void AE::LayerCollection::pop(size_t index) {
    LayerSuite9().DeleteLayer(m_collection[index]->getLayer());
	m_collection.erase(m_collection.begin() + index);
}

void AE::LayerCollection::clear() {
    for (auto layer : m_collection)
    {
		LayerSuite9().DeleteLayer(layer->getLayer());
	}
	m_collection.clear();
}

std::vector<std::shared_ptr<AE::Layer>> AE::LayerCollection::slice(int start,
                                                               int end)
{
    std::vector<std::shared_ptr<Layer>> newCollection;
    for (int i = start; i < end; i++)
    {
		newCollection.push_back(m_collection[i]);
	}
    return newCollection;
}

std::vector<std::shared_ptr<AE::Layer>> AE::LayerCollection::slice(int start)
{
    std::vector<std::shared_ptr<Layer>> newCollection;
    for (int i = start; i < m_collection.size(); i++)
    {
		newCollection.push_back(m_collection[i]);
	}
	return newCollection;
}

void AE::LayerCollection::reverse() {
    for (int i = 0; i < m_collection.size(); i++)
    {
		LayerSuite9().ReorderLayer(m_collection[i]->getLayer(), static_cast<int>(m_collection.size()) - i);
	}
    std::reverse(m_collection.begin(), m_collection.end());
}

void AE::LayerCollection::sort(
    std::function<bool(std::shared_ptr<AE::Layer>, std::shared_ptr<AE::Layer>)> compare)
{
    std::sort(m_collection.begin(), m_collection.end(), compare);
}

std::vector<std::shared_ptr<AE::Layer>> AE::LayerCollection::createCollection()
{
    int numLayers = LayerSuite9().GetCompNumLayers(baseComp);
    for (int i = 0; i < numLayers; i++)
    {
        auto layer = LayerSuite9().GetCompLayerByIndex(baseComp, i);
        m_collection.push_back(std::make_shared<Layer>(layer));
    }
    return m_collection;
}
