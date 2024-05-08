/*****************************************************************/ /**
                                                                     * \file   Enums.hpp
                                                                     * \brief  Enums for the AEGP SDK.
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef ENUMS_HPP
#define ENUMS_HPP

#include "AETK/Common/Common.hpp"

enum class MemFlag
{
    NONE = AEGP_MemFlag_NONE, /* No Memory Flag.*/
    CLEAR = AEGP_MemFlag_CLEAR, /* Clear Memory Flag.*/
    QUIET = AEGP_MemFlag_QUIET /* Quiet Memory Flag.*/
};

enum class Platform
{
    WIN = AEGP_Platform_WIN, /* Windows Platform.*/
    MAC = AEGP_Platform_MAC  /* Mac Platform.*/
};

enum class ProjBitDepth
{
    _8 = AEGP_ProjBitDepth_8,   /* 8 Bit Depth.*/
    _16 = AEGP_ProjBitDepth_16, /* 16 Bit Depth.*/
    _32 = AEGP_ProjBitDepth_32, /* 32 Bit Depth.*/
    NUM_VALID_DEPTHS = AEGP_ProjBitDepth_NUM_VALID_DEPTHS
};

enum class CameraType
{
    NONE = AEGP_CameraType_NONE,                 /* No Camera Type.*/
    PERSPECTIVE = AEGP_CameraType_PERSPECTIVE,   /* Perspective Camera Type.*/
    ORTHOGRAPHIC = AEGP_CameraType_ORTHOGRAPHIC, /* Orthographic Camera Type.*/
    NUM_TYPES = AEGP_CameraType_NUM_TYPES
};

enum class TimeDisplayType
{
    TIMECODE = AEGP_TimeDisplayType_TIMECODE, /* Timecode Display Type.*/
    FRAMES = AEGP_TimeDisplayType_FRAMES,     /* Frames Display Type.*/
    FEET_AND_FRAMES =
        AEGP_TimeDisplayType_FEET_AND_FRAMES /* Feet and Frames
                                                                                                            Display
                                                Type.*/
};

enum class FilmSizeUnits
{
    NONE = AEGP_FilmSizeUnits_NONE,
    HORIZONTAL = AEGP_FilmSizeUnits_HORIZONTAL,
    VERTICAL = AEGP_FilmSizeUnits_VERTICAL,
    DIAGONAL = AEGP_FilmSizeUnits_DIAGONAL
};

enum class LightType
{
    NONE = AEGP_LightType_NONE,
    PARALLEL = AEGP_LightType_PARALLEL,
    SPOT = AEGP_LightType_SPOT,
    POINT = AEGP_LightType_POINT,
    AMBIENT = AEGP_LightType_AMBIENT,
    RESERVED1 = AEGP_LightType_RESERVED1,
    NUM_TYPES = AEGP_LightType_NUM_TYPES
};

enum class FootageSignature
{
	NONE = AEGP_FootageSignature_NONE,
	MISSING = AEGP_FootageSignature_MISSING,
	SOLID = AEGP_FootageSignature_SOLID
};

enum class LightFalloffType
{
    NONE = AEGP_LightFalloff_NONE,
    SMOOTH = AEGP_LightFalloff_SMOOTH,
    INVERSE_SQUARE_CLAMPED = AEGP_LightFalloff_INVERSE_SQUARE_CLAMPED
};

enum class FootageDepth
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

enum class FramesPerFoot
{
    _35MM = AEGP_FramesPerFoot_35MM,
    _16MM = AEGP_FramesPerFoot_16MM
};

enum class TimeDisplayMode
{
    TIMECODE = AEGP_TimeDisplay_TIMECODE,
    FRAMES = AEGP_TimeDisplay_FRAMES
};

enum class SourceTimecodeDisplayMode
{
    ZERO = AEGP_SourceTimecode_ZERO,
    SOURCE_TIMECODE = AEGP_SourceTimecode_SOURCE_TIMECODE
};

enum class FramesDisplayMode
{
    ZERO_BASED = AEGP_Frames_ZERO_BASED,
    ONE_BASED = AEGP_Frames_ONE_BASED,
    TIMECODE_CONVERSION = AEGP_Frames_TIMECODE_CONVERSION
};

enum class SoundEncoding
{
    UNSIGNED_PCM = AEGP_SoundEncoding_UNSIGNED_PCM,
    SIGNED_PCM = AEGP_SoundEncoding_SIGNED_PCM,
    FLOAT = AEGP_SoundEncoding_FLOAT,
    END = AEGP_SoundEncoding_END,
    BEGIN = AEGP_SoundEncoding_BEGIN
};

enum class ItemType
{
    NONE = AEGP_ItemType_NONE,
    FOLDER = AEGP_ItemType_FOLDER,
    COMP = AEGP_ItemType_COMP,
    SOLID = AEGP_ItemType_SOLID_defunct,
    FOOTAGE = AEGP_ItemType_FOOTAGE,
    NUM_TYPES = AEGP_ItemType_NUM_TYPES1
};

enum class ItemFlag
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

enum class Label
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

enum class PersistentType
{
    MACHINE_SPECIFIC = AEGP_PersistentType_MACHINE_SPECIFIC,
    MACHINE_INDEPENDENT = AEGP_PersistentType_MACHINE_INDEPENDENT,
    MACHINE_INDEPENDENT_RENDER = AEGP_PersistentType_MACHINE_INDEPENDENT_RENDER,
    MACHINE_INDEPENDENT_OUTPUT = AEGP_PersistentType_MACHINE_INDEPENDENT_OUTPUT,
    MACHINE_INDEPENDENT_COMPOSITION = AEGP_PersistentType_MACHINE_INDEPENDENT_COMPOSITION,
    MACHINE_SPECIFIC_TEXT = AEGP_PersistentType_MACHINE_SPECIFIC_TEXT,
    MACHINE_SPECIFIC_PAINT = AEGP_PersistentType_MACHINE_SPECIFIC_PAINT,
    MACHINE_SPECIFIC_EFFECTS = AEGP_PersistentType_MACHINE_SPECIFIC_EFFECTS,
    MACHINE_SPECIFIC_EXPRESSION_SNIPPETS = AEGP_PersistentType_MACHINE_SPECIFIC_EXPRESSION_SNIPPETS,
    MACHINE_SPECIFIC_SCRIPT_SNIPPETS = AEGP_PersistentType_MACHINE_SPECIFIC_SCRIPT_SNIPPETS,
    NUM_TYPES = AEGP_PersistentType_NUMTYPES
};

enum class CompFlag
{
    SHOW_ALL_SHY = AEGP_CompFlag_SHOW_ALL_SHY,             /* Show All Shy.*/
    ENABLE_MOTION_BLUR = AEGP_CompFlag_ENABLE_MOTION_BLUR, /* Enable Motion Blur.*/
    ENABLE_TIME_FILTER = AEGP_CompFlag_ENABLE_TIME_FILTER, /* Enable Time Filter.*/
    GRID_TO_FRAMES = AEGP_CompFlag_GRID_TO_FRAMES,         /* Grid to Frames.*/
    GRID_TO_FIELDS = AEGP_CompFlag_GRID_TO_FIELDS,         /* Grid to Fields.*/
    USE_LOCAL_DSF = AEGP_CompFlag_USE_LOCAL_DSF,           /* Use Local DSF.*/
    DRAFT_3D = AEGP_CompFlag_DRAFT_3D,                     /* Draft 3D.*/
    SHOW_GRAPH = AEGP_CompFlag_SHOW_GRAPH                  /* Show Graph.*/
};

enum class TransferFlags
{
    PRESERVE_ALPHA = AEGP_TransferFlag_PRESERVE_ALPHA,
    RANDOMIZE_DISSOLVE = AEGP_TransferFlag_RANDOMIZE_DISSOLVE
};

enum class TrackMatte
{
    NO_TRACK_MATTE = AEGP_TrackMatte_NO_TRACK_MATTE,
    ALPHA = AEGP_TrackMatte_ALPHA,
    NOT_ALPHA = AEGP_TrackMatte_NOT_ALPHA,
    LUMA = AEGP_TrackMatte_LUMA,
    NOT_LUMA = AEGP_TrackMatte_NOT_LUMA
};

enum class LayerQual
{
    NONE = AEGP_LayerQual_NONE,
    WIREFRAME = AEGP_LayerQual_WIREFRAME,
    DRAFT = AEGP_LayerQual_DRAFT,
    BEST = AEGP_LayerQual_BEST
};

enum class LayerSamplingQual
{
    BILINEAR = AEGP_LayerSamplingQual_BILINEAR,
    BICUBIC = AEGP_LayerSamplingQual_BICUBIC
};

enum class LayerFlag
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

enum class ObjectType
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

enum class LTimeMode
{
    LayerTime = AEGP_LTimeMode_LayerTime,
    CompTime = AEGP_LTimeMode_CompTime
};

enum class LayerStream
{
    SOURCE_TEXT = AEGP_LayerStream_SOURCE_TEXT,
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

enum class MaskStream
{
    OUTLINE = AEGP_MaskStream_OUTLINE,
    OPACITY = AEGP_MaskStream_OPACITY,
    FEATHER = AEGP_MaskStream_FEATHER,
    EXPANSION = AEGP_MaskStream_EXPANSION
};

enum class StreamFlag
{
    NONE = AEGP_StreamFlag_NONE,
    HAS_MIN = AEGP_StreamFlag_HAS_MIN,
    HAS_MAX = AEGP_StreamFlag_HAS_MAX,
    IS_SPATIAL = AEGP_StreamFlag_IS_SPATIAL
};

enum class KeyInterp
{
    NONE = AEGP_KeyInterp_NONE,
    LINEAR = AEGP_KeyInterp_LINEAR,
    BEZIER = AEGP_KeyInterp_BEZIER,
    HOLD = AEGP_KeyInterp_HOLD
};

enum class KeyInterpMask
{
    NONE = AEGP_KeyInterpMask_NONE,
    LINEAR = AEGP_KeyInterpMask_LINEAR,
    BEZIER = AEGP_KeyInterpMask_BEZIER,
    HOLD = AEGP_KeyInterpMask_HOLD,
    CUSTOM = AEGP_KeyInterpMask_CUSTOM,
    ANY = AEGP_KeyInterpMask_ANY
};

enum class StreamType
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

enum class StreamGroupingType
{
    NONE = AEGP_StreamGroupingType_NONE,
    LEAF = AEGP_StreamGroupingType_LEAF,
    NAMED_GROUP = AEGP_StreamGroupingType_NAMED_GROUP,
    INDEXED_GROUP = AEGP_StreamGroupingType_INDEXED_GROUP
};

enum class DynStreamFlag
{
    ACTIVE_EYEBALL = AEGP_DynStreamFlag_ACTIVE_EYEBALL,
    HIDDEN = AEGP_DynStreamFlag_HIDDEN,
    DISABLED = AEGP_DynStreamFlag_DISABLED,
    ELIDED = AEGP_DynStreamFlag_ELIDED,
    SHOWN_WHEN_EMPTY = AEGP_DynStreamFlag_SHOWN_WHEN_EMPTY,
    SKIP_REVEAL_WHEN_UNHIDDEN = AEGP_DynStreamFlag_SKIP_REVEAL_WHEN_UNHIDDEN
};

enum class KeyframeFlag
{
    NONE = AEGP_KeyframeFlag_NONE,
    TEMPORAL_CONTINUOUS = AEGP_KeyframeFlag_TEMPORAL_CONTINUOUS,
    TEMPORAL_AUTOBEZIER = AEGP_KeyframeFlag_TEMPORAL_AUTOBEZIER,
    SPATIAL_CONTINUOUS = AEGP_KeyframeFlag_SPATIAL_CONTINUOUS,
    SPATIAL_AUTOBEZIER = AEGP_KeyframeFlag_SPATIAL_AUTOBEZIER,
    ROVING = AEGP_KeyframeFlag_ROVING
};

enum class MarkerStringType
{
    COMMENT = AEGP_MarkerString_COMMENT,
    CHAPTER = AEGP_MarkerString_CHAPTER,
    URL = AEGP_MarkerString_URL,
    FRAME_TARGET = AEGP_MarkerString_FRAME_TARGET,
    CUE_POINT_NAME = AEGP_MarkerString_CUE_POINT_NAME
};

enum class MarkerFlag
{
	NONE = AEGP_MarkerFlag_NONE,
	NAVIGATION = AEGP_MarkerFlag_NAVIGATION,
	PROTECT_REGION = AEGP_MarkerFlag_PROTECT_REGION
};

enum class EffectFlags
{
    NONE = AEGP_EffectFlags_NONE,
    ACTIVE = AEGP_EffectFlags_ACTIVE,
    AUDIO_ONLY = AEGP_EffectFlags_AUDIO_ONLY,
    AUDIO_TOO = AEGP_EffectFlags_AUDIO_TOO,
    MISSING = AEGP_EffectFlags_MISSING
};

enum class MaskMode
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

enum class MaskMBlur
{
    SAME_AS_LAYER = AEGP_MaskMBlur_SAME_AS_LAYER,
    OFF = AEGP_MaskMBlur_OFF,
    ON = AEGP_MaskMBlur_ON
};

enum class MaskFeatherFalloff
{
    SMOOTH = AEGP_MaskFeatherFalloff_SMOOTH,
    LINEAR = AEGP_MaskFeatherFalloff_LINEAR
};

enum class MaskFeatherInterp
{
    NORMAL = AEGP_MaskFeatherInterp_NORMAL,
    HOLD_CW = AEGP_MaskFeatherInterp_HOLD_CW
};

enum class MaskFeatherType
{
    OUTER = AEGP_MaskFeatherType_OUTER,
    INNER = AEGP_MaskFeatherType_INNER
};

enum class AlphaFlags
{
    PREMUL = AEGP_AlphaPremul,
    INVERTED = AEGP_AlphaInverted,
    ALPHA_IGNORE = AEGP_AlphaIgnore
};

enum class PulldownPhase
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

enum class LayerDrawStyle
{
    LAYER_BOUNDS = AEGP_LayerDrawStyle_LAYER_BOUNDS,
    DOCUMENT_BOUNDS = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS
};

enum class InterpretationStyle
{
    NO_DIALOG_GUESS = AEGP_InterpretationStyle_NO_DIALOG_GUESS,
    DIALOG_OK = AEGP_InterpretationStyle_DIALOG_OK,
    NO_DIALOG_NO_GUESS = AEGP_InterpretationStyle_NO_DIALOG_NO_GUESS
};

enum class PluginPathType
{
    PLUGIN = AEGP_GetPathTypes_PLUGIN,
    USER_PLUGIN = AEGP_GetPathTypes_USER_PLUGIN,
    ALLUSER_PLUGIN = AEGP_GetPathTypes_ALLUSER_PLUGIN,
    APP = AEGP_GetPathTypes_APP
};

enum class RenderQueueState
{
    STOPPED = AEGP_RenderQueueState_STOPPED,
    PAUSED = AEGP_RenderQueueState_PAUSED,
    RENDERING = AEGP_RenderQueueState_RENDERING
};

enum class RenderItemStatus
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

enum class LogType
{
    NONE = AEGP_LogType_NONE,
    ERRORS_ONLY = AEGP_LogType_ERRORS_ONLY,
    PLUS_SETTINGS = AEGP_LogType_PLUS_SETTINGS,
    PER_FRAME_INFO = AEGP_LogType_PER_FRAME_INFO
};

enum class EmbeddingType
{
    NONE = AEGP_Embedding_NONE,
    NOTHING = AEGP_Embedding_NOTHING,
    LINK = AEGP_Embedding_LINK,
    LINK_AND_COPY = AEGP_Embedding_LINK_AND_COPY
};

enum class PostRenderAction
{
    NONE = AEGP_PostRenderOptions_NONE,
    IMPORT = AEGP_PostRenderOptions_IMPORT,
    IMPORT_AND_REPLACE_USAGE = AEGP_PostRenderOptions_IMPORT_AND_REPLACE_USAGE,
    SET_PROXY = AEGP_PostRenderOptions_SET_PROXY
};

enum class OutputTypes
{
    NONE = AEGP_OutputType_NONE,
    VIDEO = AEGP_OutputType_VIDEO,
    AUDIO = AEGP_OutputType_AUDIO
};

enum class VideoChannels
{
    NONE = AEGP_VideoChannels_NONE,
    RGB = AEGP_VideoChannels_RGB,
    RGBA = AEGP_VideoChannels_RGBA,
    ALPHA = AEGP_VideoChannels_ALPHA
};

enum class StretchQuality
{
    NONE = AEGP_StretchQual_NONE,
    LOW = AEGP_StretchQual_LOW,
    HIGH = AEGP_StretchQual_HIGH
};

enum class OutputColorType
{
    STRAIGHT = AEGP_OutputColorType_STRAIGHT,
    PREMUL = AEGP_OutputColorType_PREMUL
};

enum class WorldType
{
    NONE = AEGP_WorldType_NONE,
    W8 = AEGP_WorldType_8,
    W16 = AEGP_WorldType_16,
    W32 = AEGP_WorldType_32
};

enum class MatteMode
{
    STRAIGHT = AEGP_MatteMode_STRAIGHT,
    PREMUL_BLACK = AEGP_MatteMode_PREMUL_BLACK,
    PREMUL_BG_COLOR = AEGP_MatteMode_PREMUL_BG_COLOR
};

enum class ChannelOrder
{
    ARGB = AEGP_ChannelOrder_ARGB,
    BGRA = AEGP_ChannelOrder_BGRA
};

enum class ItemQuality
{
    DRAFT = AEGP_ItemQuality_DRAFT,
    BEST = AEGP_ItemQuality_BEST
};

enum class CollectionItemType
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

enum class StreamCollectionItemType
{
    NONE = AEGP_StreamCollectionItemType_NONE,
    LAYER = AEGP_StreamCollectionItemType_LAYER,
    MASK = AEGP_StreamCollectionItemType_MASK,
    EFFECT = AEGP_StreamCollectionItemType_EFFECT
};

enum class WindowType
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

enum class MenuID
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

#endif // ENUMS_HPP
