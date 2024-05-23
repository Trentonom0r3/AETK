/*****************************************************************/ /**
                                                                     * \file   Factories.hpp
                                                                     * \brief  A file containing the factories for the
                                                                     *different classes
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef FACTORIES_HPP
#define FACTORIES_HPP
#include "AETK/AEGP/Core/Core.hpp"
#include "AETK/AEGP/Items.hpp"
#include "AETK/AEGP/Layers.hpp"
#include "AETK/AEGP/Util/Properties.hpp"


class ItemFactory
{
  public:
    inline static tk::shared_ptr<Item> createItem(ItemPtr item)
    {
        ItemType type = ItemSuite().GetItemType(item);
        switch (type)
        {
        case ItemType::FOLDER:
            return tk::make_shared<FolderItem>(item);
        case ItemType::COMP:
            return tk::make_shared<CompItem>(item);
        case ItemType::FOOTAGE:
            return tk::make_shared<FootageItem>(item);
        default:
            return tk::make_shared<Item>(item);
        }
    }
};

class PropertyFactory
{
  public:
    static tk::shared_ptr<BaseProperty> CreateProperty(StreamRefPtr property)
    {

        StreamGroupingType groupType = DynamicStreamSuite().GetStreamGroupingType(property);
        if (groupType == StreamGroupingType::INDEXED_GROUP || groupType == StreamGroupingType::NAMED_GROUP)
        {
            return tk::make_shared<PropertyGroup>(property);
        }
        else if (groupType == StreamGroupingType::LEAF)
        {
            StreamType streamType = StreamSuite().GetStreamType(property);
            switch (streamType)
            {
            case StreamType::OneD:
                return tk::make_shared<OneDProperty>(property);
            case StreamType::TwoD:
            case StreamType::TwoD_SPATIAL:
                return tk::make_shared<TwoDProperty>(property);
            case StreamType::ThreeD:
            case StreamType::ThreeD_SPATIAL:
                return tk::make_shared<ThreeDProperty>(property);
            case StreamType::COLOR:
                return tk::make_shared<ColorProperty>(property);
            case StreamType::MARKER:
                return tk::make_shared<MarkerProperty>(property);
            case StreamType::LAYER_ID:
                return tk::make_shared<LayerIDProperty>(property);
            case StreamType::MASK_ID:
                return tk::make_shared<MaskIDProperty>(property);
            case StreamType::MASK:
                return tk::make_shared<MaskOutlineProperty>(property);
            case StreamType::TEXT_DOCUMENT:
                return tk::make_shared<TextDocumentProperty>(property);
            // Add additional cases as necessary for other property types
            default:
                return tk::make_shared<BaseProperty>(property); // Fallback for unrecognized or generic properties
            }
        }
        return nullptr; // Return nullptr if no suitable type found
    }
};

class LayerFactory
{
  public:
    inline static tk::shared_ptr<Layer> createLayer(LayerPtr layer)
    {
        if (layer == nullptr)
		{
			return nullptr;
		}
        ObjectType type = LayerSuite().GetLayerObjectType(layer);
        switch (type)
        {
        case ObjectType::AV:
            return tk::make_shared<AVLayer>(layer);
        case ObjectType::CAMERA:
            return tk::make_shared<CameraLayer>(layer);
        case ObjectType::LIGHT:
            return tk::make_shared<LightLayer>(layer);
        case ObjectType::TEXT:
            return tk::make_shared<TextLayer>(layer);
        case ObjectType::VECTOR:
            return tk::make_shared<VectorLayer>(layer);
        default:
            return tk::make_shared<AVLayer>(layer);
        }
    }
};

#endif // FACTORIES_HPP
