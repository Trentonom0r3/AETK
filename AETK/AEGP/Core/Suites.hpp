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
    A_UTF16Char *unicode_nameP = nullptr;
    MemorySuite memorySuite;
    MemHandlePtr ptr = std::shared_ptr<AEGP_MemHandle>(&memHandle, MemHandleDeleter());

    AE_CHECK(suites.MemorySuite1()->AEGP_LockMemHandle(memHandle, reinterpret_cast<void **>(&unicode_nameP)));
    std::string stringVal = ConvertUTF16ToUTF8(unicode_nameP);
    AE_CHECK(suites.MemorySuite1()->AEGP_UnlockMemHandle(memHandle));

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

    ItemPtr GetFirstProjItem(ProjectPtr project);                                      /* Get First Project Item.*/
    ItemPtr GetNextProjItem(ProjectPtr project, ItemPtr item);                         /* Get Next Project Item.*/
    ItemPtr GetActiveItem();                                                           /* Get Active Item.*/
    bool IsItemSelected(ItemPtr item);                                                 /* Check if Item is Selected.*/
    void SelectItem(ItemPtr item, bool select, bool deselectOthers);                   /* Select Item.*/
    ItemType GetItemType(ItemPtr item);                                                /* Get Item Type.*/
    std::string GetTypeName(ItemType itemType);                                        /* Get Type Name.*/
    std::string GetItemName(ItemPtr item);                                             /* Get Item Name.*/
    void SetItemName(ItemPtr item, const std::string &name);                           /* Set Item Name.*/
    int GetItemID(ItemPtr item);                                                       /* Get Item ID.*/
    ItemFlag GetItemFlags(ItemPtr item);                                               /* Get Item Flags.*/
    void SetItemUseProxy(ItemPtr item, bool useProxy);                                 /* Set Item Use Proxy.*/
    ItemPtr GetItemParentFolder(ItemPtr item);                                         /* Get Item Parent Folder.*/
    void SetItemParentFolder(ItemPtr item, ItemPtr parentFolder);                      /* Set Item Parent Folder.*/
    A_Time GetItemDuration(ItemPtr item);                                              /* Get Item Duration.*/
    A_Time GetItemCurrentTime(ItemPtr item);                                           /* Get Item Current Time.*/
    std::tuple<int, int> GetItemDimensions(ItemPtr item);                              /* Get Item Dimensions.*/
    A_Ratio GetItemPixelAspectRatio(ItemPtr item);                                     /* Get Item Pixel Aspect Ratio.*/
    void DeleteItem(ItemPtr item);                                                     /* Delete Item.*/
    ItemPtr CreateNewFolder(const std::string &name, ItemPtr parentFolder);            /* Create New Folder.*/
    void SetItemCurrentTime(ItemPtr item, A_Time newTime);                             /* Set Item Current Time.*/
    std::string GetItemComment(ItemPtr item);                                          /* Get Item Comment.*/
    void SetItemComment(ItemPtr item, const std::string &comment);                     /* Set Item Comment.*/
    Label GetItemLabel(ItemPtr item);                                                  /* Get Item Label.*/
    void SetItemLabel(ItemPtr item, Label label);                                      /* Set Item Label.*/
    ItemViewPtr GetItemMRUView(ItemPtr item);                                          /* Get Item MRU View.*/
    A_Time GetItemViewPlaybackTime(ItemViewPtr itemView, bool &isCurrentlyPreviewing); /* Get Item View Playback Time.*/
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
    std::tuple<A_Ratio, A_Ratio> GetCompShutterAnglePhase(CompPtr comp); /* Get Comp Shutter Angle Phase.*/
    std::tuple<A_Time, A_Time> GetCompShutterFrameRange(CompPtr comp,
                                                        A_Time compTime); /* Get Comp Shutter Frame Range.*/
    int GetCompSuggestedMotionBlurSamples(CompPtr comp);                  /* Get Comp Suggested Motion Blur Samples.*/
    void SetCompSuggestedMotionBlurSamples(CompPtr comp, int samples);    /* Set Comp Suggested Motion Blur Samples.*/
    int GetCompMotionBlurAdaptiveSampleLimit(CompPtr comp);               /* Get
                                                                           Comp Motion Blur Adaptive Sample Limit.*/
    void SetCompMotionBlurAdaptiveSampleLimit(CompPtr comp,
                                              int samples); /* Set Comp Motion Blur Adaptive Sample Limit.*/
    A_Time GetCompWorkAreaStart(CompPtr comp);              /* Get Comp Work Area Start.*/
    A_Time GetCompWorkAreaDuration(CompPtr comp);           /* Get Comp Work Area Duration.*/
    void SetCompWorkAreaStartAndDuration(CompPtr comp, A_Time workAreaStart,
                                         A_Time workAreaDuration); /* Set Comp Work Area Start and Duration.*/
    LayerPtr CreateSolidInComp(CompPtr comp, const std::string &name, int width, int height, ColorVal color,
                               A_Time duration); /* Create Solid in Comp.*/
    LayerPtr CreateCameraInComp(CompPtr comp, const std::string &name,
                                FloatPoint centerPoint); /* Create Camera in Comp.*/
    LayerPtr CreateLightInComp(CompPtr comp, const std::string &name,
                               FloatPoint centerPoint); /* Create Light in Comp.*/
    CompPtr CreateComp(ItemPtr parentFolder, const std::string &name, int width, int height,
                       const A_Ratio &pixelAspectRatio, A_Time duration, const A_Ratio &framerate); /* Create Comp.*/
    Collection2Ptr GetNewCollectionFromCompSelection(AEGP_PluginID pluginId,
                                                     CompPtr comp); /* Get New Collection from Comp Selection.*/
    A_Time GetCompDisplayStartTime(CompPtr comp);                   /* Get Comp Display Start Time.*/
    void SetCompDisplayStartTime(CompPtr comp, A_Time startTime);   /* Set Comp Display Start Time.*/
    void SetCompDuration(CompPtr comp, A_Time duration);            /* Set Comp Duration.*/
    CompPtr DuplicateComp(CompPtr comp);                            /* Duplicate Comp.*/
    A_Time GetCompFrameDuration(CompPtr comp);                      /* Get Comp Frame Duration.*/
    CompPtr GetMostRecentlyUsedComp();                              /* Get Most Recently Used Comp.*/
    LayerPtr CreateVectorLayerInComp(CompPtr comp);                 /* Create Vector Layer in Comp.*/
    StreamRefPtr GetNewCompMarkerStream(CompPtr parentComp);        /* Get New Comp Marker Stream.*/
    bool GetCompDisplayDropFrame(CompPtr comp);                     /* Get Comp Display Drop Frame.*/
    void SetCompDisplayDropFrame(CompPtr comp, bool dropFrame);     /* Set Comp Display Drop Frame.*/
    void ReorderCompSelection(CompPtr comp, int index);             /* Reorder Comp Selection.*/
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
    A_Time GetLayerCurrentTime(LayerPtr layer, LTimeMode timeMode);      /* Get Layer Current Time.*/
    A_Time GetLayerInPoint(LayerPtr layer, LTimeMode timeMode);          /* Get Layer In Point.*/
    A_Time GetLayerDuration(LayerPtr layer, LTimeMode timeMode);         /* Get Layer Duration.*/
    void SetLayerInPointAndDuration(LayerPtr layer, LTimeMode timeMode, A_Time inPoint,
                                    A_Time duration);                           /* Set Layer In Point and Duration.*/
    A_Time GetLayerOffset(LayerPtr layer);                                      /* Get Layer Offset.*/
    void SetLayerOffset(LayerPtr layer, A_Time offset);                         /* Set Layer Offset.*/
    A_Ratio GetLayerStretch(LayerPtr layer);                                    /* Get Layer Stretch.*/
    void SetLayerStretch(LayerPtr layer, A_Ratio stretch);                      /* Set Layer Stretch.*/
    std::tuple<TransferFlags, TrackMatte> GetLayerTransferMode(LayerPtr layer); /* Get Layer Transfer Mode.*/
    void SetLayerTransferMode(LayerPtr layer, TransferFlags flags, TrackMatte trackMatte); /* Set Layer Transfer Mode.*/
    bool IsAddLayerValid(ItemPtr itemToAdd, CompPtr intoComp);                             /* Is Add Layer Valid.*/
    LayerPtr AddLayer(ItemPtr itemToAdd, CompPtr intoComp);                                /* Add Layer.*/
    void ReorderLayer(LayerPtr layer, int layerIndex);                                     /* Reorder Layer.*/
    FloatRect GetLayerMaskedBounds(LayerPtr layer, LTimeMode timeMode, A_Time time);       /* Get Layer Masked Bounds.*/
    ObjectType GetLayerObjectType(LayerPtr layer);                                         /* Get Layer Object Type.*/
    bool IsLayer3D(LayerPtr layer);                                                        /* Is Layer 3D.*/
    bool IsLayer2D(LayerPtr layer);                                                        /* Is Layer 2D.*/
    bool IsVideoActive(LayerPtr layer, LTimeMode timeMode, A_Time time);                   /* Is Video Active.*/
    bool IsLayerUsedAsTrackMatte(LayerPtr layer, bool fillMustBeActive); /* Is Layer Used As Track Matte.*/
    bool DoesLayerHaveTrackMatte(LayerPtr layer);                        /* Does Layer Have Track Matte.*/
    A_Time ConvertCompToLayerTime(LayerPtr layer, A_Time compTime);      /* Convert Comp To Layer Time.*/
    A_Time ConvertLayerToCompTime(LayerPtr layer, A_Time layerTime);     /* Convert Layer To Comp Time.*/
    int GetLayerDancingRandValue(LayerPtr layer, A_Time compTime);       /* Get Layer Dancing Rand Value.*/
    AEGP_LayerIDVal GetLayerID(LayerPtr layer);                          /* Get Layer ID.*/
    Matrix4 GetLayerToWorldXform(LayerPtr layer, A_Time compTime);       /* Get Layer To World Xform.*/
    Matrix4 GetLayerToWorldXformFromView(LayerPtr layer, A_Time viewTime,
                                         A_Time compTime);                   /* Get Layer To World Xform From View.*/
    void SetLayerName(LayerPtr layer, const std::string &newName);           /* Set Layer Name.*/
    LayerPtr GetLayerParent(LayerPtr layer);                                 /* Get Layer Parent.*/
    void SetLayerParent(LayerPtr layer, LayerPtr parentLayer);               /* Set Layer Parent.*/
    void DeleteLayer(LayerPtr layer);                                        /* Delete Layer.*/
    LayerPtr DuplicateLayer(LayerPtr origLayer);                             /* Duplicate Layer.*/
    LayerPtr GetLayerFromLayerID(CompPtr parentComp, AEGP_LayerIDVal id);    /* Get Layer From Layer ID.*/
    AEGP_LabelID GetLayerLabel(LayerPtr layer);                              /* Get Layer Label.*/
    void SetLayerLabel(LayerPtr layer, AEGP_LabelID label);                  /* Set Layer Label.*/
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
    StreamValue2Ptr GetNewStreamValue(StreamRefPtr stream, LTimeMode timeMode, A_Time time,
                                      bool preExpression);           /* Get New Stream Value.*/
    void SetStreamValue(StreamRefPtr stream, StreamValue2Ptr value); /* Set Stream Value.*/
    std::tuple<AEGP_StreamVal2, StreamType> GetLayerStreamValue(LayerPtr layer, LayerStream whichStream,
                                                                LTimeMode timeMode, A_Time time,
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

    int GetStreamNumKFs(StreamRefPtr stream); /* Get Stream Num KFs.*/
    A_Time GetKeyframeTime(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                           LTimeMode timeMode); /* Get Keyframe Time.*/
    AEGP_KeyframeIndex InsertKeyframe(StreamRefPtr stream, LTimeMode timeMode,
                                      const A_Time &time);                                 /* Insert Keyframe.*/
    void DeleteKeyframe(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex);                 /* Delete Keyframe.*/
    StreamValue2Ptr GetNewKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex); /* Get New Keyframe Value.*/
    void SetKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                          StreamValue2Ptr value);                 /* Set Keyframe Value.*/
    A_short GetStreamValueDimensionality(StreamRefPtr stream);    /* Get Stream Value Dimensionality.*/
    A_short GetStreamTemporalDimensionality(StreamRefPtr stream); /* Get Stream Temporal Dimensionality.*/
    std::tuple<StreamValue2Ptr, StreamValue2Ptr>
    GetNewKeyframeSpatialTangents(StreamRefPtr stream,
                                  AEGP_KeyframeIndex keyIndex); /* Get New Keyframe Spatial Tangents.*/
    void SetKeyframeSpatialTangents(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr inTan,
                                    StreamValue2Ptr outTan); /* Set Keyframe Spatial Tangents.*/
    std::tuple<KeyframeEase, KeyframeEase> GetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
                                                                   int dimension); /* Get Keyframe Temporal Ease.*/
    void SetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int dimension, KeyframeEase inEase,
                                 KeyframeEase outEase);                              /* Set Keyframe Temporal Ease.*/
    KeyframeFlag GetKeyframeFlags(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex); /* Get Keyframe Flags.*/
    void SetKeyframeFlag(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyframeFlag flag,
                         bool value); /* Set Keyframe Flag.*/
    std::tuple<KeyInterp, KeyInterp>
    GetKeyframeInterpolation(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex); /* Get Keyframe Interpolation.*/
    void SetKeyframeInterpolation(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyInterp inInterp,
                                  KeyInterp outInterp);         /* Set Keyframe Interpolation.*/
    AddKeyframesInfoPtr StartAddKeyframes(StreamRefPtr stream); /* Start Add Keyframes.*/
    AEGP_KeyframeIndex AddKeyframes(AddKeyframesInfoPtr akH, LTimeMode timeMode,
                                    const A_Time &time); /* Add Keyframes.*/
    void SetAddKeyframe(AddKeyframesInfoPtr akH, AEGP_KeyframeIndex keyIndex,
                        StreamValue2Ptr value);    /* Set Add Keyframe.*/
    void EndAddKeyframes(AddKeyframesInfoPtr akH); /* End Add Keyframes.*/
    int GetKeyframeLabelColorIndex(StreamRefPtr stream,
                                   AEGP_KeyframeIndex keyIndex); /* Get Keyframe Label Color Index.*/
    void SetKeyframeLabelColorIndex(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex,
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

    MarkerValPtr getNewMarker(); /* Creates a New Marker */
    MarkerValPtr duplicateMarker(MarkerValPtr markerP); /* Duplicates a Marker */
    void setMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType, bool valueB); // #TODO : make MarkerFlagType
    bool getMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType); 		   // #TODO : make MarkerFlagType
    std::string getMarkerString(MarkerValPtr markerP, MarkerStringType strType);
    void setMarkerString(MarkerValPtr markerP, MarkerStringType strType, const std::string &unicodeP);
    int countCuePointParams(MarkerValPtr markerP);
    std::tuple<std::string, std::string> getIndCuePointParam(

        MarkerValPtr markerP, int param_indexL);
    void setIndCuePointParam(MarkerValPtr markerP, int param_indexL, const std::string &unicodeKeyP,
                             const std::string &unicodeValueP);
    void insertCuePointParam(MarkerValPtr markerP, int param_indexL);
    void deleteIndCuePointParam(MarkerValPtr markerP, int param_indexL);
    void setMarkerDuration(MarkerValPtr markerP, const A_Time &durationPT);
    A_Time getMarkerDuration(MarkerValPtr markerP);
    void setMarkerLabel(MarkerValPtr markerP, int value);
    int getMarkerLabel(MarkerValPtr markerP);
};

class TextLayerSuite
{
  public:
    TextLayerSuite(){};

    TextOutlinesPtr getNewTextOutlines(LayerPtr layer, const A_Time &layer_time);
    int getNumTextOutlines(TextOutlinesPtr outlines);
    PF_PathOutlinePtr getIndexedTextOutline(TextOutlinesPtr outlines, int path_index);
};

class EffectSuite
{
  public:
    EffectSuite(){};

    int getLayerNumEffects(LayerPtr layer);
    EffectRefPtr getLayerEffectByIndex(LayerPtr layer, AEGP_EffectIndex layer_effect_index);
    AEGP_InstalledEffectKey getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref);
    std::tuple<PF_ParamType, PF_ParamDefUnion> getEffectParamUnionByIndex(EffectRefPtr effect_ref,
                                                                          PF_ParamIndex param_index);
    EffectFlags getEffectFlags(EffectRefPtr effect_ref);
    void setEffectFlags(EffectRefPtr effect_ref, EffectFlags effect_flags_set_mask, EffectFlags effect_flags);
    void reorderEffect(EffectRefPtr effect_ref, int effect_index);
    void effectCallGeneric(EffectRefPtr effect_ref, const A_Time *timePT, PF_Cmd effect_cmd, void *effect_extraPV);
    EffectRefPtr applyEffect(LayerPtr layer, AEGP_InstalledEffectKey installed_effect_key);
    void deleteLayerEffect(EffectRefPtr effect_ref);
    int getNumInstalledEffects();
    AEGP_InstalledEffectKey getNextInstalledEffect(AEGP_InstalledEffectKey installed_effect_key);
    std::string getEffectName(AEGP_InstalledEffectKey installed_effect_key);
    std::string getEffectMatchName(AEGP_InstalledEffectKey installed_effect_key);
    std::string getEffectCategory(AEGP_InstalledEffectKey installed_effect_key);
    EffectRefPtr duplicateEffect(EffectRefPtr original_effect_ref);
    A_u_long numEffectMask(EffectRefPtr effect_ref);
    AEGP_MaskIDVal getEffectMaskID(EffectRefPtr effect_ref, A_u_long mask_indexL);
    // Reulsts in MaskStream?
    StreamRefPtr addEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val);
    void removeEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val);
    StreamRefPtr setEffectMask(EffectRefPtr effect_ref, A_u_long mask_indexL, AEGP_MaskIDVal id_val);
};

class MaskSuite
{
  public:
    MaskSuite(){};

    int getLayerNumMasks(LayerPtr aegp_layerH);
    MaskRefPtr getLayerMaskByIndex(LayerPtr aegp_layerH, AEGP_MaskIndex mask_indexL);
    bool getMaskInvert(MaskRefPtr mask_refH);
    void setMaskInvert(MaskRefPtr mask_refH, bool invertB);
    MaskMode getMaskMode(MaskRefPtr mask_refH);
    void setMaskMode(MaskRefPtr maskH, MaskMode mode);
    MaskMBlur getMaskMotionBlurState(MaskRefPtr mask_refH);
    void setMaskMotionBlurState(MaskRefPtr mask_refH, MaskMBlur blur_state);
    MaskFeatherFalloff getMaskFeatherFalloff(MaskRefPtr mask_refH);
    void setMaskFeatherFalloff(MaskRefPtr mask_refH, MaskFeatherFalloff feather_falloffP);
    AEGP_MaskIDVal getMaskID(MaskRefPtr mask_refH);
    MaskRefPtr createNewMask(LayerPtr layerH, int mask_indexPL0);
    void deleteMaskFromLayer(MaskRefPtr mask_refH);
    ColorVal getMaskColor(MaskRefPtr mask_refH);
    void setMaskColor(MaskRefPtr mask_refH, ColorVal colorP);
    bool getMaskLockState(MaskRefPtr mask_refH);
    void setMaskLockState(MaskRefPtr mask_refH, bool lockB);
    bool getMaskIsRotoBezier(MaskRefPtr mask_refH);
    void setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB);
    MaskRefPtr duplicateMask(MaskRefPtr orig_mask_refH);
};

class MaskOutlineSuite
{
  public:
    MaskOutlineSuite(){};

    bool isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH);
    void setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH, bool openB);
    int getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH);
    MaskVertex getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL);
    void setMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL, MaskVertex vertexP);
    void createVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex insert_position);
    void deleteVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex index);
    int getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH);
    MaskFeather getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH, AEGP_FeatherIndex which_featherL);
    void setMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_featherL,
                                   MaskFeather featherP);
    AEGP_FeatherIndex createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, MaskFeather featherP0);
    void deleteMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, AEGP_FeatherIndex index);
};

class FootageSuite
{
  public:
    FootageSuite(){};

    FootagePtr getMainFootageFromItem(ItemPtr itemH);
    FootagePtr getProxyFootageFromItem(ItemPtr itemH);
    std::tuple<int, int> getFootageNumFiles(FootagePtr footageH);
    std::string getFootagePath(FootagePtr footageH, int frame_numL, int file_indexL);
    AEGP_FootageSignature getFootageSignature(FootagePtr footageH);
    FootagePtr newFootage(std::string pathZ, AEGP_FootageLayerKey layer_infoP0,
                          AEGP_FileSequenceImportOptions *sequence_optionsP0, InterpretationStyle interp_style);
    ItemPtr addFootageToProject(FootagePtr footageH, ItemPtr folderH);
    void setItemProxyFootage(FootagePtr footageH, ItemPtr itemH);
    void replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH);
    AEGP_FootageInterp getFootageInterpretation(ItemPtr itemH, bool proxyB);
    void setFootageInterpretation(ItemPtr itemH, bool proxyB, const AEGP_FootageInterp *interpP);
    AEGP_FootageLayerKey getFootageLayerKey(FootagePtr footageH);
    FootagePtr newPlaceholderFootage(std::string nameZ, int width, int height, A_Time durationPT);
    FootagePtr newPlaceholderFootageWithPath(std::string pathZ, Platform path_platform, AEIO_FileType file_type,
                                             int widthL, int heightL, A_Time durationPT);
    FootagePtr newSolidFootage(std::string nameZ, int width, int height, ColorVal colorP);
    ColorVal getSolidFootageColor(ItemPtr itemH, bool proxyB);
    void setSolidFootageColor(ItemPtr itemH, bool proxyB, ColorVal colorP);
    void setSolidFootageDimensions(ItemPtr itemH, bool proxyB, int widthL, int heightL);
    AEGP_SoundDataFormat getFootageSoundDataFormat(FootagePtr footageH);
    AEGP_FileSequenceImportOptions getFootageSequenceImportOptions(FootagePtr footageH);
};

class UtilitySuite
{
  public:
    UtilitySuite(){};

    void reportInfo(const std::string &info_string);
    void reportInfoUnicode(const std::string &info_string);
    std::tuple<A_short, A_short> getDriverPluginInitFuncVersion();
    std::tuple<A_short, A_short> getDriverImplementationVersion();
    void startQuietErrors();
    void endQuietErrors(bool report_quieted_errorsB);
    std::string getLastErrorMessage(int buffer_size);
    void startUndoGroup(const std::string &undo_name);
    void endUndoGroup();
    void *getMainHWND();
    void showHideAllFloaters(bool include_tool_palB);
    ColorVal getPaintPalForeColor();                    /*Brush Tool Panel*/
    ColorVal getPaintPalBackColor();                    /*Brush Tool Panel*/
    void setPaintPalForeColor(ColorVal fore_color);     /*Brush Tool Panel*/
    void setPaintPalBackColor(ColorVal back_color);     /*Brush Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalFillColor();   /*Character Tool Panel*/
    std::tuple<bool, ColorVal> getCharPalStrokeColor(); /*Character Tool Panel*/
    void setCharPalFillColor(ColorVal fill_color);      /*Character Tool Panel*/
    void setCharPalStrokeColor(ColorVal stroke_color);  /*Character Tool Panel*/
    bool charPalIsFillColorUIFrontmost();               /*Returns whether or not the fill
                                                           color is frontmost. If it isn’t,
                                                           the stroke color is frontmost.*/
    A_Ratio convertFpLongToHSFRatio(double numberF);
    double convertHSFRatioToFpLong(A_Ratio ratioR);
    void causeIdleRoutinesToBeCalled();
    bool getSuppressInteractiveUI();
    void writeToOSConsole(const std::string &text);
    void writeToDebugLog(const std::string &subsystem, const std::string &eventType, const std::string &text);
    std::string getPluginPath(PluginPathType path_type);
};

class RenderQueueSuite
{
  public:
    RenderQueueSuite(){};

    void addCompToRenderQueue(CompPtr comp, const std::string &path);
    void setRenderQueueState(RenderQueueState state);
    RenderQueueState getRenderQueueState();
};

class RenderQueueItemSuite
{
  public:
    RenderQueueItemSuite(){};

    int getNumRQItems();
    RQItemRefPtr getRQItemByIndex(int rq_item_index);
    RQItemRefPtr getNextRQItem(RQItemRefPtr current_rq_item);
    int getNumOutputModulesForRQItem(RQItemRefPtr rq_item);
    RenderItemStatus getRenderState(RQItemRefPtr rq_item);
    void setRenderState(RQItemRefPtr rq_item, RenderItemStatus status);
    A_Time getStartedTime(RQItemRefPtr rq_item);
    A_Time getElapsedTime(RQItemRefPtr rq_item);
    LogType getLogType(RQItemRefPtr rq_item);
    void setLogType(RQItemRefPtr rq_item, LogType logtype);
    void removeOutputModule(RQItemRefPtr rq_item, OutputModuleRefPtr outmod);
    std::string getComment(RQItemRefPtr rq_item);
    void setComment(RQItemRefPtr rq_item, const std::string &comment);
    CompPtr getCompFromRQItem(RQItemRefPtr rq_item);
    void deleteRQItem(RQItemRefPtr rq_item);
};

class OutputModuleSuite
{
  public:
    OutputModuleSuite(){};

    OutputModuleRefPtr getOutputModuleByIndex(RQItemRefPtr rq_itemH, int outmod_indexL);
    EmbeddingType getEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, EmbeddingType embed_options);
    PostRenderAction getPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, PostRenderAction post_render_action);
    OutputTypes getEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, OutputTypes enabled_types);
    VideoChannels getOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, VideoChannels output_channels);
    std::tuple<bool, StretchQuality, bool> getStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool is_enabledB,
                        StretchQuality stretch_quality);
    std::tuple<bool, LRect> getCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool enableB, LRect crop_rect);
    std::tuple<AEGP_SoundDataFormat, bool> getSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, AEGP_SoundDataFormat sound_format_info,
                            bool audio_enabledB);
    std::string getOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH);
    void setOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, const std::string &path);
    OutputModuleRefPtr addDefaultOutputModule(RQItemRefPtr rq_itemH);
    std::tuple<std::string, std::string, bool, bool> getExtraOutputModuleInfo(RQItemRefPtr rq_itemH,
                                                                              OutputModuleRefPtr outmodH);
};

class WorldSuite
{
  public:
    WorldSuite(){};

    WorldPtr newWorld(WorldType type, int widthL, int heightL);
    WorldType getType(WorldPtr worldH);
    std::tuple<int, int> getSize(WorldPtr worldH);
    A_u_long getRowBytes(WorldPtr worldH);
    PF_Pixel8 *getBaseAddr8(WorldPtr worldH);
    PF_Pixel16 *getBaseAddr16(WorldPtr worldH);
    PF_PixelFloat *getBaseAddr32(WorldPtr worldH);
    PF_EffectWorld fillOutPFEffectWorld(WorldPtr worldH);
    void fastBlur(double radiusF, PF_ModeFlags mode, PF_Quality quality, WorldPtr worldH);
    PlatformWorldPtr newPlatformWorld(AEGP_WorldType type, int widthL, int heightL);
    WorldPtr newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH);
};

class RenderOptionsSuite
{
  public:
    RenderOptionsSuite(){};

    RenderOptionsPtr newFromItem(ItemPtr itemH);
    RenderOptionsPtr duplicate(RenderOptionsPtr optionsH);
    void setTime(RenderOptionsPtr optionsH, A_Time time);
    A_Time getTime(RenderOptionsPtr optionsH);
    void setTimeStep(RenderOptionsPtr optionsH, A_Time time_step);
    A_Time getTimeStep(RenderOptionsPtr optionsH);
    void setFieldRender(RenderOptionsPtr optionsH, PF_Field field_render);
    PF_Field getFieldRender(RenderOptionsPtr optionsH);
    void setWorldType(RenderOptionsPtr optionsH, WorldType type);
    WorldType getWorldType(RenderOptionsPtr optionsH);
    void setDownsampleFactor(RenderOptionsPtr optionsH, DownsampleFactor downsample_factor);
    DownsampleFactor getDownsampleFactor(RenderOptionsPtr optionsH);
    void setRegionOfInterest(RenderOptionsPtr optionsH, LRect roiP);
    LRect getRegionOfInterest(RenderOptionsPtr optionsH);
    void setMatteMode(RenderOptionsPtr optionsH, MatteMode mode);
    MatteMode getMatteMode(RenderOptionsPtr optionsH);
    void setChannelOrder(RenderOptionsPtr optionsH, ChannelOrder channel_order);
    ChannelOrder getChannelOrder(RenderOptionsPtr optionsH);
    bool getRenderGuideLayers(RenderOptionsPtr optionsH);
    void setRenderGuideLayers(RenderOptionsPtr optionsH, bool render_themB);
};

class LayerRenderOptionsSuite
{
  public:
    LayerRenderOptionsSuite(){};

    LayerRenderOptionsPtr newFromLayer(LayerPtr layer);
    LayerRenderOptionsPtr newFromUpstreamOfEffect(EffectRefPtr effect_ref);
    LayerRenderOptionsPtr newFromDownstreamOfEffect(EffectRefPtr effect_ref);
    LayerRenderOptionsPtr duplicate(LayerRenderOptionsPtr optionsH);

    void setTime(LayerRenderOptionsPtr optionsH, A_Time time);
    A_Time getTime(LayerRenderOptionsPtr optionsH);
    void setTimeStep(LayerRenderOptionsPtr optionsH, A_Time time_step);
    A_Time getTimeStep(LayerRenderOptionsPtr optionsH);
    void setWorldType(LayerRenderOptionsPtr optionsH, WorldType type);
    WorldType getWorldType(LayerRenderOptionsPtr optionsH);
    void setDownsampleFactor(LayerRenderOptionsPtr optionsH, DownsampleFactor dsf);
    DownsampleFactor getDownsampleFactor(LayerRenderOptionsPtr optionsH);
    void setMatteMode(LayerRenderOptionsPtr optionsH, MatteMode mode);
    MatteMode getMatteMode(LayerRenderOptionsPtr optionsH);
};

class RenderSuite
{
  public:
    RenderSuite(){};

    FrameReceiptPtr renderAndCheckoutFrame(RenderOptionsPtr optionsH);

    FrameReceiptPtr renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH);

    A_u_longlong renderAndCheckoutLayerFrameAsync(LayerRenderOptionsPtr optionsH,
                                                  AEGP_AsyncFrameReadyCallback callback);

    void cancelAsyncRequest(AEGP_AsyncRequestId async_request_id);

    WorldPtr getReceiptWorld(FrameReceiptPtr receiptH);

    LRect getRenderedRegion(FrameReceiptPtr receiptH);

    bool isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH, RenderOptionsPtr proposed_optionsH);
    TimeStampPtr getCurrentTimestamp();

    bool hasItemChangedSinceTimestamp(ItemPtr itemH, A_Time start_timeP, A_Time durationP, TimeStampPtr time_stampP);

    bool isItemWorthwhileToRender(RenderOptionsPtr roH, TimeStampPtr time_stampP);

    void checkinRenderedFrame(RenderOptionsPtr roH, TimeStampPtr time_stampP, A_u_long ticks_to_renderL,
                              PlatformWorldPtr imageH);

    std::string getReceiptGuid(FrameReceiptPtr receiptH);
};

class CollectionSuite
{
  public:
    CollectionSuite(){};

    Collection2Ptr newCollection();
    int getCollectionNumItems(Collection2Ptr collectionH);
    AEGP_CollectionItemV2 getCollectionItemByIndex(Collection2Ptr collectionH, int indexL);
    void collectionPushBack(Collection2Ptr collectionH, const AEGP_CollectionItemV2 &itemP);
    void collectionErase(Collection2Ptr collectionH, int index_firstL, int index_lastL);
};

class RegisterSuite
{
  public:
    RegisterSuite(){};

    void registerCommandHook(AEGP_HookPriority hook_priority, AEGP_Command command, AEGP_CommandHook command_hook_func,
                             AEGP_CommandRefcon refconP);
    void registerUpdateMenuHook(AEGP_UpdateMenuHook update_menu_hook_func, AEGP_UpdateMenuRefcon refconP);
    void registerDeathHook(AEGP_DeathHook death_hook_func, AEGP_DeathRefcon refconP);
    void registerIdleHook(AEGP_IdleHook idle_hook_func, AEGP_IdleRefcon refconP);
    void registerPresetLocalizationString(const std::string &english_nameZ, const std::string &localized_nameZ);
};

class CommandSuite
{
  public:
    CommandSuite(){};

    AEGP_Command getUniqueCommand();
    void insertMenuCommand(AEGP_Command command, const std::string &nameZ, MenuID menu_id, int after_itemL);
    void removeMenuCommand(AEGP_Command command);
    void setMenuCommandName(AEGP_Command command, const std::string &nameZ);
    void enableCommand(AEGP_Command command);
    void disableCommand(AEGP_Command command);
    void checkMarkMenuCommand(AEGP_Command command, bool checkB);
    void doCommand(AEGP_Command command);
};

inline double TimeToSeconds(const A_Time &time)
{
    // Scale the value to move the decimal two places to the right
    double scaledValue = static_cast<double>(time.value) * 100.0 / static_cast<double>(time.scale);

    // Round the scaled value to the nearest integer
    double rounded = std::round(scaledValue);

    // Scale the rounded value back down
    return rounded / 100.0;
} // Will find active comp and convert using frame rate

inline A_Time SecondsToTime(double seconds)
{
    double frameRate = CompSuite().GetCompFramerate(CompSuite().GetMostRecentlyUsedComp());
    A_u_long scale = static_cast<A_u_long>(frameRate);
    return {static_cast<int>(std::round(seconds * scale)), scale};
}

inline int TimeToFrames(const A_Time &time)
{
    double seconds = TimeToSeconds(time);
    double frameRate = CompSuite().GetCompFramerate(CompSuite().GetMostRecentlyUsedComp());
    return static_cast<int>(std::round(seconds * frameRate));
}

inline A_Time FramesToTime(int frames)
{
    double frameRate = CompSuite().GetCompFramerate(CompSuite().GetMostRecentlyUsedComp());
    A_u_long scale = static_cast<A_u_long>(frameRate);
    return {frames, scale};
}



#endif // SUITES_HPP
