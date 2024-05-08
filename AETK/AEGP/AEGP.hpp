/*****************************************************************/ /**
                                                                     * \file   AEGP.hpp
                                                                     * \brief  The Core of the AEGP Library
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef AEGP_HPP
#define AEGP_HPP

#include "AETK/Common/Common.hpp" // Common includes

#include "AETK/AEGP/Core/Core.hpp" // Core Classes

#include "AETK/AEGP/Memory/Memory.hpp"

#include "AETK/AEGP/Template/Collection.hpp" // Generic Collection Template
#include "AETK/AEGP/Template/ItemCollection.hpp"
#include "AETK/AEGP/Template/LayerCollection.hpp"
#include "AETK/AEGP/Template/Plugin.hpp"

#include "AETK/AEGP/Util/AssetManager.hpp"
#include "AETK/AEGP/Util/Context.hpp"
#include "AETK/AEGP/Util/Effects.hpp"
#include "AETK/AEGP/Util/Factories.hpp"
#include "AETK/AEGP/Util/Image.hpp"
#include "AETK/AEGP/Util/Keyframe.hpp"
#include "AETK/AEGP/Util/Masks.hpp"
#include "AETK/AEGP/Util/Properties.hpp"
#include "AETK/AEGP/Util/TaskScheduler.hpp"

#include "AETK/AEGP/App.hpp"     // Application Class
#include "AETK/AEGP/Items.hpp"   // Item Classes
#include "AETK/AEGP/Layers.hpp"  // Layer Classes
#include "AETK/AEGP/Project.hpp" // Project Class


class AsyncRenderManager
    {
  public:
    AsyncRenderManager() {}

    // Method to initiate async rendering with an optional custom callback
    void renderAsync(LayerRenderOptionsPtr optionsH, std::function<void(WorldPtr)> callbackF)
    {
        auto callbackPtr = new std::function<void(WorldPtr)>(callbackF);

        auto ret = std::async(std::launch::async, [optionsH, callbackPtr]() {
            RenderSuite().renderAndCheckoutLayerFrameAsync(optionsH, callback,
                                                           reinterpret_cast<AEGP_AsyncFrameRequestRefcon>(callbackPtr));
        });
    }


    // Existing static callback method remains unchanged
    static A_Err callback(AEGP_AsyncRequestId request_id, A_Boolean was_canceled, A_Err error,
                          AEGP_FrameReceiptH receiptH, AEGP_AsyncFrameRequestRefcon refconP0)
    {
        auto callbackPtr = reinterpret_cast<std::function<void(WorldPtr)> *>(refconP0);

        if (callbackPtr && *callbackPtr)
        {
            FrameReceiptPtr ptr = makeFrameReceiptPtr(receiptH);
            auto& world = RenderSuite().getReceiptWorld(ptr);
            (*callbackPtr)(world);
            delete callbackPtr;
        }
        return error;
    }
};

#endif // AEGP_HPP
