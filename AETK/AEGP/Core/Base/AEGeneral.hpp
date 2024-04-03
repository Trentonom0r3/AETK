/*****************************************************************//**
 * \file   AEGeneral.hpp
 * \brief  General functions and utilities for After Effects SDK.
 * This File provides various utilities modernizing the After Effects SDK.
 * This is the lowest level of wrappers provided in this library.
 * All AE Types are wrapped in shared pointers with custom deleters (where necessary)
 * and all suites align with the AE SDK naming conventions.
 * 
 * For more detailed info, please refer to the After Effects SDK documentation.
 * For higher level abstractions, documentation is provided in the respective header files.
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef AE_MAIN_HPP
#define AE_MAIN_HPP
#define NOMINMAX
#include "Headers/AEConfig.h"

#ifdef AE_OS_WIN
#include <windows.h>
#endif

#include "AETK/AEGP/Core/Base/SuiteManager.hpp"
#include "AETK/AEGP/Exception/Exception.hpp"
#include "Headers/AE_GeneralPlug.h"
#include "Util/entry.h"
#include <unicode/unistr.h>
#include <any>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream> // For std::ostringstream
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>

template <class... Ts> struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

double TimeToSeconds(
    const A_Time &time); // Will find active comp and convert using frame rate
A_Time SecondsToTime(double seconds);
int TimeToFrames(const A_Time &time);

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
#define AE_CHECK(expr)                                                         \
    do                                                                         \
    {                                                                          \
        A_Err err = (expr);                                                    \
        if (err != A_Err_NONE)                                                 \
        {                                                                      \
            std::string errorMessage = GetErrorMessage(err);                   \
            throw AEException(errorMessage.c_str());                           \
        }                                                                      \
    } while (0)

class WorldPtr
{
  public:
    WorldPtr(AEGP_WorldH &world) : m_world(std::make_shared<AEGP_WorldH>(world)) {}

    AEGP_WorldH get() const { return *m_world; }

    void set(AEGP_WorldH world) { m_world = std::make_shared<AEGP_WorldH>(world); }

    void setUserAllocated(bool userAllocated) { this->userAllocated = userAllocated; }

    ~WorldPtr()
    {
        if (userAllocated)
		{
			SuiteManager::GetInstance()
				.GetSuiteHandler()
				.WorldSuite3()
				->AEGP_Dispose(*m_world.get());
		}
    }
    private:
  std::shared_ptr<AEGP_WorldH> m_world;
  bool userAllocated = false;

};

/**
 * @brief Define shared pointers for After Effects SDK types
 *
 */
typedef std::shared_ptr<AEGP_ProjectH> ProjectPtr;
typedef std::shared_ptr<AEGP_ItemH> ItemPtr;
typedef std::shared_ptr<AEGP_CompH> CompPtr;
typedef std::shared_ptr<AEGP_FootageH> FootagePtr;
typedef std::shared_ptr<AEGP_LayerH> LayerPtr;
typedef std::shared_ptr<AEGP_EffectRefH> EffectRefPtr;
typedef std::shared_ptr<AEGP_MaskRefH> MaskRefPtr;
typedef std::shared_ptr<AEGP_StreamRefH> StreamRefPtr;
typedef std::shared_ptr<AEGP_RenderLayerContextH> RenderLayerContextPtr;
typedef std::shared_ptr<AEGP_PersistentBlobH> PersistentBlobPtr;
typedef std::shared_ptr<AEGP_MaskOutlineValH> MaskOutlineValPtr;
typedef std::shared_ptr<AEGP_CollectionH> CollectionPtr;
typedef std::shared_ptr<AEGP_Collection2H> Collection2Ptr;
typedef std::shared_ptr<AEGP_SoundDataH> SoundDataPtr;
typedef std::shared_ptr<AEGP_AddKeyframesInfoH> AddKeyframesInfoPtr;
typedef std::shared_ptr<AEGP_RenderReceiptH> RenderReceiptPtr;
//typedef std::shared_ptr<AEGP_WorldH> WorldPtr;
typedef std::shared_ptr<AEGP_RenderOptionsH> RenderOptionsPtr;
typedef std::shared_ptr<AEGP_LayerRenderOptionsH> LayerRenderOptionsPtr;
typedef std::shared_ptr<AEGP_FrameReceiptH> FrameReceiptPtr;
typedef std::shared_ptr<AEGP_RQItemRefH> RQItemRefPtr;
typedef std::shared_ptr<AEGP_OutputModuleRefH> OutputModuleRefPtr;
typedef std::shared_ptr<AEGP_TextDocumentH> TextDocumentPtr;
typedef std::shared_ptr<AEGP_MarkerValP> MarkerValPtr;
typedef std::shared_ptr<AEGP_TextOutlinesH> TextOutlinesPtr;
typedef std::shared_ptr<AEGP_PlatformWorldH> PlatformWorldPtr;
typedef std::shared_ptr<AEGP_ItemViewP> ItemViewPtr;
typedef std::shared_ptr<AEGP_ColorProfileP> ColorProfilePtr;
typedef std::shared_ptr<AEGP_ConstColorProfileP> ConstColorProfilePtr;
typedef std::shared_ptr<AEGP_TimeStamp> TimeStampPtr;

typedef std::shared_ptr<AEGP_MarkerValP> MarkerValPtr;
typedef std::shared_ptr<AEGP_StreamValue2> StreamValue2Ptr;
typedef std::shared_ptr<AEGP_MemHandle> MemHandlePtr;
typedef std::shared_ptr<AEGP_TimeStamp> TimeStampPtr;

/**
 * @brief Custom Deleters for After Effects SDK types
 * These Wrap AEGP_HANDLEs safely with std::shared_ptr, and call the appropriate
 * dispose function.
 */
class StreamRefDeleter
{
  public:
    void operator()(AEGP_StreamRefH *stream)
    {
        if (stream && *stream)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .StreamSuite2()
                ->AEGP_DisposeStream(*stream);
        }
    }
};

class MarkerDeleter
{
  public:
    void operator()(AEGP_MarkerValP *marker)
    {
        if (marker && *marker)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .MarkerSuite3()
                ->AEGP_DisposeMarker(*marker);
        }
    }
};

class WorldDeleter
{
  public:
    void operator()(AEGP_WorldH *world)
    {
        if (world && *world)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .WorldSuite3()
                ->AEGP_Dispose(*world);
        }
    }
};

class PlatformDeleter
{
  public:
    void operator()(AEGP_PlatformWorldH *platform)
    {
        if (platform && *platform)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .WorldSuite3()
                ->AEGP_DisposePlatformWorld(*platform);
        }
    }
};

class EffectDeleter
{
  public:
    void operator()(AEGP_EffectRefH *effect)
    {
        if (effect && *effect)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .EffectSuite4()
                ->AEGP_DisposeEffect(*effect);
        }
    }
};

class FootageDeleter
{
  public:
    void operator()(AEGP_FootageH *footage)
    {
        if (footage && *footage)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .FootageSuite5()
                ->AEGP_DisposeFootage(*footage);
        }
    }
};

class MaskDeleter
{
  public:
    void operator()(AEGP_MaskRefH *mask)
    {
        if (mask && *mask)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .MaskSuite6()
                ->AEGP_DisposeMask(*mask);
        }
    }
};

class RenderOptionsDeleter
{
  public:
    void operator()(AEGP_RenderOptionsH *renderOptions)
    {
        if (renderOptions && *renderOptions)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .RenderOptionsSuite3()
                ->AEGP_Dispose(*renderOptions);
        }
    }
};

class LayerRenderOptionsDeleter
{
  public:
    void operator()(AEGP_LayerRenderOptionsH *layerRenderOptions)
    {
        if (layerRenderOptions && *layerRenderOptions)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .LayerRenderOptionsSuite2()
                ->AEGP_Dispose(*layerRenderOptions);
        }
    }
};

class MemHandleDeleter
{
  public:
    void operator()(AEGP_MemHandle *memHandle)
    {
        if (memHandle && *memHandle)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .MemorySuite1()
                ->AEGP_FreeMemHandle(*memHandle);
        }
    }
};

class TextOutlineDeleter
{
  public:
    void operator()(AEGP_TextOutlinesH *memHandle)
    {
        if (memHandle && *memHandle)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .TextLayerSuite1()
                ->AEGP_DisposeTextOutlines(*memHandle);
        }
    }
};

class AddKeyframesInfoDeleter
{
  public:
    void operator()(AEGP_AddKeyframesInfoH *addKeyframesInfo)
    {
        if (addKeyframesInfo && *addKeyframesInfo)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .KeyframeSuite5()
                ->AEGP_EndAddKeyframes(true, *addKeyframesInfo);
        }
    }
};

class CollectionDeleter
{
  public:
    void operator()(AEGP_Collection2H *collection)
    {
        if (collection && *collection)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .CollectionSuite2()
                ->AEGP_DisposeCollection(*collection);
        }
    }
};

class FrameReceiptDeleter
{
  public:
    void operator()(AEGP_FrameReceiptH *frameReceipt)
    {
        if (frameReceipt && *frameReceipt)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .RenderSuite5()
                ->AEGP_CheckinFrame(*frameReceipt);
        }
    }
};

enum class AE_MemFlag
{
    NONE = AEGP_MemFlag_NONE,
    CLEAR = AEGP_MemFlag_CLEAR,
    QUIET = AEGP_MemFlag_QUIET
};

/**
 * @brief AE Memory Suite
 *
 * @details The Memory Suite provides access to the After Effects memory
 * management.
 *
 */
class MemorySuite1
{
  public:
    MemorySuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    MemorySuite1(const MemorySuite1 &) = delete;
    MemorySuite1 &operator=(const MemorySuite1 &) = delete;
    MemorySuite1(MemorySuite1 &&) = delete;
    MemorySuite1 &operator=(MemorySuite1 &&) = delete;

    /**
     * @brief Create a new memory handle.
     *
     * @param what : A String description of the memory handle.
     * @param size : The size of the memory handle.
     * @param flags : The flags for the memory handle.
     *
     * @return A shared pointer to the memory handle. Managed and disposed of by
     * the Custom Deleter.
     */
    MemHandlePtr NewMemHandle(const std::string &what, AEGP_MemSize size,
                              AE_MemFlag flags); /* New Mem Handle.*/
    /**
     * @brief Free a memory handle.
     *
     * @param memHandle : The memory handle to free.
     *
     */
    void FreeMemHandle(MemHandlePtr memHandle); /* Free Mem Handle.*/
    /**
     * @brief Lock a memory handle.
     *
     * @param memHandle : The memory handle to lock.
     * @param ptrToPtr : A pointer to a pointer to the memory handle.
     */
    void LockMemHandle(MemHandlePtr memHandle,
                       void **ptrToPtr);          /* Lock Mem Handle.*/
                                                  /**
                                                   * @brief Unlock a memory handle.
                                                   *
                                                   * @param memHandle : The memory handle to unlock.
                                                   */
    void UnlockMemHandle(MemHandlePtr memHandle); /* Unlock Mem Handle.*/
                                                  /**
                                                   * @brief Get the size of a memory handle.
                                                   *
                                                   * @param memHandle : The memory handle to get the size of.
                                                   *
                                                   * @return The size of the memory handle.
                                                   */
    AEGP_MemSize
    GetMemHandleSize(MemHandlePtr memHandle); /* Get Mem Handle Size.*/
                                              /**
                                               * @brief Resize a memory handle.
                                               *
                                               * @param what : A String description of the memory handle.
                                               * @param newSize : The new size of the memory handle.
                                               * @param memHandle : The memory handle to resize.
                                               */
    void ResizeMemHandle(const std::string &what, AEGP_MemSize newSize,
                         MemHandlePtr memHandle); /* Resize Mem Handle.*/

    /**
     * @brief Set Memory Reporting On.
     *
     * @param turnOn : A boolean to turn on memory reporting.
     */
    void SetMemReportingOn(bool turnOn);      /* Set Mem Reporting On.*/
                                              /**
                                               * @brief Get Memory Statistics.
                                               *
                                               * @return A tuple of the memory statistics, handles allocated.
                                               */
    std::tuple<A_long, A_long> GetMemStats(); /* Get Mem Stats.*/
    /**
     * @brief Create a shared pointer to a memory handle.
     *
     * \param memHandle
     * \return
     */
    static inline MemHandlePtr createPtr(AEGP_MemHandle memHandle)
    {
        return std::shared_ptr<AEGP_MemHandle>(new AEGP_MemHandle(memHandle),
                                               MemHandleDeleter());
    }

  private:
    SuiteManager &m_suiteManager;
};

/**
 * \brief Convert a UTF-8 string to a UTF-16 string.
 *
 * \param utf16String
 * \return
 */
inline std::string ConvertUTF16ToUTF8(const A_UTF16Char *utf16String)
{
    icu::UnicodeString unicodeString(
        reinterpret_cast<const UChar *>(utf16String));
    std::string utf8String;
    unicodeString.toUTF8String(utf8String);
    return utf8String;
}

/**
 * \brief Convert a UTF-16 string to a UTF-8 string.
 *
 * \param utf8String
 * \return
 */
inline std::vector<UChar>
ConvertUTF8ToUTF16UnSafe(const std::string &utf8String)
{
    icu::UnicodeString unicodeString = icu::UnicodeString::fromUTF8(utf8String);
    std::vector<UChar> utf16Vector(unicodeString.length() +
                                   1); // +1 for null terminator
    UErrorCode status = U_ZERO_ERROR;
    unicodeString.extract(&utf16Vector[0], unicodeString.length() + 1, status);

    // Check the status to ensure the operation was successful
    if (U_FAILURE(status))
    {
        // Handle the error, possibly clearing the vector or logging the failure
        utf16Vector.clear();
    }
    else
    {
        // Ensure null termination if needed. The extract method should already
        // do this, but this is just in case your logic requires it.
        utf16Vector[unicodeString.length()] = 0;
    }

    return utf16Vector;
}

/**
 * \brief Convert a UTF-8 string to a UTF-16 string.
 *
 * \param utf8String
 * \return
 */
inline std::vector<A_UTF16Char>
ConvertUTF8ToUTF16(const std::string &utf8String)
{
    auto utf16Vector = ConvertUTF8ToUTF16UnSafe(utf8String);
    return std::vector<A_UTF16Char>(utf16Vector.begin(), utf16Vector.end());
}

inline std::string memHandleToString(AEGP_MemHandle memHandle)
{
    A_Err err = A_Err_NONE;
    AEGP_SuiteHandler &suites = SuiteManager::GetInstance().GetSuiteHandler();
    A_UTF16Char *unicode_nameP = nullptr;
    MemorySuite1 memorySuite;
    MemHandlePtr ptr = memorySuite.createPtr(memHandle);

    AE_CHECK(suites.MemorySuite1()->AEGP_LockMemHandle(
        memHandle, reinterpret_cast<void **>(&unicode_nameP)));
    std::string stringVal = ConvertUTF16ToUTF8(unicode_nameP);
    AE_CHECK(suites.MemorySuite1()->AEGP_UnlockMemHandle(memHandle));

    return stringVal;
}

/**
 * @brief AE Platforms.
 */
enum class AE_Platform
{
    WIN = AEGP_Platform_WIN, /* Windows Platform.*/
    MAC = AEGP_Platform_MAC  /* Mac Platform.*/
};

/**
 * @brief AE Project Bit Depth
 */
enum class AE_ProjBitDepth
{
    _8 = AEGP_ProjBitDepth_8,   /* 8 Bit Depth.*/
    _16 = AEGP_ProjBitDepth_16, /* 16 Bit Depth.*/
    _32 = AEGP_ProjBitDepth_32, /* 32 Bit Depth.*/
    NUM_VALID_DEPTHS = AEGP_ProjBitDepth_NUM_VALID_DEPTHS
};

/**
 * @brief AE Color Profiles
 *
 *
 */
typedef std::tuple<double, double, double, double> ColorVal; /* Color Value.*/

/**
 * @brief Convert AE ColorVal to ColorVal
 *
 * @param color
 * @return ColorVal
 */
inline ColorVal toColorVal(const AEGP_ColorVal &color)
{
    return std::make_tuple(color.alphaF, color.redF, color.greenF, color.blueF);
}

/**
 * @brief Convert ColorVal to AE ColorVal
 *
 * @param color
 * @return AEGP_ColorVal
 */
inline AEGP_ColorVal toAEGP_ColorVal(const ColorVal &color)
{
    return {std::get<0>(color), std::get<1>(color), std::get<2>(color),
            std::get<3>(color)};
}

/**
 * @brief AE Camera Type
 *
 */
enum class AE_CameraType
{
    NONE = AEGP_CameraType_NONE,                 /* No Camera Type.*/
    PERSPECTIVE = AEGP_CameraType_PERSPECTIVE,   /* Perspective Camera Type.*/
    ORTHOGRAPHIC = AEGP_CameraType_ORTHOGRAPHIC, /* Orthographic Camera Type.*/
    NUM_TYPES = AEGP_CameraType_NUM_TYPES
};

/**
 * @brief AE Time Display Type
 *
 */
enum class AE_TimeDisplayType
{
    TIMECODE = AEGP_TimeDisplayType_TIMECODE, /* Timecode Display Type.*/
    FRAMES = AEGP_TimeDisplayType_FRAMES,     /* Frames Display Type.*/
    FEET_AND_FRAMES =
        AEGP_TimeDisplayType_FEET_AND_FRAMES /* Feet and Frames
                                                                                                            Display Type.*/
};

enum class AE_FilmSizeUnits
{
    NONE = AEGP_FilmSizeUnits_NONE,
    HORIZONTAL = AEGP_FilmSizeUnits_HORIZONTAL,
    VERTICAL = AEGP_FilmSizeUnits_VERTICAL,
    DIAGONAL = AEGP_FilmSizeUnits_DIAGONAL
};

enum class AE_LightType
{
    NONE = AEGP_LightType_NONE,
    PARALLEL = AEGP_LightType_PARALLEL,
    SPOT = AEGP_LightType_SPOT,
    POINT = AEGP_LightType_POINT,
    AMBIENT = AEGP_LightType_AMBIENT,
    RESERVED1 = AEGP_LightType_RESERVED1,
    NUM_TYPES = AEGP_LightType_NUM_TYPES
};

enum class AE_LightFalloffType
{
    NONE = AEGP_LightFalloff_NONE,
    SMOOTH = AEGP_LightFalloff_SMOOTH,
    INVERSE_SQUARE_CLAMPED = AEGP_LightFalloff_INVERSE_SQUARE_CLAMPED
};

enum class AE_FootageDepth
{
    _1 = AEGP_FootageDepth_1,
    _2 = AEGP_FootageDepth_2,
    _4 = AEGP_FootageDepth_4,
    _8 = AEGP_FootageDepth_8,
    _16 = AEGP_FootageDepth_16,
    _24 = AEGP_FootageDepth_24,
    _30 = AEGP_FootageDepth_30,
    _32 = AEGP_FootageDepth_32,
    GRAY_2 = AEGP_FootageDepth_GRAY_2,
    GRAY_4 = AEGP_FootageDepth_GRAY_4,
    GRAY_8 = AEGP_FootageDepth_GRAY_8,
    _48 = AEGP_FootageDepth_48,
    _64 = AEGP_FootageDepth_64,
    GRAY_16 = AEGP_FootageDepth_GRAY_16
};

enum class AE_FramesPerFoot
{
    _35MM = AEGP_FramesPerFoot_35MM,
    _16MM = AEGP_FramesPerFoot_16MM
};

enum class AE_TimeDisplayMode
{
    TIMECODE = AEGP_TimeDisplay_TIMECODE,
    FRAMES = AEGP_TimeDisplay_FRAMES
};

enum class AE_SourceTimecodeDisplayMode
{
    ZERO = AEGP_SourceTimecode_ZERO,
    SOURCE_TIMECODE = AEGP_SourceTimecode_SOURCE_TIMECODE
};

enum class AE_FramesDisplayMode
{
    ZERO_BASED = AEGP_Frames_ZERO_BASED,
    ONE_BASED = AEGP_Frames_ONE_BASED,
    TIMECODE_CONVERSION = AEGP_Frames_TIMECODE_CONVERSION
};

class TimeDisplay3
{
  public:
    TimeDisplay3()
    {
        m_timeDisplay.display_mode = AEGP_TimeDisplay_TIMECODE;
        m_timeDisplay.footage_display_mode = AEGP_SourceTimecode_ZERO;
        m_timeDisplay.display_dropframeB = FALSE;
        m_timeDisplay.use_feet_framesB = FALSE;
        m_timeDisplay.timebaseC = 0;
        m_timeDisplay.frames_per_footC = 0;
        m_timeDisplay.frames_display_mode = AEGP_Frames_ZERO_BASED;
    }

    TimeDisplay3(AEGP_TimeDisplay3 timeDisplay) : m_timeDisplay(timeDisplay) {}
    TimeDisplay3(AE_TimeDisplayMode displayMode,
                 AE_SourceTimecodeDisplayMode footageDisplayMode,
                 bool displayDropFrame, bool useFeetFrames, char timeBase,
                 char framesPerFoot, AE_FramesDisplayMode framesDisplayMode)
    {
        m_timeDisplay.display_mode = AEGP_TimeDisplayMode(displayMode);
        m_timeDisplay.footage_display_mode =
            AEGP_SourceTimecodeDisplayMode(footageDisplayMode);
        m_timeDisplay.display_dropframeB = displayDropFrame;
        m_timeDisplay.use_feet_framesB = useFeetFrames;
        m_timeDisplay.timebaseC = timeBase;
        m_timeDisplay.frames_per_footC = framesPerFoot;
        m_timeDisplay.frames_display_mode =
            AEGP_FramesDisplayMode(framesDisplayMode);
    }

    AEGP_TimeDisplay3 get() const { return m_timeDisplay; }

    void set(AEGP_TimeDisplay3 timeDisplay) { m_timeDisplay = timeDisplay; }

    AEGP_TimeDisplayMode getDisplayMode() const
    {
        return m_timeDisplay.display_mode;
    }

    void setDisplayMode(AEGP_TimeDisplayMode displayMode)
    {
        m_timeDisplay.display_mode = displayMode;
    }

    AEGP_SourceTimecodeDisplayMode getFootageDisplayMode() const
    {
        return m_timeDisplay.footage_display_mode;
    }

    void
    setFootageDisplayMode(AEGP_SourceTimecodeDisplayMode footageDisplayMode)
    {
        m_timeDisplay.footage_display_mode = footageDisplayMode;
    }

    bool getDisplayDropFrame() const
    {
        return m_timeDisplay.display_dropframeB;
    }

    void setDisplayDropFrame(bool displayDropFrame)
    {
        m_timeDisplay.display_dropframeB = displayDropFrame;
    }

    bool getUseFeetFrames() const { return m_timeDisplay.use_feet_framesB; }

    void setUseFeetFrames(bool useFeetFrames)
    {
        m_timeDisplay.use_feet_framesB = useFeetFrames;
    }

    char getTimeBase() const { return m_timeDisplay.timebaseC; }

    void setTimeBase(char timeBase) { m_timeDisplay.timebaseC = timeBase; }

    char getFramesPerFoot() const { return m_timeDisplay.frames_per_footC; }

    void setFramesPerFoot(char framesPerFoot)
    {
        m_timeDisplay.frames_per_footC = framesPerFoot;
    }

    AEGP_FramesDisplayMode getFramesDisplayMode() const
    {
        return m_timeDisplay.frames_display_mode;
    }

    void setFramesDisplayMode(AEGP_FramesDisplayMode framesDisplayMode)
    {
        m_timeDisplay.frames_display_mode = framesDisplayMode;
    }

  private:
    AEGP_TimeDisplay3 m_timeDisplay;
};

/**
 * @brief AE Project Suite
 *
 * @details The Project Suite provides access to the After Effects project.
 *
 *
 */
class ProjSuite6
{
  public:
    ProjSuite6() : m_suiteManager(SuiteManager::GetInstance()){};
    ProjSuite6(const ProjSuite6 &) = delete;
    ProjSuite6 &operator=(const ProjSuite6 &) = delete;
    ProjSuite6(ProjSuite6 &&) = delete;
    ProjSuite6 &operator=(ProjSuite6 &&) = delete;

    int GetNumProjects(); /* Get The Number of Projects in AE.*/
    ProjectPtr GetProjectByIndex(A_long projIndex); /* Get Project by Index.*/
    std::string GetProjectName(ProjectPtr project); /* Get Project Name.*/
    std::string GetProjectPath(ProjectPtr project); /* Get Project Path.*/
    ItemPtr
    GetProjectRootFolder(ProjectPtr project); /* Get Project Root Folder.*/
    void SaveProjectToPath(ProjectPtr project,
                           const std::string &path); /* Save Project to Path.*/
    TimeDisplay3
    GetProjectTimeDisplay(ProjectPtr project); /* Get Project Time Display.*/
    void SetProjectTimeDisplay(
        ProjectPtr project,
        TimeDisplay3 timeDisplay); /* Set Project Time Display.*/
    bool ProjectIsDirty(
        ProjectPtr project); /* Check if Project is Dirty (changed).*/
    void SaveProjectAs(ProjectPtr project,
                       const std::string &path); /* Save Project As.*/
    ProjectPtr NewProject();                     /* Create a New Project.*/
    ProjectPtr
    OpenProjectFromPath(const std::string &path); /* Open Project from Path.*/
    AE_ProjBitDepth
    GetProjectBitDepth(ProjectPtr project); /* Get Project Bit Depth.*/
    void
    SetProjectBitDepth(ProjectPtr project,
                       AE_ProjBitDepth bitDepth); /* Set Project Bit Depth.*/

  private:
    SuiteManager &m_suiteManager;
};

enum class AE_SoundEncoding
{
    UNSIGNED_PCM = AEGP_SoundEncoding_UNSIGNED_PCM,
    SIGNED_PCM = AEGP_SoundEncoding_SIGNED_PCM,
    FLOAT = AEGP_SoundEncoding_FLOAT,
    END = AEGP_SoundEncoding_END,
    BEGIN = AEGP_SoundEncoding_BEGIN
};

/**
 * @brief AE Sound Data Format
 *
 */
class SoundDataFormat
{
  public:
    SoundDataFormat()
    {
        m_soundDataFormat.sample_rateF = 0;
        m_soundDataFormat.encoding = AEGP_SoundEncoding_UNSIGNED_PCM;
        m_soundDataFormat.bytes_per_sampleL = 0;
        m_soundDataFormat.num_channelsL = 0;
    }

    SoundDataFormat(AEGP_SoundDataFormat soundDataFormat)
        : m_soundDataFormat(soundDataFormat)
    {
    }
    SoundDataFormat(double sampleRate, AE_SoundEncoding encoding,
                    A_long bytesPerSample, A_long numChannels)
    {
        m_soundDataFormat.sample_rateF = sampleRate;
        m_soundDataFormat.encoding = AEGP_SoundEncoding(encoding);
        m_soundDataFormat.bytes_per_sampleL = bytesPerSample;
        m_soundDataFormat.num_channelsL = numChannels;
    }

    /**
     * @brief Get the Sound Data Format object
     *
     * @return AEGP_SoundDataFormat
     */
    AEGP_SoundDataFormat get() const { return m_soundDataFormat; }

    void set(AEGP_SoundDataFormat soundDataFormat)
    {
        m_soundDataFormat = soundDataFormat;
    }

    double getSampleRate() const { return m_soundDataFormat.sample_rateF; }

    void setSampleRate(double sampleRate)
    {
        m_soundDataFormat.sample_rateF = sampleRate;
    }

    AE_SoundEncoding getEncoding() const
    {
        return AE_SoundEncoding(m_soundDataFormat.encoding);
    }

    void setEncoding(AE_SoundEncoding encoding)
    {
        m_soundDataFormat.encoding = AEGP_SoundEncoding(encoding);
    }

    A_long getBytesPerSample() const
    {
        return m_soundDataFormat.bytes_per_sampleL;
    }

    void setBytesPerSample(A_long bytesPerSample)
    {
        m_soundDataFormat.bytes_per_sampleL = bytesPerSample;
    }

    A_long getNumChannels() const { return m_soundDataFormat.num_channelsL; }

    void setNumChannels(A_long numChannels)
    {
        m_soundDataFormat.num_channelsL = numChannels;
    }

  private:
    AEGP_SoundDataFormat m_soundDataFormat;
};

enum class AE_ItemType
{
    NONE = AEGP_ItemType_NONE,
    FOLDER = AEGP_ItemType_FOLDER,
    COMP = AEGP_ItemType_COMP,
    SOLID = AEGP_ItemType_SOLID_defunct,
    FOOTAGE = AEGP_ItemType_FOOTAGE,
    NUM_TYPES = AEGP_ItemType_NUM_TYPES1
};

enum class AE_ItemFlag
{
    MISSING = AEGP_ItemFlag_MISSING,
    HAS_PROXY = AEGP_ItemFlag_HAS_PROXY,
    USING_PROXY = AEGP_ItemFlag_USING_PROXY,
    MISSING_PROXY = AEGP_ItemFlag_MISSING_PROXY,
    HAS_VIDEO = AEGP_ItemFlag_HAS_VIDEO,
    HAS_AUDIO = AEGP_ItemFlag_HAS_AUDIO,
    STILL = AEGP_ItemFlag_STILL,
    HAS_ACTIVE_AUDIO = AEGP_ItemFlag_HAS_ACTIVE_AUDIO
};

enum class AE_Label
{
    NONE = AEGP_Label_NONE,
    NO_LABEL = AEGP_Label_NO_LABEL,
    LABEL_1 = AEGP_Label_1,
    LABEL_2 = AEGP_Label_2,
    LABEL_3 = AEGP_Label_3,
    LABEL_4 = AEGP_Label_4,
    LABEL_5 = AEGP_Label_5,
    LABEL_6 = AEGP_Label_6,
    LABEL_7 = AEGP_Label_7,
    LABEL_8 = AEGP_Label_8,
    LABEL_9 = AEGP_Label_9,
    LABEL_10 = AEGP_Label_10,
    LABEL_11 = AEGP_Label_11,
    LABEL_12 = AEGP_Label_12,
    LABEL_13 = AEGP_Label_13,
    LABEL_14 = AEGP_Label_14,
    LABEL_15 = AEGP_Label_15,
    LABEL_16 = AEGP_Label_16,
    NUM_TYPES = AEGP_Label_NUMTYPES
};

enum class AE_PersistentType
{
    MACHINE_SPECIFIC = AEGP_PersistentType_MACHINE_SPECIFIC,
    MACHINE_INDEPENDENT = AEGP_PersistentType_MACHINE_INDEPENDENT,
    MACHINE_INDEPENDENT_RENDER = AEGP_PersistentType_MACHINE_INDEPENDENT_RENDER,
    MACHINE_INDEPENDENT_OUTPUT = AEGP_PersistentType_MACHINE_INDEPENDENT_OUTPUT,
    MACHINE_INDEPENDENT_COMPOSITION =
        AEGP_PersistentType_MACHINE_INDEPENDENT_COMPOSITION,
    MACHINE_SPECIFIC_TEXT = AEGP_PersistentType_MACHINE_SPECIFIC_TEXT,
    MACHINE_SPECIFIC_PAINT = AEGP_PersistentType_MACHINE_SPECIFIC_PAINT,
    MACHINE_SPECIFIC_EFFECTS = AEGP_PersistentType_MACHINE_SPECIFIC_EFFECTS,
    MACHINE_SPECIFIC_EXPRESSION_SNIPPETS =
        AEGP_PersistentType_MACHINE_SPECIFIC_EXPRESSION_SNIPPETS,
    MACHINE_SPECIFIC_SCRIPT_SNIPPETS =
        AEGP_PersistentType_MACHINE_SPECIFIC_SCRIPT_SNIPPETS,
    NUM_TYPES = AEGP_PersistentType_NUMTYPES
};

/**
 * @brief AE Item Suite
 *
 * @details The Item Suite provides access to the After Effects project items.
 *
 */
class ItemSuite9
{
  public:
    ItemSuite9() : m_suiteManager(SuiteManager::GetInstance()){};
    ItemSuite9(const ItemSuite9 &) = delete;
    ItemSuite9 &operator=(const ItemSuite9 &) = delete;
    ItemSuite9(ItemSuite9 &&) = delete;
    ItemSuite9 &operator=(ItemSuite9 &&) = delete;

    ItemPtr GetFirstProjItem(ProjectPtr project); /* Get First Project Item.*/
    ItemPtr GetNextProjItem(ProjectPtr project,
                            ItemPtr item); /* Get Next Project Item.*/
    ItemPtr GetActiveItem();               /* Get Active Item.*/
    bool IsItemSelected(ItemPtr item);     /* Check if Item is Selected.*/
    void SelectItem(ItemPtr item, bool select,
                    bool deselectOthers);                    /* Select Item.*/
    AE_ItemType GetItemType(ItemPtr item);                   /* Get Item Type.*/
    std::string GetTypeName(AE_ItemType itemType);           /* Get Type Name.*/
    std::string GetItemName(ItemPtr item);                   /* Get Item Name.*/
    void SetItemName(ItemPtr item, const std::string &name); /* Set Item Name.*/
    A_long GetItemID(ItemPtr item);                          /* Get Item ID.*/
    AE_ItemFlag GetItemFlags(ItemPtr item);            /* Get Item Flags.*/
    void SetItemUseProxy(ItemPtr item, bool useProxy); /* Set Item Use Proxy.*/
    ItemPtr GetItemParentFolder(ItemPtr item); /* Get Item Parent Folder.*/
    void SetItemParentFolder(ItemPtr item,
                             ItemPtr parentFolder); /* Set Item Parent Folder.*/
    A_Time GetItemDuration(ItemPtr item);           /* Get Item Duration.*/
    A_Time GetItemCurrentTime(ItemPtr item);        /* Get Item Current Time.*/
    std::tuple<A_long, A_long>
    GetItemDimensions(ItemPtr item); /* Get Item Dimensions.*/
    A_Ratio
    GetItemPixelAspectRatio(ItemPtr item); /* Get Item Pixel Aspect Ratio.*/
    void DeleteItem(ItemPtr item);         /* Delete Item.*/
    ItemPtr CreateNewFolder(const std::string &name,
                            ItemPtr parentFolder); /* Create New Folder.*/
    void SetItemCurrentTime(ItemPtr item,
                            A_Time newTime);  /* Set Item Current Time.*/
    std::string GetItemComment(ItemPtr item); /* Get Item Comment.*/
    void SetItemComment(ItemPtr item,
                        const std::string &comment); /* Set Item Comment.*/
    AE_Label GetItemLabel(ItemPtr item);             /* Get Item Label.*/
    void SetItemLabel(ItemPtr item, AE_Label label); /* Set Item Label.*/
    ItemViewPtr GetItemMRUView(ItemPtr item);        /* Get Item MRU View.*/
  private:
    SuiteManager &m_suiteManager;
};

class ItemViewSuite1
{
  public:
    ItemViewSuite1() : m_suiteManager(SuiteManager::GetInstance()){};

    A_Time GetItemViewPlaybackTime(
        ItemViewPtr itemView,
        bool &isCurrentlyPreviewing); /* Get Item View Playback Time.*/

  private:
    SuiteManager &m_suiteManager;
};

class SoundDataDeleter
{
  public:
    void operator()(AEGP_SoundDataH *soundData)
    {
        if (soundData && *soundData)
        {
            SuiteManager::GetInstance()
                .GetSuiteHandler()
                .SoundDataSuite1()
                ->AEGP_DisposeSoundData(*soundData);
        }
    }
};

class SoundDataSuite1
{
  public:
    SoundDataSuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    SoundDataSuite1(const SoundDataSuite1 &) = delete;
    SoundDataSuite1 &operator=(const SoundDataSuite1 &) = delete;
    SoundDataSuite1(SoundDataSuite1 &&) = delete;
    SoundDataSuite1 &operator=(SoundDataSuite1 &&) = delete;

    SoundDataPtr NewSoundData(const SoundDataFormat &soundFormat);

    SoundDataFormat GetSoundDataFormat(SoundDataPtr soundData);

    void LockSoundDataSamples(SoundDataPtr soundData, void **samples);
    void UnlockSoundDataSamples(SoundDataPtr soundData);
    int GetNumSamples(SoundDataPtr soundData);

  private:
    SuiteManager &m_suiteManager;
    inline SoundDataPtr toSoundDataPtr(AEGP_SoundDataH soundData)
    {
        return std::shared_ptr<AEGP_SoundDataH>(new AEGP_SoundDataH(soundData),
                                                SoundDataDeleter());
    }
};

/**
 * @brief AE Footage Suite
 *
 * @details The Footage Suite provides access to the After Effects project
 * footage.
 *
 */
inline AEGP_DownsampleFactor
toAEGP_DownsampleFactor(const std::tuple<A_short, A_short> &factor)
{
    return {std::get<0>(factor), std::get<1>(factor)};
}

/**
 * @brief Convert AEGP_DownsampleFactor to tuple
 *
 * @param factor
 * @return std::tuple<A_short, A_short>
 */
inline std::tuple<short, short>
toDownsampleFactor(const AEGP_DownsampleFactor &factor)
{
    return std::make_tuple(factor.xS, factor.yS);
}

enum class AE_CompFlag
{
    SHOW_ALL_SHY = AEGP_CompFlag_SHOW_ALL_SHY, /* Show All Shy.*/
    ENABLE_MOTION_BLUR =
        AEGP_CompFlag_ENABLE_MOTION_BLUR, /* Enable Motion Blur.*/
    ENABLE_TIME_FILTER =
        AEGP_CompFlag_ENABLE_TIME_FILTER,          /* Enable Time Filter.*/
    GRID_TO_FRAMES = AEGP_CompFlag_GRID_TO_FRAMES, /* Grid to Frames.*/
    GRID_TO_FIELDS = AEGP_CompFlag_GRID_TO_FIELDS, /* Grid to Fields.*/
    USE_LOCAL_DSF = AEGP_CompFlag_USE_LOCAL_DSF,   /* Use Local DSF.*/
    DRAFT_3D = AEGP_CompFlag_DRAFT_3D,             /* Draft 3D.*/
    SHOW_GRAPH = AEGP_CompFlag_SHOW_GRAPH          /* Show Graph.*/
};                                                 /* Comp Flag.*/

class CompSuite11
{
  public:
    CompSuite11() : m_suiteManager(SuiteManager::GetInstance()){};
    CompSuite11(const CompSuite11 &) = delete;
    CompSuite11 &operator=(const CompSuite11 &) = delete;
    CompSuite11(CompSuite11 &&) = delete;
    CompSuite11 &operator=(CompSuite11 &&) = delete;

    CompPtr GetCompFromItem(ItemPtr item); /* Get Comp from Item.*/
    ItemPtr GetItemFromComp(CompPtr comp); /* Get Item from Comp.*/
    std::tuple<short, short>
    GetCompDownsampleFactor(CompPtr comp); /* Get Comp Downsample Factor.*/
    void SetCompDownsampleFactor(CompPtr comp,
                                 const std::tuple<short, short>
                                     &factor); /* Set Comp Downsample Factor.*/
    ColorVal GetCompBGColor(CompPtr comp);     /* Get Comp BG Color.*/
    void SetCompBGColor(CompPtr comp,
                        const ColorVal &color); /* Set Comp BG Color.*/
    AE_CompFlag GetCompFlags(CompPtr comp);     /* Get Comp Flags.*/
    bool GetShowLayerNameOrSourceName(
        CompPtr comp); /* Get Show Layer Name or Source Name.*/
    void SetShowLayerNameOrSourceName(
        CompPtr comp,
        bool showLayerName); /* Set Show Layer Name or Source Name.*/
    bool GetShowBlendModes(CompPtr comp); /* Get Show Blend Modes.*/
    void SetShowBlendModes(CompPtr comp,
                           bool showBlendModes);     /* Set Show Blend Modes.*/
    double GetCompFramerate(CompPtr comp);           /* Get Comp Framerate.*/
    void SetCompFrameRate(CompPtr comp, double fps); /* Set Comp Frame Rate.*/
    std::tuple<A_Ratio, A_Ratio>
    GetCompShutterAnglePhase(CompPtr comp); /* Get Comp Shutter Angle Phase.*/
    std::tuple<A_Time, A_Time> GetCompShutterFrameRange(
        CompPtr comp, A_Time compTime); /* Get Comp Shutter Frame Range.*/
    int GetCompSuggestedMotionBlurSamples(
        CompPtr comp); /* Get Comp Suggested Motion Blur Samples.*/
    void SetCompSuggestedMotionBlurSamples(
        CompPtr comp, int samples); /* Set Comp Suggested Motion Blur Samples.*/
    int GetCompMotionBlurAdaptiveSampleLimit(
        CompPtr comp); /* Get
                        Comp Motion Blur Adaptive Sample Limit.*/
    void SetCompMotionBlurAdaptiveSampleLimit(
        CompPtr comp,
        int samples); /* Set Comp Motion Blur Adaptive Sample Limit.*/
    A_Time GetCompWorkAreaStart(CompPtr comp); /* Get Comp Work Area Start.*/
    A_Time
    GetCompWorkAreaDuration(CompPtr comp); /* Get Comp Work Area Duration.*/
    void SetCompWorkAreaStartAndDuration(
        CompPtr comp, A_Time workAreaStart,
        A_Time workAreaDuration); /* Set Comp Work Area Start and Duration.*/
    LayerPtr CreateSolidInComp(CompPtr comp, const std::string &name, int width,
                               int height, const ColorVal &color,
                               A_Time duration); /* Create Solid in Comp.*/
    LayerPtr
    CreateCameraInComp(CompPtr comp, const std::string &name,
                       A_FloatPoint centerPoint); /* Create Camera in Comp.*/
    LayerPtr
    CreateLightInComp(CompPtr comp, const std::string &name,
                      A_FloatPoint centerPoint); /* Create Light in Comp.*/
    CompPtr CreateComp(ItemPtr parentFolder, const std::string &name, int width,
                       int height, const A_Ratio &pixelAspectRatio,
                       A_Time duration,
                       const A_Ratio &framerate); /* Create Comp.*/
    Collection2Ptr GetNewCollectionFromCompSelection(
        AEGP_PluginID pluginId,
        CompPtr comp); /* Get New Collection from Comp Selection.*/
    A_Time
    GetCompDisplayStartTime(CompPtr comp); /* Get Comp Display Start Time.*/
    void
    SetCompDisplayStartTime(CompPtr comp,
                            A_Time startTime); /* Set Comp Display Start Time.*/
    void SetCompDuration(CompPtr comp, A_Time duration); /* Set Comp Duration.*/
    CompPtr DuplicateComp(CompPtr comp);                 /* Duplicate Comp.*/
    A_Time GetCompFrameDuration(CompPtr comp); /* Get Comp Frame Duration.*/
    CompPtr GetMostRecentlyUsedComp();         /* Get Most Recently Used Comp.*/
    LayerPtr
    CreateVectorLayerInComp(CompPtr comp); /* Create Vector Layer in Comp.*/
    StreamRefPtr
    GetNewCompMarkerStream(CompPtr parentComp); /* Get New Comp Marker Stream.*/
    bool
    GetCompDisplayDropFrame(CompPtr comp); /* Get Comp Display Drop Frame.*/
    void
    SetCompDisplayDropFrame(CompPtr comp,
                            bool dropFrame); /* Set Comp Display Drop Frame.*/
    void ReorderCompSelection(CompPtr comp,
                              int index); /* Reorder Comp Selection.*/
  private:
    SuiteManager &m_suiteManager;
};

inline StreamRefPtr toStreamRefPtr(AEGP_StreamRefH streamRef)
{
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamRef),
                                            StreamRefDeleter());
}

enum class AE_TransferFlags
{
    PRESERVE_ALPHA = AEGP_TransferFlag_PRESERVE_ALPHA,
    RANDOMIZE_DISSOLVE = AEGP_TransferFlag_RANDOMIZE_DISSOLVE
};

enum class AE_TrackMatte
{
    NO_TRACK_MATTE = AEGP_TrackMatte_NO_TRACK_MATTE,
    ALPHA = AEGP_TrackMatte_ALPHA,
    NOT_ALPHA = AEGP_TrackMatte_NOT_ALPHA,
    LUMA = AEGP_TrackMatte_LUMA,
    NOT_LUMA = AEGP_TrackMatte_NOT_LUMA
};

enum class AE_LayerQual
{
    NONE = AEGP_LayerQual_NONE,
    WIREFRAME = AEGP_LayerQual_WIREFRAME,
    DRAFT = AEGP_LayerQual_DRAFT,
    BEST = AEGP_LayerQual_BEST
};

enum class AE_LayerSamplingQual
{
    BILINEAR = AEGP_LayerSamplingQual_BILINEAR,
    BICUBIC = AEGP_LayerSamplingQual_BICUBIC
};

enum class AE_LayerFlag
{
    NONE = AEGP_LayerFlag_NONE,
    VIDEO_ACTIVE = AEGP_LayerFlag_VIDEO_ACTIVE,
    AUDIO_ACTIVE = AEGP_LayerFlag_AUDIO_ACTIVE,
    EFFECTS_ACTIVE = AEGP_LayerFlag_EFFECTS_ACTIVE,
    MOTION_BLUR = AEGP_LayerFlag_MOTION_BLUR,
    FRAME_BLENDING = AEGP_LayerFlag_FRAME_BLENDING,
    LOCKED = AEGP_LayerFlag_LOCKED,
    SHY = AEGP_LayerFlag_SHY,
    COLLAPSE = AEGP_LayerFlag_COLLAPSE,
    AUTO_ORIENT_ROTATION = AEGP_LayerFlag_AUTO_ORIENT_ROTATION,
    ADJUSTMENT_LAYER = AEGP_LayerFlag_ADJUSTMENT_LAYER,
    TIME_REMAPPING = AEGP_LayerFlag_TIME_REMAPPING,
    LAYER_IS_3D = AEGP_LayerFlag_LAYER_IS_3D,
    LOOK_AT_CAMERA = AEGP_LayerFlag_LOOK_AT_CAMERA,
    LOOK_AT_POI = AEGP_LayerFlag_LOOK_AT_POI,
    SOLO = AEGP_LayerFlag_SOLO,
    MARKERS_LOCKED = AEGP_LayerFlag_MARKERS_LOCKED,
    NULL_LAYER = AEGP_LayerFlag_NULL_LAYER,
    HIDE_LOCKED_MASKS = AEGP_LayerFlag_HIDE_LOCKED_MASKS,
    GUIDE_LAYER = AEGP_LayerFlag_GUIDE_LAYER,
    ADVANCED_FRAME_BLENDING = AEGP_LayerFlag_ADVANCED_FRAME_BLENDING,
    SUBLAYERS_RENDER_SEPARATELY = AEGP_LayerFlag_SUBLAYERS_RENDER_SEPARATELY,
    ENVIRONMENT_LAYER = AEGP_LayerFlag_ENVIRONMENT_LAYER
};

enum class AE_ObjectType
{
    NONE = AEGP_ObjectType_NONE,
    AV = AEGP_ObjectType_AV,
    LIGHT = AEGP_ObjectType_LIGHT,
    CAMERA = AEGP_ObjectType_CAMERA,
    TEXT = AEGP_ObjectType_TEXT,
    VECTOR = AEGP_ObjectType_VECTOR,
    RESERVED1 = AEGP_ObjectType_RESERVED1,
    RESERVED2 = AEGP_ObjectType_RESERVED2,
    RESERVED3 = AEGP_ObjectType_RESERVED3,
    RESERVED4 = AEGP_ObjectType_RESERVED4,
    RESERVED5 = AEGP_ObjectType_RESERVED5,
    NUM_TYPES = AEGP_ObjectType_NUM_TYPES
};

enum class AE_LTimeMode
{
    LayerTime = AEGP_LTimeMode_LayerTime,
    CompTime = AEGP_LTimeMode_CompTime
};

inline A_FloatRect
toA_FloatRect(const std::tuple<double, double, double, double> &rect)
{
    return {std::get<0>(rect), std::get<1>(rect), std::get<2>(rect),
            std::get<3>(rect)};
}

inline std::tuple<double, double, double, double>
toFloatRect(const A_FloatRect &rect)
{
    return std::make_tuple(rect.left, rect.top, rect.right, rect.bottom);
}

typedef std::tuple<double, double, double, double> FloatRect;

class LayerSuite9
{
  public:
    LayerSuite9() : m_suiteManager(SuiteManager::GetInstance()){};
    LayerSuite9(const LayerSuite9 &) = delete;
    LayerSuite9 &operator=(const LayerSuite9 &) = delete;
    LayerSuite9(LayerSuite9 &&) = delete;
    LayerSuite9 &operator=(LayerSuite9 &&) = delete;

    A_long GetCompNumLayers(CompPtr comp); /* Get Comp Num Layers.*/
    LayerPtr
    GetCompLayerByIndex(CompPtr comp,
                        A_long layerIndex);      /* Get Comp Layer By Index.*/
    LayerPtr GetActiveLayer();                   /* Get Active Layer.*/
    A_long GetLayerIndex(LayerPtr layer);        /* Get Layer Index.*/
    ItemPtr GetLayerSourceItem(LayerPtr layer);  /* Get Layer Source Item.*/
    A_long GetLayerSourceItemID(LayerPtr layer); /* Get Layer Source Item ID.*/
    CompPtr GetLayerParentComp(LayerPtr layer);  /* Get Layer Parent Comp.*/
    std::tuple<std::string, std::string>
    GetLayerName(LayerPtr layer);                 /* Get Layer Name.*/
    AE_LayerQual GetLayerQuality(LayerPtr layer); /* Get Layer Quality.*/
    void SetLayerQuality(LayerPtr layer,
                         AE_LayerQual quality); /* Set Layer Quality.*/
    AE_LayerFlag GetLayerFlags(LayerPtr layer); /* Get Layer Flags.*/
    void SetLayerFlag(LayerPtr layer, AE_LayerFlag singleFlag,
                      bool value);             /* Set Layer Flag.*/
    bool IsLayerVideoReallyOn(LayerPtr layer); /* Is Layer Video Really On.*/
    bool IsLayerAudioReallyOn(LayerPtr layer); /* Is Layer Audio Really On.*/
    A_Time
    GetLayerCurrentTime(LayerPtr layer,
                        AE_LTimeMode timeMode); /* Get Layer Current Time.*/
    A_Time GetLayerInPoint(LayerPtr layer,
                           AE_LTimeMode timeMode); /* Get Layer In Point.*/
    A_Time GetLayerDuration(LayerPtr layer,
                            AE_LTimeMode timeMode); /* Get Layer Duration.*/
    void SetLayerInPointAndDuration(
        LayerPtr layer, AE_LTimeMode timeMode, A_Time inPoint,
        A_Time duration);                  /* Set Layer In Point and Duration.*/
    A_Time GetLayerOffset(LayerPtr layer); /* Get Layer Offset.*/
    void SetLayerOffset(LayerPtr layer, A_Time offset); /* Set Layer Offset.*/
    A_Ratio GetLayerStretch(LayerPtr layer);            /* Get Layer Stretch.*/
    void SetLayerStretch(LayerPtr layer,
                         A_Ratio stretch); /* Set Layer Stretch.*/
    std::tuple<AE_TransferFlags, AE_TrackMatte>
    GetLayerTransferMode(LayerPtr layer); /* Get Layer Transfer Mode.*/
    void SetLayerTransferMode(
        LayerPtr layer, AE_TransferFlags flags,
        AE_TrackMatte trackMatte); /* Set Layer Transfer Mode.*/
    bool IsAddLayerValid(ItemPtr itemToAdd,
                         CompPtr intoComp); /* Is Add Layer Valid.*/
    LayerPtr AddLayer(ItemPtr itemToAdd, CompPtr intoComp); /* Add Layer.*/
    void ReorderLayer(LayerPtr layer, A_long layerIndex);   /* Reorder Layer.*/
    FloatRect GetLayerMaskedBounds(LayerPtr layer, AE_LTimeMode timeMode,
                                   A_Time time); /* Get Layer Masked Bounds.*/
    AE_ObjectType
    GetLayerObjectType(LayerPtr layer); /* Get Layer Object Type.*/
    bool IsLayer3D(LayerPtr layer);     /* Is Layer 3D.*/
    bool IsLayer2D(LayerPtr layer);     /* Is Layer 2D.*/
    bool IsVideoActive(LayerPtr layer, AE_LTimeMode timeMode,
                       A_Time time); /* Is Video Active.*/
    bool IsLayerUsedAsTrackMatte(
        LayerPtr layer,
        bool fillMustBeActive); /* Is Layer Used As Track Matte.*/
    bool
    DoesLayerHaveTrackMatte(LayerPtr layer); /* Does Layer Have Track Matte.*/
    A_Time
    ConvertCompToLayerTime(LayerPtr layer,
                           A_Time compTime); /* Convert Comp To Layer Time.*/
    A_Time
    ConvertLayerToCompTime(LayerPtr layer,
                           A_Time layerTime); /* Convert Layer To Comp Time.*/
    A_long GetLayerDancingRandValue(
        LayerPtr layer, A_Time compTime); /* Get Layer Dancing Rand Value.*/
    AEGP_LayerIDVal GetLayerID(LayerPtr layer); /* Get Layer ID.*/
    A_Matrix4
    GetLayerToWorldXform(LayerPtr layer,
                         A_Time compTime); /* Get Layer To World Xform.*/
    A_Matrix4 GetLayerToWorldXformFromView(
        LayerPtr layer, A_Time viewTime,
        A_Time compTime); /* Get Layer To World Xform From View.*/
    void SetLayerName(LayerPtr layer,
                      const std::string &newName); /* Set Layer Name.*/
    LayerPtr GetLayerParent(LayerPtr layer);       /* Get Layer Parent.*/
    void SetLayerParent(LayerPtr layer,
                        LayerPtr parentLayer);   /* Set Layer Parent.*/
    void DeleteLayer(LayerPtr layer);            /* Delete Layer.*/
    LayerPtr DuplicateLayer(LayerPtr origLayer); /* Duplicate Layer.*/
    LayerPtr
    GetLayerFromLayerID(CompPtr parentComp,
                        AEGP_LayerIDVal id);    /* Get Layer From Layer ID.*/
    AEGP_LabelID GetLayerLabel(LayerPtr layer); /* Get Layer Label.*/
    void SetLayerLabel(LayerPtr layer,
                       AEGP_LabelID label); /* Set Layer Label.*/
    AE_LayerSamplingQual
    GetLayerSamplingQuality(LayerPtr layer); /* Get Layer Sampling Quality.*/
    void SetLayerSamplingQuality(
        LayerPtr layer,
        AE_LayerSamplingQual quality); /* Set Layer Sampling Quality.*/
    LayerPtr GetTrackMatteLayer(LayerPtr layer); /* Get Track Matte Layer.*/
    void SetTrackMatte(LayerPtr layer, LayerPtr trackMatteLayer,
                       AE_TrackMatte trackMatteType); /* Set Track Matte.*/
    void RemoveTrackMatte(LayerPtr layer);            /* Remove Track Matte.*/

  private:
    SuiteManager &m_suiteManager;
};

bool isLayerValid(ItemPtr item, CompPtr comp);

enum class AE_LayerStream
{
    // Valid for all layer types
    ANCHORPOINT = AEGP_LayerStream_ANCHORPOINT,
    POSITION = AEGP_LayerStream_POSITION,
    SCALE = AEGP_LayerStream_SCALE,
    ROTATION = AEGP_LayerStream_ROTATION,
    ROTATE_Z = AEGP_LayerStream_ROTATE_Z,
    OPACITY = AEGP_LayerStream_OPACITY,
    AUDIO = AEGP_LayerStream_AUDIO,
    MARKER = AEGP_LayerStream_MARKER,
    TIME_REMAP = AEGP_LayerStream_TIME_REMAP,
    ROTATE_X = AEGP_LayerStream_ROTATE_X,
    ROTATE_Y = AEGP_LayerStream_ROTATE_Y,
    ORIENTATION = AEGP_LayerStream_ORIENTATION,
    TEXT = AEGP_LayerStream_SOURCE_TEXT,
    // only valid for AEGP_ObjectType == AEGP_ObjectType_CAMERA
    ZOOM = AEGP_LayerStream_ZOOM,
    DEPTH_OF_FIELD = AEGP_LayerStream_DEPTH_OF_FIELD,
    FOCUS_DISTANCE = AEGP_LayerStream_FOCUS_DISTANCE,
    APERTURE = AEGP_LayerStream_APERTURE,
    BLUR_LEVEL = AEGP_LayerStream_BLUR_LEVEL,
    IRIS_SHAPE = AEGP_LayerStream_IRIS_SHAPE,
    IRIS_ROTATION = AEGP_LayerStream_IRIS_ROTATION,
    IRIS_ROUNDNESS = AEGP_LayerStream_IRIS_ROUNDNESS,
    IRIS_ASPECT_RATIO = AEGP_LayerStream_IRIS_ASPECT_RATIO,
    IRIS_DIFFRACTION_FRINGE = AEGP_LayerStream_IRIS_DIFFRACTION_FRINGE,
    IRIS_HIGHLIGHT_GAIN = AEGP_LayerStream_IRIS_HIGHLIGHT_GAIN,
    IRIS_HIGHLIGHT_THRESHOLD = AEGP_LayerStream_IRIS_HIGHLIGHT_THRESHOLD,
    IRIS_HIGHLIGHT_SATURATION = AEGP_LayerStream_IRIS_HIGHLIGHT_SATURATION,

    // only valid for AEGP_ObjectType == AEGP_ObjectType_LIGHT
    INTENSITY = AEGP_LayerStream_INTENSITY,
    COLOR = AEGP_LayerStream_COLOR,
    CONE_ANGLE = AEGP_LayerStream_CONE_ANGLE,
    CONE_FEATHER = AEGP_LayerStream_CONE_FEATHER,
    SHADOW_DARKNESS = AEGP_LayerStream_SHADOW_DARKNESS,
    SHADOW_DIFFUSION = AEGP_LayerStream_SHADOW_DIFFUSION,
    LIGHT_FALLOFF_TYPE = AEGP_LayerStream_LIGHT_FALLOFF_TYPE,
    LIGHT_FALLOFF_START = AEGP_LayerStream_LIGHT_FALLOFF_START,
    LIGHT_FALLOFF_DISTANCE = AEGP_LayerStream_LIGHT_FALLOFF_DISTANCE,

    // only valid for AEGP_ObjectType == AEGP_ObjectType_AV
    ACCEPTS_SHADOWS = AEGP_LayerStream_ACCEPTS_SHADOWS,
    ACCEPTS_LIGHTS = AEGP_LayerStream_ACCEPTS_LIGHTS,
    AMBIENT_COEFF = AEGP_LayerStream_AMBIENT_COEFF,
    DIFFUSE_COEFF = AEGP_LayerStream_DIFFUSE_COEFF,
    SPECULAR_INTENSITY = AEGP_LayerStream_SPECULAR_INTENSITY,
    SPECULAR_SHININESS = AEGP_LayerStream_SPECULAR_SHININESS,
    CASTS_SHADOWS = AEGP_LayerStream_CASTS_SHADOWS,
    LIGHT_TRANSMISSION = AEGP_LayerStream_LIGHT_TRANSMISSION,
    METAL = AEGP_LayerStream_METAL,
    REFLECTION_INTENSITY = AEGP_LayerStream_REFLECTION_INTENSITY,
    REFLECTION_SHARPNESS = AEGP_LayerStream_REFLECTION_SHARPNESS,
    REFLECTION_ROLLOFF = AEGP_LayerStream_REFLECTION_ROLLOFF,
    TRANSPARENCY_COEFF = AEGP_LayerStream_TRANSPARENCY_COEFF,
    TRANSPARENCY_ROLLOFF = AEGP_LayerStream_TRANSPARENCY_ROLLOFF,
    INDEX_OF_REFRACTION = AEGP_LayerStream_INDEX_OF_REFRACTION,
    EXTRUSION_BEVEL_STYLE = AEGP_LayerStream_EXTRUSION_BEVEL_STYLE,
    EXTRUSION_BEVEL_DIRECTION = AEGP_LayerStream_EXTRUSION_BEVEL_DIRECTION,
    EXTRUSION_BEVEL_DEPTH = AEGP_LayerStream_EXTRUSION_BEVEL_DEPTH,
    EXTRUSION_HOLE_BEVEL_DEPTH = AEGP_LayerStream_EXTRUSION_HOLE_BEVEL_DEPTH,
    EXTRUSION_DEPTH = AEGP_LayerStream_EXTRUSION_DEPTH,
    PLANE_CURVATURE = AEGP_LayerStream_PLANE_CURVATURE,
    PLANE_SUBDIVISION = AEGP_LayerStream_PLANE_SUBDIVISION
};

enum class AE_MaskStream
{
    OUTLINE = AEGP_MaskStream_OUTLINE,
    OPACITY = AEGP_MaskStream_OPACITY,
    FEATHER = AEGP_MaskStream_FEATHER,
    EXPANSION = AEGP_MaskStream_EXPANSION
};

enum class AE_StreamFlag
{
    NONE = AEGP_StreamFlag_NONE,
    HAS_MIN = AEGP_StreamFlag_HAS_MIN,
    HAS_MAX = AEGP_StreamFlag_HAS_MAX,
    IS_SPATIAL = AEGP_StreamFlag_IS_SPATIAL
};

enum class AE_KeyInterp
{
    NONE = AEGP_KeyInterp_NONE,
    LINEAR = AEGP_KeyInterp_LINEAR,
    BEZIER = AEGP_KeyInterp_BEZIER,
    HOLD = AEGP_KeyInterp_HOLD
};

enum class AE_KeyInterpMask
{
    NONE = AEGP_KeyInterpMask_NONE,
    LINEAR = AEGP_KeyInterpMask_LINEAR,
    BEZIER = AEGP_KeyInterpMask_BEZIER,
    HOLD = AEGP_KeyInterpMask_HOLD,
    CUSTOM = AEGP_KeyInterpMask_CUSTOM,
    ANY = AEGP_KeyInterpMask_ANY
};

inline AEGP_TwoDVal toAEGP_TwoDVal(const std::tuple<double, double> &val)
{
    return {std::get<0>(val), std::get<1>(val)};
}

inline std::tuple<double, double> toTwoDVal(const AEGP_TwoDVal &val)
{
    return std::make_tuple(val.x, val.y);
}

inline AEGP_ThreeDVal
toAEGP_ThreeDVal(const std::tuple<double, double, double> &val)
{
    return {std::get<0>(val), std::get<1>(val), std::get<2>(val)};
}

inline std::tuple<double, double, double> toThreeDVal(const AEGP_ThreeDVal &val)
{
    return std::make_tuple(val.x, val.y, val.z);
}

enum class AE_StreamType
{
    NONE = AEGP_StreamType_NO_DATA,
    ThreeD_SPATIAL = AEGP_StreamType_ThreeD_SPATIAL,
    ThreeD = AEGP_StreamType_ThreeD,
    TwoD_SPATIAL = AEGP_StreamType_TwoD_SPATIAL,
    TwoD = AEGP_StreamType_TwoD,
    OneD = AEGP_StreamType_OneD,
    COLOR = AEGP_StreamType_COLOR,
    ARB = AEGP_StreamType_ARB,
    MARKER = AEGP_StreamType_MARKER,
    LAYER_ID = AEGP_StreamType_LAYER_ID,
    MASK_ID = AEGP_StreamType_MASK_ID,
    MASK = AEGP_StreamType_MASK,
    TEXT_DOCUMENT = AEGP_StreamType_TEXT_DOCUMENT
};

typedef std::tuple<double, double> AE_KeyframeEase;

inline AEGP_KeyframeEase
toAEGP_KeyframeEase(const std::tuple<double, double> &val)
{
    return {std::get<0>(val), std::get<1>(val)};
}

inline std::tuple<double, double> toKeyframeEase(const AEGP_KeyframeEase &val)
{
    return std::make_tuple(val.speedF, val.influenceF);
}

class StreamSuite6
{
  public:
    StreamSuite6() : m_suiteManager(SuiteManager::GetInstance()){};
    StreamSuite6(const StreamSuite6 &) = delete;

    StreamSuite6 &operator=(const StreamSuite6 &) = delete;

    StreamSuite6(StreamSuite6 &&) = delete;

    StreamSuite6 &operator=(StreamSuite6 &&) = delete;

    bool IsStreamLegal(LayerPtr layer,
                       AE_LayerStream whichStream); /* Is Stream Legal.*/
    bool CanVaryOverTime(StreamRefPtr stream);      /* Can Vary Over Time.*/
    AE_KeyInterpMask
    GetValidInterpolations(StreamRefPtr stream); /* Get Valid Interpolations.*/
    StreamRefPtr
    GetNewLayerStream(LayerPtr layer,
                      AE_LayerStream whichStream); /* Get New Layer Stream.*/
    A_long GetEffectNumParamStreams(
        EffectRefPtr effectRef); /* Get Effect Num Param Streams.*/
    StreamRefPtr GetNewEffectStreamByIndex(
        EffectRefPtr effectRef,
        A_long paramIndex); /* Get New Effect Stream By Index.*/
    StreamRefPtr
    GetNewMaskStream(MaskRefPtr maskRef,
                     AE_MaskStream whichStream); /* Get New Mask Stream.*/
    std::string GetStreamName(StreamRefPtr stream,
                              bool forceEnglish); /* Get Stream Name.*/
    std::string
    GetStreamUnitsText(StreamRefPtr stream,
                       bool forceEnglish); /* Get Stream Units Text.*/
    std::tuple<AE_StreamFlag, double, double>
    GetStreamProperties(StreamRefPtr stream);      /* Get Stream Properties.*/
    bool IsStreamTimevarying(StreamRefPtr stream); /* Is Stream Timevarying.*/
    AE_StreamType GetStreamType(StreamRefPtr stream); /* Get Stream Type.*/
    AEGP_StreamValue2
    GetNewStreamValue(StreamRefPtr stream, AE_LTimeMode timeMode, A_Time time,
                      bool preExpression);            /* Get New Stream Value.*/
    void DisposeStreamValue(AEGP_StreamValue2 value); /* Dispose Stream Value.*/
    void SetStreamValue(StreamRefPtr stream,
                        AEGP_StreamValue2 value); /* Set Stream Value.*/
    std::tuple<AEGP_StreamVal2, AE_StreamType>
    GetLayerStreamValue(LayerPtr layer, AE_LayerStream whichStream,
                        AE_LTimeMode timeMode, A_Time time,
                        bool preExpression); /* Get Layer Stream Value.*/

    StreamRefPtr
    DuplicateStreamRef(StreamRefPtr stream);    /* Duplicate Stream Ref.*/
    int GetUniqueStreamID(StreamRefPtr stream); /* Get Unique Stream ID.*/

    static inline StreamRefPtr createPtr(AEGP_StreamRefH streamRef)
    {
        return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamRef),
                                                StreamRefDeleter());
    }

  private:
    SuiteManager &m_suiteManager;
};

enum class AE_StreamGroupingType
{
    NONE = AEGP_StreamGroupingType_NONE,
    LEAF = AEGP_StreamGroupingType_LEAF,
    NAMED_GROUP = AEGP_StreamGroupingType_NAMED_GROUP,
    INDEXED_GROUP = AEGP_StreamGroupingType_INDEXED_GROUP
};

enum class AE_DynStreamFlag
{
    ACTIVE_EYEBALL = AEGP_DynStreamFlag_ACTIVE_EYEBALL,
    HIDDEN = AEGP_DynStreamFlag_HIDDEN,
    DISABLED = AEGP_DynStreamFlag_DISABLED,
    ELIDED = AEGP_DynStreamFlag_ELIDED,
    SHOWN_WHEN_EMPTY = AEGP_DynStreamFlag_SHOWN_WHEN_EMPTY,
    SKIP_REVEAL_WHEN_UNHIDDEN = AEGP_DynStreamFlag_SKIP_REVEAL_WHEN_UNHIDDEN
};

// TODO: Add support for AEGP_StreamSuite4
class DynamicStreamSuite4
{
  public:
    DynamicStreamSuite4() : m_suiteManager(SuiteManager::GetInstance()){};
    DynamicStreamSuite4(const DynamicStreamSuite4 &) = delete;
    DynamicStreamSuite4 &operator=(const DynamicStreamSuite4 &) = delete;
    DynamicStreamSuite4(DynamicStreamSuite4 &&) = delete;
    DynamicStreamSuite4 &operator=(DynamicStreamSuite4 &&) = delete;

    StreamRefPtr
    GetNewStreamRefForLayer(LayerPtr layer); /* Get New Stream Ref For Layer.*/
    StreamRefPtr
    GetNewStreamRefForMask(MaskRefPtr mask); /* Get New Stream Ref For Mask.*/
    A_long GetStreamDepth(StreamRefPtr stream); /* Get Stream Depth.*/
    AE_StreamGroupingType
    GetStreamGroupingType(StreamRefPtr stream); /* Get Stream Grouping Type.*/
    A_long
    GetNumStreamsInGroup(StreamRefPtr stream); /* Get Num Streams In Group.*/
    AE_DynStreamFlag
    GetDynamicStreamFlags(StreamRefPtr stream); /* Get Dynamic Stream Flags.*/
    void SetDynamicStreamFlag(StreamRefPtr stream, AE_DynStreamFlag oneFlag,
                              bool undoable,
                              bool set); /* Set Dynamic Stream Flag.*/
    StreamRefPtr
    GetNewStreamRefByIndex(StreamRefPtr parentGroup,
                           A_long index); /* Get New Stream Ref By Index.*/
    StreamRefPtr GetNewStreamRefByMatchname(
        StreamRefPtr parentGroup,
        const std::string &matchName); /* Get New Stream Ref By Matchname.*/
    void DeleteStream(StreamRefPtr stream); /* Delete Stream.*/
    void ReorderStream(StreamRefPtr stream,
                       A_long newIndex);         /* Reorder Stream.*/
    A_long DuplicateStream(StreamRefPtr stream); /* Duplicate Stream.*/
    void SetStreamName(StreamRefPtr stream,
                       const std::string &newName); /* Set Stream Name.*/
    bool CanAddStream(StreamRefPtr parentGroup,
                      const std::string &matchName); /* Can Add Stream.*/
    StreamRefPtr AddStream(StreamRefPtr parentGroup,
                           const std::string &matchName); /* Add Stream.*/
    std::string GetMatchname(StreamRefPtr stream);        /* Get Matchname.*/
    StreamRefPtr
    GetNewParentStreamRef(StreamRefPtr stream); /* Get New Parent Stream Ref.*/
    bool GetStreamIsModified(StreamRefPtr stream); /* Get Stream Is Modified.*/
    bool IsSeparationLeader(StreamRefPtr stream);  /* Is Separation Leader.*/
    bool AreDimensionsSeparated(
        StreamRefPtr leaderStream); /* Are Dimensions Separated.*/
    void SetDimensionsSeparated(StreamRefPtr leaderStream,
                                bool separated); /* Set Dimensions Separated.*/
    StreamRefPtr GetSeparationFollower(
        A_long dimension,
        StreamRefPtr leaderStream); /* Get Separation Follower.*/
    bool IsSeparationFollower(StreamRefPtr stream); /* Is Separation Follower.*/
    StreamRefPtr GetSeparationLeader(
        StreamRefPtr followerStream); /* Get Separation Leader.*/
    A_short
    GetSeparationDimension(StreamRefPtr stream); /* Get Separation Dimension.*/
  private:
    SuiteManager &m_suiteManager;
};
;
using StreamVal =
    std::variant<double, std::tuple<double, double>,
                 std::tuple<double, double, double>,
                 std::tuple<double, double, double, double>, MarkerValPtr, int,
                 MaskOutlineValPtr, TextDocumentPtr>;

using TwoDVal = std::tuple<double, double>;
using ThreeDVal = std::tuple<double, double, double>;
enum class AE_KeyframeFlag
{
    NONE = AEGP_KeyframeFlag_NONE,
    TEMPORAL_CONTINUOUS = AEGP_KeyframeFlag_TEMPORAL_CONTINUOUS,
    TEMPORAL_AUTOBEZIER = AEGP_KeyframeFlag_TEMPORAL_AUTOBEZIER,
    SPATIAL_CONTINUOUS = AEGP_KeyframeFlag_SPATIAL_CONTINUOUS,
    SPATIAL_AUTOBEZIER = AEGP_KeyframeFlag_SPATIAL_AUTOBEZIER,
    ROVING = AEGP_KeyframeFlag_ROVING
};

class KeyframeSuite5
{
  public:
    KeyframeSuite5() : m_suiteManager(SuiteManager::GetInstance()){};
    KeyframeSuite5(const KeyframeSuite5 &) = delete;
    KeyframeSuite5 &operator=(const KeyframeSuite5 &) = delete;
    KeyframeSuite5(KeyframeSuite5 &&) = delete;
    KeyframeSuite5 &operator=(KeyframeSuite5 &&) = delete;

    A_long GetStreamNumKFs(StreamRefPtr stream); /* Get Stream Num KFs.*/
    A_Time GetKeyframeTime(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                           AE_LTimeMode timeMode); /* Get Keyframe Time.*/
    AEGP_KeyframeIndex InsertKeyframe(StreamRefPtr stream,
                                      AE_LTimeMode timeMode,
                                      const A_Time &time); /* Insert Keyframe.*/
    void DeleteKeyframe(StreamRefPtr stream,
                        AEGP_KeyframeIndex keyIndex); /* Delete Keyframe.*/
    AEGP_StreamValue2 GetNewKeyframeValue(
        StreamRefPtr stream,
        AEGP_KeyframeIndex keyIndex); /* Get New Keyframe Value.*/
    void SetKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                          AEGP_StreamValue2 value); /* Set Keyframe Value.*/
    A_short GetStreamValueDimensionality(
        StreamRefPtr stream); /* Get Stream Value Dimensionality.*/
    A_short GetStreamTemporalDimensionality(
        StreamRefPtr stream); /* Get Stream Temporal Dimensionality.*/
    std::tuple<AEGP_StreamValue2, AEGP_StreamValue2>
    GetNewKeyframeSpatialTangents(
        StreamRefPtr stream,
        AEGP_KeyframeIndex keyIndex); /* Get New Keyframe Spatial Tangents.*/
    void SetKeyframeSpatialTangents(
        StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
        AEGP_StreamValue2 inTan,
        AEGP_StreamValue2 outTan); /* Set Keyframe Spatial Tangents.*/
    std::tuple<AE_KeyframeEase, AE_KeyframeEase>
    GetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                            A_long dimension); /* Get Keyframe Temporal Ease.*/
    void SetKeyframeTemporalEase(
        StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, A_long dimension,
        AE_KeyframeEase inEase,
        AE_KeyframeEase outEase); /* Set Keyframe Temporal Ease.*/
    AE_KeyframeFlag
    GetKeyframeFlags(StreamRefPtr stream,
                     AEGP_KeyframeIndex keyIndex); /* Get Keyframe Flags.*/
    void SetKeyframeFlag(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                         AE_KeyframeFlag flag,
                         bool value); /* Set Keyframe Flag.*/
    std::tuple<AE_KeyInterp, AE_KeyInterp> GetKeyframeInterpolation(
        StreamRefPtr stream,
        AEGP_KeyframeIndex keyIndex); /* Get Keyframe Interpolation.*/
    void SetKeyframeInterpolation(
        StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, AE_KeyInterp inInterp,
        AE_KeyInterp outInterp); /* Set Keyframe Interpolation.*/
    AddKeyframesInfoPtr
    StartAddKeyframes(StreamRefPtr stream); /* Start Add Keyframes.*/
    AEGP_KeyframeIndex AddKeyframes(AddKeyframesInfoPtr akH,
                                    AE_LTimeMode timeMode,
                                    const A_Time &time); /* Add Keyframes.*/
    void SetAddKeyframe(AddKeyframesInfoPtr akH, AEGP_KeyframeIndex keyIndex,
                        AEGP_StreamValue2 value); /* Set Add Keyframe.*/
    void EndAddKeyframes(AddKeyframesInfoPtr akH); /* End Add Keyframes.*/
    A_long GetKeyframeLabelColorIndex(
        StreamRefPtr stream,
        AEGP_KeyframeIndex keyIndex); /* Get Keyframe Label Color Index.*/
    void SetKeyframeLabelColorIndex(
        StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
        A_long keyLabel); /* Set Keyframe Label Color Index.*/

  private:
    SuiteManager &m_suiteManager;
    static inline AddKeyframesInfoPtr createPtr(AEGP_AddKeyframesInfoH ref)
    {
        return std::shared_ptr<AEGP_AddKeyframesInfoH>(
            new AEGP_AddKeyframesInfoH(ref), AddKeyframesInfoDeleter());
    }
};

class TextDocumentSuite1
{
  public:
    TextDocumentSuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    TextDocumentSuite1(const TextDocumentSuite1 &) = delete;
    TextDocumentSuite1 &operator=(const TextDocumentSuite1 &) = delete;
    TextDocumentSuite1(TextDocumentSuite1 &&) = delete;
    TextDocumentSuite1 &operator=(TextDocumentSuite1 &&) = delete;

    std::string getNewText(TextDocumentPtr text_documentH);
    void setText(TextDocumentPtr text_documentH, const std::string &unicodePS);

  private:
    SuiteManager &m_suiteManager;
};

/*enum {
        AEGP_MarkerString_NONE,

        AEGP_MarkerString_COMMENT,
        AEGP_MarkerString_CHAPTER,
        AEGP_MarkerString_URL,
        AEGP_MarkerString_FRAME_TARGET,
        AEGP_MarkerString_CUE_POINT_NAME,

        AEGP_MarkerString_NUMTYPES
};
typedef A_long AEGP_MarkerStringType;
*/

enum class AE_MarkerStringType
{
    COMMENT = AEGP_MarkerString_COMMENT,
    CHAPTER = AEGP_MarkerString_CHAPTER,
    URL = AEGP_MarkerString_URL,
    FRAME_TARGET = AEGP_MarkerString_FRAME_TARGET,
    CUE_POINT_NAME = AEGP_MarkerString_CUE_POINT_NAME
};

class MarkerSuite3
{
  public:
    MarkerSuite3() : m_suiteManager(SuiteManager::GetInstance()){};
    MarkerSuite3(const MarkerSuite3 &) = delete;
    MarkerSuite3 &operator=(const MarkerSuite3 &) = delete;
    MarkerSuite3(MarkerSuite3 &&) = delete;
    MarkerSuite3 &operator=(MarkerSuite3 &&) = delete;

    MarkerValPtr getNewMarker();
    void disposeMarker(MarkerValPtr markerP);
    MarkerValPtr duplicateMarker(MarkerValPtr markerP);
    void setMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType,
                       bool valueB);
    bool getMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType);
    std::string getMarkerString(MarkerValPtr markerP,
                                AE_MarkerStringType strType);
    void setMarkerString(MarkerValPtr markerP, AE_MarkerStringType strType,
                         const std::string &unicodeP, A_long lengthL);
    A_long countCuePointParams(MarkerValPtr markerP);
    std::tuple<std::string, std::string> getIndCuePointParam(

        MarkerValPtr markerP, A_long param_indexL);
    void setIndCuePointParam(MarkerValPtr markerP, A_long param_indexL,
                             const std::string &unicodeKeyP, A_long key_lengthL,
                             const std::string &unicodeValueP,
                             A_long value_lengthL);
    void insertCuePointParam(MarkerValPtr markerP, A_long param_indexL);
    void deleteIndCuePointParam(MarkerValPtr markerP, A_long param_indexL);
    void setMarkerDuration(MarkerValPtr markerP, const A_Time &durationPT);
    A_Time getMarkerDuration(MarkerValPtr markerP);
    void setMarkerLabel(MarkerValPtr markerP, A_long value);
    A_long getMarkerLabel(MarkerValPtr markerP);
    static inline MarkerValPtr createPtr(AEGP_MarkerValP ref)
    {
        return std::shared_ptr<AEGP_MarkerValP>(new AEGP_MarkerValP(ref),
                                                MarkerDeleter());
    }

  private:
    SuiteManager &m_suiteManager;
};

class TextLayerSuite1
{
  public:
    TextLayerSuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    TextLayerSuite1(const TextLayerSuite1 &) = delete;
    TextLayerSuite1 &operator=(const TextLayerSuite1 &) = delete;
    TextLayerSuite1(TextLayerSuite1 &&) = delete;
    TextLayerSuite1 &operator=(TextLayerSuite1 &&) = delete;

    TextOutlinesPtr getNewTextOutlines(LayerPtr layer,
                                       const A_Time &layer_time);
    int getNumTextOutlines(TextOutlinesPtr outlines);
    PF_PathOutlinePtr getIndexedTextOutline(TextOutlinesPtr outlines,
                                            int path_index);

  private:
    SuiteManager &m_suiteManager;
    static inline TextOutlinesPtr createPtr(AEGP_TextOutlinesH ref)
    {
        return std::shared_ptr<AEGP_TextOutlinesH>(new AEGP_TextOutlinesH(ref),
                                                   TextOutlineDeleter());
    }
};

enum class AE_EffectFlags
{
    NONE = AEGP_EffectFlags_NONE,
    ACTIVE = AEGP_EffectFlags_ACTIVE,
    AUDIO_ONLY = AEGP_EffectFlags_AUDIO_ONLY,
    AUDIO_TOO = AEGP_EffectFlags_AUDIO_TOO,
    MISSING = AEGP_EffectFlags_MISSING
};

class EffectSuite4
{
  public:
    EffectSuite4() : m_suiteManager(SuiteManager::GetInstance()){};
    EffectSuite4(const EffectSuite4 &) = delete;
    EffectSuite4 &operator=(const EffectSuite4 &) = delete;
    EffectSuite4(EffectSuite4 &&) = delete;
    EffectSuite4 &operator=(EffectSuite4 &&) = delete;

    A_long getLayerNumEffects(LayerPtr layer);
    EffectRefPtr getLayerEffectByIndex(LayerPtr layer,
                                       AEGP_EffectIndex layer_effect_index);
    AEGP_InstalledEffectKey
    getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref);
    std::tuple<PF_ParamType, PF_ParamDefUnion>
    getEffectParamUnionByIndex(EffectRefPtr effect_ref,
                               PF_ParamIndex param_index);
    AE_EffectFlags getEffectFlags(EffectRefPtr effect_ref);
    void setEffectFlags(EffectRefPtr effect_ref,
                        AE_EffectFlags effect_flags_set_mask,
                        AE_EffectFlags effect_flags);
    void reorderEffect(EffectRefPtr effect_ref, A_long effect_index);
    void effectCallGeneric(EffectRefPtr effect_ref, const A_Time *timePT,
                           PF_Cmd effect_cmd, void *effect_extraPV);
    void disposeEffect(EffectRefPtr effect_ref);
    EffectRefPtr applyEffect(LayerPtr layer,
                             AEGP_InstalledEffectKey installed_effect_key);
    void deleteLayerEffect(EffectRefPtr effect_ref);
    A_long getNumInstalledEffects();
    AEGP_InstalledEffectKey
    getNextInstalledEffect(AEGP_InstalledEffectKey installed_effect_key);
    std::string getEffectName(AEGP_InstalledEffectKey installed_effect_key);
    std::string
    getEffectMatchName(AEGP_InstalledEffectKey installed_effect_key);
    std::string getEffectCategory(AEGP_InstalledEffectKey installed_effect_key);
    EffectRefPtr duplicateEffect(EffectRefPtr original_effect_ref);
    A_u_long numEffectMask(EffectRefPtr effect_ref);
    AEGP_MaskIDVal getEffectMaskID(EffectRefPtr effect_ref,
                                   A_u_long mask_indexL);
    // Reulsts in MaskStream?
    StreamRefPtr addEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val);
    void removeEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val);
    StreamRefPtr setEffectMask(EffectRefPtr effect_ref, A_u_long mask_indexL,
                               AEGP_MaskIDVal id_val);

  private:
    SuiteManager &m_suiteManager;
    static inline EffectRefPtr createPtr(AEGP_EffectRefH ref)
    {
        return std::shared_ptr<AEGP_EffectRefH>(new AEGP_EffectRefH(ref),
                                                EffectDeleter());
    }
};

enum class AE_MaskMode
{
    NONE = PF_MaskMode_NONE,
    ADD = PF_MaskMode_ADD,
    SUBTRACT = PF_MaskMode_SUBTRACT,
    INTERSECT = PF_MaskMode_INTERSECT,
    LIGHTEN = PF_MaskMode_LIGHTEN,
    DARKEN = PF_MaskMode_DARKEN,
    DIFF = PF_MaskMode_DIFFERENCE,
    ACCUM = PF_MaskMode_ACCUM
};

enum class AE_MaskMBlur
{
    SAME_AS_LAYER = AEGP_MaskMBlur_SAME_AS_LAYER,
    OFF = AEGP_MaskMBlur_OFF,
    ON = AEGP_MaskMBlur_ON
};

enum class AE_MaskFeatherFalloff
{
    SMOOTH = AEGP_MaskFeatherFalloff_SMOOTH,
    LINEAR = AEGP_MaskFeatherFalloff_LINEAR
};

enum class AE_MaskFeatherInterp
{
    NORMAL = AEGP_MaskFeatherInterp_NORMAL,
    HOLD_CW = AEGP_MaskFeatherInterp_HOLD_CW
};

enum class AE_MaskFeatherType
{
    OUTER = AEGP_MaskFeatherType_OUTER,
    INNER = AEGP_MaskFeatherType_INNER
};
class MaskSuite6
{
  public:
    MaskSuite6() : m_suiteManager(SuiteManager::GetInstance()){};
    MaskSuite6(const MaskSuite6 &) = delete;
    MaskSuite6 &operator=(const MaskSuite6 &) = delete;
    MaskSuite6(MaskSuite6 &&) = delete;
    MaskSuite6 &operator=(MaskSuite6 &&) = delete;

    A_long getLayerNumMasks(LayerPtr aegp_layerH);
    MaskRefPtr getLayerMaskByIndex(LayerPtr aegp_layerH,
                                   AEGP_MaskIndex mask_indexL);
    void disposeMask(MaskRefPtr mask_refH);
    bool getMaskInvert(MaskRefPtr mask_refH);
    void setMaskInvert(MaskRefPtr mask_refH, bool invertB);
    AE_MaskMode getMaskMode(MaskRefPtr mask_refH);
    void setMaskMode(MaskRefPtr maskH, AE_MaskMode mode);
    AE_MaskMBlur getMaskMotionBlurState(MaskRefPtr mask_refH);
    void setMaskMotionBlurState(MaskRefPtr mask_refH, AE_MaskMBlur blur_state);
    AE_MaskFeatherFalloff getMaskFeatherFalloff(MaskRefPtr mask_refH);
    void setMaskFeatherFalloff(MaskRefPtr mask_refH,
                               AE_MaskFeatherFalloff feather_falloffP);
    AEGP_MaskIDVal getMaskID(MaskRefPtr mask_refH);
    MaskRefPtr createNewMask(LayerPtr layerH, A_long mask_indexPL0);
    void deleteMaskFromLayer(MaskRefPtr mask_refH);
    ColorVal getMaskColor(MaskRefPtr mask_refH);
    void setMaskColor(MaskRefPtr mask_refH, ColorVal colorP);
    bool getMaskLockState(MaskRefPtr mask_refH);
    void setMaskLockState(MaskRefPtr mask_refH, bool lockB);
    bool getMaskIsRotoBezier(MaskRefPtr mask_refH);
    void setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB);
    MaskRefPtr duplicateMask(MaskRefPtr orig_mask_refH);

  private:
    SuiteManager &m_suiteManager;
    inline MaskRefPtr createPtr(AEGP_MaskRefH ref)
    {
        return std::shared_ptr<AEGP_MaskRefH>(new AEGP_MaskRefH(ref),
                                              MaskDeleter());
    }
};

inline AEGP_MaskFeather createAEGP_MaskFeather()
{
    AEGP_MaskFeather feather;
    feather.segment = 0;
    feather.segment_sF = 0;
    feather.radiusF = 0;
    feather.ui_corner_angleF = 0;
    feather.tensionF = 0;
    feather.interp = AEGP_MaskFeatherInterp_NORMAL;
    feather.type = AEGP_MaskFeatherType_OUTER;
    return feather;
}

inline std::tuple<A_long, PF_FpLong, PF_FpLong, PF_FpShort, PF_FpShort,
                  AE_MaskFeatherInterp, AE_MaskFeatherType>
getAEGP_MaskFeatherInfo(const AEGP_MaskFeather &feather)
{
    return std::make_tuple(feather.segment, feather.segment_sF, feather.radiusF,
                           feather.ui_corner_angleF, feather.tensionF,
                           AE_MaskFeatherInterp(feather.interp),
                           AE_MaskFeatherType(feather.type));
}

struct MaskVertex
{
    double x, y;
    double tan_in_x, tan_in_y;
    double tan_out_x, tan_out_y;
    MaskVertex();
    MaskVertex(double x, double y, double tan_in_x, double tan_in_y,
               double tan_out_x, double tan_out_y)
        : x(x), y(y), tan_in_x(tan_in_x), tan_in_y(tan_in_y),
          tan_out_x(tan_out_x), tan_out_y(tan_out_y){};
    MaskVertex(PF_PathVertex vertex)
        : x(vertex.x), y(vertex.y), tan_in_x(vertex.tan_in_x),
          tan_in_y(vertex.tan_in_y), tan_out_x(vertex.tan_out_x),
          tan_out_y(vertex.tan_out_y){};

    PF_PathVertex toPF_PathVertex()
    {
        PF_PathVertex vertex;
        vertex.x = x;
        vertex.y = y;
        vertex.tan_in_x = tan_in_x;
        vertex.tan_in_y = tan_in_y;
        vertex.tan_out_x = tan_out_x;
        vertex.tan_out_y = tan_out_y;
        return vertex;
    }
};

struct FeatherInfo
{
    A_long segment;
    PF_FpLong segment_sF;
    PF_FpLong radiusF;
    PF_FpShort ui_corner_angleF;
    PF_FpShort tensionF;
    AEGP_MaskFeatherInterp interp;
    AEGP_MaskFeatherType type;
    FeatherInfo();
    FeatherInfo(AEGP_MaskFeather feather)
        : segment(feather.segment), segment_sF(feather.segment_sF),
          radiusF(feather.radiusF), ui_corner_angleF(feather.ui_corner_angleF),
          tensionF(feather.tensionF), interp(feather.interp),
          type(feather.type){};

    AEGP_MaskFeather toAEGP_MaskFeather()
    {
        AEGP_MaskFeather feather;
        feather.segment = segment;
        feather.segment_sF = segment_sF;
        feather.radiusF = radiusF;
        feather.ui_corner_angleF = ui_corner_angleF;
        feather.tensionF = tensionF;
        feather.interp = interp;
        feather.type = type;
        return feather;
    }
};

class MaskOutlineSuite3
{
  public:
    MaskOutlineSuite3() : m_suiteManager(SuiteManager::GetInstance()){};
    MaskOutlineSuite3(const MaskOutlineSuite3 &) = delete;
    MaskOutlineSuite3 &operator=(const MaskOutlineSuite3 &) = delete;
    MaskOutlineSuite3(MaskOutlineSuite3 &&) = delete;
    MaskOutlineSuite3 &operator=(MaskOutlineSuite3 &&) = delete;

    bool isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH);
    void setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH, bool openB);
    A_long getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH);
    AEGP_MaskVertex getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH,
                                             AEGP_VertexIndex which_pointL);
    void setMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH,
                                  AEGP_VertexIndex which_pointL,
                                  const AEGP_MaskVertex &vertexP);
    void createVertex(MaskOutlineValPtr mask_outlineH,
                      AEGP_VertexIndex insert_position);
    void deleteVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex index);
    A_long getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH);
    AEGP_MaskFeather
    getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                              AEGP_FeatherIndex which_featherL);
    void setMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                                   AEGP_VertexIndex which_featherL,
                                   const AEGP_MaskFeather &featherP);
    AEGP_FeatherIndex
    createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH,
                             const AEGP_MaskFeather &featherP0);
    void deleteMaskOutlineFeather(MaskOutlineValPtr mask_outlineH,
                                  AEGP_FeatherIndex index);

  private:
    SuiteManager &m_suiteManager;
    static inline MaskOutlineValPtr createPtr(AEGP_MaskOutlineValH ref)
    {
        return std::make_shared<AEGP_MaskOutlineValH>(ref);
    }
};

enum class AE_AlphaFlags
{
    PREMUL = AEGP_AlphaPremul,
    INVERTED = AEGP_AlphaInverted,
    ALPHA_IGNORE = AEGP_AlphaIgnore
};

inline AEGP_AlphaLabel createAEGP_AlphaLabel()
{
    AEGP_AlphaLabel label;
    label.flags = 0;
    label.redCu = 0;
    label.greenCu = 0;
    label.blueCu = 0;
    return label;
}

inline std::tuple<AEGP_AlphaFlags, A_u_char, A_u_char, A_u_char>
getAEGP_AlphaLabelInfo(const AEGP_AlphaLabel &label)
{
    return std::make_tuple(label.flags, label.redCu, label.greenCu,
                           label.blueCu);
}

enum class AE_PulldownPhase
{
    NO_PULLDOWN = AEGP_PulldownPhase_NO_PULLDOWN,
    WSSWW = AEGP_PulldownPhase_WSSWW,
    SSWWW = AEGP_PulldownPhase_SSWWW,
    SWWWS = AEGP_PulldownPhase_SWWWS,
    WWWSS = AEGP_PulldownPhase_WWWSS,
    WWSSW = AEGP_PulldownPhase_WWSSW,
    WWWSW = AEGP_PulldownPhase_WWWSW,
    WWSWW = AEGP_PulldownPhase_WWSWW,
    WSWWW = AEGP_PulldownPhase_WSWWW,
    SWWWW = AEGP_PulldownPhase_SWWWW,
    WWWWS = AEGP_PulldownPhase_WWWWS
};

inline AEGP_LoopBehavior createAEGP_LoopBehavior()
{
    AEGP_LoopBehavior behavior;
    behavior.loops = 0;
    behavior.reserved = 0;
    return behavior;
}

inline std::tuple<A_long, A_long>
getAEGP_LoopBehaviorInfo(const AEGP_LoopBehavior &behavior)
{
    return std::make_tuple(behavior.loops, behavior.reserved);
}

enum class AE_LayerDrawStyle
{
    LAYER_BOUNDS = AEGP_LayerDrawStyle_LAYER_BOUNDS,
    DOCUMENT_BOUNDS = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS
};

inline AEGP_FootageLayerKey createAEGP_FootageLayerKey()
{
    AEGP_FootageLayerKey key;
    key.layer_idL = AEGP_LayerID_UNKNOWN;
    key.layer_indexL = AEGP_LayerIndex_MERGED;
    key.nameAC[0] = '\0';
    key.layer_draw_style = AEGP_LayerDrawStyle_LAYER_BOUNDS;
    return key;
}

inline std::tuple<A_long, A_long, std::string, AEGP_LayerDrawStyle>
getAEGP_FootageLayerKeyInfo(const AEGP_FootageLayerKey &key)
{
    return std::make_tuple(key.layer_idL, key.layer_indexL, key.nameAC,
                           key.layer_draw_style);
}

inline AEGP_FileSequenceImportOptions createAEGP_FileSequenceImportOptions()
{
    AEGP_FileSequenceImportOptions options;
    options.all_in_folderB = true;
    options.force_alphabeticalB = true;
    options.start_frameL = 0;
    options.end_frameL = 0;
    return options;
}

inline std::tuple<bool, bool, A_long, A_long>
getAEGP_FileSequenceImportOptionsInfo(
    const AEGP_FileSequenceImportOptions &options)
{
    return std::make_tuple(options.all_in_folderB, options.force_alphabeticalB,
                           options.start_frameL, options.end_frameL);
}

#define FOOTAGE_MAIN_FILE_INDEX 0

enum class AE_InterpretationStyle
{
    NO_DIALOG_GUESS = AEGP_InterpretationStyle_NO_DIALOG_GUESS,
    DIALOG_OK = AEGP_InterpretationStyle_DIALOG_OK,
    NO_DIALOG_NO_GUESS = AEGP_InterpretationStyle_NO_DIALOG_NO_GUESS
};

class FootageSuite5
{
  public:
    FootageSuite5() : m_suiteManager(SuiteManager::GetInstance()){};
    FootageSuite5(const FootageSuite5 &) = delete;
    FootageSuite5 &operator=(const FootageSuite5 &) = delete;
    FootageSuite5(FootageSuite5 &&) = delete;
    FootageSuite5 &operator=(FootageSuite5 &&) = delete;

    FootagePtr getMainFootageFromItem(ItemPtr itemH);
    FootagePtr getProxyFootageFromItem(ItemPtr itemH);
    std::tuple<A_long, A_long> getFootageNumFiles(FootagePtr footageH);
    std::string getFootagePath(FootagePtr footageH, A_long frame_numL,
                               A_long file_indexL);
    AEGP_FootageSignature getFootageSignature(FootagePtr footageH);
    FootagePtr newFootage(

        std::string pathZ, AEGP_FootageLayerKey layer_infoP0,
        AEGP_FileSequenceImportOptions *sequence_optionsP0,
        AE_InterpretationStyle interp_style);
    ItemPtr addFootageToProject(FootagePtr footageH, ItemPtr folderH);
    void setItemProxyFootage(FootagePtr footageH, ItemPtr itemH);
    void replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH);
    void disposeFootage(FootagePtr footageH);
    AEGP_FootageInterp getFootageInterpretation(ItemPtr itemH, bool proxyB);
    void setFootageInterpretation(ItemPtr itemH, bool proxyB,
                                  const AEGP_FootageInterp *interpP);
    AEGP_FootageLayerKey getFootageLayerKey(FootagePtr footageH);
    FootagePtr newPlaceholderFootage(std::string nameZ, A_long width,
                                     A_long height, A_Time durationPT);
    FootagePtr newPlaceholderFootageWithPath(std::string pathZ,
                                             AE_Platform path_platform,
                                             AEIO_FileType file_type,
                                             A_long widthL, A_long heightL,
                                             A_Time durationPT);
    FootagePtr newSolidFootage(std::string nameZ, A_long width, A_long height,
                               ColorVal colorP);
    ColorVal getSolidFootageColor(ItemPtr itemH, bool proxyB);
    void setSolidFootageColor(ItemPtr itemH, bool proxyB, ColorVal colorP);
    void setSolidFootageDimensions(ItemPtr itemH, bool proxyB, A_long widthL,
                                   A_long heightL);
    AEGP_SoundDataFormat getFootageSoundDataFormat(FootagePtr footageH);
    AEGP_FileSequenceImportOptions
    getFootageSequenceImportOptions(FootagePtr footageH);

  private:
    SuiteManager &m_suiteManager;
    static inline FootagePtr createPtr(AEGP_FootageH ref)
    {
        return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(ref),
                                              FootageDeleter());
    }
};

enum class AE_PluginPathType
{
    PLUGIN = AEGP_GetPathTypes_PLUGIN,
    USER_PLUGIN = AEGP_GetPathTypes_USER_PLUGIN,
    ALLUSER_PLUGIN = AEGP_GetPathTypes_ALLUSER_PLUGIN,
    APP = AEGP_GetPathTypes_APP
};

class UtilitySuite6
{
  public:
    UtilitySuite6() : m_suiteManager(SuiteManager::GetInstance()){};
    UtilitySuite6(const UtilitySuite6 &) = delete;
    UtilitySuite6 &operator=(const UtilitySuite6 &) = delete;
    UtilitySuite6(UtilitySuite6 &&) = delete;
    UtilitySuite6 &operator=(UtilitySuite6 &&) = delete;

    void reportInfo(const std::string &info_string);
    void reportInfoUnicode(const std::string &info_string);
    std::tuple<A_short, A_short> getDriverPluginInitFuncVersion();
    std::tuple<A_short, A_short> getDriverImplementationVersion();
    void startQuietErrors();
    void endQuietErrors(bool report_quieted_errorsB);
    std::string getLastErrorMessage(A_long buffer_size);
    void startUndoGroup(const std::string &undo_name);
    void endUndoGroup();
    void *getMainHWND();
    void showHideAllFloaters(bool include_tool_palB);
    ColorVal getPaintPalForeColor();                       /*Brush Tool Panel*/
    ColorVal getPaintPalBackColor();                       /*Brush Tool Panel*/
    void setPaintPalForeColor(const ColorVal &fore_color); /*Brush Tool Panel*/
    void setPaintPalBackColor(const ColorVal &back_color); /*Brush Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalFillColor();   /*Character Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalStrokeColor(); /*Character Tool Panel*/
    void
    setCharPalFillColor(const ColorVal &fill_color); /*Character Tool Panel*/
    void setCharPalStrokeColor(
        const ColorVal &stroke_color);    /*Character Tool Panel*/
    bool charPalIsFillColorUIFrontmost(); /*Returns whether or not the fill
                                             color is frontmost. If it isn’t,
                                             the stroke color is frontmost.*/
    A_Ratio convertFpLongToHSFRatio(A_FpLong numberF);
    A_FpLong convertHSFRatioToFpLong(A_Ratio ratioR);
    void causeIdleRoutinesToBeCalled();
    bool getSuppressInteractiveUI();
    void writeToOSConsole(const std::string &text);
    void writeToDebugLog(const std::string &subsystem,
                         const std::string &eventType, const std::string &text);
    std::string getPluginPath(AE_PluginPathType path_type);

  private:
    SuiteManager &m_suiteManager;
};

enum class AE_RenderQueueState
{
    STOPPED = AEGP_RenderQueueState_STOPPED,
    PAUSED = AEGP_RenderQueueState_PAUSED,
    RENDERING = AEGP_RenderQueueState_RENDERING
};

enum class AE_RenderItemStatus
{
    NONE = AEGP_RenderItemStatus_NONE,
    WILL_CONTINUE = AEGP_RenderItemStatus_WILL_CONTINUE,
    NEEDS_OUTPUT = AEGP_RenderItemStatus_NEEDS_OUTPUT,
    UNQUEUED = AEGP_RenderItemStatus_UNQUEUED,
    QUEUED = AEGP_RenderItemStatus_QUEUED,
    RENDERING = AEGP_RenderItemStatus_RENDERING,
    USER_STOPPED = AEGP_RenderItemStatus_USER_STOPPED,
    ERR_STOPPED = AEGP_RenderItemStatus_ERR_STOPPED,
    DONE = AEGP_RenderItemStatus_DONE
};

enum class AE_LogType
{
    NONE = AEGP_LogType_NONE,
    ERRORS_ONLY = AEGP_LogType_ERRORS_ONLY,
    PLUS_SETTINGS = AEGP_LogType_PLUS_SETTINGS,
    PER_FRAME_INFO = AEGP_LogType_PER_FRAME_INFO
};

enum class AE_EmbeddingType
{
    NONE = AEGP_Embedding_NONE,
    NOTHING = AEGP_Embedding_NOTHING,
    LINK = AEGP_Embedding_LINK,
    LINK_AND_COPY = AEGP_Embedding_LINK_AND_COPY
};

enum class AE_PostRenderAction
{
    NONE = AEGP_PostRenderOptions_NONE,
    IMPORT = AEGP_PostRenderOptions_IMPORT,
    IMPORT_AND_REPLACE_USAGE = AEGP_PostRenderOptions_IMPORT_AND_REPLACE_USAGE,
    SET_PROXY = AEGP_PostRenderOptions_SET_PROXY
};

enum class AE_OutputTypes
{
    NONE = AEGP_OutputType_NONE,
    VIDEO = AEGP_OutputType_VIDEO,
    AUDIO = AEGP_OutputType_AUDIO
};

enum class AE_VideoChannels
{
    NONE = AEGP_VideoChannels_NONE,
    RGB = AEGP_VideoChannels_RGB,
    RGBA = AEGP_VideoChannels_RGBA,
    ALPHA = AEGP_VideoChannels_ALPHA
};

enum class AE_StretchQuality
{
    NONE = AEGP_StretchQual_NONE,
    LOW = AEGP_StretchQual_LOW,
    HIGH = AEGP_StretchQual_HIGH
};

enum class AE_OutputColorType
{
    STRAIGHT = AEGP_OutputColorType_STRAIGHT,
    PREMUL = AEGP_OutputColorType_PREMUL
};

class RenderQueueSuite1
{
  public:
    RenderQueueSuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    RenderQueueSuite1(const RenderQueueSuite1 &) = delete;
    RenderQueueSuite1 &operator=(const RenderQueueSuite1 &) = delete;
    RenderQueueSuite1(RenderQueueSuite1 &&) = delete;
    RenderQueueSuite1 &operator=(RenderQueueSuite1 &&) = delete;

    void addCompToRenderQueue(CompPtr comp, const std::string &path);
    void setRenderQueueState(AE_RenderQueueState state);
    AE_RenderQueueState getRenderQueueState();

  private:
    SuiteManager &m_suiteManager;
};

class RenderQueueItemSuite4
{
  public:
    RenderQueueItemSuite4() : m_suiteManager(SuiteManager::GetInstance()){};
    RenderQueueItemSuite4(const RenderQueueItemSuite4 &) = delete;
    RenderQueueItemSuite4 &operator=(const RenderQueueItemSuite4 &) = delete;
    RenderQueueItemSuite4(RenderQueueItemSuite4 &&) = delete;
    RenderQueueItemSuite4 &operator=(RenderQueueItemSuite4 &&) = delete;

    A_long getNumRQItems();
    RQItemRefPtr getRQItemByIndex(A_long rq_item_index);
    RQItemRefPtr getNextRQItem(RQItemRefPtr current_rq_item);
    A_long getNumOutputModulesForRQItem(RQItemRefPtr rq_item);
    AE_RenderItemStatus getRenderState(RQItemRefPtr rq_item);
    void setRenderState(RQItemRefPtr rq_item, AE_RenderItemStatus status);
    A_Time getStartedTime(RQItemRefPtr rq_item);
    A_Time getElapsedTime(RQItemRefPtr rq_item);
    AE_LogType getLogType(RQItemRefPtr rq_item);
    void setLogType(RQItemRefPtr rq_item, AE_LogType logtype);
    void removeOutputModule(RQItemRefPtr rq_item, OutputModuleRefPtr outmod);
    std::string getComment(RQItemRefPtr rq_item);
    void setComment(RQItemRefPtr rq_item, const std::string &comment);
    CompPtr getCompFromRQItem(RQItemRefPtr rq_item);
    void deleteRQItem(RQItemRefPtr rq_item);

  private:
    SuiteManager &m_suiteManager;
};

class OutputModuleSuite4
{
  public:
    OutputModuleSuite4() : m_suiteManager(SuiteManager::GetInstance()){};
    OutputModuleSuite4(const OutputModuleSuite4 &) = delete;
    OutputModuleSuite4 &operator=(const OutputModuleSuite4 &) = delete;
    OutputModuleSuite4(OutputModuleSuite4 &&) = delete;
    OutputModuleSuite4 &operator=(OutputModuleSuite4 &&) = delete;

    OutputModuleRefPtr getOutputModuleByIndex(RQItemRefPtr rq_itemH,
                                              A_long outmod_indexL);
    AE_EmbeddingType getEmbedOptions(RQItemRefPtr rq_itemH,
                                     OutputModuleRefPtr outmodH);
    void setEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                         AE_EmbeddingType embed_options);
    AE_PostRenderAction getPostRenderAction(RQItemRefPtr rq_itemH,
                                            OutputModuleRefPtr outmodH);
    void setPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                             AE_PostRenderAction post_render_action);
    AE_OutputTypes getEnabledOutputs(RQItemRefPtr rq_itemH,
                                     OutputModuleRefPtr outmodH);
    void setEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           AE_OutputTypes enabled_types);
    AE_VideoChannels getOutputChannels(RQItemRefPtr rq_itemH,
                                       OutputModuleRefPtr outmodH);
    void setOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           AE_VideoChannels output_channels);
    std::tuple<bool, AE_StretchQuality, bool>
    getStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                        bool is_enabledB, AE_StretchQuality stretch_quality);
    std::tuple<bool, A_Rect> getCropInfo(RQItemRefPtr rq_itemH,
                                         OutputModuleRefPtr outmodH);
    void setCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                     bool enableB, A_Rect crop_rect);
    std::tuple<AEGP_SoundDataFormat, bool>
    getSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                            AEGP_SoundDataFormat sound_format_info,
                            bool audio_enabledB);
    std::string getOutputFilePath(RQItemRefPtr rq_itemH,
                                  OutputModuleRefPtr outmodH);
    void setOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           const std::string &path);
    OutputModuleRefPtr addDefaultOutputModule(RQItemRefPtr rq_itemH);
    std::tuple<std::string, std::string, bool, bool>
    getExtraOutputModuleInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);

  private:
    SuiteManager &m_suiteManager;
};

enum class AE_WorldType
{
    NONE = AEGP_WorldType_NONE,
    W8 = AEGP_WorldType_8,
    W16 = AEGP_WorldType_16,
    W32 = AEGP_WorldType_32
};

enum class AE_MatteMode
{
    STRAIGHT = AEGP_MatteMode_STRAIGHT,
    PREMUL_BLACK = AEGP_MatteMode_PREMUL_BLACK,
    PREMUL_BG_COLOR = AEGP_MatteMode_PREMUL_BG_COLOR
};

enum class AE_ChannelOrder
{
    ARGB = AEGP_ChannelOrder_ARGB,
    BGRA = AEGP_ChannelOrder_BGRA
};

enum class AE_ItemQuality
{
    DRAFT = AEGP_ItemQuality_DRAFT,
    BEST = AEGP_ItemQuality_BEST
};

class WorldSuite3
{
  public:
    WorldSuite3() : m_suiteManager(SuiteManager::GetInstance()){};
    WorldSuite3(const WorldSuite3 &) = delete;
    WorldSuite3 &operator=(const WorldSuite3 &) = delete;
    WorldSuite3(WorldSuite3 &&) = delete;
    WorldSuite3 &operator=(WorldSuite3 &&) = delete;

    WorldPtr newWorld(AE_WorldType type, A_long widthL, A_long heightL);
    AE_WorldType getType(WorldPtr worldH);
    std::tuple<A_long, A_long> getSize(WorldPtr worldH);
    A_u_long getRowBytes(WorldPtr worldH);
    PF_Pixel8 *getBaseAddr8(WorldPtr worldH);
    PF_Pixel16 *getBaseAddr16(WorldPtr worldH);
    PF_PixelFloat *getBaseAddr32(WorldPtr worldH);
    PF_EffectWorld fillOutPFEffectWorld(WorldPtr worldH);
    void fastBlur(A_FpLong radiusF, PF_ModeFlags mode, PF_Quality quality,
                  WorldPtr worldH);
    PlatformWorldPtr newPlatformWorld(AEGP_WorldType type, A_long widthL,
                                      A_long heightL);
    WorldPtr newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH);

    static inline WorldPtr createPtr(AEGP_WorldH ref) { 
        return WorldPtr(ref);
    }
    static inline PlatformWorldPtr createPlatformPtr(AEGP_PlatformWorldH ref)
    {
        return std::shared_ptr<AEGP_PlatformWorldH>(
            new AEGP_PlatformWorldH(ref), PlatformDeleter());
    }

  private:
    SuiteManager &m_suiteManager;
};

class RenderOptionsSuite4
{
  public:
    RenderOptionsSuite4() : m_suiteManager(SuiteManager::GetInstance()){};
    RenderOptionsSuite4(const RenderOptionsSuite4 &) = delete;
    RenderOptionsSuite4 &operator=(const RenderOptionsSuite4 &) = delete;
    RenderOptionsSuite4(RenderOptionsSuite4 &&) = delete;
    RenderOptionsSuite4 &operator=(RenderOptionsSuite4 &&) = delete;

    RenderOptionsPtr newFromItem(ItemPtr itemH);
    RenderOptionsPtr duplicate(RenderOptionsPtr optionsH);
    void setTime(RenderOptionsPtr optionsH, A_Time time);
    A_Time getTime(RenderOptionsPtr optionsH);
    void setTimeStep(RenderOptionsPtr optionsH, A_Time time_step);
    A_Time getTimeStep(RenderOptionsPtr optionsH);
    void setFieldRender(RenderOptionsPtr optionsH, PF_Field field_render);
    PF_Field getFieldRender(RenderOptionsPtr optionsH);
    void setWorldType(RenderOptionsPtr optionsH, AE_WorldType type);
    AE_WorldType getWorldType(RenderOptionsPtr optionsH);
    void setDownsampleFactor(RenderOptionsPtr optionsH, A_short x, A_short y);
    std::tuple<A_short, A_short> getDownsampleFactor(RenderOptionsPtr optionsH);
    void setRegionOfInterest(RenderOptionsPtr optionsH, const A_LRect *roiP);
    A_LRect getRegionOfInterest(RenderOptionsPtr optionsH);
    void setMatteMode(RenderOptionsPtr optionsH, AE_MatteMode mode);
    AE_MatteMode getMatteMode(RenderOptionsPtr optionsH);
    void setChannelOrder(RenderOptionsPtr optionsH,
                         AE_ChannelOrder channel_order);
    AE_ChannelOrder getChannelOrder(RenderOptionsPtr optionsH);
    bool getRenderGuideLayers(RenderOptionsPtr optionsH);
    void setRenderGuideLayers(RenderOptionsPtr optionsH, bool render_themB);

  private:
    SuiteManager &m_suiteManager;
    static inline RenderOptionsPtr createPtr(AEGP_RenderOptionsH ref)
    {
        return std::shared_ptr<AEGP_RenderOptionsH>(
            new AEGP_RenderOptionsH(ref), RenderOptionsDeleter());
    }
};

class LayerRenderOptionsSuite2
{
  public:
    LayerRenderOptionsSuite2() : m_suiteManager(SuiteManager::GetInstance()){};
    LayerRenderOptionsSuite2(const LayerRenderOptionsSuite2 &) = delete;
    LayerRenderOptionsSuite2 &
    operator=(const LayerRenderOptionsSuite2 &) = delete;
    LayerRenderOptionsSuite2(LayerRenderOptionsSuite2 &&) = delete;
    LayerRenderOptionsSuite2 &operator=(LayerRenderOptionsSuite2 &&) = delete;

    LayerRenderOptionsPtr newFromLayer(LayerPtr layer);
    LayerRenderOptionsPtr newFromUpstreamOfEffect(EffectRefPtr effect_ref);
    LayerRenderOptionsPtr newFromDownstreamOfEffect(EffectRefPtr effect_ref);
    LayerRenderOptionsPtr duplicate(LayerRenderOptionsPtr optionsH);
    void dispose(LayerRenderOptionsPtr optionsH);
    void setTime(LayerRenderOptionsPtr optionsH, A_Time time);
    A_Time getTime(LayerRenderOptionsPtr optionsH);
    void setTimeStep(LayerRenderOptionsPtr optionsH, A_Time time_step);
    A_Time getTimeStep(LayerRenderOptionsPtr optionsH);
    void setWorldType(LayerRenderOptionsPtr optionsH, AE_WorldType type);
    AE_WorldType getWorldType(LayerRenderOptionsPtr optionsH);
    void setDownsampleFactor(LayerRenderOptionsPtr optionsH, A_short x,
                             A_short y);
    std::tuple<A_short, A_short>
    getDownsampleFactor(LayerRenderOptionsPtr optionsH);
    void setMatteMode(LayerRenderOptionsPtr optionsH, AE_MatteMode mode);
    AE_MatteMode getMatteMode(LayerRenderOptionsPtr optionsH);

  private:
    SuiteManager &m_suiteManager;
    static inline LayerRenderOptionsPtr createPtr(AEGP_LayerRenderOptionsH ref)
    {
        return std::shared_ptr<AEGP_LayerRenderOptionsH>(
            new AEGP_LayerRenderOptionsH(ref), LayerRenderOptionsDeleter());
    }
};

/**
 * @class RenderSuite5
 *
 * RenderSuite5 provides a high-level abstraction over the AEGP_RenderSuite5,
 * facilitating rendering operations within Adobe After Effects plugins.
 * It encapsulates synchronous and asynchronous rendering functionalities,
 * frame checkout, and utility methods for managing rendered frames.
 *
 * Usage of synchronous calls on the UI thread is deprecated except in very
 * specific cases, as they may hinder UI interactivity. Asynchronous methods
 * are recommended for UI responsiveness.
 */
class RenderSuite5
{
  public:
    /**
     * Constructs a RenderSuite5 instance, acquiring the necessary AE rendering
     * suites from the SuiteManager.
     */
    RenderSuite5() : m_suiteManager(SuiteManager::GetInstance()){};

    // Deleted copy and move constructors and assignment operators
    RenderSuite5(const RenderSuite5 &) = delete;
    RenderSuite5 &operator=(const RenderSuite5 &) = delete;
    RenderSuite5(RenderSuite5 &&) = delete;
    RenderSuite5 &operator=(RenderSuite5 &&) = delete;

    /**
     * Synchronously renders a frame based on given render options and checks it
     * out.
     *
     * @param optionsH Pointer to the render options.
     * @return A pointer to the frame receipt if successful; nullptr otherwise.
     */
    FrameReceiptPtr renderAndCheckoutFrame(RenderOptionsPtr optionsH);

    /**
     * Synchronously renders a layer frame based on given layer render options
     * and checks it out.
     *
     * @param optionsH Pointer to the layer render options.
     * @return A pointer to the frame receipt if successful; nullptr otherwise.
     */
    FrameReceiptPtr renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH);

    /**
     * Asynchronously renders a layer frame based on given layer render options.
     *
     * @param optionsH Pointer to the layer render options.
     * @param callback The callback function to be called when the frame is
     * ready or if the render was canceled.
     * @return An AEGP_AsyncRequestId associated with the frame request, useful
     * for cancellation.
     */
    A_u_longlong
    renderAndCheckoutLayerFrameAsync(LayerRenderOptionsPtr optionsH,
                                     AEGP_AsyncFrameReadyCallback callback);

    /**
     * Cancels an asynchronous render request.
     *
     * @param async_request_id The ID of the render request to cancel.
     */
    void cancelAsyncRequest(AEGP_AsyncRequestId async_request_id);

    /**
     * Retrieves the world associated with a frame receipt.
     *
     * @param receiptH The frame receipt.
     * @return A pointer to the world if successful; nullptr otherwise.
     */
    WorldPtr getReceiptWorld(FrameReceiptPtr receiptH);

    /**
     * Determines the rendered region of a frame receipt.
     *
     * @param receiptH The frame receipt.
     * @return The rendered region as an A_LRect.
     */
    A_LRect getRenderedRegion(FrameReceiptPtr receiptH);

    /**
     * Checks if a rendered frame is sufficient based on proposed render
     * options.
     *
     * @param rendered_optionsH Render options of the already rendered frame.
     * @param proposed_optionsH Proposed render options to compare against.
     * @return true if the rendered frame is sufficient; false otherwise.
     */
    bool isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH,
                                   RenderOptionsPtr proposed_optionsH);

    /**
     * Obtains the current timestamp of the project. This timestamp increases
     * anytime something in the project affecting rendering is modified.
     *
     * @return TimeStampPtr pointing to the current timestamp.
     */
    TimeStampPtr getCurrentTimestamp();

    /**
     * Determines if the video content of an item has changed since a specified
     * timestamp. Audio changes do not affect this determination.
     *
     * @param itemH Pointer to the item being queried.
     * @param start_timeP The start time from which changes are considered.
     * @param durationP The duration for which changes are considered.
     * @param time_stampP The timestamp against which changes are checked.
     * @return true if the item has changed since the given timestamp; false
     * otherwise.
     */
    bool hasItemChangedSinceTimestamp(ItemPtr itemH, A_Time start_timeP,
                                      A_Time durationP,
                                      TimeStampPtr time_stampP);

    /**
     * Evaluates whether rendering a particular frame with specific render
     * options is worthwhile. This is intended for speculative rendering where
     * it's necessary to decide whether to render a frame externally and check
     * it into the cache.
     *
     * @param roH The render options for the frame.
     * @param time_stampP The current project timestamp.
     * @return true if rendering the frame is considered worthwhile; false
     * otherwise.
     */
    bool isItemWorthwhileToRender(RenderOptionsPtr roH,
                                  TimeStampPtr time_stampP);

    /**
     * Checks in a rendered frame to release it. This should be called after a
     * frame is no longer needed to ensure resources are freed.
     *
     * @param roH The render options used for rendering the frame.
     * @param time_stampP The timestamp when the frame was rendered.
     * @param ticks_to_renderL The approximate amount of time needed to render
     * the frame, measured in 60Hz ticks.
     * @param imageH A platform-specific handle to the rendered image.
     */
    void checkinRenderedFrame(RenderOptionsPtr roH, TimeStampPtr time_stampP,
                              A_u_long ticks_to_renderL,
                              PlatformWorldPtr imageH);

    /**
     * Retrieves a globally unique identifier (GUID) for a frame receipt. This
     * GUID can be used to uniquely identify a frame across sessions.
     *
     * @param receiptH The frame receipt from which the GUID is retrieved.
     * @return A string representation of the GUID.
     */
    std::string getReceiptGuid(FrameReceiptPtr receiptH);

  private:
    SuiteManager
        &m_suiteManager; ///< The SuiteManager instance for acquiring AE suites.

    /**
     * Helper function to create a FrameReceiptPtr from an AEGP_FrameReceiptH.
     *
     * @param ref The AEGP_FrameReceiptH handle.
     * @return A shared pointer wrapping the AEGP_FrameReceiptH handle.
     */
    static inline FrameReceiptPtr createPtr(AEGP_FrameReceiptH ref)
    {
        return std::shared_ptr<AEGP_FrameReceiptH>(new AEGP_FrameReceiptH(ref),
                                                   FrameReceiptDeleter());
    }
};

enum class AE_CollectionItemType
{
    NONE = AEGP_CollectionItemType_NONE,
    LAYER = AEGP_CollectionItemType_LAYER,
    MASK = AEGP_CollectionItemType_MASK,
    EFFECT = AEGP_CollectionItemType_EFFECT,
    STREAM = AEGP_CollectionItemType_STREAM,
    KEYFRAME = AEGP_CollectionItemType_KEYFRAME,
    MASK_VERTEX = AEGP_CollectionItemType_MASK_VERTEX,
    STREAMREF = AEGP_CollectionItemType_STREAMREF
};

enum class AE_StreamCollectionItemType
{
    NONE = AEGP_StreamCollectionItemType_NONE,
    LAYER = AEGP_StreamCollectionItemType_LAYER,
    MASK = AEGP_StreamCollectionItemType_MASK,
    EFFECT = AEGP_StreamCollectionItemType_EFFECT
};

class CollectionSuite2
{
  public:
    CollectionSuite2() : m_suiteManager(SuiteManager::GetInstance()){};
    CollectionSuite2(const CollectionSuite2 &) = delete;
    CollectionSuite2 &operator=(const CollectionSuite2 &) = delete;
    CollectionSuite2(CollectionSuite2 &&) = delete;
    CollectionSuite2 &operator=(CollectionSuite2 &&) = delete;

    Collection2Ptr newCollection();
    void disposeCollection(Collection2Ptr collectionH);
    A_long getCollectionNumItems(Collection2Ptr collectionH);
    AEGP_CollectionItemV2 getCollectionItemByIndex(Collection2Ptr collectionH,
                                                   A_long indexL);
    void collectionPushBack(Collection2Ptr collectionH,
                            const AEGP_CollectionItemV2 &itemP);
    void collectionErase(Collection2Ptr collectionH, A_long index_firstL,
                         A_long index_lastL);

  private:
    SuiteManager &m_suiteManager;
    static inline Collection2Ptr createPtr(AEGP_Collection2H ref)
    {
        return std::shared_ptr<AEGP_Collection2H>(new AEGP_Collection2H(ref),
                                                  CollectionDeleter());
    }
};

enum class AE_WindowType
{
    NONE = AEGP_WindType_NONE,
    PROJECT = AEGP_WindType_PROJECT,
    COMP = AEGP_WindType_COMP,
    TIME_LAYOUT = AEGP_WindType_TIME_LAYOUT,
    LAYER = AEGP_WindType_LAYER,
    FOOTAGE = AEGP_WindType_FOOTAGE,
    RENDER_QUEUE = AEGP_WindType_RENDER_QUEUE,
    QT = AEGP_WindType_QT,
    DIALOG = AEGP_WindType_DIALOG,
    FLOWCHART = AEGP_WindType_FLOWCHART,
    EFFECT = AEGP_WindType_EFFECT,
    OTHER = AEGP_WindType_OTHER
};

class RegisterSuite5
{
  public:
    RegisterSuite5() : m_suiteManager(SuiteManager::GetInstance()){};
    RegisterSuite5(const RegisterSuite5 &) = delete;
    RegisterSuite5 &operator=(const RegisterSuite5 &) = delete;
    RegisterSuite5(RegisterSuite5 &&) = delete;
    RegisterSuite5 &operator=(RegisterSuite5 &&) = delete;

    void registerCommandHook(AEGP_HookPriority hook_priority,
                             AEGP_Command command,
                             AEGP_CommandHook command_hook_func,
                             AEGP_CommandRefcon refconP);
    void registerUpdateMenuHook(AEGP_UpdateMenuHook update_menu_hook_func,
                                AEGP_UpdateMenuRefcon refconP);
    void registerDeathHook(AEGP_DeathHook death_hook_func,
                           AEGP_DeathRefcon refconP);
    void registerIdleHook(AEGP_IdleHook idle_hook_func,
                          AEGP_IdleRefcon refconP);
    void registerPresetLocalizationString(const std::string &english_nameZ,
                                          const std::string &localized_nameZ);

  private:
    SuiteManager &m_suiteManager;
};

enum class AE_MenuID
{
    NONE = AEGP_Menu_NONE,
    APPLE = AEGP_Menu_APPLE,
    FILE = AEGP_Menu_FILE,
    EDIT = AEGP_Menu_EDIT,
    COMPOSITION = AEGP_Menu_COMPOSITION,
    LAYER = AEGP_Menu_LAYER,
    EFFECT = AEGP_Menu_EFFECT,
    WINDOW = AEGP_Menu_WINDOW,
    FLOATERS = AEGP_Menu_FLOATERS,
    KF_ASSIST = AEGP_Menu_KF_ASSIST,
    IMPORT = AEGP_Menu_IMPORT,
    SAVE_FRAME_AS = AEGP_Menu_SAVE_FRAME_AS,
    PREFS = AEGP_Menu_PREFS,
    EXPORT = AEGP_Menu_EXPORT,
    ANIMATION = AEGP_Menu_ANIMATION,
    PURGE = AEGP_Menu_PURGE,
    NEW = AEGP_Menu_NEW
};

#define INSERT_SORTED (-2)
#define INSERT_BOTTOM (-1)
#define INSERT_TOP 0

class CommandSuite1
{
  public:
    CommandSuite1() : m_suiteManager(SuiteManager::GetInstance()){};
    CommandSuite1(const CommandSuite1 &) = delete;
    CommandSuite1 &operator=(const CommandSuite1 &) = delete;
    CommandSuite1(CommandSuite1 &&) = delete;
    CommandSuite1 &operator=(CommandSuite1 &&) = delete;

    AEGP_Command getUniqueCommand();
    void insertMenuCommand(AEGP_Command command, const std::string &nameZ,
                           AE_MenuID menu_id, A_long after_itemL);
    void removeMenuCommand(AEGP_Command command);
    void setMenuCommandName(AEGP_Command command, const std::string &nameZ);
    void enableCommand(AEGP_Command command);
    void disableCommand(AEGP_Command command);
    void checkMarkMenuCommand(AEGP_Command command, A_Boolean checkB);
    void doCommand(AEGP_Command command);

  private:
    SuiteManager &m_suiteManager;
};
/*

#define kAEGPRenderQueueMonitorSuite				"AEGP
RenderQueue Monitor Suite" #define kAEGPRenderQueueMonitorSuiteVersion1
1 /* frozen AE 11.0

typedef struct _AEGP_RQM_Refcon *AEGP_RQM_Refcon;
typedef A_u_longlong AEGP_RQM_SessionId;
typedef A_u_longlong AEGP_RQM_ItemId;
typedef A_u_longlong AEGP_RQM_FrameId;

typedef enum
{
    AEGP_RQM_FinishedStatus_UNKNOWN,
    AEGP_RQM_FinishedStatus_SUCCEEDED,
    AEGP_RQM_FinishedStatus_ABORTED,
    AEGP_RQM_FinishedStatus_ERRED
} AEGP_RQM_FinishedStatus;

typedef struct _AEGP_RQM_BasicData
{
    const struct SPBasicSuite *pica_basicP;
    A_long aegp_plug_id;
    AEGP_RQM_Refcon aegp_refconPV;
} AEGP_RQM_BasicData;

typedef struct _AEGP_RQM_FunctionBlock1
{
    A_Err (*AEGP_RQM_RenderJobStarted)(AEGP_RQM_BasicData *basic_dataP,
                                       AEGP_RQM_SessionId jobid);
    A_Err (*AEGP_RQM_RenderJobEnded)(AEGP_RQM_BasicData *basic_dataP,
                                     AEGP_RQM_SessionId jobid);
    A_Err (*AEGP_RQM_RenderJobItemStarted)(AEGP_RQM_BasicData *basic_dataP,
                                           AEGP_RQM_SessionId jobid,
                                           AEGP_RQM_ItemId itemid);
    A_Err (*AEGP_RQM_RenderJobItemUpdated)(AEGP_RQM_BasicData *basic_dataP,
                                           AEGP_RQM_SessionId jobid,
                                           AEGP_RQM_ItemId itemid,
                                           AEGP_RQM_FrameId frameid);
    A_Err (*AEGP_RQM_RenderJobItemEnded)(AEGP_RQM_BasicData *basic_dataP,
                                         AEGP_RQM_SessionId jobid,
                                         AEGP_RQM_ItemId itemid,
                                         AEGP_RQM_FinishedStatus fstatus);
    A_Err (*AEGP_RQM_RenderJobItemReportLog)(AEGP_RQM_BasicData *basic_dataP,
                                             AEGP_RQM_SessionId jobid,
                                             AEGP_RQM_ItemId itemid,
                                             A_Boolean isError,
                                             AEGP_MemHandle logbuf);
} AEGP_RQM_FunctionBlock1;

typedef struct AEGP_RenderQueueMonitorSuite1
{

    SPAPI A_Err (*AEGP_RegisterListener)( //use custom deleter here
        AEGP_PluginID aegp_plugin_id,               /* >>
        AEGP_RQM_Refcon aegp_refconP,               /* >>
        const AEGP_RQM_FunctionBlock1 *fcn_blockP); /* >>

    SPAPI
        A_Err (*AEGP_DeregisterListener)(AEGP_PluginID aegp_plugin_id,  /* >>
                                         AEGP_RQM_Refcon aegp_refconP); /* >>

    SPAPI A_Err (*AEGP_GetProjectName)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_MemHandle
            *utf_project_namePH0); // <<	handle of A_UTF16Char (contains
null
                                   // terminated UTF16 string); must be disposed
                                   // with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetAppVersion)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_MemHandle
            *utf_app_versionPH0); // <<	handle of A_UTF16Char (contains null
                                  // terminated UTF16 string); must be disposed
                                  // with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetNumJobItems)(AEGP_RQM_SessionId sessid, // >>
                                       A_long *num_jobitemsPL);   // <<

    SPAPI A_Err (*AEGP_GetJobItemID)(AEGP_RQM_SessionId sessid,   // >>
                                     A_long jobItemIndex,         // >>
                                     AEGP_RQM_ItemId *jobItemID); // <<

    SPAPI A_Err (*AEGP_GetNumJobItemRenderSettings)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long *num_settingsPL);   // <<

    SPAPI A_Err (*AEGP_GetJobItemRenderSetting)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long settingIndex,       // >>
        AEGP_MemHandle
            *utf_setting_namePH0, // <<	handle of A_UTF16Char (contains null
                                  // terminated UTF16 string); must be disposed
                                  // with AEGP_FreeMemHandle
        AEGP_MemHandle
            *utf_setting_valuePH0); // <<	handle of A_UTF16Char (contains
null
                                    // terminated UTF16 string); must be
                                    // disposed with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetNumJobItemOutputModules)(
        AEGP_RQM_SessionId sessid,    // >>
        AEGP_RQM_ItemId itemid,       // >>
        A_long *num_outputmodulesPL); // <<

    SPAPI A_Err (*AEGP_GetNumJobItemOutputModuleSettings)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long *num_settingsPL);   // <<

    SPAPI A_Err (*AEGP_GetJobItemOutputModuleSetting)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long settingIndex,       // >>
        AEGP_MemHandle
            *utf_setting_namePH0, // <<	handle of A_UTF16Char (contains null
                                  // terminated UTF16 string); must be disposed
                                  // with AEGP_FreeMemHandle
        AEGP_MemHandle
            *utf_setting_valuePH0); // <<	handle of A_UTF16Char (contains
null
                                    // terminated UTF16 string); must be
                                    // disposed with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetNumJobItemOutputModuleWarnings)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long *num_warningsPL);   // <<

    SPAPI A_Err (*AEGP_GetJobItemOutputModuleWarning)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long warningIndex,       // >>
        AEGP_MemHandle
            *utf_warning_valuePH0); // <<	handle of A_UTF16Char (contains
null
                                    // terminated UTF16 string); must be
                                    // disposed with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetNumJobItemFrameProperties)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        AEGP_RQM_FrameId frameid,  // >>
        A_long *num_propertiesPL); // <<

    SPAPI A_Err (*AEGP_GetJobItemFrameProperty)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        AEGP_RQM_FrameId frameid,  // >>
        A_long propertyIndex,      // >>
        AEGP_MemHandle
            *utf_property_namePH0, // <<	handle of A_UTF16Char (contains
null
                                   // terminated UTF16 string); must be disposed
                                   // with AEGP_FreeMemHandle
        AEGP_MemHandle
            *utf_property_valuePH0); // <<	handle of A_UTF16Char (contains
                                     // null terminated UTF16 string); must be
                                     // disposed with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetNumJobItemOutputModuleProperties)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long *num_propertiesPL); // <<

    SPAPI A_Err (*AEGP_GetJobItemOutputModuleProperty)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        A_long outputModuleIndex,  // >>
        A_long propertyIndex,      // >>
        AEGP_MemHandle
            *utf_property_namePH0, // <<	handle of A_UTF16Char (contains
null
                                   // terminated UTF16 string); must be disposed
                                   // with AEGP_FreeMemHandle
        AEGP_MemHandle
            *utf_property_valuePH0); // <<	handle of A_UTF16Char (contains
                                     // null terminated UTF16 string); must be
                                     // disposed with AEGP_FreeMemHandle

    SPAPI A_Err (*AEGP_GetJobItemFrameThumbnail)(
        AEGP_RQM_SessionId sessid, // >>
        AEGP_RQM_ItemId itemid,    // >>
        AEGP_RQM_FrameId frameid,  // >>
        A_long *widthPL,  // <> 	pass in the maximum width, returns the
actual
                          // width
        A_long *heightPL, // <>	pass in the maximum height, returns the actual
                          // height
        AEGP_MemHandle *thumbnailPH0); // <<	handle of an image memory block
                                       // in JPEG format

} AEGP_RenderQueueMonitorSuite1;

*/
#endif // AE_MAIN_HPP
