/*****************************************************************/ /**
                                                                     * \file   Suites.hpp
                                                                     * \brief  Header file for the Suites class
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef SUITES_HPP
#define SUITES_HPP

#include "AETK/AEGP/Core/Enums.hpp"
#include "AETK/AEGP/Core/Types.hpp"
#include "AETK/AEGP/Core/Utility.hpp"
#include "AETK/AEGP/Util/TaskScheduler.hpp"

/**
 * @brief AE Memory Suite
 *
 * @details The Memory Suite provides access to the After Effects memory
 * management.
 *
 */
class MemorySuite
{
  public:
    MemorySuite(){};

    MemHandlePtr NewMemHandle(const std::string &what, AEGP_MemSize size, MemFlag flags); /* New Mem Handle.*/
    void FreeMemHandle(MemHandlePtr memHandle);                                           /* Free Mem Handle.*/
    void LockMemHandle(MemHandlePtr memHandle, void **ptrToPtr);                          /* Lock Mem Handle.*/
    void UnlockMemHandle(MemHandlePtr memHandle);                                         /* Unlock Mem Handle.*/
    AEGP_MemSize GetMemHandleSize(MemHandlePtr memHandle);                                /* Get Mem Handle Size.*/
    void ResizeMemHandle(const std::string &what, AEGP_MemSize newSize, MemHandlePtr memHandle); /* Resize Mem Handle.*/
    void SetMemReportingOn(bool turnOn); /* Set Mem Reporting On.*/
    std::tuple<int, int> GetMemStats();  /* Get Mem Stats.*/
};

/**
 * @brief Macro to check if an expression returns an error and throw an
 * AEException with the error message.
 */
#define AE_CHECK(expr)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        A_Err err = (expr);                                                                                            \
        if (err != A_Err_NONE)                                                                                         \
        {                                                                                                              \
            std::string errorMessage = GetErrorMessage(err);                                                           \
            throw AEException(errorMessage.c_str());                                                                   \
        }                                                                                                              \
    } while (0)

/**
 * \brief Convert a UTF-8 string to a UTF-16 string.
 *
 * \param utf16String
 * \return
 */
inline std::string ConvertUTF16ToUTF8(const A_UTF16Char *utf16String)
{
    icu::UnicodeString unicodeString(reinterpret_cast<const UChar *>(utf16String));
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
inline std::vector<UChar> ConvertUTF8ToUTF16UnSafe(const std::string &utf8String)
{
    icu::UnicodeString unicodeString = icu::UnicodeString::fromUTF8(utf8String);
    std::vector<UChar> utf16Vector(unicodeString.length() + 1); // +1 for null terminator
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
inline std::vector<A_UTF16Char> ConvertUTF8ToUTF16(const std::string &utf8String)
{
    auto utf16Vector = ConvertUTF8ToUTF16UnSafe(utf8String);
    return std::vector<A_UTF16Char>(utf16Vector.begin(), utf16Vector.end());
}

inline std::string memHandleToString(AEGP_MemHandle memHandle)
{
    A_Err err = A_Err_NONE;
    AEGP_SuiteHandler &suites = SuiteManager::GetInstance().GetSuiteHandler();
    A_UTF16Char *unicode_nameP;

    AE_CHECK(suites.MemorySuite1()->AEGP_LockMemHandle(memHandle, reinterpret_cast<void **>(&unicode_nameP)));
    const std::string stringVal = ConvertUTF16ToUTF8(unicode_nameP);
    AE_CHECK(suites.MemorySuite1()->AEGP_UnlockMemHandle(memHandle));
    AE_CHECK(suites.MemorySuite1()->AEGP_FreeMemHandle(memHandle));
    return stringVal;
}
/**
 * @brief AE Project Suite
 *
 * @details The Project Suite provides access to the After Effects project.
 *
 *
 */
class ProjSuite
{
  public:
    ProjSuite(){};

    int GetNumProjects();                                                     /* Get The Number of Projects in AE.*/
    ProjectPtr GetProjectByIndex(int projIndex);                              /* Get Project by Index.*/
    std::string GetProjectName(ProjectPtr project);                           /* Get Project Name.*/
    std::string GetProjectPath(ProjectPtr project);                           /* Get Project Path.*/
    ItemPtr GetProjectRootFolder(ProjectPtr project);                         /* Get Project Root Folder.*/
    void SaveProjectToPath(ProjectPtr project, const std::string &path);      /* Save Project to Path.*/
    TimeDisplay3 GetProjectTimeDisplay(ProjectPtr project);                   /* Get Project Time Display.*/
    void SetProjectTimeDisplay(ProjectPtr project, TimeDisplay3 timeDisplay); /* Set Project Time Display.*/
    bool ProjectIsDirty(ProjectPtr project);                                  /* Check if Project is Dirty (changed).*/
    void SaveProjectAs(ProjectPtr project, const std::string &path);          /* Save Project As.*/
    ProjectPtr NewProject();                                                  /* Create a New Project.*/
    ProjectPtr OpenProjectFromPath(const std::string &path);                  /* Open Project from Path.*/
    ProjBitDepth GetProjectBitDepth(ProjectPtr project);                      /* Get Project Bit Depth.*/
    void SetProjectBitDepth(ProjectPtr project, ProjBitDepth bitDepth);       /* Set Project Bit Depth.*/
};
// TODO: Replace Time and Ratio with Time and Ratio. Ensure all other AE types are wrapped.
// TODO: Bind abstracted functions (wrapped) to python.
// TODO: In python, write the higher level API and classes that use the wrapped functions.
// TODO: Write tests for the python API.

/**
 * @brief AE Item Suite
 *
 * @details The Item Suite provides access to the After Effects project items.
 *
 */
class ItemSuite
{
  public:
    ItemSuite(){};
    ~ItemSuite(){};

    ItemPtr GetFirstProjItem(ProjectPtr project);                                    /* Get First Project Item.*/
    ItemPtr GetNextProjItem(ProjectPtr project, ItemPtr item);                       /* Get Next Project Item.*/
    ItemPtr GetActiveItem();                                                         /* Get Active Item.*/
    bool IsItemSelected(ItemPtr item);                                               /* Check if Item is Selected.*/
    void SelectItem(ItemPtr item, bool select, bool deselectOthers);                 /* Select Item.*/
    ItemType GetItemType(ItemPtr item);                                              /* Get Item Type.*/
    std::string GetTypeName(ItemType itemType);                                      /* Get Type Name.*/
    std::string GetItemName(ItemPtr item);                                           /* Get Item Name.*/
    void SetItemName(ItemPtr item, const std::string &name);                         /* Set Item Name.*/
    int GetItemID(ItemPtr item);                                                     /* Get Item ID.*/
    ItemFlag GetItemFlags(ItemPtr item);                                             /* Get Item Flags.*/
    void SetItemUseProxy(ItemPtr item, bool useProxy);                               /* Set Item Use Proxy.*/
    ItemPtr GetItemParentFolder(ItemPtr item);                                       /* Get Item Parent Folder.*/
    void SetItemParentFolder(ItemPtr item, ItemPtr parentFolder);                    /* Set Item Parent Folder.*/
    Time GetItemDuration(ItemPtr item);                                              /* Get Item Duration.*/
    Time GetItemCurrentTime(ItemPtr item);                                           /* Get Item Current Time.*/
    std::tuple<int, int> GetItemDimensions(ItemPtr item);                            /* Get Item Dimensions.*/
    Ratio GetItemPixelAspectRatio(ItemPtr item);                                     /* Get Item Pixel Aspect Ratio.*/
    void DeleteItem(ItemPtr item);                                                   /* Delete Item.*/
    ItemPtr CreateNewFolder(const std::string &name, ItemPtr parentFolder);          /* Create New Folder.*/
    void SetItemCurrentTime(ItemPtr item, Time newTime);                             /* Set Item Current Time.*/
    std::string GetItemComment(ItemPtr item);                                        /* Get Item Comment.*/
    void SetItemComment(ItemPtr item, const std::string &comment);                   /* Set Item Comment.*/
    Label GetItemLabel(ItemPtr item);                                                /* Get Item Label.*/
    void SetItemLabel(ItemPtr item, Label label);                                    /* Set Item Label.*/
    ItemViewPtr GetItemMRUView(ItemPtr item);                                        /* Get Item MRU View.*/
    Time GetItemViewPlaybackTime(ItemViewPtr itemView, bool &isCurrentlyPreviewing); /* Get Item View Playback Time.*/
};

class SoundDataSuite
{
  public:
    SoundDataSuite(){};

    SoundDataPtr NewSoundData(SoundDataFormat soundFormat); /* New Sound Data.*/

    SoundDataFormat GetSoundDataFormat(SoundDataPtr soundData); /* Get Sound Data Format.*/

    void LockSoundDataSamples(SoundDataPtr soundData, void **samples); /* Lock Sound Data Samples.*/
    void UnlockSoundDataSamples(SoundDataPtr soundData);               /* Unlock Sound Data Samples.*/
    int GetNumSamples(SoundDataPtr soundData);                         /* Get Num Samples.*/
};

class CompSuite
{
  public:
    CompSuite(){};
    ~CompSuite(){};

    CompPtr GetCompFromItem(ItemPtr item);                               /* Get Comp from Item.*/
    ItemPtr GetItemFromComp(CompPtr comp);                               /* Get Item from Comp.*/
    DownsampleFactor GetCompDownsampleFactor(CompPtr comp);              /* Get Comp Downsample Factor.*/
    void SetCompDownsampleFactor(CompPtr comp, DownsampleFactor factor); /* Set Comp Downsample Factor.*/
    ColorVal GetCompBGColor(CompPtr comp);                               /* Get Comp BG Color.*/
    void SetCompBGColor(CompPtr comp, ColorVal color);                   /* Set Comp BG Color.*/
    CompFlag GetCompFlags(CompPtr comp);                                 /* Get Comp Flags.*/
    bool GetShowLayerNameOrSourceName(CompPtr comp);                     /* Get Show Layer Name or Source Name.*/
    void SetShowLayerNameOrSourceName(CompPtr comp, bool showLayerName); /* Set Show Layer Name or Source Name.*/
    bool GetShowBlendModes(CompPtr comp);                                /* Get Show Blend Modes.*/
    void SetShowBlendModes(CompPtr comp, bool showBlendModes);           /* Set Show Blend Modes.*/
    double GetCompFramerate(CompPtr comp);                               /* Get Comp Framerate.*/
    void SetCompFrameRate(CompPtr comp, double fps);                     /* Set Comp Frame Rate.*/
    std::tuple<Ratio, Ratio> GetCompShutterAnglePhase(CompPtr comp);     /* Get Comp Shutter Angle Phase.*/
    std::tuple<Time, Time> GetCompShutterFrameRange(CompPtr comp, Time compTime); /* Get Comp Shutter Frame Range.*/
    int GetCompSuggestedMotionBlurSamples(CompPtr comp);               /* Get Comp Suggested Motion Blur Samples.*/
    void SetCompSuggestedMotionBlurSamples(CompPtr comp, int samples); /* Set Comp Suggested Motion Blur Samples.*/
    int GetCompMotionBlurAdaptiveSampleLimit(CompPtr comp);            /* Get
                                                                        Comp Motion Blur Adaptive Sample Limit.*/
    void SetCompMotionBlurAdaptiveSampleLimit(CompPtr comp,
                                              int samples); /* Set Comp Motion Blur Adaptive Sample Limit.*/
    Time GetCompWorkAreaStart(CompPtr comp);                /* Get Comp Work Area Start.*/
    Time GetCompWorkAreaDuration(CompPtr comp);             /* Get Comp Work Area Duration.*/
    void SetCompWorkAreaStartAndDuration(CompPtr comp, Time workAreaStart,
                                         Time workAreaDuration); /* Set Comp Work Area Start and Duration.*/
    LayerPtr CreateSolidInComp(CompPtr comp, const std::string &name, int width, int height, ColorVal color,
                               Time duration); /* Create Solid in Comp.*/
    LayerPtr CreateCameraInComp(CompPtr comp, const std::string &name,
                                FloatPoint centerPoint); /* Create Camera in Comp.*/
    LayerPtr CreateLightInComp(CompPtr comp, const std::string &name,
                               FloatPoint centerPoint); /* Create Light in Comp.*/
    CompPtr CreateComp(ItemPtr parentFolder, const std::string &name, int width, int height, Ratio pixelAspectRatio,
                       Time duration, Ratio framerate); /* Create Comp.*/
    Collection2Ptr GetNewCollectionFromCompSelection(AEGP_PluginID pluginId,
                                                     CompPtr comp); /* Get New Collection from Comp Selection.*/
    Time GetCompDisplayStartTime(CompPtr comp);                     /* Get Comp Display Start Time.*/
    void SetCompDisplayStartTime(CompPtr comp, Time startTime);     /* Set Comp Display Start Time.*/
    void SetCompDuration(CompPtr comp, Time duration);              /* Set Comp Duration.*/

    void SetCompDimensions(CompPtr comp, int width, int height);        /* Set Comp Dimensions.*/
    void SetCompPixelAspectRatio(CompPtr comp, Ratio pixelAspectRatio); /* Set Comp Pixel Aspect Ratio.*/
    LayerPtr CreateTextLayerInComp(CompPtr comp, bool newLayer = true); /* Create Text Layer in Comp.*/
    LayerPtr CreateBoxTextLayerInComp(CompPtr comp, FloatPoint boxDimensions,
                                      bool newLayer = true);                         /* Create Box Text Layer in Comp.*/
    LayerPtr CreateNullInComp(CompPtr comp, const std::string &name, Time duration); /* Create Null in Comp.*/
    CompPtr DuplicateComp(CompPtr comp);                                             /* Duplicate Comp.*/
    Time GetCompFrameDuration(CompPtr comp);                                         /* Get Comp Frame Duration.*/
    CompPtr GetMostRecentlyUsedComp();                                               /* Get Most Recently Used Comp.*/
    LayerPtr CreateVectorLayerInComp(CompPtr comp);                                  /* Create Vector Layer in Comp.*/
    StreamRefPtr GetNewCompMarkerStream(CompPtr parentComp);                         /* Get New Comp Marker Stream.*/
    bool GetCompDisplayDropFrame(CompPtr comp);                                      /* Get Comp Display Drop Frame.*/
    void SetCompDisplayDropFrame(CompPtr comp, bool dropFrame);                      /* Set Comp Display Drop Frame.*/
    void ReorderCompSelection(CompPtr comp, int index);                              /* Reorder Comp Selection.*/
};

class LayerSuite
{
  public:
    LayerSuite(){};

    int GetCompNumLayers(CompPtr comp);                                  /* Get Comp Num Layers.*/
    LayerPtr GetCompLayerByIndex(CompPtr comp, int layerIndex);          /* Get Comp Layer By Index.*/
    LayerPtr GetActiveLayer();                                           /* Get Active Layer.*/
    int GetLayerIndex(LayerPtr layer);                                   /* Get Layer Index.*/
    ItemPtr GetLayerSourceItem(LayerPtr layer);                          /* Get Layer Source Item.*/
    int GetLayerSourceItemID(LayerPtr layer);                            /* Get Layer Source Item ID.*/
    CompPtr GetLayerParentComp(LayerPtr layer);                          /* Get Layer Parent Comp.*/
    std::tuple<std::string, std::string> GetLayerName(LayerPtr layer);   /* Get Layer Name.*/
    LayerQual GetLayerQuality(LayerPtr layer);                           /* Get Layer Quality.*/
    void SetLayerQuality(LayerPtr layer, LayerQual quality);             /* Set Layer Quality.*/
    LayerFlag GetLayerFlags(LayerPtr layer);                             /* Get Layer Flags.*/
    void SetLayerFlag(LayerPtr layer, LayerFlag singleFlag, bool value); /* Set Layer Flag.*/
    bool IsLayerVideoReallyOn(LayerPtr layer);                           /* Is Layer Video Really On.*/
    bool IsLayerAudioReallyOn(LayerPtr layer);                           /* Is Layer Audio Really On.*/
    Time GetLayerCurrentTime(LayerPtr layer, LTimeMode timeMode);        /* Get Layer Current Time.*/
    Time GetLayerInPoint(LayerPtr layer, LTimeMode timeMode);            /* Get Layer In Point.*/
    Time GetLayerDuration(LayerPtr layer, LTimeMode timeMode);           /* Get Layer Duration.*/
    void SetLayerInPointAndDuration(LayerPtr layer, LTimeMode timeMode, Time inPoint,
                                    Time duration);                             /* Set Layer In Point and Duration.*/
    Time GetLayerOffset(LayerPtr layer);                                        /* Get Layer Offset.*/
    void SetLayerOffset(LayerPtr layer, Time offset);                           /* Set Layer Offset.*/
    Ratio GetLayerStretch(LayerPtr layer);                                      /* Get Layer Stretch.*/
    void SetLayerStretch(LayerPtr layer, Ratio stretch);                        /* Set Layer Stretch.*/
    std::tuple<TransferFlags, TrackMatte> GetLayerTransferMode(LayerPtr layer); /* Get Layer Transfer Mode.*/
    void SetLayerTransferMode(LayerPtr layer, TransferFlags flags, TrackMatte trackMatte); /* Set Layer Transfer Mode.*/
    bool IsAddLayerValid(ItemPtr itemToAdd, CompPtr intoComp);                             /* Is Add Layer Valid.*/
    LayerPtr AddLayer(ItemPtr itemToAdd, CompPtr intoComp);                                /* Add Layer.*/
    void ReorderLayer(LayerPtr layer, int layerIndex);                                     /* Reorder Layer.*/
    FloatRect GetLayerMaskedBounds(LayerPtr layer, LTimeMode timeMode, Time time);         /* Get Layer Masked Bounds.*/
    ObjectType GetLayerObjectType(LayerPtr layer);                                         /* Get Layer Object Type.*/
    bool IsLayer3D(LayerPtr layer);                                                        /* Is Layer 3D.*/
    bool IsLayer2D(LayerPtr layer);                                                        /* Is Layer 2D.*/
    bool IsVideoActive(LayerPtr layer, LTimeMode timeMode, Time time);                     /* Is Video Active.*/
    bool IsLayerUsedAsTrackMatte(LayerPtr layer, bool fillMustBeActive); /* Is Layer Used As Track Matte.*/
    bool DoesLayerHaveTrackMatte(LayerPtr layer);                        /* Does Layer Have Track Matte.*/
    Time ConvertCompToLayerTime(LayerPtr layer, Time compTime);          /* Convert Comp To Layer Time.*/
    Time ConvertLayerToCompTime(LayerPtr layer, Time layerTime);         /* Convert Layer To Comp Time.*/
    int GetLayerDancingRandValue(LayerPtr layer, Time compTime);         /* Get Layer Dancing Rand Value.*/
    int GetLayerID(LayerPtr layer);                                      /* Get Layer ID.*/
    Matrix4 GetLayerToWorldXform(LayerPtr layer, Time compTime);         /* Get Layer To World Xform.*/
    Matrix4 GetLayerToWorldXformFromView(LayerPtr layer, Time viewTime,
                                         Time compTime);                     /* Get Layer To World Xform From View.*/
    void SetLayerName(LayerPtr layer, const std::string &newName);           /* Set Layer Name.*/
    LayerPtr GetLayerParent(LayerPtr layer);                                 /* Get Layer Parent.*/
    void SetLayerParent(LayerPtr layer, LayerPtr parentLayer);               /* Set Layer Parent.*/
    void DeleteLayer(LayerPtr layer);                                        /* Delete Layer.*/
    LayerPtr DuplicateLayer(LayerPtr origLayer);                             /* Duplicate Layer.*/
    LayerPtr GetLayerFromLayerID(CompPtr parentComp, int id);                /* Get Layer From Layer ID.*/
    Label GetLayerLabel(LayerPtr layer);                                     /* Get Layer Label.*/
    void SetLayerLabel(LayerPtr layer, Label label);                         /* Set Layer Label.*/
    LayerSamplingQual GetLayerSamplingQuality(LayerPtr layer);               /* Get Layer Sampling Quality.*/
    void SetLayerSamplingQuality(LayerPtr layer, LayerSamplingQual quality); /* Set Layer Sampling Quality.*/
    LayerPtr GetTrackMatteLayer(LayerPtr layer);                             /* Get Track Matte Layer.*/
    void SetTrackMatte(LayerPtr layer, LayerPtr trackMatteLayer, TrackMatte trackMatteType); /* Set Track Matte.*/
    void RemoveTrackMatte(LayerPtr layer);                                                   /* Remove Track Matte.*/
};

class StreamSuite
{
  public:
    StreamSuite(){};

    bool IsStreamLegal(LayerPtr layer, LayerStream whichStream);                    /* Is Stream Legal.*/
    bool CanVaryOverTime(StreamRefPtr stream);                                      /* Can Vary Over Time.*/
    KeyInterpMask GetValidInterpolations(StreamRefPtr stream);                      /* Get Valid Interpolations.*/
    StreamRefPtr GetNewLayerStream(LayerPtr layer, LayerStream whichStream);        /* Get New Layer Stream.*/
    int GetEffectNumParamStreams(EffectRefPtr effectRef);                           /* Get Effect Num Param Streams.*/
    StreamRefPtr GetNewEffectStreamByIndex(EffectRefPtr effectRef, int paramIndex); /* Get New Effect Stream By Index.*/
    StreamRefPtr GetNewMaskStream(MaskRefPtr maskRef, MaskStream whichStream);      /* Get New Mask Stream.*/
    std::string GetStreamName(StreamRefPtr stream, bool forceEnglish);              /* Get Stream Name.*/
    std::string GetStreamUnitsText(StreamRefPtr stream, bool forceEnglish);         /* Get Stream Units Text.*/
    std::tuple<StreamFlag, double, double> GetStreamProperties(StreamRefPtr stream); /* Get Stream Properties.*/
    bool IsStreamTimevarying(StreamRefPtr stream);                                   /* Is Stream Timevarying.*/
    StreamType GetStreamType(StreamRefPtr stream);                                   /* Get Stream Type.*/
    StreamValue2Ptr GetNewStreamValue(StreamRefPtr stream, LTimeMode timeMode, Time time,
                                      bool preExpression);           /* Get New Stream Value.*/
    void SetStreamValue(StreamRefPtr stream, StreamValue2Ptr value); /* Set Stream Value.*/
    std::tuple<AEGP_StreamVal2, StreamType> GetLayerStreamValue(LayerPtr layer, LayerStream whichStream,
                                                                LTimeMode timeMode, Time time,
                                                                bool preExpression); /* Get Layer Stream Value.*/

    StreamRefPtr DuplicateStreamRef(StreamRefPtr stream); /* Duplicate Stream Ref.*/
    int GetUniqueStreamID(StreamRefPtr stream);           /* Get Unique Stream ID.*/
};

class DynamicStreamSuite
{
  public:
    DynamicStreamSuite(){};

    StreamRefPtr GetNewStreamRefForLayer(LayerPtr layer);          /* Get New Stream Ref For Layer.*/
    StreamRefPtr GetNewStreamRefForMask(MaskRefPtr mask);          /* Get New Stream Ref For Mask.*/
    int GetStreamDepth(StreamRefPtr stream);                       /* Get Stream Depth.*/
    StreamGroupingType GetStreamGroupingType(StreamRefPtr stream); /* Get Stream Grouping Type.*/
    int GetNumStreamsInGroup(StreamRefPtr stream);                 /* Get Num Streams In Group.*/
    DynStreamFlag GetDynamicStreamFlags(StreamRefPtr stream);      /* Get Dynamic Stream Flags.*/
    void SetDynamicStreamFlag(StreamRefPtr stream, DynStreamFlag oneFlag, bool undoable,
                              bool set);                                      /* Set Dynamic Stream Flag.*/
    StreamRefPtr GetNewStreamRefByIndex(StreamRefPtr parentGroup, int index); /* Get New Stream Ref By Index.*/
    StreamRefPtr GetNewStreamRefByMatchname(StreamRefPtr parentGroup,
                                            const std::string &matchName);     /* Get New Stream Ref By Matchname.*/
    void DeleteStream(StreamRefPtr stream);                                    /* Delete Stream.*/
    void ReorderStream(StreamRefPtr stream, int newIndex);                     /* Reorder Stream.*/
    int DuplicateStream(StreamRefPtr stream);                                  /* Duplicate Stream.*/
    void SetStreamName(StreamRefPtr stream, const std::string &newName);       /* Set Stream Name.*/
    bool CanAddStream(StreamRefPtr parentGroup, const std::string &matchName); /* Can Add Stream.*/
    StreamRefPtr AddStream(StreamRefPtr parentGroup, const std::string &matchName); /* Add Stream.*/
    std::string GetMatchname(StreamRefPtr stream);                                  /* Get Matchname.*/
    StreamRefPtr GetNewParentStreamRef(StreamRefPtr stream);                        /* Get New Parent Stream Ref.*/
    bool GetStreamIsModified(StreamRefPtr stream);                                  /* Get Stream Is Modified.*/
    bool IsSeparationLeader(StreamRefPtr stream);                                   /* Is Separation Leader.*/
    bool AreDimensionsSeparated(StreamRefPtr leaderStream);                         /* Are Dimensions Separated.*/
    void SetDimensionsSeparated(StreamRefPtr leaderStream, bool separated);         /* Set Dimensions Separated.*/
    StreamRefPtr GetSeparationFollower(int dimension, StreamRefPtr leaderStream);   /* Get Separation Follower.*/
    bool IsSeparationFollower(StreamRefPtr stream);                                 /* Is Separation Follower.*/
    StreamRefPtr GetSeparationLeader(StreamRefPtr followerStream);                  /* Get Separation Leader.*/
    A_short GetSeparationDimension(StreamRefPtr stream);                            /* Get Separation Dimension.*/
};

class KeyframeSuite
{
  public:
    KeyframeSuite(){};

    int GetStreamNumKFs(StreamRefPtr stream);                                        /* Get Stream Num KFs.*/
    Time GetKeyframeTime(StreamRefPtr stream, int keyIndex, LTimeMode timeMode);     /* Get Keyframe Time.*/
    int InsertKeyframe(StreamRefPtr stream, LTimeMode timeMode, const Time &time);   /* Insert Keyframe.*/
    void DeleteKeyframe(StreamRefPtr stream, int keyIndex);                          /* Delete Keyframe.*/
    StreamValue2Ptr GetNewKeyframeValue(StreamRefPtr stream, int keyIndex);          /* Get New Keyframe Value.*/
    void SetKeyframeValue(StreamRefPtr stream, int keyIndex, StreamValue2Ptr value); /* Set Keyframe Value.*/
    A_short GetStreamValueDimensionality(StreamRefPtr stream);    /* Get Stream Value Dimensionality.*/
    A_short GetStreamTemporalDimensionality(StreamRefPtr stream); /* Get Stream Temporal Dimensionality.*/
    std::tuple<StreamValue2Ptr, StreamValue2Ptr>
    GetNewKeyframeSpatialTangents(StreamRefPtr stream, int keyIndex); /* Get New Keyframe Spatial Tangents.*/
    void SetKeyframeSpatialTangents(StreamRefPtr stream, int keyIndex, StreamValue2Ptr inTan,
                                    StreamValue2Ptr outTan); /* Set Keyframe Spatial Tangents.*/
    std::tuple<KeyframeEase, KeyframeEase> GetKeyframeTemporalEase(StreamRefPtr stream, int keyIndex,
                                                                   int dimension); /* Get Keyframe Temporal Ease.*/
    void SetKeyframeTemporalEase(StreamRefPtr stream, int keyIndex, int dimension, KeyframeEase inEase,
                                 KeyframeEase outEase);               /* Set Keyframe Temporal Ease.*/
    KeyframeFlag GetKeyframeFlags(StreamRefPtr stream, int keyIndex); /* Get Keyframe Flags.*/
    void SetKeyframeFlag(StreamRefPtr stream, int keyIndex, KeyframeFlag flag, bool value); /* Set Keyframe Flag.*/
    std::tuple<KeyInterp, KeyInterp> GetKeyframeInterpolation(StreamRefPtr stream,
                                                              int keyIndex); /* Get Keyframe Interpolation.*/
    void SetKeyframeInterpolation(StreamRefPtr stream, int keyIndex, KeyInterp inInterp,
                                  KeyInterp outInterp);                                /* Set Keyframe Interpolation.*/
    AddKeyframesInfoPtr StartAddKeyframes(StreamRefPtr stream);                        /* Start Add Keyframes.*/
    int AddKeyframes(AddKeyframesInfoPtr akH, LTimeMode timeMode, const Time &time);   /* Add Keyframes.*/
    void SetAddKeyframe(AddKeyframesInfoPtr akH, int keyIndex, StreamValue2Ptr value); /* Set Add Keyframe.*/
    void EndAddKeyframes(AddKeyframesInfoPtr akH);                                     /* End Add Keyframes.*/
    int GetKeyframeLabelColorIndex(StreamRefPtr stream, int keyIndex); /* Get Keyframe Label Color Index.*/
    void SetKeyframeLabelColorIndex(StreamRefPtr stream, int keyIndex,
                                    int keyLabel); /* Set Keyframe Label Color Index.*/
};

class TextDocumentSuite
{
  public:
    TextDocumentSuite(){};

    std::string getNewText(TextDocumentPtr text_documentH);
    void setText(TextDocumentPtr text_documentH, const std::string &unicodePS);
};

class MarkerSuite
{
  public:
    MarkerSuite(){};

    MarkerValPtr getNewMarker();                                                 /* Creates a New Marker */
    MarkerValPtr duplicateMarker(MarkerValPtr markerP);                          /* Duplicates a Marker */
    void setMarkerFlag(MarkerValPtr markerP, MarkerFlag flagType, bool valueB);  /* Sets a Marker Flag */
    bool getMarkerFlag(MarkerValPtr markerP, MarkerFlag flagType);               /* Gets a Marker Flag */
    std::string getMarkerString(MarkerValPtr markerP, MarkerStringType strType); /* Gets a Marker String */
    void setMarkerString(MarkerValPtr markerP, MarkerStringType strType,
                         const std::string &unicodeP); /* Sets a Marker String */
    int countCuePointParams(MarkerValPtr markerP);     /* Counts Cue Point Params */
    std::tuple<std::string, std::string> getIndCuePointParam(MarkerValPtr markerP,
                                                             int param_indexL); /* Gets an Individual Cue Point Param */
    void setIndCuePointParam(MarkerValPtr markerP, int param_indexL, const std::string &unicodeKeyP,
                             const std::string &unicodeValueP);           /* Sets an Individual Cue Point Param */
    void insertCuePointParam(MarkerValPtr markerP, int param_indexL);     /* Inserts a Cue Point Param */
    void deleteIndCuePointParam(MarkerValPtr markerP, int param_indexL);  /* Deletes an Individual Cue Point Param */
    void setMarkerDuration(MarkerValPtr markerP, const Time &durationPT); /* Sets a Marker Duration */
    Time getMarkerDuration(MarkerValPtr markerP);                         /* Gets a Marker Duration */
    void setMarkerLabel(MarkerValPtr markerP, int value);                 /* Sets a Marker Label */
    int getMarkerLabel(MarkerValPtr markerP);                             /* Gets a Marker Label */
};

class TextLayerSuite
{
  public:
    TextLayerSuite(){};

    TextOutlinesPtr getNewTextOutlines(LayerPtr layer, const Time &layer_time);        /* Get New Text Outlines.*/
    int getNumTextOutlines(TextOutlinesPtr outlines);                                  /* Get Num Text Outlines.*/
    PF_PathOutlinePtr getIndexedTextOutline(TextOutlinesPtr outlines, int path_index); /* Get Indexed Text Outline.*/
};

class EffectSuite
{
  public:
    EffectSuite(){};

    int getLayerNumEffects(LayerPtr layer);                                     /* Get Layer Num Effects.*/
    EffectRefPtr getLayerEffectByIndex(LayerPtr layer, int layer_effect_index); /* Get Layer Effect By Index.*/
    int getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref); /* Get Installed Key From Layer Effect.*/
    std::tuple<PF_ParamType, PF_ParamDefUnion>
    getEffectParamUnionByIndex(EffectRefPtr effect_ref, int param_index); /* Get Effect Param Union By Index.*/
    EffectFlags getEffectFlags(EffectRefPtr effect_ref);                  /* Get Effect Flags.*/
    void setEffectFlags(EffectRefPtr effect_ref, EffectFlags effect_flags_set_mask,
                        EffectFlags effect_flags);                 /* Set Effect Flags.*/
    void reorderEffect(EffectRefPtr effect_ref, int effect_index); /* Reorder Effect.*/
    void effectCallGeneric(EffectRefPtr effect_ref, Time timePT, PF_Cmd effect_cmd,
                           void *effect_extraPV);                                     /* Effect Call Generic.*/
    EffectRefPtr applyEffect(LayerPtr layer, int installed_effect_key);               /* Apply Effect.*/
    void deleteLayerEffect(EffectRefPtr effect_ref);                                  /* Delete Layer Effect.*/
    int getNumInstalledEffects();                                                     /* Get Num Installed Effects.*/
    int getNextInstalledEffect(int installed_effect_key);                             /* Get Next Installed Effect.*/
    std::string getEffectName(int installed_effect_key);                              /* Get Effect Name.*/
    std::string getEffectMatchName(int installed_effect_key);                         /* Get Effect Match Name.*/
    std::string getEffectCategory(int installed_effect_key);                          /* Get Effect Category.*/
    EffectRefPtr duplicateEffect(EffectRefPtr original_effect_ref);                   /* Duplicate Effect.*/
    int numEffectMask(EffectRefPtr effect_ref);                                       /* Num Effect Mask.*/
    int getEffectMaskID(EffectRefPtr effect_ref, int mask_indexL);                    /* Get Effect Mask ID.*/
    StreamRefPtr addEffectMask(EffectRefPtr effect_ref, int id_val);                  /* Add Effect Mask.*/
    void removeEffectMask(EffectRefPtr effect_ref, int id_val);                       /* Remove Effect Mask.*/
    StreamRefPtr setEffectMask(EffectRefPtr effect_ref, int mask_indexL, int id_val); /* Set Effect Mask.*/
};

class MaskSuite
{
  public:
    MaskSuite(){};

    int getLayerNumMasks(LayerPtr aegp_layerH);                              /* Get Layer Num Masks.*/
    MaskRefPtr getLayerMaskByIndex(LayerPtr aegp_layerH, int mask_indexL);   /* Get Layer Mask By Index.*/
    bool getMaskInvert(MaskRefPtr mask_refH);                                /* Get Mask Invert.*/
    void setMaskInvert(MaskRefPtr mask_refH, bool invertB);                  /* Set Mask Invert.*/
    MaskMode getMaskMode(MaskRefPtr mask_refH);                              /* Get Mask Mode.*/
    void setMaskMode(MaskRefPtr maskH, MaskMode mode);                       /* Set Mask Mode.*/
    MaskMBlur getMaskMotionBlurState(MaskRefPtr mask_refH);                  /* Get Mask Motion Blur State.*/
    void setMaskMotionBlurState(MaskRefPtr mask_refH, MaskMBlur blur_state); /* Set Mask Motion Blur State.*/
    MaskFeatherFalloff getMaskFeatherFalloff(MaskRefPtr mask_refH);          /* Get Mask Feather Falloff.*/
    void setMaskFeatherFalloff(MaskRefPtr mask_refH,
                               MaskFeatherFalloff feather_falloffP);      /* Set Mask Feather Falloff.*/
    int getMaskID(MaskRefPtr mask_refH);                                  /* Get Mask ID.*/
    MaskRefPtr createNewMask(LayerPtr layerH, int mask_indexPL0);         /* Create New Mask.*/
    void deleteMaskFromLayer(MaskRefPtr mask_refH);                       /* Delete Mask From Layer.*/
    ColorVal getMaskColor(MaskRefPtr mask_refH);                          /* Get Mask Color.*/
    void setMaskColor(MaskRefPtr mask_refH, ColorVal colorP);             /* Set Mask Color.*/
    bool getMaskLockState(MaskRefPtr mask_refH);                          /* Get Mask Lock State.*/
    void setMaskLockState(MaskRefPtr mask_refH, bool lockB);              /* Set Mask Lock State.*/
    bool getMaskIsRotoBezier(MaskRefPtr mask_refH);                       /* Get Mask Is Roto Bezier.*/
    void setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB); /* Set Mask Is Roto Bezier.*/
    MaskRefPtr duplicateMask(MaskRefPtr orig_mask_refH);                  /* Duplicate Mask.*/
};

class MaskOutlineSuite
{
  public:
    MaskOutlineSuite(){};

    bool isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH);              /* Is Mask Outline Open.*/
    void setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH, bool openB); /* Set Mask Outline Open.*/
    int getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH);       /* Get Mask Outline Num Segments.*/
    MaskVertex getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH,
                                        int which_pointL); /* Get Mask Outline Vertex Info.*/
    void setMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, int which_pointL,
                                  MaskVertex vertexP);                       /* Set Mask Outline Vertex Info.*/
    void createVertex(MaskOutlineValPtr mask_outlineH, int insert_position); /* Create Vertex.*/
    void deleteVertex(MaskOutlineValPtr mask_outlineH, int index);           /* Delete Vertex.*/
    int getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH);          /* Get Mask Outline Num Feathers.*/
    MaskFeather getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                                          int which_featherL); /* Get Mask Outline Feather Info.*/
    void setMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH, int which_featherL,
                                   MaskFeather featherP); /* Set Mask Outline Feather Info.*/
    int createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH,
                                 MaskFeather featherP0);                       /* Create Mask Outline Feather.*/
    void deleteMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, int index); /* Delete Mask Outline Feather.*/
};

class FootageSuite
{
  public:
    FootageSuite(){};

    FootagePtr getMainFootageFromItem(ItemPtr itemH);                                 /* Get Main Footage From Item.*/
    FootagePtr getProxyFootageFromItem(ItemPtr itemH);                                /* Get Proxy Footage From Item.*/
    std::tuple<int, int> getFootageNumFiles(FootagePtr footageH);                     /* Get Footage Num Files.*/
    std::string getFootagePath(FootagePtr footageH, int frame_numL, int file_indexL); /* Get Footage Path.*/
    FootageSignature getFootageSignature(FootagePtr footageH);                        /* Get Footage Signature.*/
    FootagePtr newFootage(std::string pathZ, FootageLayerKey layer_infoP0,
                          FileSequenceImportOptions *sequence_optionsP0,
                          InterpretationStyle interp_style);                 /* New Footage.*/
    ItemPtr addFootageToProject(FootagePtr footageH, ItemPtr folderH);       /* Add Footage To Project.*/
    void setItemProxyFootage(FootagePtr footageH, ItemPtr itemH);            /* Set Item Proxy Footage.*/
    void replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH);         /* Replace Item Main Footage.*/
    AEGP_FootageInterp getFootageInterpretation(ItemPtr itemH, bool proxyB); /* Get Footage Interpretation.*/
    void setFootageInterpretation(ItemPtr itemH, bool proxyB,
                                  const AEGP_FootageInterp *interpP); /* Set Footage Interpretation.*/
    FootageLayerKey getFootageLayerKey(FootagePtr footageH);          /* Get Footage Layer Key.*/
    FootagePtr newPlaceholderFootage(std::string nameZ, int width, int height,
                                     Time durationPT); /* New Placeholder Footage.*/
    FootagePtr newPlaceholderFootageWithPath(std::string pathZ, Platform path_platform, AEIO_FileType file_type,
                                             int widthL, int heightL,
                                             Time durationPT); /* New Placeholder Footage With Path.*/
    FootagePtr newSolidFootage(std::string nameZ, int width, int height, ColorVal colorP); /* New Solid Footage.*/
    ColorVal getSolidFootageColor(ItemPtr itemH, bool proxyB);                             /* Get Solid Footage Color.*/
    void setSolidFootageColor(ItemPtr itemH, bool proxyB, ColorVal colorP);                /* Set Solid Footage Color.*/
    void setSolidFootageDimensions(ItemPtr itemH, bool proxyB, int widthL,
                                   int heightL);                    /* Set Solid Footage Dimensions.*/
    SoundDataFormat getFootageSoundDataFormat(FootagePtr footageH); /* Get Footage Sound Data Format.*/
    FileSequenceImportOptions
    getFootageSequenceImportOptions(FootagePtr footageH); /* Get Footage Sequence Import Options.*/
};

class UtilitySuite // Generally Ssafe to call from any thread
{
  public:
    UtilitySuite(){};
    ~UtilitySuite(){};

    void reportInfo(const std::string &info_string);               /* Report Info.*/
    void reportInfoUnicode(const std::string &info_string);        /* Report Info Unicode.*/
    std::tuple<A_short, A_short> getDriverPluginInitFuncVersion(); /* Get Driver Plugin Init Func Version.*/
    std::tuple<A_short, A_short> getDriverImplementationVersion(); /* Get Driver Implementation Version.*/
    void startQuietErrors();                                       /* Start Quiet Errors.*/
    void endQuietErrors(bool report_quieted_errorsB);              /* End Quiet Errors.*/
    std::string getLastErrorMessage(int buffer_size);              /* Get Last Error Message.*/
    void startUndoGroup(const std::string &undo_name);             /* Start Undo Group.*/
    void endUndoGroup();                                           /* End Undo Group.*/
    void *getMainHWND();                                           /* Get Main HWND.*/
    void showHideAllFloaters(bool include_tool_palB);              /* Show Hide All Floaters.*/
    ColorVal getPaintPalForeColor();                               /*Brush Tool Panel*/
    ColorVal getPaintPalBackColor();                               /*Brush Tool Panel*/
    void setPaintPalForeColor(ColorVal fore_color);                /*Brush Tool Panel*/
    void setPaintPalBackColor(ColorVal back_color);                /*Brush Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalFillColor();              /*Character Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalStrokeColor();            /*Character Tool Panel*/
    void setCharPalFillColor(ColorVal fill_color);                 /*Character Tool Panel*/
    void setCharPalStrokeColor(ColorVal stroke_color);             /*Character Tool Panel*/
    bool charPalIsFillColorUIFrontmost();                          /*Returns whether or not the fill
                                                                      color is frontmost. If it isn’t,
                                                                      the stroke color is frontmost.*/
    Ratio convertFpLongToHSFRatio(double numberF);                 /*Converts a floating-point number to a ratio.*/
    double convertHSFRatioToFpLong(Ratio ratioR);                  /*Converts a ratio to a floating-point number.*/
    void causeIdleRoutinesToBeCalled();                            /*Causes idle routines to be called.*/
    bool getSuppressInteractiveUI();                               /*Get Suppress Interactive UI.*/
    void writeToOSConsole(const std::string &text);                /* Write To OS Console.*/
    void writeToDebugLog(const std::string &subsystem, const std::string &eventType,
                         const std::string &text);       /* Write To Debug Log.*/
    std::string getPluginPath(PluginPathType path_type); /* Get Plugin Path.*/
};

class RenderQueueSuite // Main Thread Only
{
  public:
    RenderQueueSuite(){};

    void addCompToRenderQueue(CompPtr comp, const std::string &path); /* Add Comp To Render Queue.*/
    void setRenderQueueState(RenderQueueState state);                 /* Set Render Queue State.*/
    RenderQueueState getRenderQueueState();                           /* Get Render Queue State.*/
};

class RenderQueueItemSuite
{
  public:
    RenderQueueItemSuite(){};

    int getNumRQItems();                                                      /* Get Num RQ Items.*/
    RQItemRefPtr getRQItemByIndex(int rq_item_index);                         /* Get RQ Item By Index.*/
    RQItemRefPtr getNextRQItem(RQItemRefPtr current_rq_item);                 /* Get Next RQ Item.*/
    int getNumOutputModulesForRQItem(RQItemRefPtr rq_item);                   /* Get Num Output Modules For RQ Item.*/
    RenderItemStatus getRenderState(RQItemRefPtr rq_item);                    /* Get Render State.*/
    void setRenderState(RQItemRefPtr rq_item, RenderItemStatus status);       /* Set Render State.*/
    Time getStartedTime(RQItemRefPtr rq_item);                                /* Get Started Time.*/
    Time getElapsedTime(RQItemRefPtr rq_item);                                /* Get Elapsed Time.*/
    LogType getLogType(RQItemRefPtr rq_item);                                 /* Get Log Type.*/
    void setLogType(RQItemRefPtr rq_item, LogType logtype);                   /* Set Log Type.*/
    void removeOutputModule(RQItemRefPtr rq_item, OutputModuleRefPtr outmod); /* Remove Output Module.*/
    std::string getComment(RQItemRefPtr rq_item);                             /* Get Comment.*/
    void setComment(RQItemRefPtr rq_item, const std::string &comment);        /* Set Comment.*/
    CompPtr getCompFromRQItem(RQItemRefPtr rq_item);                          /* Get Comp From RQ Item.*/
    void deleteRQItem(RQItemRefPtr rq_item);                                  /* Delete RQ Item.*/
};

class OutputModuleSuite
{
  public:
    OutputModuleSuite(){};

    OutputModuleRefPtr getOutputModuleByIndex(RQItemRefPtr rq_itemH,
                                              int outmod_indexL);                     /* Get Output Module By Index.*/
    EmbeddingType getEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Embed Options.*/
    void setEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                         EmbeddingType embed_options); /* Set Embed Options.*/
    PostRenderAction getPostRenderAction(RQItemRefPtr rq_itemH,
                                         OutputModuleRefPtr outmodH); /* Get Post Render Action.*/
    void setPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                             PostRenderAction post_render_action);                    /* Set Post Render Action.*/
    OutputTypes getEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Enabled Outputs.*/
    void setEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           OutputTypes enabled_types);                                  /* Set Enabled Outputs.*/
    VideoChannels getOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Output Channels.*/
    void setOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           VideoChannels output_channels); /* Set Output Channels.*/
    std::tuple<bool, StretchQuality, bool> getStretchInfo(RQItemRefPtr rq_itemH,
                                                          OutputModuleRefPtr outmodH); /* Get Stretch Info.*/
    void setStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool is_enabledB,
                        StretchQuality stretch_quality);                                    /* Set Stretch Info.*/
    std::tuple<bool, LRect> getCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Crop Info.*/
    void setCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool enableB,
                     LRect crop_rect); /* Set Crop Info.*/
    std::tuple<SoundDataFormat, bool> getSoundFormatInfo(RQItemRefPtr rq_itemH,
                                                         OutputModuleRefPtr outmodH); /* Get Sound Format Info.*/
    void setSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, SoundDataFormat sound_format_info,
                            bool audio_enabledB);                                     /* Set Sound Format Info.*/
    std::string getOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Output File Path.*/
    void setOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                           const std::string &path);                  /* Set Output File Path.*/
    OutputModuleRefPtr addDefaultOutputModule(RQItemRefPtr rq_itemH); /* Add Default Output Module.*/
    std::tuple<std::string, std::string, bool, bool>
    getExtraOutputModuleInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH); /* Get Extra Output Module Info.*/
};

class WorldSuite
{
  public:
    WorldSuite(){};

    WorldPtr newWorld(WorldType type, int widthL, int heightL); /* New World.*/
    WorldType getType(WorldPtr worldH);                         /* Get Type.*/
    std::tuple<int, int> getSize(WorldPtr worldH);              /* Get Size.*/
    A_u_long getRowBytes(WorldPtr worldH);                      /* Get Row Bytes.*/
    PF_Pixel8 *getBaseAddr8(WorldPtr worldH);                   /* Get Base Addr 8.*/
    PF_Pixel16 *getBaseAddr16(WorldPtr worldH);                 /* Get Base Addr 16.*/
    PF_PixelFloat *getBaseAddr32(WorldPtr worldH);              /* Get Base Addr 32.*/
    PF_EffectWorld fillOutPFEffectWorld(WorldPtr worldH);       /* Fill Out PF Effect World.*/
    void fastBlur(double radiusF, PF_ModeFlags mode, PF_Quality quality, WorldPtr worldH); /* Fast Blur.*/
    PlatformWorldPtr newPlatformWorld(WorldType type, int widthL, int heightL);            /* New Platform World.*/
    WorldPtr newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH); /* New Reference From Platform World.*/
};

class RenderOptionsSuite
{
  public:
    RenderOptionsSuite(){};

    RenderOptionsPtr newFromItem(ItemPtr itemH);                                             /* New From Item.*/
    RenderOptionsPtr duplicate(RenderOptionsPtr optionsH);                                   /* Duplicate.*/
    void setTime(RenderOptionsPtr optionsH, Time time);                                      /* Set Time.*/
    Time getTime(RenderOptionsPtr optionsH);                                                 /* Get Time.*/
    void setTimeStep(RenderOptionsPtr optionsH, Time time_step);                             /* Set Time Step.*/
    Time getTimeStep(RenderOptionsPtr optionsH);                                             /* Get Time Step.*/
    void setFieldRender(RenderOptionsPtr optionsH, PF_Field field_render);                   /* Set Field Render.*/
    PF_Field getFieldRender(RenderOptionsPtr optionsH);                                      /* Get Field Render.*/
    void setWorldType(RenderOptionsPtr optionsH, WorldType type);                            /* Set World Type.*/
    WorldType getWorldType(RenderOptionsPtr optionsH);                                       /* Get World Type.*/
    void setDownsampleFactor(RenderOptionsPtr optionsH, DownsampleFactor downsample_factor); /* Set Downsample Factor.*/
    DownsampleFactor getDownsampleFactor(RenderOptionsPtr optionsH);                         /* Get Downsample Factor.*/
    void setRegionOfInterest(RenderOptionsPtr optionsH, LRect roiP);             /* Set Region Of Interest.*/
    LRect getRegionOfInterest(RenderOptionsPtr optionsH);                        /* Get Region Of Interest.*/
    void setMatteMode(RenderOptionsPtr optionsH, MatteMode mode);                /* Set Matte Mode.*/
    MatteMode getMatteMode(RenderOptionsPtr optionsH);                           /* Get Matte Mode.*/
    void setChannelOrder(RenderOptionsPtr optionsH, ChannelOrder channel_order); /* Set Channel Order.*/
    ChannelOrder getChannelOrder(RenderOptionsPtr optionsH);                     /* Get Channel Order.*/
    bool getRenderGuideLayers(RenderOptionsPtr optionsH);                        /* Get Render Guide Layers.*/
    void setRenderGuideLayers(RenderOptionsPtr optionsH, bool render_themB);     /* Set Render Guide Layers.*/
};

class LayerRenderOptionsSuite
{
  public:
    LayerRenderOptionsSuite(){};

    LayerRenderOptionsPtr newFromLayer(LayerPtr layer);                       /* New From Layer.*/
    LayerRenderOptionsPtr newFromUpstreamOfEffect(EffectRefPtr effect_ref);   /* New From Upstream Of Effect.*/
    LayerRenderOptionsPtr newFromDownstreamOfEffect(EffectRefPtr effect_ref); /* New From Downstream Of Effect.*/
    LayerRenderOptionsPtr duplicate(LayerRenderOptionsPtr optionsH);          /* Duplicate.*/

    void setTime(LayerRenderOptionsPtr optionsH, Time time);                        /* Set Time.*/
    Time getTime(LayerRenderOptionsPtr optionsH);                                   /* Get Time.*/
    void setTimeStep(LayerRenderOptionsPtr optionsH, Time time_step);               /* Set Time Step.*/
    Time getTimeStep(LayerRenderOptionsPtr optionsH);                               /* Get Time Step.*/
    void setWorldType(LayerRenderOptionsPtr optionsH, WorldType type);              /* Set World Type.*/
    WorldType getWorldType(LayerRenderOptionsPtr optionsH);                         /* Get World Type.*/
    void setDownsampleFactor(LayerRenderOptionsPtr optionsH, DownsampleFactor dsf); /* Set Downsample Factor.*/
    DownsampleFactor getDownsampleFactor(LayerRenderOptionsPtr optionsH);           /* Get Downsample Factor.*/
    void setMatteMode(LayerRenderOptionsPtr optionsH, MatteMode mode);              /* Set Matte Mode.*/
    MatteMode getMatteMode(LayerRenderOptionsPtr optionsH);                         /* Get Matte Mode.*/
};

class RenderSuite
{
  public:
    RenderSuite(){};

    FrameReceiptPtr renderAndCheckoutFrame(RenderOptionsPtr optionsH); /* Render And Checkout Frame.*/

    FrameReceiptPtr renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH); /* Render And Checkout Layer Frame.*/

    A_u_longlong
    renderAndCheckoutLayerFrameAsync(LayerRenderOptionsPtr optionsH, AEGP_AsyncFrameReadyCallback callback,
                                     AEGP_AsyncFrameRequestRefcon refcon); /* Render And Checkout Layer Frame Async.*/

    void cancelAsyncRequest(AEGP_AsyncRequestId async_request_id); /* Cancel Async Request.*/

    WorldPtr getReceiptWorld(FrameReceiptPtr receiptH); /* Get Receipt World.*/

    LRect getRenderedRegion(FrameReceiptPtr receiptH); /* Get Rendered Region.*/

    bool isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH,
                                   RenderOptionsPtr proposed_optionsH); /* Is Rendered Frame Sufficient.*/
    TimeStampPtr getCurrentTimestamp();                                 /* Get Current Timestamp.*/

    bool hasItemChangedSinceTimestamp(ItemPtr itemH, Time start_timeP, Time durationP,
                                      TimeStampPtr time_stampP); /* Has Item Changed Since Timestamp.*/

    bool isItemWorthwhileToRender(RenderOptionsPtr roH, TimeStampPtr time_stampP); /* Is Item Worthwhile To Render.*/

    void checkinRenderedFrame(RenderOptionsPtr roH, TimeStampPtr time_stampP, A_u_long ticks_to_renderL,
                              PlatformWorldPtr imageH); /* Checkin Rendered Frame.*/

    std::string getReceiptGuid(FrameReceiptPtr receiptH); /* Get Receipt Guid.*/
};

class CollectionSuite
{
  public:
    CollectionSuite(){};

    Collection2Ptr newCollection();                        /* New Collection.*/
    int getCollectionNumItems(Collection2Ptr collectionH); /* Get Collection Num Items.*/
    AEGP_CollectionItemV2 getCollectionItemByIndex(Collection2Ptr collectionH,
                                                   int indexL); /* Get Collection Item By Index.*/
    void collectionPushBack(Collection2Ptr collectionH, const AEGP_CollectionItemV2 &itemP); /* Collection Push Back.*/
    void collectionErase(Collection2Ptr collectionH, int index_firstL, int index_lastL);     /* Collection Erase.*/
};

class RegisterSuite
{
  public:
    RegisterSuite(){};

    void registerCommandHook(AEGP_HookPriority hook_priority, AEGP_Command command, AEGP_CommandHook command_hook_func,
                             AEGP_CommandRefcon refconP); /* Register Command Hook.*/
    void registerUpdateMenuHook(AEGP_UpdateMenuHook update_menu_hook_func,
                                AEGP_UpdateMenuRefcon refconP);                       /* Register Update Menu Hook.*/
    void registerDeathHook(AEGP_DeathHook death_hook_func, AEGP_DeathRefcon refconP); /* Register Death Hook.*/
    void registerIdleHook(AEGP_IdleHook idle_hook_func, AEGP_IdleRefcon refconP);     /* Register Idle Hook.*/
    void registerPresetLocalizationString(const std::string &english_nameZ,
                                          const std::string &localized_nameZ); /* Register Preset Localization String.*/
};

class CommandSuite
{
  public:
    CommandSuite(){};

    AEGP_Command getUniqueCommand(); /* Get Unique Command.*/
    void insertMenuCommand(AEGP_Command command, const std::string &nameZ, MenuID menu_id,
                           int after_itemL);                                 /* Insert Menu Command.*/
    void removeMenuCommand(AEGP_Command command);                            /* Remove Menu Command.*/
    void setMenuCommandName(AEGP_Command command, const std::string &nameZ); /* Set Menu Command Name.*/
    void enableCommand(AEGP_Command command);                                /* Enable Command.*/
    void disableCommand(AEGP_Command command);                               /* Disable Command.*/
    void checkMarkMenuCommand(AEGP_Command command, bool checkB);            /* Check Mark Menu Command.*/
    void doCommand(AEGP_Command command);                                    /* Do Command.*/
};

#endif // SUITES_HPP
