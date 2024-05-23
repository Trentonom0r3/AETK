/*****************************************************************/ /**
                                                                     * \file   Types.hpp
                                                                     * \brief  A file containing all the types used in
                                                                     *the project
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#pragma once

#ifndef TYPES_H
#define TYPES_H

#include "AETK/AEGP/Core/Enums.hpp"
#include "AETK/AEGP/Core/Exception.hpp"
#include "AETK/AEGP/Core/Utility.hpp"
#include "AETK/Common/Common.hpp"

// #define USE_MEMORY
#ifdef USE_MEMORY
#include "AETK/AEGP/Memory/Memory.hpp"
namespace tk = ae;
#else
namespace tk = std;
#endif

/**
 * @brief Converts A_Err into a more meaningful error message.
 *
 * \param errorCode
 * \return String with a meaningful error message.
 */
inline std::string GetErrorMessage(int errorCode)
{
    switch (errorCode)
    {
    case A_Err_NONE:
        return "No error occurred.";
    case A_Err_GENERIC:
        return "A generic error occurred.";
    case A_Err_STRUCT:
        return "Structural error, possibly in plugin or project configuration.";
    case A_Err_PARAMETER:
        return "Parameter error: One or more parameters are invalid.";
    case A_Err_ALLOC:
        return "Allocation error: Failed to allocate necessary resources.";
    case A_Err_WRONG_THREAD:
        return "Wrong thread error: Attempted to execute a thread-specific "
               "operation on the wrong thread.";
    case A_Err_CONST_PROJECT_MODIFICATION:
        return "Constant project modification error: Attempted to modify a "
               "read-only project.";
    case A_Err_MISSING_SUITE:
        return "Missing suite error: Failed to acquire a required suite.";
    case A_Err_NOT_IN_CACHE_OR_COMPUTE_PENDING:
        return "Data not in cache or compute pending: Requested data is not "
               "available and is either being computed or must be "
               "re-requested.";
    case A_Err_PROJECT_LOAD_FATAL:
        return "Fatal project load error: Unable to load the project due to a "
               "critical error.";
    case A_Err_EFFECT_APPLY_FATAL:
        return "Fatal effect application error: Applying the effect resulted "
               "in "
               "a critical error.";
    default:
        // Handle reserved errors generically, as specifics are unknown
        /**  A_Err_MISSING_SUITE = 13 */
        if (errorCode >= A_Err_RESERVED_7 && errorCode <= A_Err_RESERVED_21)
        {
            if (errorCode == A_Err_MISSING_SUITE)
            {
                return "Missing suite error: Failed to acquire a required suite.";
            }
            return "Reserved error: An unspecified error occurred. Please "
                   "consult "
                   "the documentation or contact support.";
        }
        return "Unknown error: An unrecognized error occurred. Please consult "
               "the documentation or contact support.";
    }
}

/**
 * @brief Macro to check if an expression returns an error and throw an
 * AEException with the error message.
 */
#define CHECK(expr)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        A_Err err = (expr);                                                                                            \
        if (err != A_Err_NONE)                                                                                         \
        {                                                                                                              \
            std::string errorMessage = GetErrorMessage(err);                                                           \
            throw AEException(errorMessage.c_str());                                                                   \
        }                                                                                                              \
    } while (0)

template <typename HandleType> class HandleWrapper
{
  private:
    HandleType handle;
    std::function<void(HandleType)> deleter;

  public:
    explicit HandleWrapper(HandleType handle, std::function<void(HandleType)> deleter = nullptr)
        : handle(handle), deleter(deleter)
    {
    }
    HandleWrapper() : handle(nullptr), deleter(nullptr) {}

    ~HandleWrapper()
    {
        if (deleter)
        {
            deleter(handle);
        }
    }

    // Disable copying
    // HandleWrapper(const HandleWrapper &) = delete;
    // HandleWrapper &operator=(const HandleWrapper &) = delete;

    // Enable move semantics
    HandleWrapper(HandleWrapper &&other) noexcept : handle(other.handle), deleter(std::move(other.deleter))
    {
        other.handle = nullptr;
    }
    HandleWrapper(const HandleWrapper &other) : handle(other.handle), deleter(other.deleter)
    {
        // Additional logic for copying can be added here.
        if (deleter)
        {
            deleter(handle);
        }

        if (other.handle != nullptr)
        {
            handle = other.handle;
            deleter = other.deleter; // Or any other copying logic necessary.
        }
    }

    HandleWrapper &operator=(const HandleWrapper &other)
    {
        if (this != &other)
        {
            handle = other.handle;
            deleter = other.deleter; // Or any other copying logic necessary.
        }
        return *this;
    }

    HandleWrapper &operator=(HandleWrapper &&other) noexcept
    {
        if (this != &other)
        {
            if (deleter)
            {
                deleter(handle);
            }
            handle = other.handle;
            deleter = std::move(other.deleter);
            other.handle = nullptr; // Ensure the moved-from object is left in a valid state
        }
        return *this;
    }

    HandleType &get() { return handle; }
    operator HandleType() const { return handle; }
    HandleType operator->() const { return handle; }
    HandleType &operator*() const { return handle; }

    operator bool() const { return handle != nullptr; }

    void reset(HandleType newHandle = nullptr)
    {
        if (deleter)
        {
            deleter(handle);
        }
        handle = newHandle;
    }

    void swap(HandleWrapper &other)
    {
        std::swap(handle, other.handle);
        std::swap(deleter, other.deleter);
    }

    void release() { handle = nullptr; }

    // remove deleter
    void removeDeleter() { deleter = nullptr; }
};

inline void disposeStream(AEGP_StreamRefH stream)
{
    SuiteManager::GetInstance().GetSuiteHandler().StreamSuite2()->AEGP_DisposeStream(stream);
}

inline void disposeMarker(AEGP_MarkerValP marker)
{
    SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_DisposeMarker(marker);
}

inline void disposeWorld(AEGP_WorldH world)
{
    SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_Dispose(world);
}

inline void disposePlatform(AEGP_PlatformWorldH platform)
{
    SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_DisposePlatformWorld(platform);
}

inline void disposeEffect(AEGP_EffectRefH effect)
{
    SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_DisposeEffect(effect);
}

inline void disposeFootage(AEGP_FootageH footage)
{
    SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_DisposeFootage(footage);
}

inline void disposeMask(AEGP_MaskRefH mask)
{
    SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_DisposeMask(mask);
}

inline void disposeRenderOptions(AEGP_RenderOptionsH renderOptions)
{
    SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_Dispose(renderOptions);
}

inline void disposeLayerRenderOptions(AEGP_LayerRenderOptionsH layerRenderOptions)
{
    SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_Dispose(layerRenderOptions);
}

inline void disposeMemHandle(AEGP_MemHandle memHandle)
{
    SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(memHandle);
}

inline void disposeTextOutline(AEGP_TextOutlinesH textOutline)
{
    SuiteManager::GetInstance().GetSuiteHandler().TextLayerSuite1()->AEGP_DisposeTextOutlines(textOutline);
}

inline void disposeAddKeyframesInfo(AEGP_AddKeyframesInfoH addKeyframesInfo)
{
    SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_EndAddKeyframes(true, addKeyframesInfo);
}

inline void disposeCollection(AEGP_Collection2H collection)
{
    SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_DisposeCollection(collection);
}

inline void disposeFrameReceipt(AEGP_FrameReceiptH frameReceipt)
{
    SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_CheckinFrame(frameReceipt);
}

inline void disposeStreamValue(AEGP_StreamValue2 streamValue)
{
    SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_DisposeStreamValue(&streamValue);
}

inline void disposeSoundData(AEGP_SoundDataH soundData)
{
    SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_DisposeSoundData(soundData);
}

using ProjectH = HandleWrapper<AEGP_ProjectH>;
using ItemH = HandleWrapper<AEGP_ItemH>;
using CompH = HandleWrapper<AEGP_CompH>;
using FootageH = HandleWrapper<AEGP_FootageH>;
using LayerH = HandleWrapper<AEGP_LayerH>;
using EffectRefH = HandleWrapper<AEGP_EffectRefH>;
using MaskRefH = HandleWrapper<AEGP_MaskRefH>;
using StreamRefH = HandleWrapper<AEGP_StreamRefH>;
using RenderLayerContextH = HandleWrapper<AEGP_RenderLayerContextH>;
using PersistentBlobH = HandleWrapper<AEGP_PersistentBlobH>;
using MaskOutlineValH = HandleWrapper<AEGP_MaskOutlineValH>;
using CollectionH = HandleWrapper<AEGP_CollectionH>;
using Collection2H = HandleWrapper<AEGP_Collection2H>;
using SoundDataH = HandleWrapper<AEGP_SoundDataH>;
using AddKeyframesInfoH = HandleWrapper<AEGP_AddKeyframesInfoH>;
using RenderReceiptH = HandleWrapper<AEGP_RenderReceiptH>;
using WorldH = HandleWrapper<AEGP_WorldH>;
using RenderOptionsH = HandleWrapper<AEGP_RenderOptionsH>;
using LayerRenderOptionsH = HandleWrapper<AEGP_LayerRenderOptionsH>;
using FrameReceiptH = HandleWrapper<AEGP_FrameReceiptH>;
using RQItemRefH = HandleWrapper<AEGP_RQItemRefH>;
using OutputModuleRefH = HandleWrapper<AEGP_OutputModuleRefH>;
using TextDocumentH = HandleWrapper<AEGP_TextDocumentH>;
using MarkerValP = HandleWrapper<AEGP_MarkerValP>;
using TextOutlinesH = HandleWrapper<AEGP_TextOutlinesH>;
using PlatformWorldH = HandleWrapper<AEGP_PlatformWorldH>;
using ItemViewP = HandleWrapper<AEGP_ItemViewP>;
using ColorProfileP = HandleWrapper<AEGP_ColorProfileP>;
using ConstColorProfileP = HandleWrapper<AEGP_ConstColorProfileP>;
using TimeStamp = HandleWrapper<AEGP_TimeStamp>;
// using StreamValue2 = HandleWrapper<AEGP_StreamValue2>;
using MemHandle = HandleWrapper<AEGP_MemHandle>;
typedef std::shared_ptr<StreamRefH> StreamRefPtr;
class StreamValue2 : public HandleWrapper<AEGP_StreamValue2>
{
  public:
    StreamValue2(AEGP_StreamValue2 streamValue) : HandleWrapper(streamValue, disposeStreamValue) {}
    StreamValue2() : HandleWrapper(AEGP_StreamValue2()) {}

    StreamValue2(StreamRefPtr streamref, std::variant<OneD, TwoD, ThreeD, Color> value)
        : HandleWrapper(streamFromValue(streamref, value), disposeStreamValue)
    {
    }

    std::variant<OneD, TwoD, ThreeD, Color> value();

  private:
    AEGP_StreamValue2 &streamFromValue(StreamRefPtr streamref, std::variant<OneD, TwoD, ThreeD, Color> value);
};

/**
 * @brief Define shared pointers for After Effects SDK types
 *
 */
typedef std::shared_ptr<ProjectH> ProjectPtr;
typedef std::shared_ptr<ItemH> ItemPtr;
typedef std::shared_ptr<CompH> CompPtr;
typedef std::shared_ptr<FootageH> FootagePtr;
typedef std::shared_ptr<LayerH> LayerPtr;
typedef std::shared_ptr<EffectRefH> EffectRefPtr;
typedef std::shared_ptr<MaskRefH> MaskRefPtr;
typedef std::shared_ptr<RenderLayerContextH> RenderLayerContextPtr;
typedef std::shared_ptr<PersistentBlobH> PersistentBlobPtr;
typedef std::shared_ptr<MaskOutlineValH> MaskOutlineValPtr;
typedef std::shared_ptr<CollectionH> CollectionPtr;
typedef std::shared_ptr<Collection2H> Collection2Ptr;
typedef std::shared_ptr<SoundDataH> SoundDataPtr;
typedef std::shared_ptr<AddKeyframesInfoH> AddKeyframesInfoPtr;
typedef std::shared_ptr<RenderReceiptH> RenderReceiptPtr;
typedef std::shared_ptr<WorldH> WorldPtr;
typedef std::shared_ptr<RenderOptionsH> RenderOptionsPtr;
typedef std::shared_ptr<LayerRenderOptionsH> LayerRenderOptionsPtr;
typedef std::shared_ptr<FrameReceiptH> FrameReceiptPtr;
typedef std::shared_ptr<RQItemRefH> RQItemRefPtr;
typedef std::shared_ptr<OutputModuleRefH> OutputModuleRefPtr;
typedef std::shared_ptr<TextDocumentH> TextDocumentPtr;
typedef std::shared_ptr<MarkerValP> MarkerValPtr;
typedef std::shared_ptr<TextOutlinesH> TextOutlinesPtr;
typedef std::shared_ptr<PlatformWorldH> PlatformWorldPtr;
typedef std::shared_ptr<ItemViewP> ItemViewPtr;
typedef std::shared_ptr<ColorProfileP> ColorProfilePtr;
typedef std::shared_ptr<ConstColorProfileP> ConstColorProfilePtr;
typedef std::shared_ptr<TimeStamp> TimeStampPtr;
typedef std::shared_ptr<StreamValue2> StreamValue2Ptr;
typedef std::shared_ptr<MemHandle> MemHandlePtr;

// define a macro to check if handle is nullptr, and return nullptr if it is
#define NULLCHECK(handle)                                                                                              \
    if (handle == nullptr)                                                                                             \
    {                                                                                                                  \
        return nullptr;                                                                                                \
    }

inline ProjectPtr makeProjectPtr(AEGP_ProjectH project)
{
    NULLCHECK(project);
    return std::make_shared<ProjectH>(project);
}

inline ItemPtr makeItemPtr(AEGP_ItemH item)
{
    NULLCHECK(item);
    return std::make_shared<ItemH>(item);
}

inline CompPtr makeCompPtr(AEGP_CompH comp)
{
    NULLCHECK(comp);
    return std::make_shared<CompH>(comp);
}

inline FootagePtr makeFootagePtr(AEGP_FootageH footage, bool dispose = true)
{
    NULLCHECK(footage);
    if (dispose)
    {
        return std::make_shared<FootageH>(footage, disposeFootage);
    }
    return std::make_shared<FootageH>(footage);
}

inline LayerPtr makeLayerPtr(AEGP_LayerH layer)
{
    NULLCHECK(layer);
    return std::make_shared<LayerH>(layer);
}

inline EffectRefPtr makeEffectRefPtr(AEGP_EffectRefH effect, bool dispose = true)
{
    NULLCHECK(effect);
    if (dispose)
    {
        return std::make_shared<EffectRefH>(effect, disposeEffect);
    }
    return std::make_shared<EffectRefH>(effect);
}

inline MaskRefPtr makeMaskRefPtr(AEGP_MaskRefH mask, bool dispose = true)
{
    NULLCHECK(mask);
    if (dispose)
    {
        return std::make_shared<MaskRefH>(mask, disposeMask);
    }
    return std::make_shared<MaskRefH>(mask);
}

inline StreamRefPtr makeStreamRefPtr(AEGP_StreamRefH stream, bool dispose = true)
{
    NULLCHECK(stream);
    if (dispose)
    {
        return std::make_shared<StreamRefH>(stream, disposeStream);
    }
    return std::make_shared<StreamRefH>(stream);
}

inline RenderLayerContextPtr makeRenderLayerContextPtr(AEGP_RenderLayerContextH renderLayerContext)
{
    NULLCHECK(renderLayerContext);
    return std::make_shared<RenderLayerContextH>(renderLayerContext);
}

inline PersistentBlobPtr makePersistentBlobPtr(AEGP_PersistentBlobH persistentBlob)
{
    NULLCHECK(persistentBlob);
    return std::make_shared<PersistentBlobH>(persistentBlob);
}

inline MaskOutlineValPtr makeMaskOutlineValPtr(AEGP_MaskOutlineValH maskOutlineVal)
{
    NULLCHECK(maskOutlineVal);
    return std::make_shared<MaskOutlineValH>(maskOutlineVal);
}

inline CollectionPtr makeCollectionPtr(AEGP_CollectionH collection)
{
    NULLCHECK(collection);
    return std::make_shared<CollectionH>(collection);
}

inline Collection2Ptr makeCollection2Ptr(AEGP_Collection2H collection)
{
    NULLCHECK(collection);
    return std::make_shared<Collection2H>(collection, disposeCollection);
}

inline SoundDataPtr makeSoundDataPtr(AEGP_SoundDataH soundData, bool dispose = true)
{
    NULLCHECK(soundData);
    if (dispose)
    {
        return std::make_shared<SoundDataH>(soundData, disposeSoundData);
    }
    return std::make_shared<SoundDataH>(soundData);
}

inline AddKeyframesInfoPtr makeAddKeyframesInfoPtr(AEGP_AddKeyframesInfoH addKeyframesInfo)
{
    NULLCHECK(addKeyframesInfo);
    return std::make_shared<AddKeyframesInfoH>(addKeyframesInfo);
}

inline RenderReceiptPtr makeRenderReceiptPtr(AEGP_RenderReceiptH renderReceipt)
{
    NULLCHECK(renderReceipt);
    return std::make_shared<RenderReceiptH>(renderReceipt);
}

inline WorldPtr makeWorldPtr(AEGP_WorldH world, bool dispose = true)
{
    NULLCHECK(world);
    if (dispose)
    {
        return std::make_shared<WorldH>(world, disposeWorld);
    }
    return std::make_shared<WorldH>(world);
}

inline RenderOptionsPtr makeRenderOptionsPtr(AEGP_RenderOptionsH renderOptions, bool dispose = true)
{
    NULLCHECK(renderOptions);
    if (dispose)
    {
        return std::make_shared<RenderOptionsH>(renderOptions, disposeRenderOptions);
    }
    return std::make_shared<RenderOptionsH>(renderOptions);
}

inline LayerRenderOptionsPtr makeLayerRenderOptionsPtr(AEGP_LayerRenderOptionsH layerRenderOptions, bool dispose = true)
{
    NULLCHECK(layerRenderOptions);
    if (dispose)
    {
        return std::make_shared<LayerRenderOptionsH>(layerRenderOptions, disposeLayerRenderOptions);
    }
    return std::make_shared<LayerRenderOptionsH>(layerRenderOptions);
}

inline FrameReceiptPtr makeFrameReceiptPtr(AEGP_FrameReceiptH frameReceipt)
{
    NULLCHECK(frameReceipt);
    return std::make_shared<FrameReceiptH>(frameReceipt);
}

inline RQItemRefPtr makeRQItemRefPtr(AEGP_RQItemRefH rqItemRef)
{
    NULLCHECK(rqItemRef);
    return std::make_shared<RQItemRefH>(rqItemRef);
}

inline OutputModuleRefPtr makeOutputModuleRefPtr(AEGP_OutputModuleRefH outputModuleRef)
{
    NULLCHECK(outputModuleRef);
    return std::make_shared<OutputModuleRefH>(outputModuleRef);
}

inline TextDocumentPtr makeTextDocumentPtr(AEGP_TextDocumentH textDocument)
{
    NULLCHECK(textDocument);
    return std::make_shared<TextDocumentH>(textDocument);
}

inline MarkerValPtr makeMarkerValPtr(AEGP_MarkerValP markerVal, bool dispose = true)
{
    NULLCHECK(markerVal);
    if (dispose)
    {
        return std::make_shared<MarkerValP>(markerVal, disposeMarker);
    }
    return std::make_shared<MarkerValP>(markerVal);
}

inline TextOutlinesPtr makeTextOutlinesPtr(AEGP_TextOutlinesH textOutlines, bool dispose = true)
{
    NULLCHECK(textOutlines);
    if (dispose)
    {
        return std::make_shared<TextOutlinesH>(textOutlines, disposeTextOutline);
    }
    return std::make_shared<TextOutlinesH>(textOutlines);
}

inline PlatformWorldPtr makePlatformWorldPtr(AEGP_PlatformWorldH platformWorld)
{
    NULLCHECK(platformWorld);
    return std::make_shared<PlatformWorldH>(platformWorld);
}

inline ItemViewPtr makeItemViewPtr(AEGP_ItemViewP itemView)
{
    NULLCHECK(itemView);
    return std::make_shared<ItemViewP>(itemView);
}

inline ColorProfilePtr makeColorProfilePtr(AEGP_ColorProfileP colorProfile)
{
    NULLCHECK(colorProfile);
    return std::make_shared<ColorProfileP>(colorProfile);
}

inline ConstColorProfilePtr makeConstColorProfilePtr(AEGP_ConstColorProfileP constColorProfile)
{
    NULLCHECK(constColorProfile);
    return std::make_shared<ConstColorProfileP>(constColorProfile);
}

inline TimeStampPtr makeTimeStampPtr(AEGP_TimeStamp timeStamp)
{
    NULLCHECK(&timeStamp);
    return std::make_shared<TimeStamp>(timeStamp);
}

inline StreamValue2Ptr makeStreamValue2Ptr(AEGP_StreamValue2 streamValue)
{
    NULLCHECK(&streamValue);
    return std::make_shared<StreamValue2>(streamValue);
}

inline MemHandlePtr makeMemHandlePtr(AEGP_MemHandle memHandle)
{
    NULLCHECK(memHandle);
    return std::make_shared<MemHandle>(memHandle, disposeMemHandle);
}

/**
 * @brief A class to manage AEGP_ColorVal
 */
class ColorVal
{
  public:
    ColorVal() : red(0), green(0), blue(0), alpha(0) {}                                       // Default constructor
    ColorVal(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {} // Constructor from values
    ColorVal(AEGP_ColorVal color)
        : red(color.redF), green(color.greenF), blue(color.blueF), alpha(color.alphaF)
    {} // Constructor from AEGP_ColorVal
    ColorVal(std::tuple<double, double, double, double> tuple)
        : red(std::get<0>(tuple)), green(std::get<1>(tuple)), blue(std::get<2>(tuple)), alpha(std::get<3>(tuple))
    {
    } // Constructor from Tuple)
    /**
     * @brief Convert to AEGP_ColorVal
     *
     * \return AEGP_ColorVal
     */
    AEGP_ColorVal toAEGP()
    {
        AEGP_ColorVal color;
        color.redF = red;
        color.greenF = green;
        color.blueF = blue;
        color.alphaF = alpha;
        return color;
    }
    /**
     * @brief Convert to Tuple
     *
     * \return std::tuple<double, double, double, double>
     */
    std::tuple<double, double, double, double> ToTuple() { return std::make_tuple(red, green, blue, alpha); }

    double red;
    double green;
    double blue;
    double alpha;
};

/**
 * @brief Class to Manage AEGP_TimeDisplay3
 */
class TimeDisplay3
{
  public:
    TimeDisplay3()
        : display_mode(TimeDisplayMode::FRAMES), footage_display_mode(SourceTimecodeDisplayMode::ZERO),
          display_dropframeB(FALSE), use_feet_framesB(FALSE), timebaseC('0'), frames_per_footC('0'),
          frames_display_mode(FramesDisplayMode::ONE_BASED)
    {
    } // Default constructor
    TimeDisplay3(AEGP_TimeDisplay3 timeDisplay)
        : display_mode(TimeDisplayMode(timeDisplay.display_mode)),
          footage_display_mode(SourceTimecodeDisplayMode(timeDisplay.footage_display_mode)),
          display_dropframeB(timeDisplay.display_dropframeB), use_feet_framesB(timeDisplay.use_feet_framesB),
          timebaseC(timeDisplay.timebaseC), frames_per_footC(timeDisplay.frames_per_footC),
          frames_display_mode(FramesDisplayMode(timeDisplay.frames_display_mode))
    {
    } // Constructor from AEGP_TimeDisplay3

    /**
     * @brief Convert to AEGP_TimeDisplay3
     *
     * \return AEGP_TimeDisplay3
     */
    AEGP_TimeDisplay3 toAEGP()
    {
        AEGP_TimeDisplay3 timeDisplay;
        timeDisplay.display_mode = AEGP_TimeDisplayMode(display_mode);
        timeDisplay.footage_display_mode = AEGP_SourceTimecodeDisplayMode(footage_display_mode);
        timeDisplay.display_dropframeB = display_dropframeB;
        timeDisplay.use_feet_framesB = use_feet_framesB;
        timeDisplay.timebaseC = timebaseC;
        timeDisplay.frames_per_footC = frames_per_footC;
        timeDisplay.frames_display_mode = AEGP_FramesDisplayMode(frames_display_mode);
        return timeDisplay;
    }

    /**
     * @brief Convert to Tuple
     *
     * \return std::tuple<TimeDisplayMode, SourceTimecodeDisplayMode, bool, bool, char, char, FramesDisplayMode>
     */
    std::tuple<TimeDisplayMode, SourceTimecodeDisplayMode, bool, bool, char, char, FramesDisplayMode> ToTuple()
    {
        return std::make_tuple(display_mode, footage_display_mode, display_dropframeB, use_feet_framesB, timebaseC,
                               frames_per_footC, frames_display_mode);
    }

    TimeDisplayMode display_mode;
    SourceTimecodeDisplayMode footage_display_mode;
    bool display_dropframeB;
    bool use_feet_framesB;
    char timebaseC;
    char frames_per_footC;
    FramesDisplayMode frames_display_mode;
};

class SoundDataFormat
{
  public:
    SoundDataFormat() : sample_rateF(0), encoding(SoundEncoding::BEGIN), bytes_per_sampleL(0), num_channelsL(0) {}
    SoundDataFormat(AEGP_SoundDataFormat soundDataFormat)
        : sample_rateF(soundDataFormat.sample_rateF), encoding(SoundEncoding(soundDataFormat.encoding)),
          bytes_per_sampleL(soundDataFormat.bytes_per_sampleL), num_channelsL(soundDataFormat.num_channelsL)
    {
    }

    AEGP_SoundDataFormat toAEGP()
    {
        AEGP_SoundDataFormat soundDataFormat;
        soundDataFormat.sample_rateF = sample_rateF;
        soundDataFormat.encoding = AEGP_SoundEncoding(encoding);
        soundDataFormat.bytes_per_sampleL = bytes_per_sampleL;
        soundDataFormat.num_channelsL = num_channelsL;
        return soundDataFormat;
    }

    std::tuple<double, SoundEncoding, long, long> ToTuple()
    {
        return std::make_tuple(sample_rateF, encoding, bytes_per_sampleL, num_channelsL);
    }

    double sample_rateF;
    SoundEncoding encoding;
    long bytes_per_sampleL;
    long num_channelsL;
};

class DownsampleFactor
{
  public:
    DownsampleFactor() : xS(0), yS(0) {}
    DownsampleFactor(short x, short y) : xS(x), yS(y) {}
    DownsampleFactor(AEGP_DownsampleFactor downsampleFactor) : xS(downsampleFactor.xS), yS(downsampleFactor.yS) {}

    AEGP_DownsampleFactor toAEGP()
    {
        AEGP_DownsampleFactor downsampleFactor;
        downsampleFactor.xS = xS;
        downsampleFactor.yS = yS;
        return downsampleFactor;
    }

    std::tuple<short, short> ToTuple() { return std::make_tuple(xS, yS); }

    short xS;
    short yS;
};

class LayerTransferMode
{
  public:
    LayerTransferMode() : mode(0), flags(TransferFlags::PRESERVE_ALPHA), track_matte(TrackMatte::NO_TRACK_MATTE) {}
    LayerTransferMode(AEGP_LayerTransferMode layerTransferMode)
        : mode(int(layerTransferMode.mode)), flags(TransferFlags(layerTransferMode.flags)),
          track_matte(TrackMatte(layerTransferMode.track_matte))
    {
    }

    AEGP_LayerTransferMode toAEGP()
    {
        AEGP_LayerTransferMode layerTransferMode;
        layerTransferMode.mode = PF_TransferMode(mode);
        layerTransferMode.flags = AEGP_TransferFlags(flags);
        layerTransferMode.track_matte = AEGP_TrackMatte(track_matte);
        return layerTransferMode;
    }

    std::tuple<int, TransferFlags, TrackMatte> ToTuple() { return std::make_tuple(mode, flags, track_matte); }

    int mode;
    TransferFlags flags;
    TrackMatte track_matte;
};

class OneDVal
{
  public:
    OneDVal() : value(0) {}
    OneDVal(AEGP_OneDVal oneDVal) : value(oneDVal) {}

    AEGP_OneDVal toAEGP() { return value; }

    double val() { return value; }

    double value;
};

class TwoDVal
{
  public:
    TwoDVal() : x(0), y(0) {}
    TwoDVal(AEGP_TwoDVal twoDVal) : x(twoDVal.x), y(twoDVal.y) {}
    TwoDVal(double xVal, double yVal) : x(xVal), y(yVal) {}
    TwoDVal(std::tuple<double, double> tuple) : x(std::get<0>(tuple)), y(std::get<1>(tuple)) {}

    AEGP_TwoDVal toAEGP()
    {
        AEGP_TwoDVal twoDVal;
        twoDVal.x = x;
        twoDVal.y = y;
        return twoDVal;
    }

    std::tuple<double, double> ToTuple() { return std::make_tuple(x, y); }

    double x;
    double y;
};

class ThreeDVal
{
  public:
    ThreeDVal() : x(0), y(0), z(0) {}
    ThreeDVal(AEGP_ThreeDVal threeDVal) : x(threeDVal.x), y(threeDVal.y), z(threeDVal.z) {}
    ThreeDVal(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}
    ThreeDVal(std::tuple<double, double, double> tuple)
        : x(std::get<0>(tuple)), y(std::get<1>(tuple)), z(std::get<2>(tuple))
    {
    }

    AEGP_ThreeDVal toAEGP()
    {
        AEGP_ThreeDVal threeDVal;
        threeDVal.x = x;
        threeDVal.y = y;
        threeDVal.z = z;
        return threeDVal;
    }

    std::tuple<double, double, double> ToTuple() { return std::make_tuple(x, y, z); }

    double x;
    double y;
    double z;
};

class KeyframeEase
{
  public:
    KeyframeEase() : speedF(0), influenceF(0) {}
    KeyframeEase(AEGP_KeyframeEase keyframeEase) : speedF(keyframeEase.speedF), influenceF(keyframeEase.influenceF) {}
    KeyframeEase(double speed, double influence) : speedF(speed), influenceF(influence) {}
    KeyframeEase(std::tuple<double, double> tuple) : speedF(std::get<0>(tuple)), influenceF(std::get<1>(tuple)) {}

    AEGP_KeyframeEase toAEGP()
    {
        AEGP_KeyframeEase keyframeEase;
        keyframeEase.speedF = speedF;
        keyframeEase.influenceF = influenceF;
        return keyframeEase;
    }

    std::tuple<double, double> ToTuple() { return std::make_tuple(speedF, influenceF); }

    double speedF;
    double influenceF;
};

class MaskFeather
{
  public:
    MaskFeather()
        : segment(0), segment_sF(0), radiusF(0), ui_corner_angleF(0), tensionF(0), interp(MaskFeatherInterp::NORMAL),
          type(MaskFeatherType::OUTER)
    {
    }
    MaskFeather(AEGP_MaskFeather maskFeather)
        : segment(maskFeather.segment), segment_sF(maskFeather.segment_sF), radiusF(maskFeather.radiusF),
          ui_corner_angleF(maskFeather.ui_corner_angleF), tensionF(maskFeather.tensionF),
          interp(MaskFeatherInterp(maskFeather.interp)), type(MaskFeatherType(maskFeather.type))
    {
    }
    MaskFeather(int segment, double segment_sF, double radiusF, float ui_corner_angleF, float tensionF,
                MaskFeatherInterp interp, MaskFeatherType type)
        : segment(segment), segment_sF(segment_sF), radiusF(radiusF), ui_corner_angleF(ui_corner_angleF),
          tensionF(tensionF), interp(interp), type(type)
    {
    }

    AEGP_MaskFeather toAEGP()
    {
        AEGP_MaskFeather maskFeather;
        maskFeather.segment = segment;
        maskFeather.segment_sF = segment_sF;
        maskFeather.radiusF = radiusF;
        maskFeather.ui_corner_angleF = ui_corner_angleF;
        maskFeather.tensionF = tensionF;
        maskFeather.interp = AEGP_MaskFeatherInterp(interp);
        maskFeather.type = AEGP_MaskFeatherType(type);
        return maskFeather;
    }

    std::tuple<int, double, double, float, float, MaskFeatherInterp, MaskFeatherType> ToTuple()
    {
        return std::make_tuple(segment, segment_sF, radiusF, ui_corner_angleF, tensionF, interp, type);
    }

    int segment;
    double segment_sF;
    double radiusF;
    float ui_corner_angleF;
    float tensionF;
    MaskFeatherInterp interp;
    MaskFeatherType type;
};

class MaskVertex
{
  public:
    MaskVertex() : x(0), y(0), tan_in_x(0), tan_in_y(0), tan_out_x(0), tan_out_y(0) {}
    MaskVertex(AEGP_MaskVertex maskVertex)
        : x(maskVertex.x), y(maskVertex.y), tan_in_x(maskVertex.tan_in_x), tan_in_y(maskVertex.tan_in_y),
          tan_out_x(maskVertex.tan_out_x), tan_out_y(maskVertex.tan_out_y)
    {
    }
    MaskVertex(double xVal, double yVal, double tanInX, double tanInY, double tanOutX, double tanOutY)
        : x(xVal), y(yVal), tan_in_x(tanInX), tan_in_y(tanInY), tan_out_x(tanOutX), tan_out_y(tanOutY)
    {
    }

    AEGP_MaskVertex toAEGP()
    {
        AEGP_MaskVertex maskVertex;
        maskVertex.x = x;
        maskVertex.y = y;
        maskVertex.tan_in_x = tan_in_x;
        maskVertex.tan_in_y = tan_in_y;
        maskVertex.tan_out_x = tan_out_x;
        maskVertex.tan_out_y = tan_out_y;
        return maskVertex;
    }

    std::tuple<double, double, double, double, double, double> ToTuple()
    {
        return std::make_tuple(x, y, tan_in_x, tan_in_y, tan_out_x, tan_out_y);
    }

    double x;
    double y;
    double tan_in_x;
    double tan_in_y;
    double tan_out_x;
    double tan_out_y;
};

class LoopBehavior
{
  public:
    LoopBehavior() : loops(0), reserved(0) {}
    LoopBehavior(AEGP_LoopBehavior loopBehavior) : loops(loopBehavior.loops), reserved(loopBehavior.reserved) {}
    LoopBehavior(int loopsVal, int reservedVal) : loops(loopsVal), reserved(reservedVal) {}

    AEGP_LoopBehavior toAEGP()
    {
        AEGP_LoopBehavior loopBehavior;
        loopBehavior.loops = loops;
        loopBehavior.reserved = reserved;
        return loopBehavior;
    }

    std::tuple<int, int> ToTuple() { return std::make_tuple(loops, reserved); }

    int loops;
    int reserved;
};
/*typedef struct {
        AEGP_InterlaceLabel		il;
        AEGP_AlphaLabel			al;
        AEGP_PulldownPhase		pd;
        AEGP_LoopBehavior		loop;
        A_Ratio					pix_aspect_ratio;
        A_FpLong				native_fpsF;
        A_FpLong				conform_fpsF;
        A_long					depthL;
        A_Boolean				motion_dB;
} AEGP_FootageInterp;*/

class FootageLayerKey
{
  public:
    FootageLayerKey() : layer_idL(0), layer_indexL(0), nameAC(""), layer_draw_style(LayerDrawStyle::DOCUMENT_BOUNDS) {}
    FootageLayerKey(AEGP_FootageLayerKey footageLayerKey)
        : layer_idL(footageLayerKey.layer_idL), layer_indexL(footageLayerKey.layer_indexL),
          nameAC(footageLayerKey.nameAC), layer_draw_style(LayerDrawStyle(footageLayerKey.layer_draw_style))
    {
    }
    FootageLayerKey(int layerId, int layerIndex, std::string name, LayerDrawStyle layerDrawStyle)
        : layer_idL(layerId), layer_indexL(layerIndex), nameAC(name), layer_draw_style(layerDrawStyle)
    {
    }

    AEGP_FootageLayerKey toAEGP()
    {
        AEGP_FootageLayerKey footageLayerKey;
        footageLayerKey.layer_idL = layer_idL;
        footageLayerKey.layer_indexL = layer_indexL;
        strcpy(footageLayerKey.nameAC, nameAC.c_str());
        footageLayerKey.layer_draw_style = AEGP_LayerDrawStyle(layer_draw_style);
        return footageLayerKey;
    }

    AEGP_FootageLayerKey defaultFootageLayerKey()
    {
        AEGP_FootageLayerKey footageLayerKey;
        footageLayerKey.layer_idL = AEGP_LayerID_UNKNOWN;
        footageLayerKey.layer_indexL = AEGP_LayerIndex_MERGED;
        strcpy(footageLayerKey.nameAC, "");
        footageLayerKey.layer_draw_style = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS;
        return footageLayerKey;
    }

    std::tuple<int, int, std::string, LayerDrawStyle> ToTuple()
    {
        return std::make_tuple(layer_idL, layer_indexL, nameAC, layer_draw_style);
    }

    int layer_idL;
    int layer_indexL;
    std::string nameAC;
    LayerDrawStyle layer_draw_style;
};

class FileSequenceImportOptions
{
  public:
    FileSequenceImportOptions() : all_in_folderB(FALSE), force_alphabeticalB(FALSE), start_frameL(0), end_frameL(0) {}
    FileSequenceImportOptions(AEGP_FileSequenceImportOptions fileSequenceImportOptions)
        : all_in_folderB(fileSequenceImportOptions.all_in_folderB),
          force_alphabeticalB(fileSequenceImportOptions.force_alphabeticalB),
          start_frameL(fileSequenceImportOptions.start_frameL), end_frameL(fileSequenceImportOptions.end_frameL)
    {
    }
    FileSequenceImportOptions(bool allInFolder, bool forceAlphabetical, int startFrame, int endFrame)
        : all_in_folderB(allInFolder), force_alphabeticalB(forceAlphabetical), start_frameL(startFrame),
          end_frameL(endFrame)
    {
    }

    AEGP_FileSequenceImportOptions toAEGP()
    {
        AEGP_FileSequenceImportOptions fileSequenceImportOptions;
        fileSequenceImportOptions.all_in_folderB = all_in_folderB;
        fileSequenceImportOptions.force_alphabeticalB = force_alphabeticalB;
        fileSequenceImportOptions.start_frameL = start_frameL;
        fileSequenceImportOptions.end_frameL = end_frameL;
        return fileSequenceImportOptions;
    }

    AEGP_FileSequenceImportOptions asSequence()
    {
        AEGP_FileSequenceImportOptions fileSequenceImportOptions;
        fileSequenceImportOptions.all_in_folderB = TRUE;
        fileSequenceImportOptions.force_alphabeticalB = TRUE;
        fileSequenceImportOptions.start_frameL = AEGP_ANY_FRAME;
        fileSequenceImportOptions.end_frameL = AEGP_ANY_FRAME;
        return fileSequenceImportOptions;
    }

    std::tuple<bool, bool, int, int> ToTuple()
    {
        return std::make_tuple(all_in_folderB, force_alphabeticalB, start_frameL, end_frameL);
    }

    bool all_in_folderB;
    bool force_alphabeticalB;
    int start_frameL;
    int end_frameL;
};

class Time
{
  public:
    Time() : value({0, 1}) {}
    Time(A_Time time) : value(time) {}
    Time(double seconds) { value = SecondsToTime(seconds); };
    Time(int frames) { value = FramesToTime(frames); };

    A_Time toTime() const { return value; }                   // Added const here
    double toSeconds() const { return TimeToSeconds(value); } // Added const here
    int toFrames() const { return TimeToFrames(value); }      // Added const here
    A_Time toAEGP() const { return value; }                   // Added const here

    A_Time value;
};

class Ratio // num is int, den is u_int
{
  public:
    Ratio() : num(0), den(1) {}
    Ratio(int numVal, unsigned int denVal) : num(numVal), den(denVal) {}
    Ratio(A_Ratio ratio) : num(ratio.num), den(ratio.den) {}
    Ratio(double value) : num(static_cast<int>(std::round(value * 100000))), den(100000) {}

    A_Ratio &toAEGP()
    {
        A_Ratio ratio{};
        ratio.num = num;
        ratio.den = den;
        return ratio;
    }

    std::tuple<int, unsigned int> ToTuple() { return std::make_tuple(num, den); }

    A_Ratio value() { return {num, den}; }

    int num;
    unsigned int den;
};

class FloatPoint
{
  public:
    FloatPoint() : x(0), y(0) {}
    FloatPoint(A_FloatPoint floatPoint) : x(floatPoint.x), y(floatPoint.y) {}
    FloatPoint(double xVal, double yVal) : x(xVal), y(yVal) {}

    A_FloatPoint toAEGP()
    {
        A_FloatPoint floatPoint;
        floatPoint.x = x;
        floatPoint.y = y;
        return floatPoint;
    }

    std::tuple<double, double> ToTuple() { return std::make_tuple(x, y); }

    double x;
    double y;
};

class FloatPoint3
{
  public:
    FloatPoint3() : x(0), y(0), z(0) {}
    FloatPoint3(A_FloatPoint3 floatPoint3) : x(floatPoint3.x), y(floatPoint3.y), z(floatPoint3.z) {}
    FloatPoint3(double xVal, double yVal, double zVal) : x(xVal), y(yVal), z(zVal) {}

    A_FloatPoint3 toAEGP()
    {
        A_FloatPoint3 floatPoint3;
        floatPoint3.x = x;
        floatPoint3.y = y;
        floatPoint3.z = z;
        return floatPoint3;
    }

    std::tuple<double, double, double> ToTuple() { return std::make_tuple(x, y, z); }

    double x;
    double y;
    double z;
};

class FloatRect
{
  public:
    FloatRect() : left(0), top(0), right(0), bottom(0) {}
    FloatRect(A_FloatRect floatRect)
        : left(floatRect.left), top(floatRect.top), right(floatRect.right), bottom(floatRect.bottom)
    {
    }
    FloatRect(double leftVal, double topVal, double rightVal, double bottomVal)
        : left(leftVal), top(topVal), right(rightVal), bottom(bottomVal)
    {
    }

    A_FloatRect toAEGP()
    {
        A_FloatRect floatRect;
        floatRect.left = left;
        floatRect.top = top;
        floatRect.right = right;
        floatRect.bottom = bottom;
        return floatRect;
    }

    std::tuple<double, double, double, double> ToTuple() { return std::make_tuple(left, top, right, bottom); }

    double left;
    double top;
    double right;
    double bottom;
};

class Matrix3
{
  public:
    Matrix3() : mat{0} {}
    Matrix3(A_Matrix3 matrix3)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                mat[i][j] = matrix3.mat[i][j];
            }
        }
    }
    Matrix3(double matVal[3][3])
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                mat[i][j] = matVal[i][j];
            }
        }
    }

    A_Matrix3 toAEGP()
    {
        A_Matrix3 matrix3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                matrix3.mat[i][j] = mat[i][j];
            }
        }
        return matrix3;
    }

    tk::vector<tk::vector<double>> ToVector()
    {
        tk::vector<tk::vector<double>> result;
        for (int i = 0; i < 3; i++)
        {
            tk::vector<double> row;
            for (int j = 0; j < 3; j++)
            {
                row.push_back(mat[i][j]);
            }
            result.push_back(row);
        }
        return result;
    }

    double mat[3][3];
};

class Matrix4
{
  public:
    Matrix4() : mat{0} {}
    Matrix4(A_Matrix4 matrix4)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = matrix4.mat[i][j];
            }
        }
    }
    Matrix4(double matVal[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mat[i][j] = matVal[i][j];
            }
        }
    }

    A_Matrix4 toAEGP()
    {
        A_Matrix4 matrix4;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrix4.mat[i][j] = mat[i][j];
            }
        }
        return matrix4;
    }

    tk::vector<tk::vector<double>> ToVector()
    {
        tk::vector<tk::vector<double>> result;
        for (int i = 0; i < 4; i++)
        {
            tk::vector<double> row;
            for (int j = 0; j < 4; j++)
            {
                row.push_back(mat[i][j]);
            }
            result.push_back(row);
        }
        return result;
    }

    double mat[4][4];
};

class LegacyRect
{
  public:
    LegacyRect() : top(0), left(0), bottom(0), right(0) {}
    LegacyRect(A_LegacyRect legacyRect)
        : top(legacyRect.top), left(legacyRect.left), bottom(legacyRect.bottom), right(legacyRect.right)
    {
    }
    LegacyRect(int topVal, int leftVal, int bottomVal, int rightVal)
        : top(topVal), left(leftVal), bottom(bottomVal), right(rightVal)
    {
    }

    A_LegacyRect toAEGP()
    {
        A_LegacyRect legacyRect;
        legacyRect.top = top;
        legacyRect.left = left;
        legacyRect.bottom = bottom;
        legacyRect.right = right;
        return legacyRect;
    }

    std::tuple<int, int, int, int> ToTuple() { return std::make_tuple(top, left, bottom, right); }

    int top;
    int left;
    int bottom;
    int right;
};

class LRect
{
  public:
    LRect() : left(0), top(0), right(0), bottom(0) {}
    LRect(A_LRect lRect) : left(lRect.left), top(lRect.top), right(lRect.right), bottom(lRect.bottom) {}
    LRect(int leftVal, int topVal, int rightVal, int bottomVal)
        : left(leftVal), top(topVal), right(rightVal), bottom(bottomVal)
    {
    }

    A_LRect toAEGP()
    {
        A_LRect lRect;
        lRect.left = left;
        lRect.top = top;
        lRect.right = right;
        lRect.bottom = bottom;
        return lRect;
    }

    std::tuple<int, int, int, int> ToTuple() { return std::make_tuple(left, top, right, bottom); }

    int left;
    int top;
    int right;
    int bottom;
};

class LPoint
{
  public:
    LPoint() : x(0), y(0) {}
    LPoint(A_LPoint lPoint) : x(lPoint.x), y(lPoint.y) {}
    LPoint(int xVal, int yVal) : x(xVal), y(yVal) {}

    A_LPoint toAEGP()
    {
        A_LPoint lPoint;
        lPoint.x = x;
        lPoint.y = y;
        return lPoint;
    }

    std::tuple<int, int> ToTuple() { return std::make_tuple(x, y); }

    int x;
    int y;
};

class FloatPolar
{
  public:
    FloatPolar() : radius(0), angle(0) {}
    FloatPolar(A_FloatPolar floatPolar) : radius(floatPolar.radius), angle(floatPolar.angle) {}
    FloatPolar(double radiusVal, double angleVal) : radius(radiusVal), angle(angleVal) {}

    A_FloatPolar toAEGP()
    {
        A_FloatPolar floatPolar;
        floatPolar.radius = radius;
        floatPolar.angle = angle;
        return floatPolar;
    }

    std::tuple<double, double> ToTuple() { return std::make_tuple(radius, angle); }

    double radius;
    double angle;
};
class Marker;
class MaskOutline;
class TextDocument;

/**
 * @class Marker
 * @brief Represents a Marker in Adobe After Effects.
 *
 * This class provides an interface for creating, duplicating, and manipulating
 * markers within After Effects projects. Markers are used to denote specific points
 * in time within a composition or layer and can contain additional metadata such
 * as comments, URLs, and cue point parameters.
 */
class Marker
{
  public:
    /**
     * @brief Constructs an empty Marker instance.
     */
    Marker() = default;

    /**
     * @brief Constructs a Marker instance with a given marker value pointer.
     *
     * @param markerP The marker value pointer to be associated with this Marker instance.
     */
    Marker(MarkerValPtr markerP) : m_markerP(markerP) {}

    /**
     * @brief Destroys the Marker instance.
     */
    ~Marker() = default;

    /**
     * @brief Creates a new marker with default settings.
     *
     * @return Marker The newly created Marker instance.
     */
    static Marker createMarker();

    /**
     * @brief Duplicates the current marker.
     *
     * @return Marker A new Marker instance that is a duplicate of the current marker.
     */
    Marker duplicateMarker();

    /**
     * @brief Sets the specified flag to a given value for the marker.
     *
     * @param flagType The flag type to set.
     * @param valueB The value to assign to the flag (true or false).
     */
    void setFlag(MarkerFlag flagType, bool valueB);

    /**
     * @brief Retrieves the value of the specified flag for the marker.
     *
     * @param flagType The flag type to query.
     * @return bool The value of the specified flag.
     */
    bool getFlag(MarkerFlag flagType);

    /**
     * @brief Retrieves the string value of the specified type for the marker.
     *
     * @param strType The string type to query.
     * @return std::string The string value of the specified type.
     */
    std::string getString(MarkerStringType strType);

    /**
     * @brief Sets the string value of the specified type for the marker.
     *
     * @param strType The string type to set.
     * @param unicodeP The new string value.
     * @param lengthL The length of the new string value.
     */
    void setString(MarkerStringType strType, const std::string &unicodeP);

    /**
     * @brief Returns the number of cue point parameters associated with the marker.
     *
     * @return int The number of cue point parameters.
     */
    int countCuePointParams();

    /**
     * @brief Retrieves the key and value of a specified cue point parameter.
     *
     * @param param_indexL The index of the cue point parameter to query.
     * @return std::tuple<std::string, std::string> A tuple containing the key and value of the cue point parameter.
     */
    std::tuple<std::string, std::string> getIndCuePointParam(int param_indexL);

    /**
     * @brief Sets the key and value of a specified cue point parameter.
     *
     * @param param_indexL The index of the cue point parameter to set.
     * @param unicodeKeyP The new key for the cue point parameter.
     * @param key_lengthL The length of the key.
     * @param unicodeValueP The new value for the cue point parameter.
     * @param value_lengthL The length of the value.
     */
    void setIndCuePointParam(int param_indexL, const std::string &unicodeKeyP, const std::string &unicodeValueP);

    /**
     * @brief Inserts a new cue point parameter at the specified index.
     *
     * @param param_indexL The index at which to insert the new cue point parameter.
     */
    void insertCuePointParam(int param_indexL);

    /**
     * @brief Deletes the cue point parameter at the specified index.
     *
     * @param param_indexL The index of the cue point parameter to delete.
     */
    void deleteIndCuePointParam(int param_indexL);

    /**
     * @brief Sets the duration of the marker.
     *
     * @param durationD The new duration in seconds.
     */
    void setDuration(double durationD);

    /**
     * @brief Returns the duration of the marker.
     *
     * @return double The duration in seconds.
     */
    double getDuration();

    /**
     * @brief Sets the label of the marker.
     *
     * @param value The new label value.
     */
    void setLabel(int value);

    /**
     * @brief Returns the label of the marker.
     *
     * @return int The label value.
     */
    int getLabel();

  private:
    MarkerValPtr m_markerP;
};

/**
 * @class MaskOutline
 * @brief Represents a mask outline in After Effects.
 *
 * This class provides functionalities to manipulate the outline of a mask,
 * including setting its openness, adding or removing vertices and feathers, and
 * modifying their properties.
 */

class MaskOutline
{
  public:
    MaskOutline() = default;
    MaskOutline(MaskOutlineValPtr mask_outlineP) : m_mask_outlineP(mask_outlineP){};
    ~MaskOutline() = default;

    /**
     * @brief Checks if the mask outline is open.
     *
     * An open mask does not connect its start and end points, whereas a closed mask does.
     *
     * @return bool True if the mask is open, false otherwise.
     */
    bool isOpen();
    /**
     * @brief Sets the mask outline to be open or closed.
     *
     * @param openB If true, sets the mask to be open. If false, sets the mask to be closed.
     */
    void setOpen(bool openB);

    /**
     * @brief Returns the number of segments in the mask.
     *
     * @return int The number of segments in the mask.
     */
    int numSegments();

    /**
     * @brief Returns the number of vertices in the mask.
     *
     * @return int The number of vertices in the mask.
     */
    MaskVertex getVertexInfo(int which_pointL);

    /**
     * @brief Sets the vertex information for the specified point.
     *
     * @param which_pointL The index of the vertex to set.
     */
    void setVertexInfo(int which_pointL, MaskVertex vertexP);

    /**
     * @brief Creates a new vertex at the specified position.
     *
     * @param insert_position The position at which to insert the new vertex.
     */
    void createVertex(int insert_position); // Creates a new vertex at the specified position
                                            /**
                                             * @brief Deletes the vertex at the specified index.
                                             *
                                             * @param index The index of the vertex to delete.
                                             */
    void deleteVertex(int index);           // Deletes the vertex at the specified index

    /**
     * @brief Returns the number of feathers in the mask.
     */
    int numFeathers(); // Returns the number of feathers in the mask

    /**
     * @brief Returns the feather information for the specified feather.
     *
     * FeatherInfo is defined in AEGeneral.hpp as:
     *
        struct FeatherInfo
        {
            A_long segment;
            PF_FpLong segment_sF;
            PF_FpLong radiusF;
            PF_FpShort ui_corner_angleF;
            PF_FpShort tensionF;
            AEGP_MaskFeatherInterp interp;
            AEGP_MaskFeatherType type;
          };
     *
     * @param which_featherL The index of the feather to query.
     *
     * @return FeatherInfo The feather information for the specified feather.
         */
    MaskFeather getFeatherInfo(int which_featherL); // Returns the feather information for
                                                    // the specified feather
    /**
     * @brief Sets the feather information for the specified feather.
     *
     * \param which_featherL
     * \param featherP
     */
    void setFeatherInfo(int which_featherL,
                        MaskFeather featherP); // Sets the feather information
                                               // for the specified feather

    /**
     * @brief Creates a new feather with the specified information.
     *
     * @param featherP0 The information for the new feather.
     *
     * @return int The index of the newly created feather.
     */
    int createFeather(MaskFeather featherP0); // Creates a new feather with the
                                              // specified information
    /**
     * @brief Deletes the feather at the specified index.
     *
     * @param index The index of the feather to delete.
     */
    void deleteFeather(int index); // Deletes the feather at the specified index

  private:
    MaskOutlineValPtr m_mask_outlineP;
};

/**
 * @class TextDocument
 * @brief Represents a text document in After Effects.
 *
 * Encapsulates a text layer's contents, allowing for the retrieval and setting
 * of the text string.
 */

class TextDocument
{
  public:
    TextDocument(TextDocumentPtr text_documentP) : m_text_documentP(text_documentP){};
    TextDocument() = default;
    ~TextDocument() = default;

    /**
     * @brief Returns the text of the document.
     *
     * @return std::string The text of the document.
     */
    std::string getText(); // Returns the text of the document

    /**
     * @brief Sets the text of the document.
     *
     * @param unicodePS The new text of the document.
     */
    void setText(const std::string &unicodePS); // Sets the text of the document

  private:
    TextDocumentPtr m_text_documentP;
};

#endif // TYPES_H
