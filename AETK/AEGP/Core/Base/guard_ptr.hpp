/*****************************************************************/ /**
                                                                     * \file   guard_ptr.hpp
                                                                     * \brief  A smart pointer that guards the object
                                                                     *from being deleted.
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef GUARD_PTR_HPP
#define GUARD_PTR_HPP

#include "AETK/AEGP/Core/Base/SuiteManager.hpp"
#include "Headers/AE_GeneralPlug.h"
#include <functional>
#include <memory>

/*class WorldPtr
{
  public:
    WorldPtr(AEGP_WorldH &world) : m_world(std::make_shared<AEGP_WorldH>(world)) {}

    AEGP_WorldH get() const { return *m_world; }

    void set(AEGP_WorldH world) { m_world = std::make_shared<AEGP_WorldH>(world); }

    void setRequiresDisposal(bool requiresDisposal) { this->requiresDisposal = requiresDisposal; }

    ~WorldPtr()
    {
        if (requiresDisposal)
                {
                        SuiteManager::GetInstance()
                                .GetSuiteHandler()
                                .WorldSuite3()
                                ->AEGP_Dispose(*m_world.get());
                }
    }
    private:
  std::shared_ptr<AEGP_WorldH> m_world;
      bool requiresDisposal = false;

};
*/

template <typename T, typename Deleter = std::function<void(T)>> 
class guard_ptr
{
  public:
	guard_ptr() = default;
    guard_ptr(T &handle, Deleter deleter) : m_handle(std::make_shared<T>(handle)), m_deleter(deleter), requiresDisposal(true) {}
    guard_ptr(T &handle) : m_handle(std::make_shared<T>(handle)) {}
    // Move constructor
    guard_ptr(guard_ptr &&other) noexcept
        : m_handle(std::move(other.m_handle)), m_deleter(std::move(other.m_deleter)),
          requiresDisposal(other.requiresDisposal)
    {
        other.requiresDisposal = false; // Prevent the moved-from object from releasing the resource
    }

    // Move assignment operator
    guard_ptr &operator=(guard_ptr &&other) noexcept
    {
        if (this != &other)
        {
            m_handle = std::move(other.m_handle);
            m_deleter = std::move(other.m_deleter);
            requiresDisposal = other.requiresDisposal;
            other.requiresDisposal = false; // Prevent the moved-from object from releasing the resource
        }
        return *this;
    }


    T get() const { return *m_handle; }

    inline void set(T &handle) { m_handle = std::make_shared<T>(handle); }

    inline void setRequiresDisposal(bool requiresDisposal) { this->requiresDisposal = requiresDisposal; }

    ~guard_ptr() { 
        if (requiresDisposal)
        {
            m_deleter(*m_handle.get());
        }
    }

  private:
    std::shared_ptr<T> m_handle;
    Deleter m_deleter;
    bool requiresDisposal = false;
};


inline void disposeWorld(AEGP_WorldH &world)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.WorldSuite3()
		->AEGP_Dispose(world);
}

inline void disposeStream(AEGP_StreamRefH &stream)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.StreamSuite2()
		->AEGP_DisposeStream(stream);
}

inline void disposeMarker(AEGP_MarkerValP &marker)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.MarkerSuite3()
		->AEGP_DisposeMarker(marker);
}

inline void disposePlatform(AEGP_PlatformWorldH &platform)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.WorldSuite3()
		->AEGP_DisposePlatformWorld(platform);
}

inline void disposeEffectRef(AEGP_EffectRefH &effect)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.EffectSuite4()
		->AEGP_DisposeEffect(effect);
}

inline void disposeFootageRef(AEGP_FootageH &footage)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.FootageSuite5()
		->AEGP_DisposeFootage(footage);
}

inline void disposeMaskRef(AEGP_MaskRefH &mask)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.MaskSuite6()
		->AEGP_DisposeMask(mask);
}

inline void disposeRenderOptions(AEGP_RenderOptionsH &renderOptions)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.RenderOptionsSuite3()
		->AEGP_Dispose(renderOptions);
}

inline void disposeLayerRenderOptions(AEGP_LayerRenderOptionsH &layerRenderOptions)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.LayerRenderOptionsSuite2()
		->AEGP_Dispose(layerRenderOptions);
}

inline void disposeMemHandle(AEGP_MemHandle &memHandle)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.MemorySuite1()
		->AEGP_FreeMemHandle(memHandle);
}

inline void disposeTextOutline(AEGP_TextOutlinesH &textOutline)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.TextLayerSuite1()
		->AEGP_DisposeTextOutlines(textOutline);
}

inline void disposeAddKeyframesInfo(AEGP_AddKeyframesInfoH &addKeyframesInfo)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.KeyframeSuite5()
		->AEGP_EndAddKeyframes(true, addKeyframesInfo);
}

inline void disposeCollectionRef(AEGP_Collection2H &collection)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.CollectionSuite2()
		->AEGP_DisposeCollection(collection);
}

inline void disposeFrameReceipt(AEGP_FrameReceiptH &frameReceipt)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.RenderSuite5()
		->AEGP_CheckinFrame(frameReceipt);
}

inline void disposeMarkerVal(AEGP_MarkerValP &markerVal)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.MarkerSuite3()
		->AEGP_DisposeMarker(markerVal);
}

inline void disposeSoundData(AEGP_SoundDataH &soundData)
{
	SuiteManager::GetInstance()
		.GetSuiteHandler()
		.SoundDataSuite1()
		->AEGP_DisposeSoundData(soundData);
}


using ProjectPtr = guard_ptr<AEGP_ProjectH>;
using ItemPtr = guard_ptr<AEGP_ItemH>;
using CompPtr = guard_ptr<AEGP_CompH>;
using FootagePtr = guard_ptr<AEGP_FootageH, decltype(&disposeFootageRef)>;
using LayerPtr = guard_ptr<AEGP_LayerH>;
using EffectRefPtr = guard_ptr<AEGP_EffectRefH, decltype(&disposeEffectRef)>;
using MaskRefPtr = guard_ptr<AEGP_MaskRefH, decltype(&disposeMaskRef)>;
using StreamRefPtr = guard_ptr<AEGP_StreamRefH, decltype(&disposeStream)>;
using RenderLayerContextPtr = guard_ptr<AEGP_RenderLayerContextH>;
using PersistentBlobPtr = guard_ptr<AEGP_PersistentBlobH>;
using MaskOutlineValPtr = guard_ptr<AEGP_MaskOutlineValH>;
using CollectionPtr = guard_ptr<AEGP_CollectionH>;
using Collection2Ptr = guard_ptr<AEGP_Collection2H, decltype(&disposeCollectionRef)>;
using SoundDataPtr = guard_ptr<AEGP_SoundDataH, decltype(&disposeSoundData)>;
using AddKeyframesInfoPtr = guard_ptr<AEGP_AddKeyframesInfoH, decltype(&disposeAddKeyframesInfo)>;
using RenderReceiptPtr = guard_ptr<AEGP_RenderReceiptH>;
using RenderOptionsPtr = guard_ptr<AEGP_RenderOptionsH, decltype(&disposeRenderOptions)>;
using LayerRenderOptionsPtr = guard_ptr<AEGP_LayerRenderOptionsH, decltype(&disposeLayerRenderOptions)>;
using FrameReceiptPtr = guard_ptr<AEGP_FrameReceiptH, decltype(&disposeFrameReceipt)>;
using RQItemRefPtr = guard_ptr<AEGP_RQItemRefH>;
using OutputModuleRefPtr = guard_ptr<AEGP_OutputModuleRefH>;
using TextDocumentPtr = guard_ptr<AEGP_TextDocumentH>;
using MarkerValPtr = guard_ptr<AEGP_MarkerValP, decltype(&disposeMarkerVal)>;
using TextOutlinesPtr = guard_ptr<AEGP_TextOutlinesH, decltype(&disposeTextOutline)>;
using PlatformWorldPtr = guard_ptr<AEGP_PlatformWorldH, decltype(&disposePlatform)>;
using ItemViewPtr = guard_ptr<AEGP_ItemViewP>;
using ColorProfilePtr = guard_ptr<AEGP_ColorProfileP>;
using ConstColorProfilePtr = guard_ptr<AEGP_ConstColorProfileP>;
using MemHandlePtr = guard_ptr<AEGP_MemHandle, decltype(&disposeMemHandle)>;
using TimeStampPtr = guard_ptr<AEGP_TimeStamp>;
using WorldPtr = guard_ptr<AEGP_WorldH, decltype(&disposeWorld)>;

template <typename T>
inline guard_ptr<T> make_guard(T &handle)
{
	return guard_ptr<T>(handle);
}

template <typename T, typename Deleter> inline guard_ptr<T, Deleter> make_guard(T &handle, Deleter deleter)
{
	return guard_ptr<T, Deleter>(handle, deleter);
}





#endif // GUARD_PTR_HPP
