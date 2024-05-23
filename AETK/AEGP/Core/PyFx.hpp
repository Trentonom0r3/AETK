
#ifndef PYFX_HPP
#define PYFX_HPP
// #define TK_INTERNAL
#include "AETK/AEGP/Core/Suites.hpp" /* Suite Wrappers For After Effects*/

#include <Python.h>
#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

template <typename T> inline void bind_handle_wrapper(py::module &m, const std::string &typestr)
{
    using Class = HandleWrapper<T>;
    using ClassPtr = std::shared_ptr<Class>;

    std::string wrapperName = typestr;
    // remove "H" from the end of the type string
    std::string ptrName = wrapperName.substr(0, wrapperName.size() - 1) + "Ptr";

    // Bind HandleWrapper
    py::class_<HandleWrapper<T>, std::shared_ptr<HandleWrapper<T>>>(m, wrapperName.c_str())
        .def("__del__", [](HandleWrapper<T> &self) {
            // Custom cleanup logic here
            self.~HandleWrapper();
        });

    // Bind shared_ptr<HandleWrapper>
    py::class_<ClassPtr>(m, ptrName.c_str());
}

inline void bindStreamValue2(py::module &m)
{
    using Class = StreamValue2;
    using ClassPtr = std::shared_ptr<Class>;

    py::class_<Class, std::shared_ptr<Class>>(m, "StreamValue2")
        //.def(py::init<>())
        .def(py::init<StreamRefPtr, std::variant<OneD, TwoD, ThreeD, Color>>())
        .def("value", &Class::value, py::return_value_policy::reference);

    py::class_<ClassPtr>(m, "StreamValue2Ptr");
}

inline void bind_mem_flag(py::module &m)
{
    py::enum_<MemFlag>(m, "MemFlag")
        .value("NONE", MemFlag::NONE)
        .value("CLEAR", MemFlag::CLEAR)
        .value("QUIET", MemFlag::QUIET)
        .export_values();
}

inline void bind_platform(py::module &m)
{
    py::enum_<Platform>(m, "Platform").value("WIN", Platform::WIN).value("MAC", Platform::MAC).export_values();
}

inline void bind_proj_bit_depth(py::module &m)
{
    py::enum_<ProjBitDepth>(m, "ProjBitDepth")
        .value("_8", ProjBitDepth::_8)
        .value("_16", ProjBitDepth::_16)
        .value("_32", ProjBitDepth::_32)
        .value("NUM_VALID_DEPTHS", ProjBitDepth::NUM_VALID_DEPTHS)
        .export_values();
}

inline void bind_camera_type(py::module &m)
{
    py::enum_<CameraType>(m, "CameraType")
        .value("NONE", CameraType::NONE)
        .value("PERSPECTIVE", CameraType::PERSPECTIVE)
        .value("ORTHOGRAPHIC", CameraType::ORTHOGRAPHIC)
        .value("NUM_TYPES", CameraType::NUM_TYPES)
        .export_values();
}

inline void bind_time_display_type(py::module &m)
{
    py::enum_<TimeDisplayType>(m, "TimeDisplayType")
        .value("TIMECODE", TimeDisplayType::TIMECODE)
        .value("FRAMES", TimeDisplayType::FRAMES)
        .value("FEET_AND_FRAMES", TimeDisplayType::FEET_AND_FRAMES)
        .export_values();
}

inline void bind_film_size_units(py::module &m)
{
    py::enum_<FilmSizeUnits>(m, "FilmSizeUnits")
        .value("NONE", FilmSizeUnits::NONE)
        .value("HORIZONTAL", FilmSizeUnits::HORIZONTAL)
        .value("VERTICAL", FilmSizeUnits::VERTICAL)
        .value("DIAGONAL", FilmSizeUnits::DIAGONAL)
        .export_values();
}

inline void bind_light_type(py::module &m)
{
    py::enum_<LightType>(m, "LightType")
        .value("NONE", LightType::NONE)
        .value("PARALLEL", LightType::PARALLEL)
        .value("SPOT", LightType::SPOT)
        .value("POINT", LightType::POINT)
        .value("AMBIENT", LightType::AMBIENT)
        .value("RESERVED1", LightType::RESERVED1)
        .value("NUM_TYPES", LightType::NUM_TYPES)
        .export_values();
}

inline void bind_footage_signature(py::module &m)
{
    py::enum_<FootageSignature>(m, "FootageSignature")
        .value("NONE", FootageSignature::NONE)
        .value("MISSING", FootageSignature::MISSING)
        .value("SOLID", FootageSignature::SOLID)
        .export_values();
}

inline void bind_light_falloff_type(py::module &m)
{
    py::enum_<LightFalloffType>(m, "LightFalloffType")
        .value("NONE", LightFalloffType::NONE)
        .value("SMOOTH", LightFalloffType::SMOOTH)
        .value("INVERSE_SQUARE_CLAMPED", LightFalloffType::INVERSE_SQUARE_CLAMPED)
        .export_values();
}

inline void bind_footage_depth(py::module &m)
{
    py::enum_<FootageDepth>(m, "FootageDepth")
        .value("_1", FootageDepth::_1)
        .value("_2", FootageDepth::_2)
        .value("_4", FootageDepth::_4)
        .value("_8", FootageDepth::_8)
        .value("_16", FootageDepth::_16)
        .value("_24", FootageDepth::_24)
        .value("_30", FootageDepth::_30)
        .value("_32", FootageDepth::_32)
        .value("GRAY_2", FootageDepth::GRAY_2)
        .value("GRAY_4", FootageDepth::GRAY_4)
        .value("GRAY_8", FootageDepth::GRAY_8)
        .value("_48", FootageDepth::_48)
        .value("_64", FootageDepth::_64)
        .value("GRAY_16", FootageDepth::GRAY_16)
        .export_values();
}

inline void bind_frames_per_foot(py::module &m)
{
    py::enum_<FramesPerFoot>(m, "FramesPerFoot")
        .value("_35MM", FramesPerFoot::_35MM)
        .value("_16MM", FramesPerFoot::_16MM)
        .export_values();
}

inline void bind_time_display_mode(py::module &m)
{
    py::enum_<TimeDisplayMode>(m, "TimeDisplayMode")
        .value("TIMECODE", TimeDisplayMode::TIMECODE)
        .value("FRAMES", TimeDisplayMode::FRAMES)
        .export_values();
}

inline void bind_source_timecode_display_mode(py::module &m)
{
    py::enum_<SourceTimecodeDisplayMode>(m, "SourceTimecodeDisplayMode")
        .value("ZERO", SourceTimecodeDisplayMode::ZERO)
        .value("SOURCE_TIMECODE", SourceTimecodeDisplayMode::SOURCE_TIMECODE)
        .export_values();
}

inline void bind_frames_display_mode(py::module &m)
{
    py::enum_<FramesDisplayMode>(m, "FramesDisplayMode")
        .value("ZERO_BASED", FramesDisplayMode::ZERO_BASED)
        .value("ONE_BASED", FramesDisplayMode::ONE_BASED)
        .value("TIMECODE_CONVERSION", FramesDisplayMode::TIMECODE_CONVERSION)
        .export_values();
}

inline void bind_sound_encoding(py::module &m)
{
    py::enum_<SoundEncoding>(m, "SoundEncoding")
        .value("UNSIGNED_PCM", SoundEncoding::UNSIGNED_PCM)
        .value("SIGNED_PCM", SoundEncoding::SIGNED_PCM)
        .value("FLOAT", SoundEncoding::FLOAT)
        .value("END", SoundEncoding::END)
        .value("BEGIN", SoundEncoding::BEGIN)
        .export_values();
}

inline void bind_item_type(py::module &m)
{
    py::enum_<ItemType>(m, "ItemType")
        .value("NONE", ItemType::NONE)
        .value("FOLDER", ItemType::FOLDER)
        .value("COMP", ItemType::COMP)
        .value("SOLID", ItemType::SOLID)
        .value("FOOTAGE", ItemType::FOOTAGE)
        .value("NUM_TYPES", ItemType::NUM_TYPES)
        .export_values();
}

inline void bind_item_flag(py::module &m)
{
    py::enum_<ItemFlag>(m, "ItemFlag")
        .value("MISSING", ItemFlag::MISSING)
        .value("HAS_PROXY", ItemFlag::HAS_PROXY)
        .value("USING_PROXY", ItemFlag::USING_PROXY)
        .value("MISSING_PROXY", ItemFlag::MISSING_PROXY)
        .value("HAS_VIDEO", ItemFlag::HAS_VIDEO)
        .value("HAS_AUDIO", ItemFlag::HAS_AUDIO)
        .value("STILL", ItemFlag::STILL)
        .value("HAS_ACTIVE_AUDIO", ItemFlag::HAS_ACTIVE_AUDIO)
        .export_values();
}

inline void bind_label(py::module &m)
{
    py::enum_<Label>(m, "Label")
        .value("NONE", Label::NONE)
        .value("NO_LABEL", Label::NO_LABEL)
        .value("LABEL_1", Label::LABEL_1)
        .value("LABEL_2", Label::LABEL_2)
        .value("LABEL_3", Label::LABEL_3)
        .value("LABEL_4", Label::LABEL_4)
        .value("LABEL_5", Label::LABEL_5)
        .value("LABEL_6", Label::LABEL_6)
        .value("LABEL_7", Label::LABEL_7)
        .value("LABEL_8", Label::LABEL_8)
        .value("LABEL_9", Label::LABEL_9)
        .value("LABEL_10", Label::LABEL_10)
        .value("LABEL_11", Label::LABEL_11)
        .value("LABEL_12", Label::LABEL_12)
        .value("LABEL_13", Label::LABEL_13)
        .value("LABEL_14", Label::LABEL_14)
        .value("LABEL_15", Label::LABEL_15)
        .value("LABEL_16", Label::LABEL_16)
        .value("NUM_TYPES", Label::NUM_TYPES)
        .export_values();
}

inline void bind_persistent_type(py::module &m)
{
    py::enum_<PersistentType>(m, "PersistentType")
        .value("MACHINE_SPECIFIC", PersistentType::MACHINE_SPECIFIC)
        .value("MACHINE_INDEPENDENT", PersistentType::MACHINE_INDEPENDENT)
        .value("MACHINE_INDEPENDENT_RENDER", PersistentType::MACHINE_INDEPENDENT_RENDER)
        .value("MACHINE_INDEPENDENT_OUTPUT", PersistentType::MACHINE_INDEPENDENT_OUTPUT)
        .value("MACHINE_INDEPENDENT_COMPOSITION", PersistentType::MACHINE_INDEPENDENT_COMPOSITION)
        .value("MACHINE_SPECIFIC_TEXT", PersistentType::MACHINE_SPECIFIC_TEXT)
        .value("MACHINE_SPECIFIC_PAINT", PersistentType::MACHINE_SPECIFIC_PAINT)
        .value("MACHINE_SPECIFIC_EFFECTS", PersistentType::MACHINE_SPECIFIC_EFFECTS)
        .value("MACHINE_SPECIFIC_EXPRESSION_SNIPPETS", PersistentType::MACHINE_SPECIFIC_EXPRESSION_SNIPPETS)
        .value("MACHINE_SPECIFIC_SCRIPT_SNIPPETS", PersistentType::MACHINE_SPECIFIC_SCRIPT_SNIPPETS)
        .value("NUM_TYPES", PersistentType::NUM_TYPES)
        .export_values();
}

inline void bind_comp_flag(py::module &m)
{
    py::enum_<CompFlag>(m, "CompFlag")
        .value("SHOW_ALL_SHY", CompFlag::SHOW_ALL_SHY)
        .value("ENABLE_MOTION_BLUR", CompFlag::ENABLE_MOTION_BLUR)
        .value("ENABLE_TIME_FILTER", CompFlag::ENABLE_TIME_FILTER)
        .value("GRID_TO_FRAMES", CompFlag::GRID_TO_FRAMES)
        .value("GRID_TO_FIELDS", CompFlag::GRID_TO_FIELDS)
        .value("USE_LOCAL_DSF", CompFlag::USE_LOCAL_DSF)
        .value("DRAFT_3D", CompFlag::DRAFT_3D)
        .value("SHOW_GRAPH", CompFlag::SHOW_GRAPH)
        .export_values();
}

inline void bind_transfer_flags(py::module &m)
{
    py::enum_<TransferFlags>(m, "TransferFlags")
        .value("PRESERVE_ALPHA", TransferFlags::PRESERVE_ALPHA)
        .value("RANDOMIZE_DISSOLVE", TransferFlags::RANDOMIZE_DISSOLVE)
        .export_values();
}

inline void bind_track_matte(py::module &m)
{
    py::enum_<TrackMatte>(m, "TrackMatte")
        .value("NO_TRACK_MATTE", TrackMatte::NO_TRACK_MATTE)
        .value("ALPHA", TrackMatte::ALPHA)
        .value("NOT_ALPHA", TrackMatte::NOT_ALPHA)
        .value("LUMA", TrackMatte::LUMA)
        .value("NOT_LUMA", TrackMatte::NOT_LUMA)
        .export_values();
}

inline void bind_layer_qual(py::module &m)
{
    py::enum_<LayerQual>(m, "LayerQual")
        .value("NONE", LayerQual::NONE)
        .value("WIREFRAME", LayerQual::WIREFRAME)
        .value("DRAFT", LayerQual::DRAFT)
        .value("BEST", LayerQual::BEST)
        .export_values();
}

inline void bind_layer_sampling_qual(py::module &m)
{
    py::enum_<LayerSamplingQual>(m, "LayerSamplingQual")
        .value("BILINEAR", LayerSamplingQual::BILINEAR)
        .value("BICUBIC", LayerSamplingQual::BICUBIC)
        .export_values();
}

inline void bind_layer_flag(py::module &m)
{
    py::enum_<LayerFlag>(m, "LayerFlag")
        .value("NONE", LayerFlag::NONE)
        .value("VIDEO_ACTIVE", LayerFlag::VIDEO_ACTIVE)
        .value("AUDIO_ACTIVE", LayerFlag::AUDIO_ACTIVE)
        .value("EFFECTS_ACTIVE", LayerFlag::EFFECTS_ACTIVE)
        .value("MOTION_BLUR", LayerFlag::MOTION_BLUR)
        .value("FRAME_BLENDING", LayerFlag::FRAME_BLENDING)
        .value("LOCKED", LayerFlag::LOCKED)
        .value("SHY", LayerFlag::SHY)
        .value("COLLAPSE", LayerFlag::COLLAPSE)
        .value("AUTO_ORIENT_ROTATION", LayerFlag::AUTO_ORIENT_ROTATION)
        .value("ADJUSTMENT_LAYER", LayerFlag::ADJUSTMENT_LAYER)
        .value("TIME_REMAPPING", LayerFlag::TIME_REMAPPING)
        .value("LAYER_IS_3D", LayerFlag::LAYER_IS_3D)
        .value("LOOK_AT_CAMERA", LayerFlag::LOOK_AT_CAMERA)
        .value("LOOK_AT_POI", LayerFlag::LOOK_AT_POI)
        .value("SOLO", LayerFlag::SOLO)
        .value("MARKERS_LOCKED", LayerFlag::MARKERS_LOCKED)
        .value("NULL_LAYER", LayerFlag::NULL_LAYER)
        .value("HIDE_LOCKED_MASKS", LayerFlag::HIDE_LOCKED_MASKS)
        .value("GUIDE_LAYER", LayerFlag::GUIDE_LAYER)
        .value("ADVANCED_FRAME_BLENDING", LayerFlag::ADVANCED_FRAME_BLENDING)
        .value("SUBLAYERS_RENDER_SEPARATELY", LayerFlag::SUBLAYERS_RENDER_SEPARATELY)
        .value("ENVIRONMENT_LAYER", LayerFlag::ENVIRONMENT_LAYER)
        .export_values();
}

inline void bind_object_type(py::module &m)
{
    py::enum_<ObjectType>(m, "ObjectType")
        .value("NONE", ObjectType::NONE)
        .value("AV", ObjectType::AV)
        .value("LIGHT", ObjectType::LIGHT)
        .value("CAMERA", ObjectType::CAMERA)
        .value("TEXT", ObjectType::TEXT)
        .value("VECTOR", ObjectType::VECTOR)
        .value("RESERVED1", ObjectType::RESERVED1)
        .value("RESERVED2", ObjectType::RESERVED2)
        .value("RESERVED3", ObjectType::RESERVED3)
        .value("RESERVED4", ObjectType::RESERVED4)
        .value("RESERVED5", ObjectType::RESERVED5)
        .value("NUM_TYPES", ObjectType::NUM_TYPES)
        .export_values();
}

inline void bind_ltime_mode(py::module &m)
{
    py::enum_<LTimeMode>(m, "LTimeMode")
        .value("LayerTime", LTimeMode::LayerTime)
        .value("CompTime", LTimeMode::CompTime)
        .export_values();
}

inline void bind_layer_stream(py::module &m)
{
    py::enum_<LayerStream>(m, "LayerStream")
        .value("SOURCE_TEXT", LayerStream::SOURCE_TEXT)
        .value("ANCHORPOINT", LayerStream::ANCHORPOINT)
        .value("POSITION", LayerStream::POSITION)
        .value("SCALE", LayerStream::SCALE)
        .value("ROTATION", LayerStream::ROTATION)
        .value("ROTATE_Z", LayerStream::ROTATE_Z)
        .value("OPACITY", LayerStream::OPACITY)
        .value("AUDIO", LayerStream::AUDIO)
        .value("MARKER", LayerStream::MARKER)
        .value("TIME_REMAP", LayerStream::TIME_REMAP)
        .value("ROTATE_X", LayerStream::ROTATE_X)
        .value("ROTATE_Y", LayerStream::ROTATE_Y)
        .value("ORIENTATION", LayerStream::ORIENTATION)
        .value("TEXT", LayerStream::TEXT)
        .value("ZOOM", LayerStream::ZOOM)
        .value("DEPTH_OF_FIELD", LayerStream::DEPTH_OF_FIELD)
        .value("FOCUS_DISTANCE", LayerStream::FOCUS_DISTANCE)
        .value("APERTURE", LayerStream::APERTURE)
        .value("BLUR_LEVEL", LayerStream::BLUR_LEVEL)
        .value("IRIS_SHAPE", LayerStream::IRIS_SHAPE)
        .value("IRIS_ROTATION", LayerStream::IRIS_ROTATION)
        .value("IRIS_ROUNDNESS", LayerStream::IRIS_ROUNDNESS)
        .value("IRIS_ASPECT_RATIO", LayerStream::IRIS_ASPECT_RATIO)
        .value("IRIS_DIFFRACTION_FRINGE", LayerStream::IRIS_DIFFRACTION_FRINGE)
        .value("IRIS_HIGHLIGHT_GAIN", LayerStream::IRIS_HIGHLIGHT_GAIN)
        .value("IRIS_HIGHLIGHT_THRESHOLD", LayerStream::IRIS_HIGHLIGHT_THRESHOLD)
        .value("IRIS_HIGHLIGHT_SATURATION", LayerStream::IRIS_HIGHLIGHT_SATURATION)
        .value("INTENSITY", LayerStream::INTENSITY)
        .value("COLOR", LayerStream::COLOR)
        .value("CONE_ANGLE", LayerStream::CONE_ANGLE)
        .value("CONE_FEATHER", LayerStream::CONE_FEATHER)
        .value("SHADOW_DARKNESS", LayerStream::SHADOW_DARKNESS)
        .value("SHADOW_DIFFUSION", LayerStream::SHADOW_DIFFUSION)
        .value("LIGHT_FALLOFF_TYPE", LayerStream::LIGHT_FALLOFF_TYPE)
        .value("LIGHT_FALLOFF_START", LayerStream::LIGHT_FALLOFF_START)
        .value("LIGHT_FALLOFF_DISTANCE", LayerStream::LIGHT_FALLOFF_DISTANCE)
        .value("ACCEPTS_SHADOWS", LayerStream::ACCEPTS_SHADOWS)
        .value("ACCEPTS_LIGHTS", LayerStream::ACCEPTS_LIGHTS)
        .value("AMBIENT_COEFF", LayerStream::AMBIENT_COEFF)
        .value("DIFFUSE_COEFF", LayerStream::DIFFUSE_COEFF)
        .value("SPECULAR_INTENSITY", LayerStream::SPECULAR_INTENSITY)
        .value("SPECULAR_SHININESS", LayerStream::SPECULAR_SHININESS)
        .value("CASTS_SHADOWS", LayerStream::CASTS_SHADOWS)
        .value("LIGHT_TRANSMISSION", LayerStream::LIGHT_TRANSMISSION)
        .value("METAL", LayerStream::METAL)
        .value("REFLECTION_INTENSITY", LayerStream::REFLECTION_INTENSITY)
        .value("REFLECTION_SHARPNESS", LayerStream::REFLECTION_SHARPNESS)
        .value("REFLECTION_ROLLOFF", LayerStream::REFLECTION_ROLLOFF)
        .value("TRANSPARENCY_COEFF", LayerStream::TRANSPARENCY_COEFF)
        .value("TRANSPARENCY_ROLLOFF", LayerStream::TRANSPARENCY_ROLLOFF)
        .value("INDEX_OF_REFRACTION", LayerStream::INDEX_OF_REFRACTION)
        .value("EXTRUSION_BEVEL_STYLE", LayerStream::EXTRUSION_BEVEL_STYLE)
        .value("EXTRUSION_BEVEL_DIRECTION", LayerStream::EXTRUSION_BEVEL_DIRECTION)
        .value("EXTRUSION_BEVEL_DEPTH", LayerStream::EXTRUSION_BEVEL_DEPTH)
        .value("EXTRUSION_HOLE_BEVEL_DEPTH", LayerStream::EXTRUSION_HOLE_BEVEL_DEPTH)
        .value("EXTRUSION_DEPTH", LayerStream::EXTRUSION_DEPTH)
        .value("PLANE_CURVATURE", LayerStream::PLANE_CURVATURE)
        .value("PLANE_SUBDIVISION", LayerStream::PLANE_SUBDIVISION)
        .export_values();
}

inline void bind_mask_stream(py::module &m)
{
    py::enum_<MaskStream>(m, "MaskStream")
        .value("OUTLINE", MaskStream::OUTLINE)
        .value("OPACITY", MaskStream::OPACITY)
        .value("FEATHER", MaskStream::FEATHER)
        .value("EXPANSION", MaskStream::EXPANSION)
        .export_values();
}

inline void bind_stream_flag(py::module &m)
{
    py::enum_<StreamFlag>(m, "StreamFlag")
        .value("NONE", StreamFlag::NONE)
        .value("HAS_MIN", StreamFlag::HAS_MIN)
        .value("HAS_MAX", StreamFlag::HAS_MAX)
        .value("IS_SPATIAL", StreamFlag::IS_SPATIAL)
        .export_values();
}

inline void bind_key_interp(py::module &m)
{
    py::enum_<KeyInterp>(m, "KeyInterp")
        .value("NONE", KeyInterp::NONE)
        .value("LINEAR", KeyInterp::LINEAR)
        .value("BEZIER", KeyInterp::BEZIER)
        .value("HOLD", KeyInterp::HOLD)
        .export_values();
}

inline void bind_key_interp_mask(py::module &m)
{
    py::enum_<KeyInterpMask>(m, "KeyInterpMask")
        .value("NONE", KeyInterpMask::NONE)
        .value("LINEAR", KeyInterpMask::LINEAR)
        .value("BEZIER", KeyInterpMask::BEZIER)
        .value("HOLD", KeyInterpMask::HOLD)
        .value("CUSTOM", KeyInterpMask::CUSTOM)
        .value("ANY", KeyInterpMask::ANY)
        .export_values();
}

inline void bind_stream_type(py::module &m)
{
    py::enum_<StreamType>(m, "StreamType")
        .value("NONE", StreamType::NONE)
        .value("ThreeD_SPATIAL", StreamType::ThreeD_SPATIAL)
        .value("ThreeD", StreamType::ThreeD)
        .value("TwoD_SPATIAL", StreamType::TwoD_SPATIAL)
        .value("TwoD", StreamType::TwoD)
        .value("OneD", StreamType::OneD)
        .value("COLOR", StreamType::COLOR)
        .value("ARB", StreamType::ARB)
        .value("MARKER", StreamType::MARKER)
        .value("LAYER_ID", StreamType::LAYER_ID)
        .value("MASK_ID", StreamType::MASK_ID)
        .value("MASK", StreamType::MASK)
        .value("TEXT_DOCUMENT", StreamType::TEXT_DOCUMENT)
        .export_values();
}

inline void bind_stream_grouping_type(py::module &m)
{
    py::enum_<StreamGroupingType>(m, "StreamGroupingType")
        .value("NONE", StreamGroupingType::NONE)
        .value("LEAF", StreamGroupingType::LEAF)
        .value("NAMED_GROUP", StreamGroupingType::NAMED_GROUP)
        .value("INDEXED_GROUP", StreamGroupingType::INDEXED_GROUP)
        .export_values();
}

inline void bind_dyn_stream_flag(py::module &m)
{
    py::enum_<DynStreamFlag>(m, "DynStreamFlag")
        .value("ACTIVE_EYEBALL", DynStreamFlag::ACTIVE_EYEBALL)
        .value("HIDDEN", DynStreamFlag::HIDDEN)
        .value("DISABLED", DynStreamFlag::DISABLED)
        .value("ELIDED", DynStreamFlag::ELIDED)
        .value("SHOWN_WHEN_EMPTY", DynStreamFlag::SHOWN_WHEN_EMPTY)
        .value("SKIP_REVEAL_WHEN_UNHIDDEN", DynStreamFlag::SKIP_REVEAL_WHEN_UNHIDDEN)
        .export_values();
}

inline void bind_keyframe_flag(py::module &m)
{
    py::enum_<KeyframeFlag>(m, "KeyframeFlag")
        .value("NONE", KeyframeFlag::NONE)
        .value("TEMPORAL_CONTINUOUS", KeyframeFlag::TEMPORAL_CONTINUOUS)
        .value("TEMPORAL_AUTOBEZIER", KeyframeFlag::TEMPORAL_AUTOBEZIER)
        .value("SPATIAL_CONTINUOUS", KeyframeFlag::SPATIAL_CONTINUOUS)
        .value("SPATIAL_AUTOBEZIER", KeyframeFlag::SPATIAL_AUTOBEZIER)
        .value("ROVING", KeyframeFlag::ROVING)
        .export_values();
}

inline void bind_marker_string_type(py::module &m)
{
    py::enum_<MarkerStringType>(m, "MarkerStringType")
        .value("COMMENT", MarkerStringType::COMMENT)
        .value("CHAPTER", MarkerStringType::CHAPTER)
        .value("URL", MarkerStringType::URL)
        .value("FRAME_TARGET", MarkerStringType::FRAME_TARGET)
        .value("CUE_POINT_NAME", MarkerStringType::CUE_POINT_NAME)
        .export_values();
}

inline void bind_marker_flag(py::module &m)
{
    py::enum_<MarkerFlag>(m, "MarkerFlag")
        .value("NONE", MarkerFlag::NONE)
        .value("NAVIGATION", MarkerFlag::NAVIGATION)
        .value("PROTECT_REGION", MarkerFlag::PROTECT_REGION)
        .export_values();
}

inline void bind_effect_flags(py::module &m)
{
    py::enum_<EffectFlags>(m, "EffectFlags")
        .value("NONE", EffectFlags::NONE)
        .value("ACTIVE", EffectFlags::ACTIVE)
        .value("AUDIO_ONLY", EffectFlags::AUDIO_ONLY)
        .value("AUDIO_TOO", EffectFlags::AUDIO_TOO)
        .value("MISSING", EffectFlags::MISSING)
        .export_values();
}

inline void bind_mask_mode(py::module &m)
{
    py::enum_<MaskMode>(m, "MaskMode")
        .value("NONE", MaskMode::NONE)
        .value("ADD", MaskMode::ADD)
        .value("SUBTRACT", MaskMode::SUBTRACT)
        .value("INTERSECT", MaskMode::INTERSECT)
        .value("LIGHTEN", MaskMode::LIGHTEN)
        .value("DARKEN", MaskMode::DARKEN)
        .value("DIFF", MaskMode::DIFF)
        .value("ACCUM", MaskMode::ACCUM)
        .export_values();
}

inline void bind_mask_mblur(py::module &m)
{
    py::enum_<MaskMBlur>(m, "MaskMBlur")
        .value("SAME_AS_LAYER", MaskMBlur::SAME_AS_LAYER)
        .value("OFF", MaskMBlur::OFF)
        .value("ON", MaskMBlur::ON)
        .export_values();
}

inline void bind_mask_feather_falloff(py::module &m)
{
    py::enum_<MaskFeatherFalloff>(m, "MaskFeatherFalloff")
        .value("SMOOTH", MaskFeatherFalloff::SMOOTH)
        .value("LINEAR", MaskFeatherFalloff::LINEAR)
        .export_values();
}

inline void bind_mask_feather_interp(py::module &m)
{
    py::enum_<MaskFeatherInterp>(m, "MaskFeatherInterp")
        .value("NORMAL", MaskFeatherInterp::NORMAL)
        .value("HOLD_CW", MaskFeatherInterp::HOLD_CW)
        .export_values();
}

inline void bind_mask_feather_type(py::module &m)
{
    py::enum_<MaskFeatherType>(m, "MaskFeatherType")
        .value("OUTER", MaskFeatherType::OUTER)
        .value("INNER", MaskFeatherType::INNER)
        .export_values();
}

inline void bind_alpha_flags(py::module &m)
{
    py::enum_<AlphaFlags>(m, "AlphaFlags")
        .value("PREMUL", AlphaFlags::PREMUL)
        .value("INVERTED", AlphaFlags::INVERTED)
        .value("ALPHA_IGNORE", AlphaFlags::ALPHA_IGNORE)
        .export_values();
}

inline void bind_pulldown_phase(py::module &m)
{
    py::enum_<PulldownPhase>(m, "PulldownPhase")
        .value("NO_PULLDOWN", PulldownPhase::NO_PULLDOWN)
        .value("WSSWW", PulldownPhase::WSSWW)
        .value("SSWWW", PulldownPhase::SSWWW)
        .value("SWWWS", PulldownPhase::SWWWS)
        .value("WWWSS", PulldownPhase::WWWSS)
        .value("WWSSW", PulldownPhase::WWSSW)
        .value("WWWSW", PulldownPhase::WWWSW)
        .value("WWSWW", PulldownPhase::WWSWW)
        .value("WSWWW", PulldownPhase::WSWWW)
        .value("SWWWW", PulldownPhase::SWWWW)
        .value("WWWWS", PulldownPhase::WWWWS)
        .export_values();
}

inline void bind_layer_draw_style(py::module &m)
{
    py::enum_<LayerDrawStyle>(m, "LayerDrawStyle")
        .value("LAYER_BOUNDS", LayerDrawStyle::LAYER_BOUNDS)
        .value("DOCUMENT_BOUNDS", LayerDrawStyle::DOCUMENT_BOUNDS)
        .export_values();
}

inline void bind_interpretation_style(py::module &m)
{
    py::enum_<InterpretationStyle>(m, "InterpretationStyle")
        .value("NO_DIALOG_GUESS", InterpretationStyle::NO_DIALOG_GUESS)
        .value("DIALOG_OK", InterpretationStyle::DIALOG_OK)
        .value("NO_DIALOG_NO_GUESS", InterpretationStyle::NO_DIALOG_NO_GUESS)
        .export_values();
}

inline void bind_plugin_path_type(py::module &m)
{
    py::enum_<PluginPathType>(m, "PluginPathType")
        .value("PLUGIN", PluginPathType::PLUGIN)
        .value("USER_PLUGIN", PluginPathType::USER_PLUGIN)
        .value("ALLUSER_PLUGIN", PluginPathType::ALLUSER_PLUGIN)
        .value("APP", PluginPathType::APP)
        .export_values();
}

inline void bind_render_queue_state(py::module &m)
{
    py::enum_<RenderQueueState>(m, "RenderQueueState")
        .value("STOPPED", RenderQueueState::STOPPED)
        .value("PAUSED", RenderQueueState::PAUSED)
        .value("RENDERING", RenderQueueState::RENDERING)
        .export_values();
}

inline void bind_render_item_status(py::module &m)
{
    py::enum_<RenderItemStatus>(m, "RenderItemStatus")
        .value("NONE", RenderItemStatus::NONE)
        .value("WILL_CONTINUE", RenderItemStatus::WILL_CONTINUE)
        .value("NEEDS_OUTPUT", RenderItemStatus::NEEDS_OUTPUT)
        .value("UNQUEUED", RenderItemStatus::UNQUEUED)
        .value("QUEUED", RenderItemStatus::QUEUED)
        .value("RENDERING", RenderItemStatus::RENDERING)
        .value("USER_STOPPED", RenderItemStatus::USER_STOPPED)
        .value("ERR_STOPPED", RenderItemStatus::ERR_STOPPED)
        .value("DONE", RenderItemStatus::DONE)
        .export_values();
}

inline void bind_log_type(py::module &m)
{
    py::enum_<LogType>(m, "LogType")
        .value("NONE", LogType::NONE)
        .value("ERRORS_ONLY", LogType::ERRORS_ONLY)
        .value("PLUS_SETTINGS", LogType::PLUS_SETTINGS)
        .value("PER_FRAME_INFO", LogType::PER_FRAME_INFO)
        .export_values();
}

inline void bind_embedding_type(py::module &m)
{
    py::enum_<EmbeddingType>(m, "EmbeddingType")
        .value("NONE", EmbeddingType::NONE)
        .value("NOTHING", EmbeddingType::NOTHING)
        .value("LINK", EmbeddingType::LINK)
        .value("LINK_AND_COPY", EmbeddingType::LINK_AND_COPY)
        .export_values();
}

inline void bind_post_render_action(py::module &m)
{
    py::enum_<PostRenderAction>(m, "PostRenderAction")
        .value("NONE", PostRenderAction::NONE)
        .value("IMPORT", PostRenderAction::IMPORT)
        .value("IMPORT_AND_REPLACE_USAGE", PostRenderAction::IMPORT_AND_REPLACE_USAGE)
        .value("SET_PROXY", PostRenderAction::SET_PROXY)
        .export_values();
}

inline void bind_output_types(py::module &m)
{
    py::enum_<OutputTypes>(m, "OutputTypes")
        .value("NONE", OutputTypes::NONE)
        .value("VIDEO", OutputTypes::VIDEO)
        .value("AUDIO", OutputTypes::AUDIO)
        .export_values();
}

inline void bind_video_channels(py::module &m)
{
    py::enum_<VideoChannels>(m, "VideoChannels")
        .value("NONE", VideoChannels::NONE)
        .value("RGB", VideoChannels::RGB)
        .value("RGBA", VideoChannels::RGBA)
        .value("ALPHA", VideoChannels::ALPHA)
        .export_values();
}

inline void bind_stretch_quality(py::module &m)
{
    py::enum_<StretchQuality>(m, "StretchQuality")
        .value("NONE", StretchQuality::NONE)
        .value("LOW", StretchQuality::LOW)
        .value("HIGH", StretchQuality::HIGH)
        .export_values();
}

inline void bind_output_color_type(py::module &m)
{
    py::enum_<OutputColorType>(m, "OutputColorType")
        .value("STRAIGHT", OutputColorType::STRAIGHT)
        .value("PREMUL", OutputColorType::PREMUL)
        .export_values();
}

inline void bind_world_type(py::module &m)
{
    py::enum_<WorldType>(m, "WorldType")
        .value("NONE", WorldType::NONE)
        .value("W8", WorldType::W8)
        .value("W16", WorldType::W16)
        .value("W32", WorldType::W32)
        .export_values();
}

inline void bind_matte_mode(py::module &m)
{
    py::enum_<MatteMode>(m, "MatteMode")
        .value("STRAIGHT", MatteMode::STRAIGHT)
        .value("PREMUL_BLACK", MatteMode::PREMUL_BLACK)
        .value("PREMUL_BG_COLOR", MatteMode::PREMUL_BG_COLOR)
        .export_values();
}

inline void bind_channel_order(py::module &m)
{
    py::enum_<ChannelOrder>(m, "ChannelOrder")
        .value("ARGB", ChannelOrder::ARGB)
        .value("BGRA", ChannelOrder::BGRA)
        .export_values();
}

inline void bind_item_quality(py::module &m)
{
    py::enum_<ItemQuality>(m, "ItemQuality")
        .value("DRAFT", ItemQuality::DRAFT)
        .value("BEST", ItemQuality::BEST)
        .export_values();
}

inline void bind_collection_item_type(py::module &m)
{
    py::enum_<CollectionItemType>(m, "CollectionItemType")
        .value("NONE", CollectionItemType::NONE)
        .value("LAYER", CollectionItemType::LAYER)
        .value("MASK", CollectionItemType::MASK)
        .value("EFFECT", CollectionItemType::EFFECT)
        .value("STREAM", CollectionItemType::STREAM)
        .value("KEYFRAME", CollectionItemType::KEYFRAME)
        .value("MASK_VERTEX", CollectionItemType::MASK_VERTEX)
        .value("STREAMREF", CollectionItemType::STREAMREF)
        .export_values();
}

inline void bind_stream_collection_item_type(py::module &m)
{
    py::enum_<StreamCollectionItemType>(m, "StreamCollectionItemType")
        .value("NONE", StreamCollectionItemType::NONE)
        .value("LAYER", StreamCollectionItemType::LAYER)
        .value("MASK", StreamCollectionItemType::MASK)
        .value("EFFECT", StreamCollectionItemType::EFFECT)
        .export_values();
}

inline void bind_window_type(py::module &m)
{
    py::enum_<WindowType>(m, "WindowType")
        .value("NONE", WindowType::NONE)
        .value("PROJECT", WindowType::PROJECT)
        .value("COMP", WindowType::COMP)
        .value("TIME_LAYOUT", WindowType::TIME_LAYOUT)
        .value("LAYER", WindowType::LAYER)
        .value("FOOTAGE", WindowType::FOOTAGE)
        .value("RENDER_QUEUE", WindowType::RENDER_QUEUE)
        .value("QT", WindowType::QT)
        .value("DIALOG", WindowType::DIALOG)
        .value("FLOWCHART", WindowType::FLOWCHART)
        .value("EFFECT", WindowType::EFFECT)
        .value("OTHER", WindowType::OTHER)
        .export_values();
}

inline void bind_menu_id(py::module &m)
{
    py::enum_<MenuID>(m, "MenuID")
        .value("NONE", MenuID::NONE)
        .value("APPLE", MenuID::APPLE)
        .value("FILE", MenuID::FILE)
        .value("EDIT", MenuID::EDIT)
        .value("COMPOSITION", MenuID::COMPOSITION)
        .value("LAYER", MenuID::LAYER)
        .value("EFFECT", MenuID::EFFECT)
        .value("WINDOW", MenuID::WINDOW)
        .value("FLOATERS", MenuID::FLOATERS)
        .value("KF_ASSIST", MenuID::KF_ASSIST)
        .value("IMPORT", MenuID::IMPORT)
        .value("SAVE_FRAME_AS", MenuID::SAVE_FRAME_AS)
        .value("PREFS", MenuID::PREFS)
        .value("EXPORT", MenuID::EXPORT)
        .value("ANIMATION", MenuID::ANIMATION)
        .value("PURGE", MenuID::PURGE)
        .value("NEW", MenuID::NEW)
        .export_values();
}

inline void bind_color_val(py::module &m)
{
    py::class_<ColorVal>(m, "ColorVal")
        .def(py::init<>())
        .def(py::init<double, double, double, double>())
        .def(py::init<std::tuple<double, double, double, double>>())
        .def("ToTuple", &ColorVal::ToTuple)
        .def_readwrite("red", &ColorVal::red)
        .def_readwrite("green", &ColorVal::green)
        .def_readwrite("blue", &ColorVal::blue)
        .def_readwrite("alpha", &ColorVal::alpha);
}

inline void bind_time_display3(py::module &m)
{
    py::class_<TimeDisplay3>(m, "TimeDisplay3")
        .def(py::init<>())
        .def("ToTuple", &TimeDisplay3::ToTuple)
        .def_readwrite("display_mode", &TimeDisplay3::display_mode)
        .def_readwrite("footage_display_mode", &TimeDisplay3::footage_display_mode)
        .def_readwrite("display_dropframeB", &TimeDisplay3::display_dropframeB)
        .def_readwrite("use_feet_framesB", &TimeDisplay3::use_feet_framesB)
        .def_readwrite("timebaseC", &TimeDisplay3::timebaseC)
        .def_readwrite("frames_per_footC", &TimeDisplay3::frames_per_footC)
        .def_readwrite("frames_display_mode", &TimeDisplay3::frames_display_mode);
}

inline void bind_sound_data_format(py::module &m)
{
    py::class_<SoundDataFormat>(m, "SoundDataFormat")
        .def(py::init<>())
        .def("ToTuple", &SoundDataFormat::ToTuple)
        .def_readwrite("sample_rateF", &SoundDataFormat::sample_rateF)
        .def_readwrite("encoding", &SoundDataFormat::encoding)
        .def_readwrite("bytes_per_sampleL", &SoundDataFormat::bytes_per_sampleL)
        .def_readwrite("num_channelsL", &SoundDataFormat::num_channelsL);
}

inline void bind_downsample_factor(py::module &m)
{
    py::class_<DownsampleFactor>(m, "DownsampleFactor")
        .def(py::init<>())
        .def(py::init<short, short>())
        .def("ToTuple", &DownsampleFactor::ToTuple)
        .def_readwrite("xS", &DownsampleFactor::xS)
        .def_readwrite("yS", &DownsampleFactor::yS);
}

inline void bind_layer_transfer_mode(py::module &m)
{
    py::class_<LayerTransferMode>(m, "LayerTransferMode")
        .def(py::init<>())
        .def("ToTuple", &LayerTransferMode::ToTuple)
        .def_readwrite("mode", &LayerTransferMode::mode)
        .def_readwrite("flags", &LayerTransferMode::flags)
        .def_readwrite("track_matte", &LayerTransferMode::track_matte);
}

inline void bind_one_d_val(py::module &m)
{
    py::class_<OneDVal>(m, "OneDVal").def(py::init<>()).def(py::init<double>()).def_readwrite("value", &OneDVal::value);
}

inline void bind_two_d_val(py::module &m)
{
    py::class_<TwoDVal>(m, "TwoDVal")
        .def(py::init<>())
        .def(py::init<double, double>())
        .def(py::init<std::tuple<double, double>>())
        .def("ToTuple", &TwoDVal::ToTuple)
        .def_readwrite("x", &TwoDVal::x)
        .def_readwrite("y", &TwoDVal::y);
}

inline void bind_three_d_val(py::module &m)
{
    py::class_<ThreeDVal>(m, "ThreeDVal")
        .def(py::init<>())
        .def(py::init<double, double, double>())
        .def(py::init<std::tuple<double, double, double>>())
        .def("ToTuple", &ThreeDVal::ToTuple)
        .def_readwrite("x", &ThreeDVal::x)
        .def_readwrite("y", &ThreeDVal::y)
        .def_readwrite("z", &ThreeDVal::z);
}

inline void bind_keyframe_ease(py::module &m)
{
    py::class_<KeyframeEase>(m, "KeyframeEase")
        .def(py::init<>())
        .def(py::init<double, double>())
        .def(py::init<std::tuple<double, double>>())
        .def("ToTuple", &KeyframeEase::ToTuple)
        .def_readwrite("speedF", &KeyframeEase::speedF)
        .def_readwrite("influenceF", &KeyframeEase::influenceF);
}

inline void bind_mask_feather(py::module &m)
{
    py::class_<MaskFeather>(m, "MaskFeather")
        .def(py::init<>())
        .def(py::init<int, double, double, float, float, MaskFeatherInterp, MaskFeatherType>())
        .def(py::init<AEGP_MaskFeather>())
        .def("ToTuple", &MaskFeather::ToTuple)
        .def_readwrite("segment", &MaskFeather::segment)
        .def_readwrite("segment_sF", &MaskFeather::segment_sF)
        .def_readwrite("radiusF", &MaskFeather::radiusF)
        .def_readwrite("ui_corner_angleF", &MaskFeather::ui_corner_angleF)
        .def_readwrite("tensionF", &MaskFeather::tensionF)
        .def_readwrite("interp", &MaskFeather::interp)
        .def_readwrite("type", &MaskFeather::type);
}

inline void bind_mask_vertex(py::module &m)
{
    py::class_<MaskVertex>(m, "MaskVertex")
        .def(py::init<>())
        .def(py::init<double, double, double, double, double, double>())
        .def("ToTuple", &MaskVertex::ToTuple)
        .def_readwrite("x", &MaskVertex::x)
        .def_readwrite("y", &MaskVertex::y)
        .def_readwrite("tan_in_x", &MaskVertex::tan_in_x)
        .def_readwrite("tan_in_y", &MaskVertex::tan_in_y)
        .def_readwrite("tan_out_x", &MaskVertex::tan_out_x)
        .def_readwrite("tan_out_y", &MaskVertex::tan_out_y);
}

inline void bind_loop_behavior(py::module &m)
{
    py::class_<LoopBehavior>(m, "LoopBehavior")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def("ToTuple", &LoopBehavior::ToTuple)
        .def_readwrite("loops", &LoopBehavior::loops)
        .def_readwrite("reserved", &LoopBehavior::reserved);
}

inline void bind_footage_layer_key(py::module &m)
{
    py::class_<FootageLayerKey>(m, "FootageLayerKey")
        .def(py::init<>())
        .def(py::init<int, int, std::string, LayerDrawStyle>())
        .def("ToTuple", &FootageLayerKey::ToTuple)
        .def_readwrite("layer_idL", &FootageLayerKey::layer_idL)
        .def_readwrite("layer_indexL", &FootageLayerKey::layer_indexL)
        .def_readwrite("nameAC", &FootageLayerKey::nameAC)
        .def_readwrite("layer_draw_style", &FootageLayerKey::layer_draw_style);
}

inline void bind_file_sequence_import_options(py::module &m)
{
    py::class_<FileSequenceImportOptions>(m, "FileSequenceImportOptions")
        .def(py::init<>())
        .def(py::init<bool, bool, int, int>())
        .def("ToTuple", &FileSequenceImportOptions::ToTuple)
        .def_readwrite("all_in_folderB", &FileSequenceImportOptions::all_in_folderB)
        .def_readwrite("force_alphabeticalB", &FileSequenceImportOptions::force_alphabeticalB)
        .def_readwrite("start_frameL", &FileSequenceImportOptions::start_frameL)
        .def_readwrite("end_frameL", &FileSequenceImportOptions::end_frameL);
}

inline void bind_time(py::module &m)
{
    py::class_<Time>(m, "Time")
        .def(py::init<>())
        .def(py::init<A_Time>())
        .def(py::init<double>())
        .def(py::init<int>())
        .def("toTime", &Time::toTime)
        .def("toSeconds", &Time::toSeconds)
        .def("toFrames", &Time::toFrames)
        .def("toAEGP", &Time::toAEGP);
}

inline void bind_ratio(py::module &m)
{
    py::class_<Ratio>(m, "Ratio")
        .def(py::init<>())
        .def(py::init<int, unsigned int>())
        .def(py::init<A_Ratio>())
        .def(py::init<double>())
        .def("toAEGP", &Ratio::toAEGP)
        .def("ToTuple", &Ratio::ToTuple)
        .def_readwrite("num", &Ratio::num)
        .def_readwrite("den", &Ratio::den);
}

inline void bind_float_point(py::module &m)
{
    py::class_<FloatPoint>(m, "FloatPoint")
        .def(py::init<>())
        .def(py::init<A_FloatPoint>())
        .def(py::init<double, double>())
        .def("toAEGP", &FloatPoint::toAEGP)
        .def("ToTuple", &FloatPoint::ToTuple)
        .def_readwrite("x", &FloatPoint::x)
        .def_readwrite("y", &FloatPoint::y);
}

inline void bind_float_point3(py::module &m)
{
    py::class_<FloatPoint3>(m, "FloatPoint3")
        .def(py::init<>())
        .def(py::init<A_FloatPoint3>())
        .def(py::init<double, double, double>())
        .def("toAEGP", &FloatPoint3::toAEGP)
        .def("ToTuple", &FloatPoint3::ToTuple)
        .def_readwrite("x", &FloatPoint3::x)
        .def_readwrite("y", &FloatPoint3::y)
        .def_readwrite("z", &FloatPoint3::z);
}

inline void bind_float_rect(py::module &m)
{
    py::class_<FloatRect>(m, "FloatRect")
        .def(py::init<>())
        .def(py::init<A_FloatRect>())
        .def(py::init<double, double, double, double>())
        .def("toAEGP", &FloatRect::toAEGP)
        .def("ToTuple", &FloatRect::ToTuple)
        .def_readwrite("left", &FloatRect::left)
        .def_readwrite("top", &FloatRect::top)
        .def_readwrite("right", &FloatRect::right)
        .def_readwrite("bottom", &FloatRect::bottom);
}

inline void bind_matrix3(py::module &m)
{
    py::class_<Matrix3>(m, "Matrix3")
        .def(py::init<>())
        .def(py::init<A_Matrix3>())
        // .def(py::init<tk::vector<tk::vector<double>> &>())
        .def("ToVector", &Matrix3::ToVector);
}

inline void bind_matrix4(py::module &m)
{
    py::class_<Matrix4>(m, "Matrix4")
        .def(py::init<>())
        .def(py::init<A_Matrix4>())
        // .def(py::init<tk::vector<tk::vector<double>> &>())
        .def("ToVector", &Matrix4::ToVector);
}

inline void bind_legacy_rect(py::module &m)
{
    py::class_<LegacyRect>(m, "LegacyRect")
        .def(py::init<>())
        .def(py::init<A_LegacyRect>())
        .def(py::init<int, int, int, int>())
        .def("toAEGP", &LegacyRect::toAEGP)
        .def("ToTuple", &LegacyRect::ToTuple)
        .def_readwrite("top", &LegacyRect::top)
        .def_readwrite("left", &LegacyRect::left)
        .def_readwrite("bottom", &LegacyRect::bottom)
        .def_readwrite("right", &LegacyRect::right);
}

inline void bind_lrect(py::module &m)
{
    py::class_<LRect>(m, "LRect")
        .def(py::init<>())
        .def(py::init<A_LRect>())
        .def(py::init<int, int, int, int>())
        .def("toAEGP", &LRect::toAEGP)
        .def("ToTuple", &LRect::ToTuple)
        .def_readwrite("left", &LRect::left)
        .def_readwrite("top", &LRect::top)
        .def_readwrite("right", &LRect::right)
        .def_readwrite("bottom", &LRect::bottom);
}

inline void bind_lpoint(py::module &m)
{
    py::class_<LPoint>(m, "LPoint")
        .def(py::init<>())
        .def(py::init<A_LPoint>())
        .def(py::init<int, int>())
        .def("toAEGP", &LPoint::toAEGP)
        .def("ToTuple", &LPoint::ToTuple)
        .def_readwrite("x", &LPoint::x)
        .def_readwrite("y", &LPoint::y);
}

inline void bind_float_polar(py::module &m)
{
    py::class_<FloatPolar>(m, "FloatPolar")
        .def(py::init<>())
        .def(py::init<A_FloatPolar>())
        .def(py::init<double, double>())
        .def("toAEGP", &FloatPolar::toAEGP)
        .def("ToTuple", &FloatPolar::ToTuple)
        .def_readwrite("radius", &FloatPolar::radius)
        .def_readwrite("angle", &FloatPolar::angle);
}

inline void bind_marker_val(py::module &m)
{
    py::class_<Marker>(m, "MarkerVal")
        .def(py::init<>())
        .def("createMarker", &Marker::createMarker)
        .def("duplicateMarker", &Marker::duplicateMarker)
        .def("setFlag", &Marker::setFlag)
        .def("getFlag", &Marker::getFlag)
        .def("getString", &Marker::getString)
        .def("setString", &Marker::setString)
        .def("countCuePointParams", &Marker::countCuePointParams)
        .def("getIndCuePointParam", &Marker::getIndCuePointParam)
        .def("setIndCuePointParam", &Marker::setIndCuePointParam)
        .def("insertCuePointParam", &Marker::insertCuePointParam)
        .def("deleteIndCuePointParam", &Marker::deleteIndCuePointParam)
        .def("setDuration", &Marker::setDuration)
        .def("getDuration", &Marker::getDuration)
        .def("setLabel", &Marker::setLabel)
        .def("getLabel", &Marker::getLabel);
}

inline void bind_mask_outline_val(py::module &m)
{
    py::class_<MaskOutline>(m, "MaskOutline")
        .def(py::init<>())
        .def("isOpen", &MaskOutline::isOpen)
        .def("setOpen", &MaskOutline::setOpen)
        .def("numSegments", &MaskOutline::numSegments)
        .def("getVertexInfo", &MaskOutline::getVertexInfo)
        .def("setVertexInfo", &MaskOutline::setVertexInfo)
        .def("createVertex", &MaskOutline::createVertex)
        .def("deleteVertex", &MaskOutline::deleteVertex)
        .def("numFeathers", &MaskOutline::numFeathers)
        .def("getFeatherInfo", &MaskOutline::getFeatherInfo)
        .def("setFeatherInfo", &MaskOutline::setFeatherInfo)
        .def("createFeather", &MaskOutline::createFeather)
        .def("deleteFeather", &MaskOutline::deleteFeather);
}

inline void bind_text_document_val(py::module &m)
{
    py::class_<TextDocument>(m, "TextDocument")
        .def(py::init<>())
        .def("getText", &TextDocument::getText)
        .def("setText", &TextDocument::setText);
}

inline void bind_proj_suite(py::module &m)
{
    py::class_<ProjSuite>(m, "ProjSuite")
        .def(py::init<>())
        .def("GetNumProjects", &ProjSuite::GetNumProjects)
        .def("GetProjectByIndex", &ProjSuite::GetProjectByIndex)
        .def("GetProjectName", &ProjSuite::GetProjectName)
        .def("GetProjectPath", &ProjSuite::GetProjectPath)
        .def("GetProjectRootFolder", &ProjSuite::GetProjectRootFolder)
        .def("SaveProjectToPath", &ProjSuite::SaveProjectToPath)
        .def("GetProjectTimeDisplay", &ProjSuite::GetProjectTimeDisplay)
        .def("SetProjectTimeDisplay", &ProjSuite::SetProjectTimeDisplay)
        .def("ProjectIsDirty", &ProjSuite::ProjectIsDirty)
        .def("SaveProjectAs", &ProjSuite::SaveProjectAs)
        .def("NewProject", &ProjSuite::NewProject)
        .def("OpenProjectFromPath", &ProjSuite::OpenProjectFromPath)
        .def("GetProjectBitDepth", &ProjSuite::GetProjectBitDepth)
        .def("SetProjectBitDepth", &ProjSuite::SetProjectBitDepth);
}

inline void bind_item_suite(py::module &m)
{
    py::class_<ItemSuite>(m, "ItemSuite")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("GetFirstProjItem", &ItemSuite::GetFirstProjItem)
        .def("GetNextProjItem", &ItemSuite::GetNextProjItem)
        .def("GetActiveItem", &ItemSuite::GetActiveItem, py::return_value_policy::reference)
        .def("IsItemSelected", &ItemSuite::IsItemSelected)
        .def("SelectItem", &ItemSuite::SelectItem)
        .def("GetItemType", &ItemSuite::GetItemType)
        .def("GetTypeName", &ItemSuite::GetTypeName)
        .def("GetItemName", &ItemSuite::GetItemName, py::return_value_policy::reference)
        .def("SetItemName", &ItemSuite::SetItemName)
        .def("GetItemID", &ItemSuite::GetItemID)
        .def("GetItemFlags", &ItemSuite::GetItemFlags)
        .def("SetItemUseProxy", &ItemSuite::SetItemUseProxy)
        .def("GetItemParentFolder", &ItemSuite::GetItemParentFolder)
        .def("SetItemParentFolder", &ItemSuite::SetItemParentFolder)
        .def("GetItemDuration", &ItemSuite::GetItemDuration)
        .def("GetItemCurrentTime", &ItemSuite::GetItemCurrentTime)
        .def("GetItemDimensions", &ItemSuite::GetItemDimensions)
        .def("GetItemPixelAspectRatio", &ItemSuite::GetItemPixelAspectRatio)
        .def("DeleteItem", &ItemSuite::DeleteItem)
        .def("CreateNewFolder", &ItemSuite::CreateNewFolder)
        .def("SetItemCurrentTime", &ItemSuite::SetItemCurrentTime)
        .def("GetItemComment", &ItemSuite::GetItemComment)
        .def("SetItemComment", &ItemSuite::SetItemComment)
        .def("GetItemLabel", &ItemSuite::GetItemLabel)
        .def("SetItemLabel", &ItemSuite::SetItemLabel)
        .def("GetItemMRUView", &ItemSuite::GetItemMRUView)
        .def("GetItemViewPlaybackTime", &ItemSuite::GetItemViewPlaybackTime);
}

inline void bind_comp_suite(py::module &m)
{
    py::class_<CompSuite>(m, "CompSuite")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("GetCompFromItem", &CompSuite::GetCompFromItem, py::return_value_policy::reference)
        .def("GetItemFromComp", &CompSuite::GetItemFromComp, py::return_value_policy::reference)
        .def("GetCompDownsampleFactor", &CompSuite::GetCompDownsampleFactor)
        .def("SetCompDownsampleFactor", &CompSuite::SetCompDownsampleFactor)
        .def("GetCompBGColor", &CompSuite::GetCompBGColor)
        .def("SetCompBGColor", &CompSuite::SetCompBGColor)
        .def("GetCompFlags", &CompSuite::GetCompFlags)
        .def("GetShowLayerNameOrSourceName", &CompSuite::GetShowLayerNameOrSourceName)
        .def("SetShowLayerNameOrSourceName", &CompSuite::SetShowLayerNameOrSourceName)
        .def("GetShowBlendModes", &CompSuite::GetShowBlendModes)
        .def("SetShowBlendModes", &CompSuite::SetShowBlendModes)
        .def("GetCompFramerate", &CompSuite::GetCompFramerate)
        .def("SetCompFrameRate", &CompSuite::SetCompFrameRate)
        .def("GetCompShutterAnglePhase", &CompSuite::GetCompShutterAnglePhase)
        .def("GetCompShutterFrameRange", &CompSuite::GetCompShutterFrameRange)
        .def("GetCompSuggestedMotionBlurSamples", &CompSuite::GetCompSuggestedMotionBlurSamples)
        .def("SetCompSuggestedMotionBlurSamples", &CompSuite::SetCompSuggestedMotionBlurSamples)
        .def("GetCompMotionBlurAdaptiveSampleLimit", &CompSuite::GetCompMotionBlurAdaptiveSampleLimit)
        .def("SetCompMotionBlurAdaptiveSampleLimit", &CompSuite::SetCompMotionBlurAdaptiveSampleLimit)
        .def("GetCompWorkAreaStart", &CompSuite::GetCompWorkAreaStart)
        .def("GetCompWorkAreaDuration", &CompSuite::GetCompWorkAreaDuration)
        .def("SetCompWorkAreaStartAndDuration", &CompSuite::SetCompWorkAreaStartAndDuration)
        .def("CreateSolidInComp", &CompSuite::CreateSolidInComp)
        .def("CreateCameraInComp", &CompSuite::CreateCameraInComp)
        .def("CreateLightInComp", &CompSuite::CreateLightInComp)
        .def("CreateComp", &CompSuite::CreateComp)
        .def("GetNewCollectionFromCompSelection", &CompSuite::GetNewCollectionFromCompSelection)
        .def("GetCompDisplayStartTime", &CompSuite::GetCompDisplayStartTime)
        .def("SetCompDisplayStartTime", &CompSuite::SetCompDisplayStartTime)
        .def("SetCompDuration", &CompSuite::SetCompDuration)
        .def("SetCompDimensions", &CompSuite::SetCompDimensions)
        .def("SetCompPixelAspectRatio", &CompSuite::SetCompPixelAspectRatio)
        .def("CreateTextLayerInComp", &CompSuite::CreateTextLayerInComp)
        .def("CreateBoxTextLayerInComp", &CompSuite::CreateBoxTextLayerInComp)
        .def("CreateNullInComp", &CompSuite::CreateNullInComp)
        .def("SetCompDisplayDropFrame", &CompSuite::SetCompDisplayDropFrame)
        .def("ReorderCompSelection", &CompSuite::ReorderCompSelection);
}

inline void bind_layer_suite(py::module &m)
{
    py::class_<LayerSuite>(m, "LayerSuite")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("GetCompNumLayers", &LayerSuite::GetCompNumLayers)
        .def("GetCompLayerByIndex", &LayerSuite::GetCompLayerByIndex, py::return_value_policy::reference)
        .def("GetActiveLayer", &LayerSuite::GetActiveLayer)
        .def("GetLayerIndex", &LayerSuite::GetLayerIndex)
        .def("GetLayerSourceItem", &LayerSuite::GetLayerSourceItem, py::return_value_policy::reference)
        .def("GetLayerSourceItemID", &LayerSuite::GetLayerSourceItemID)
        .def("GetLayerParentComp", &LayerSuite::GetLayerParentComp, py::return_value_policy::reference)
        .def("GetLayerName", &LayerSuite::GetLayerName)
        .def("GetLayerQuality", &LayerSuite::GetLayerQuality)
        .def("SetLayerQuality", &LayerSuite::SetLayerQuality)
        .def("GetLayerFlags", &LayerSuite::GetLayerFlags)
        .def("SetLayerFlag", &LayerSuite::SetLayerFlag)
        .def("IsLayerVideoReallyOn", &LayerSuite::IsLayerVideoReallyOn)
        .def("IsLayerAudioReallyOn", &LayerSuite::IsLayerAudioReallyOn)
        .def("GetLayerCurrentTime", &LayerSuite::GetLayerCurrentTime)
        .def("GetLayerInPoint", &LayerSuite::GetLayerInPoint)
        .def("GetLayerDuration", &LayerSuite::GetLayerDuration)
        .def("SetLayerInPointAndDuration", &LayerSuite::SetLayerInPointAndDuration)
        .def("GetLayerOffset", &LayerSuite::GetLayerOffset)
        .def("SetLayerOffset", &LayerSuite::SetLayerOffset)
        .def("GetLayerStretch", &LayerSuite::GetLayerStretch)
        .def("SetLayerStretch", &LayerSuite::SetLayerStretch)
        .def("GetLayerTransferMode", &LayerSuite::GetLayerTransferMode)
        .def("SetLayerTransferMode", &LayerSuite::SetLayerTransferMode)
        .def("IsAddLayerValid", &LayerSuite::IsAddLayerValid)
        .def("AddLayer", &LayerSuite::AddLayer)
        .def("ReorderLayer", &LayerSuite::ReorderLayer)
        .def("GetLayerMaskedBounds", &LayerSuite::GetLayerMaskedBounds)
        .def("GetLayerObjectType", &LayerSuite::GetLayerObjectType)
        .def("IsLayer3D", &LayerSuite::IsLayer3D)
        .def("IsLayer2D", &LayerSuite::IsLayer2D)
        .def("IsVideoActive", &LayerSuite::IsVideoActive)
        .def("IsLayerUsedAsTrackMatte", &LayerSuite::IsLayerUsedAsTrackMatte)
        .def("DoesLayerHaveTrackMatte", &LayerSuite::DoesLayerHaveTrackMatte)
        .def("ConvertCompToLayerTime", &LayerSuite::ConvertCompToLayerTime)
        .def("ConvertLayerToCompTime", &LayerSuite::ConvertLayerToCompTime)
        .def("GetLayerDancingRandValue", &LayerSuite::GetLayerDancingRandValue)
        .def("GetLayerID", &LayerSuite::GetLayerID)
        //.def("GetLayerToWorldXform", &LayerSuite::GetLayerToWorldXform)
        //.def("GetLayerToWorldXformFromView", &LayerSuite::GetLayerToWorldXformFromView)
        .def("SetLayerName", &LayerSuite::SetLayerName)
        .def("GetLayerParent", &LayerSuite::GetLayerParent)
        .def("SetLayerParent", &LayerSuite::SetLayerParent)
        .def("DeleteLayer", &LayerSuite::DeleteLayer)
        .def("DuplicateLayer", &LayerSuite::DuplicateLayer)
        .def("GetLayerFromLayerID", &LayerSuite::GetLayerFromLayerID)
        .def("GetLayerLabel", &LayerSuite::GetLayerLabel)
        .def("SetLayerLabel", &LayerSuite::SetLayerLabel)
        .def("GetLayerSamplingQuality", &LayerSuite::GetLayerSamplingQuality)
        .def("SetLayerSamplingQuality", &LayerSuite::SetLayerSamplingQuality)
        .def("GetTrackMatteLayer", &LayerSuite::GetTrackMatteLayer)
        .def("SetTrackMatte", &LayerSuite::SetTrackMatte)
        .def("RemoveTrackMatte", &LayerSuite::RemoveTrackMatte);
}

inline void bind_stream_suite(py::module &m)
{
    py::class_<StreamSuite>(m, "StreamSuite")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("IsStreamLegal", &StreamSuite::IsStreamLegal)
        .def("CanVaryOverTime", &StreamSuite::CanVaryOverTime)
        .def("GetValidInterpolations", &StreamSuite::GetValidInterpolations)
        .def("GetNewLayerStream", &StreamSuite::GetNewLayerStream)
        .def("GetEffectNumParamStreams", &StreamSuite::GetEffectNumParamStreams)
        .def("GetNewEffectStreamByIndex", &StreamSuite::GetNewEffectStreamByIndex)
        .def("GetNewMaskStream", &StreamSuite::GetNewMaskStream)
        .def("GetStreamName", &StreamSuite::GetStreamName)
        .def("GetStreamUnitsText", &StreamSuite::GetStreamUnitsText)
        .def("GetStreamProperties", &StreamSuite::GetStreamProperties)
        .def("IsStreamTimevarying", &StreamSuite::IsStreamTimevarying)
        .def("GetStreamType", &StreamSuite::GetStreamType, py::return_value_policy::reference)
        .def("GetNewStreamValue", &StreamSuite::GetNewStreamValue, py::return_value_policy::reference)
        .def("SetStreamValue", &StreamSuite::SetStreamValue)
        .def("GetLayerStreamValue", &StreamSuite::GetLayerStreamValue, py::return_value_policy::reference)
        .def("DuplicateStreamRef", &StreamSuite::DuplicateStreamRef)
        .def("GetUniqueStreamID", &StreamSuite::GetUniqueStreamID);
}

inline void bind_dynamic_stream_suite(py::module &m)
{
    py::class_<DynamicStreamSuite>(m, "DynamicStreamSuite")
        .def(py::init<>(), py::return_value_policy::reference)
        .def("GetNewStreamRefForLayer", &DynamicStreamSuite::GetNewStreamRefForLayer,
             py::return_value_policy::reference)
        .def("GetNewStreamRefForMask", &DynamicStreamSuite::GetNewStreamRefForMask)
        .def("GetStreamDepth", &DynamicStreamSuite::GetStreamDepth)
        .def("GetStreamGroupingType", &DynamicStreamSuite::GetStreamGroupingType, py::return_value_policy::reference)
        .def("GetNumStreamsInGroup", &DynamicStreamSuite::GetNumStreamsInGroup)
        .def("GetDynamicStreamFlags", &DynamicStreamSuite::GetDynamicStreamFlags)
        .def("SetDynamicStreamFlag", &DynamicStreamSuite::SetDynamicStreamFlag)
        .def("GetNewStreamRefByIndex", &DynamicStreamSuite::GetNewStreamRefByIndex)
        .def("GetNewStreamRefByMatchname", &DynamicStreamSuite::GetNewStreamRefByMatchname)
        .def("DeleteStream", &DynamicStreamSuite::DeleteStream)
        .def("ReorderStream", &DynamicStreamSuite::ReorderStream)
        .def("DuplicateStream", &DynamicStreamSuite::DuplicateStream)
        .def("SetStreamName", &DynamicStreamSuite::SetStreamName)
        .def("CanAddStream", &DynamicStreamSuite::CanAddStream)
        .def("AddStream", &DynamicStreamSuite::AddStream)
        .def("GetMatchname", &DynamicStreamSuite::GetMatchname)
        .def("GetNewParentStreamRef", &DynamicStreamSuite::GetNewParentStreamRef)
        .def("GetStreamIsModified", &DynamicStreamSuite::GetStreamIsModified)
        .def("IsSeparationLeader", &DynamicStreamSuite::IsSeparationLeader)
        .def("AreDimensionsSeparated", &DynamicStreamSuite::AreDimensionsSeparated)
        .def("SetDimensionsSeparated", &DynamicStreamSuite::SetDimensionsSeparated)
        .def("GetSeparationFollower", &DynamicStreamSuite::GetSeparationFollower)
        .def("IsSeparationFollower", &DynamicStreamSuite::IsSeparationFollower)
        .def("GetSeparationLeader", &DynamicStreamSuite::GetSeparationLeader)
        .def("GetSeparationDimension", &DynamicStreamSuite::GetSeparationDimension);
}

inline void bind_keyframe_suite(py::module &m)
{
    py::class_<KeyframeSuite>(m, "KeyframeSuite")
        .def(py::init<>())
        .def("GetStreamNumKFs", &KeyframeSuite::GetStreamNumKFs)
        .def("GetKeyframeTime", &KeyframeSuite::GetKeyframeTime)
        .def("InsertKeyframe", &KeyframeSuite::InsertKeyframe)
        .def("DeleteKeyframe", &KeyframeSuite::DeleteKeyframe)
        .def("GetNewKeyframeValue", &KeyframeSuite::GetNewKeyframeValue)
        .def("SetKeyframeValue", &KeyframeSuite::SetKeyframeValue)
        .def("GetStreamValueDimensionality", &KeyframeSuite::GetStreamValueDimensionality)
        .def("GetStreamTemporalDimensionality", &KeyframeSuite::GetStreamTemporalDimensionality)
        .def("GetNewKeyframeSpatialTangents", &KeyframeSuite::GetNewKeyframeSpatialTangents)
        .def("SetKeyframeSpatialTangents", &KeyframeSuite::SetKeyframeSpatialTangents)
        .def("GetKeyframeTemporalEase", &KeyframeSuite::GetKeyframeTemporalEase)
        .def("SetKeyframeTemporalEase", &KeyframeSuite::SetKeyframeTemporalEase)
        .def("GetKeyframeFlags", &KeyframeSuite::GetKeyframeFlags)
        .def("SetKeyframeFlag", &KeyframeSuite::SetKeyframeFlag)
        .def("GetKeyframeInterpolation", &KeyframeSuite::GetKeyframeInterpolation)
        .def("SetKeyframeInterpolation", &KeyframeSuite::SetKeyframeInterpolation)
        .def("StartAddKeyframes", &KeyframeSuite::StartAddKeyframes)
        .def("AddKeyframes", &KeyframeSuite::AddKeyframes)
        .def("SetAddKeyframe", &KeyframeSuite::SetAddKeyframe)
        .def("EndAddKeyframes", &KeyframeSuite::EndAddKeyframes)
        .def("GetKeyframeLabelColorIndex", &KeyframeSuite::GetKeyframeLabelColorIndex)
        .def("SetKeyframeLabelColorIndex", &KeyframeSuite::SetKeyframeLabelColorIndex);
}

inline void bind_text_document_suite(py::module &m)
{
    py::class_<TextDocumentSuite>(m, "TextDocumentSuite")
        .def(py::init<>())
        .def("getNewText", &TextDocumentSuite::getNewText)
        .def("setText", &TextDocumentSuite::setText);
}

inline void bind_marker_suite(py::module &m)
{
    py::class_<MarkerSuite>(m, "MarkerSuite")
        .def(py::init<>())
        .def("getNewMarker", &MarkerSuite::getNewMarker)
        .def("duplicateMarker", &MarkerSuite::duplicateMarker)
        .def("setMarkerFlag", &MarkerSuite::setMarkerFlag)
        .def("getMarkerFlag", &MarkerSuite::getMarkerFlag)
        .def("getMarkerString", &MarkerSuite::getMarkerString)
        .def("setMarkerString", &MarkerSuite::setMarkerString)
        .def("countCuePointParams", &MarkerSuite::countCuePointParams)
        .def("getIndCuePointParam", &MarkerSuite::getIndCuePointParam)
        .def("setIndCuePointParam", &MarkerSuite::setIndCuePointParam)
        .def("insertCuePointParam", &MarkerSuite::insertCuePointParam)
        .def("deleteIndCuePointParam", &MarkerSuite::deleteIndCuePointParam)
        .def("setMarkerDuration", &MarkerSuite::setMarkerDuration)
        .def("getMarkerDuration", &MarkerSuite::getMarkerDuration)
        .def("setMarkerLabel", &MarkerSuite::setMarkerLabel)
        .def("getMarkerLabel", &MarkerSuite::getMarkerLabel);
}

inline void bind_text_layer_suite(py::module &m)
{
    py::class_<TextLayerSuite>(m, "TextLayerSuite")
        .def(py::init<>())
        .def("getNewTextOutlines", &TextLayerSuite::getNewTextOutlines)
        .def("getNumTextOutlines", &TextLayerSuite::getNumTextOutlines);
    //.def("getIndexedTextOutline", &TextLayerSuite::getIndexedTextOutline);
}

inline void bind_effect_suite(py::module &m)
{
    py::class_<EffectSuite>(m, "EffectSuite")
        .def(py::init<>())
        .def("getLayerNumEffects", &EffectSuite::getLayerNumEffects)
        .def("getLayerEffectByIndex", &EffectSuite::getLayerEffectByIndex)
        .def("getInstalledKeyFromLayerEffect", &EffectSuite::getInstalledKeyFromLayerEffect)
        .def("getEffectParamUnionByIndex", &EffectSuite::getEffectParamUnionByIndex)
        .def("getEffectFlags", &EffectSuite::getEffectFlags)
        .def("setEffectFlags", &EffectSuite::setEffectFlags)
        .def("reorderEffect", &EffectSuite::reorderEffect)
        .def("effectCallGeneric", &EffectSuite::effectCallGeneric)
        .def("applyEffect", &EffectSuite::applyEffect)
        .def("deleteLayerEffect", &EffectSuite::deleteLayerEffect)
        .def("getNumInstalledEffects", &EffectSuite::getNumInstalledEffects)
        .def("getNextInstalledEffect", &EffectSuite::getNextInstalledEffect)
        .def("getEffectName", &EffectSuite::getEffectName)
        .def("getEffectMatchName", &EffectSuite::getEffectMatchName)
        .def("getEffectCategory", &EffectSuite::getEffectCategory)
        .def("duplicateEffect", &EffectSuite::duplicateEffect)
        .def("numEffectMask", &EffectSuite::numEffectMask)
        .def("getEffectMaskID", &EffectSuite::getEffectMaskID)
        .def("addEffectMask", &EffectSuite::addEffectMask)
        .def("removeEffectMask", &EffectSuite::removeEffectMask)
        .def("setEffectMask", &EffectSuite::setEffectMask);
}

inline void bind_mask_suite(py::module &m)
{
    py::class_<MaskSuite>(m, "MaskSuite")
        .def(py::init<>())
        .def("getLayerNumMasks", &MaskSuite::getLayerNumMasks)
        .def("getLayerMaskByIndex", &MaskSuite::getLayerMaskByIndex)
        .def("getMaskInvert", &MaskSuite::getMaskInvert)
        .def("setMaskInvert", &MaskSuite::setMaskInvert)
        .def("getMaskMode", &MaskSuite::getMaskMode)
        .def("setMaskMode", &MaskSuite::setMaskMode)
        .def("getMaskMotionBlurState", &MaskSuite::getMaskMotionBlurState)
        .def("setMaskMotionBlurState", &MaskSuite::setMaskMotionBlurState)
        .def("getMaskFeatherFalloff", &MaskSuite::getMaskFeatherFalloff)
        .def("setMaskFeatherFalloff", &MaskSuite::setMaskFeatherFalloff)
        .def("getMaskID", &MaskSuite::getMaskID)
        .def("createNewMask", &MaskSuite::createNewMask)
        .def("deleteMaskFromLayer", &MaskSuite::deleteMaskFromLayer)
        .def("getMaskColor", &MaskSuite::getMaskColor)
        .def("setMaskColor", &MaskSuite::setMaskColor)
        .def("getMaskLockState", &MaskSuite::getMaskLockState)
        .def("setMaskLockState", &MaskSuite::setMaskLockState)
        .def("getMaskIsRotoBezier", &MaskSuite::getMaskIsRotoBezier)
        .def("setMaskIsRotoBezier", &MaskSuite::setMaskIsRotoBezier)
        .def("duplicateMask", &MaskSuite::duplicateMask);
}

inline void bind_mask_outline_suite(py::module &m)
{
    py::class_<MaskOutlineSuite>(m, "MaskOutlineSuite")
        .def(py::init<>())
        .def("isMaskOutlineOpen", &MaskOutlineSuite::isMaskOutlineOpen)
        .def("setMaskOutlineOpen", &MaskOutlineSuite::setMaskOutlineOpen)
        .def("getMaskOutlineNumSegments", &MaskOutlineSuite::getMaskOutlineNumSegments)
        .def("getMaskOutlineVertexInfo", &MaskOutlineSuite::getMaskOutlineVertexInfo)
        .def("setMaskOutlineVertexInfo", &MaskOutlineSuite::setMaskOutlineVertexInfo)
        .def("createVertex", &MaskOutlineSuite::createVertex)
        .def("deleteVertex", &MaskOutlineSuite::deleteVertex)
        .def("getMaskOutlineNumFeathers", &MaskOutlineSuite::getMaskOutlineNumFeathers)
        .def("getMaskOutlineFeatherInfo", &MaskOutlineSuite::getMaskOutlineFeatherInfo)
        .def("setMaskOutlineFeatherInfo", &MaskOutlineSuite::setMaskOutlineFeatherInfo)
        .def("createMaskOutlineFeather", &MaskOutlineSuite::createMaskOutlineFeather)
        .def("deleteMaskOutlineFeather", &MaskOutlineSuite::deleteMaskOutlineFeather);
}

inline void bind_footage_suite(py::module &m)
{
    py::class_<FootageSuite>(m, "FootageSuite")
        .def(py::init<>())
        .def("getMainFootageFromItem", &FootageSuite::getMainFootageFromItem)
        .def("getProxyFootageFromItem", &FootageSuite::getProxyFootageFromItem)
        .def("getFootageNumFiles", &FootageSuite::getFootageNumFiles)
        .def("getFootagePath", &FootageSuite::getFootagePath)
        .def("getFootageSignature", &FootageSuite::getFootageSignature)
        .def("newFootage", &FootageSuite::newFootage)
        .def("addFootageToProject", &FootageSuite::addFootageToProject)
        .def("setItemProxyFootage", &FootageSuite::setItemProxyFootage)
        .def("replaceItemMainFootage", &FootageSuite::replaceItemMainFootage)
        .def("getFootageInterpretation", &FootageSuite::getFootageInterpretation)
        .def("setFootageInterpretation", &FootageSuite::setFootageInterpretation)
        .def("getFootageLayerKey", &FootageSuite::getFootageLayerKey)
        .def("newPlaceholderFootage", &FootageSuite::newPlaceholderFootage)
        .def("newPlaceholderFootageWithPath", &FootageSuite::newPlaceholderFootageWithPath)
        .def("newSolidFootage", &FootageSuite::newSolidFootage)
        .def("getSolidFootageColor", &FootageSuite::getSolidFootageColor)
        .def("setSolidFootageColor", &FootageSuite::setSolidFootageColor)
        .def("setSolidFootageDimensions", &FootageSuite::setSolidFootageDimensions)
        //.def("getFootageSoundDataFormat", &FootageSuite::getFootageSoundDataFormat)
        .def("getFootageSequenceImportOptions", &FootageSuite::getFootageSequenceImportOptions);
}

inline void bind_utility_suite(py::module &m)
{
    py::class_<UtilitySuite>(m, "UtilitySuite")
        .def(py::init<>(), py::return_value_policy::copy)
        .def("reportInfo", &UtilitySuite::reportInfo, py::return_value_policy::copy)
        .def("reportInfoUnicode", &UtilitySuite::reportInfoUnicode)
        .def("getDriverPluginInitFuncVersion", &UtilitySuite::getDriverPluginInitFuncVersion)
        .def("getDriverImplementationVersion", &UtilitySuite::getDriverImplementationVersion)
        .def("startQuietErrors", &UtilitySuite::startQuietErrors)
        .def("endQuietErrors", &UtilitySuite::endQuietErrors)
        .def("getLastErrorMessage", &UtilitySuite::getLastErrorMessage)
        .def("startUndoGroup", &UtilitySuite::startUndoGroup)
        .def("endUndoGroup", &UtilitySuite::endUndoGroup)
        .def("getMainHWND", &UtilitySuite::getMainHWND)
        .def("showHideAllFloaters", &UtilitySuite::showHideAllFloaters)
        .def("getPaintPalForeColor", &UtilitySuite::getPaintPalForeColor)
        .def("getPaintPalBackColor", &UtilitySuite::getPaintPalBackColor)
        .def("setPaintPalForeColor", &UtilitySuite::setPaintPalForeColor)
        .def("setPaintPalBackColor", &UtilitySuite::setPaintPalBackColor)
        .def("getCharPalFillColor", &UtilitySuite::getCharPalFillColor)
        .def("getCharPalStrokeColor", &UtilitySuite::getCharPalStrokeColor)
        .def("setCharPalFillColor", &UtilitySuite::setCharPalFillColor)
        .def("setCharPalStrokeColor", &UtilitySuite::setCharPalStrokeColor)
        .def("charPalIsFillColorUIFrontmost", &UtilitySuite::charPalIsFillColorUIFrontmost)
        .def("convertFpLongToHSFRatio", &UtilitySuite::convertFpLongToHSFRatio)
        .def("convertHSFRatioToFpLong", &UtilitySuite::convertHSFRatioToFpLong)
        .def("causeIdleRoutinesToBeCalled", &UtilitySuite::causeIdleRoutinesToBeCalled)
        .def("getSuppressInteractiveUI", &UtilitySuite::getSuppressInteractiveUI)
        .def("writeToOSConsole", &UtilitySuite::writeToOSConsole)
        .def("writeToDebugLog", &UtilitySuite::writeToDebugLog)
        .def("getPluginPath", &UtilitySuite::getPluginPath);
}

inline void bind_render_queue_suite(py::module &m)
{
    py::class_<RenderQueueSuite>(m, "RenderQueueSuite")
        .def(py::init<>())
        .def("addCompToRenderQueue", &RenderQueueSuite::addCompToRenderQueue)
        .def("setRenderQueueState", &RenderQueueSuite::setRenderQueueState)
        .def("getRenderQueueState", &RenderQueueSuite::getRenderQueueState);
}

inline void bind_render_queue_item_suite(py::module &m)
{
    py::class_<RenderQueueItemSuite>(m, "RenderQueueItemSuite")
        .def(py::init<>())
        .def("getNumRQItems", &RenderQueueItemSuite::getNumRQItems)
        .def("getRQItemByIndex", &RenderQueueItemSuite::getRQItemByIndex)
        .def("getNextRQItem", &RenderQueueItemSuite::getNextRQItem)
        .def("getNumOutputModulesForRQItem", &RenderQueueItemSuite::getNumOutputModulesForRQItem)
        .def("getRenderState", &RenderQueueItemSuite::getRenderState)
        .def("setRenderState", &RenderQueueItemSuite::setRenderState)
        .def("getStartedTime", &RenderQueueItemSuite::getStartedTime)
        .def("getElapsedTime", &RenderQueueItemSuite::getElapsedTime)
        .def("getLogType", &RenderQueueItemSuite::getLogType)
        .def("setLogType", &RenderQueueItemSuite::setLogType)
        .def("removeOutputModule", &RenderQueueItemSuite::removeOutputModule)
        .def("getComment", &RenderQueueItemSuite::getComment)
        .def("setComment", &RenderQueueItemSuite::setComment)
        .def("getCompFromRQItem", &RenderQueueItemSuite::getCompFromRQItem)
        .def("deleteRQItem", &RenderQueueItemSuite::deleteRQItem);
}

inline void bind_output_module_suite(py::module &m)
{
    py::class_<OutputModuleSuite>(m, "OutputModuleSuite")
        .def(py::init<>())
        .def("getOutputModuleByIndex", &OutputModuleSuite::getOutputModuleByIndex)
        .def("getEmbedOptions", &OutputModuleSuite::getEmbedOptions)
        .def("setEmbedOptions", &OutputModuleSuite::setEmbedOptions)
        .def("getPostRenderAction", &OutputModuleSuite::getPostRenderAction)
        .def("setPostRenderAction", &OutputModuleSuite::setPostRenderAction)
        .def("getEnabledOutputs", &OutputModuleSuite::getEnabledOutputs)
        .def("setEnabledOutputs", &OutputModuleSuite::setEnabledOutputs)
        .def("getOutputChannels", &OutputModuleSuite::getOutputChannels)
        .def("setOutputChannels", &OutputModuleSuite::setOutputChannels)
        .def("getStretchInfo", &OutputModuleSuite::getStretchInfo)
        .def("setStretchInfo", &OutputModuleSuite::setStretchInfo)
        .def("getCropInfo", &OutputModuleSuite::getCropInfo)
        .def("setCropInfo", &OutputModuleSuite::setCropInfo)
        .def("getSoundFormatInfo", &OutputModuleSuite::getSoundFormatInfo)
        .def("setSoundFormatInfo", &OutputModuleSuite::setSoundFormatInfo)
        .def("getOutputFilePath", &OutputModuleSuite::getOutputFilePath)
        .def("setOutputFilePath", &OutputModuleSuite::setOutputFilePath)
        .def("addDefaultOutputModule", &OutputModuleSuite::addDefaultOutputModule)
        .def("getExtraOutputModuleInfo", &OutputModuleSuite::getExtraOutputModuleInfo);
}

PYBIND11_EMBEDDED_MODULE(PyFx, m)
{
    m.doc() = "Python bindings for After Effects SDK";

    bind_handle_wrapper<AEGP_ProjectH>(m, "ProjectPtr");
    bind_handle_wrapper<AEGP_ItemH>(m, "ItemPtr");
    bind_handle_wrapper<AEGP_CompH>(m, "CompPtr");
    bind_handle_wrapper<AEGP_FootageH>(m, "FootagePtr");
    bind_handle_wrapper<AEGP_LayerH>(m, "LayerPtr");
    bind_handle_wrapper<AEGP_EffectRefH>(m, "EffectRefPtr");
    bind_handle_wrapper<AEGP_MaskRefH>(m, "MaskRefPtr");
    bind_handle_wrapper<AEGP_StreamRefH>(m, "StreamRefPtr");
    bind_handle_wrapper<AEGP_RenderLayerContextH>(m, "RenderLayerContextPtr");
    bind_handle_wrapper<AEGP_PersistentBlobH>(m, "PersistentBlobPtr");
    bind_handle_wrapper<AEGP_MaskOutlineValH>(m, "MaskOutlineValPtr");
    bind_handle_wrapper<AEGP_CollectionH>(m, "CollectionPtr");
    bind_handle_wrapper<AEGP_Collection2H>(m, "Collection2Ptr");
    // bind_handle_wrapper<SoundDataH>(m, "SoundDataPtr");
    bind_handle_wrapper<AEGP_AddKeyframesInfoH>(m, "AddKeyframesInfoPtr");
    bind_handle_wrapper<AEGP_RenderReceiptH>(m, "RenderReceiptPtr");
    bind_handle_wrapper<AEGP_WorldH>(m, "WorldPtr");
    bind_handle_wrapper<AEGP_RenderOptionsH>(m, "RenderOptionsPtr");
    bind_handle_wrapper<AEGP_LayerRenderOptionsH>(m, "LayerRenderOptionsPtr");
    bind_handle_wrapper<AEGP_FrameReceiptH>(m, "FrameReceiptPtr");
    bind_handle_wrapper<AEGP_RQItemRefH>(m, "RQItemRefPtr");
    bind_handle_wrapper<AEGP_OutputModuleRefH>(m, "OutputModuleRefPtr");
    bind_handle_wrapper<AEGP_TextDocumentH>(m, "TextDocumentPtr");
    bind_handle_wrapper<AEGP_MarkerValP>(m, "MarkerValPtr");
    bind_handle_wrapper<AEGP_TextOutlinesH>(m, "TextOutlinesPtr");
    bind_handle_wrapper<AEGP_PlatformWorldH>(m, "PlatformWorldPtr");
    bind_handle_wrapper<AEGP_ItemViewP>(m, "ItemViewPtr");
    // bind_handle_wrapper<ColorProfileP>(m, "ColorProfilePtr");
    // bind_handle_wrapper<ConstColorProfileP>(m, "ConstColorProfilePtr");
    // bind_handle_wrapper<TimeStamp>(m, "TimeStampPtr");
    // bind_handle_wrapper<MemHandle>(m, "MemHandlePtr");
    bindStreamValue2(m);
    bind_color_val(m);
    bind_mem_flag(m);
    bind_platform(m);
    bind_proj_bit_depth(m);
    bind_camera_type(m);
    bind_time_display_type(m);
    bind_film_size_units(m);
    bind_light_type(m);
    bind_footage_signature(m);
    bind_light_falloff_type(m);
    bind_footage_depth(m);
    bind_frames_per_foot(m);
    bind_time_display_mode(m);
    bind_source_timecode_display_mode(m);
    bind_frames_display_mode(m);
    bind_sound_encoding(m);
    bind_item_type(m);
    bind_item_flag(m);
    bind_label(m);
    bind_persistent_type(m);
    bind_comp_flag(m);
    bind_transfer_flags(m);
    bind_track_matte(m);
    bind_layer_qual(m);
    bind_layer_sampling_qual(m);
    bind_layer_flag(m);
    bind_object_type(m);
    bind_ltime_mode(m);
    bind_layer_stream(m);
    bind_mask_stream(m);
    bind_stream_flag(m);
    bind_key_interp(m);
    bind_key_interp_mask(m);
    bind_stream_type(m);
    bind_stream_grouping_type(m);
    bind_dyn_stream_flag(m);
    bind_keyframe_flag(m);
    bind_marker_string_type(m);
    bind_marker_flag(m);
    bind_effect_flags(m);
    bind_mask_mode(m);
    bind_mask_mblur(m);
    bind_mask_feather_falloff(m);
    bind_mask_feather_interp(m);
    bind_mask_feather_type(m);
    bind_alpha_flags(m);
    bind_pulldown_phase(m);
    bind_layer_draw_style(m);
    bind_interpretation_style(m);
    bind_plugin_path_type(m);
    bind_render_queue_state(m);
    bind_render_item_status(m);
    bind_log_type(m);
    bind_embedding_type(m);
    bind_post_render_action(m);
    bind_output_types(m);
    bind_video_channels(m);
    bind_stretch_quality(m);
    bind_output_color_type(m);
    bind_world_type(m);
    bind_matte_mode(m);
    bind_channel_order(m);
    bind_item_quality(m);
    bind_collection_item_type(m);
    bind_stream_collection_item_type(m);
    bind_window_type(m);
    bind_menu_id(m);
    // bind_color_val(m);
    bind_sound_data_format(m);
    bind_downsample_factor(m);
    bind_layer_transfer_mode(m);
    bind_one_d_val(m);
    bind_two_d_val(m);
    bind_three_d_val(m);
    bind_keyframe_ease(m);
    bind_mask_feather(m);
    bind_mask_vertex(m);
    bind_loop_behavior(m);
    bind_footage_layer_key(m);
    bind_file_sequence_import_options(m);
    bind_time(m);
    bind_ratio(m);
    bind_float_point(m);
    bind_float_rect(m);
    bind_legacy_rect(m);
    bind_lrect(m);
    bind_lpoint(m);
    bind_float_polar(m);
    bind_marker_val(m);
    bind_mask_outline_val(m);
    bind_text_document_val(m);
    bind_proj_suite(m);
    bind_item_suite(m);
    // bind_sound_data_suite(m);
    bind_comp_suite(m);
    bind_layer_suite(m);
    bind_stream_suite(m);
    bind_dynamic_stream_suite(m);
    bind_keyframe_suite(m);
    bind_text_document_suite(m);
    bind_marker_suite(m);
    bind_text_layer_suite(m);
    bind_effect_suite(m);
    bind_mask_suite(m);
    bind_mask_outline_suite(m);
    bind_footage_suite(m);
    bind_utility_suite(m);
    bind_render_queue_suite(m);
    bind_render_queue_item_suite(m);
    bind_output_module_suite(m);
    // bind_matrix3(m);
    // bind_matrix4(m);
}

#endif // PYFX_HPP
