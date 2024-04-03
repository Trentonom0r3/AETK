/*****************************************************************/ /**
                                                                     * \file
                                                                     *Misc.hpp
                                                                     * \brief
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef MISC_HPP
#define MISC_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

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
    Marker(MarkerValPtr markerP) : m_markerP(markerP), m_markerSuite(MarkerSuite3()) {}

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
    void setFlag(AEGP_MarkerFlagType flagType, bool valueB);

    /**
     * @brief Retrieves the value of the specified flag for the marker.
     *
     * @param flagType The flag type to query.
     * @return bool The value of the specified flag.
     */
    bool getFlag(AEGP_MarkerFlagType flagType);

    /**
     * @brief Retrieves the string value of the specified type for the marker.
     *
     * @param strType The string type to query.
     * @return std::string The string value of the specified type.
     */
    std::string getString(AE_MarkerStringType strType);

    /**
     * @brief Sets the string value of the specified type for the marker.
     *
     * @param strType The string type to set.
     * @param unicodeP The new string value.
     * @param lengthL The length of the new string value.
     */
    void setString(AE_MarkerStringType strType, const std::string &unicodeP, A_long lengthL);

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
    void setIndCuePointParam(int param_indexL, const std::string &unicodeKeyP, A_long key_lengthL,
                             const std::string &unicodeValueP, A_long value_lengthL);

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
    MarkerSuite3 m_markerSuite;
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
    MaskOutline(MaskOutlineValPtr mask_outlineP)
        : m_mask_outlineP(mask_outlineP), m_maskOutlineSuite(MaskOutlineSuite3()){};
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
    void setVertexInfo(int which_pointL,
                       MaskVertex vertexP);     

/**
* @brief Creates a new vertex at the specified position.
* 
* @param insert_position The position at which to insert the new vertex.
*/
    void createVertex(int insert_position);         // Creates a new vertex at the specified position
   /**
   * @brief Deletes the vertex at the specified index.
   * 
   * @param index The index of the vertex to delete.
   */
    void deleteVertex(int index);                   // Deletes the vertex at the specified index
    
    /**
     * @brief Returns the number of feathers in the mask.
     */
    int numFeathers();                              // Returns the number of feathers in the mask
    
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
    FeatherInfo getFeatherInfo(int which_featherL); // Returns the feather information for
                                                    // the specified feather
    /**
     * @brief Sets the feather information for the specified feather.
     * 
     * \param which_featherL
     * \param featherP
     */
    void setFeatherInfo(int which_featherL,
                        FeatherInfo featherP); // Sets the feather information
                                               // for the specified feather

/**
* @brief Creates a new feather with the specified information.
* 
* @param featherP0 The information for the new feather.
* 
* @return int The index of the newly created feather.
*/
    int createFeather(FeatherInfo featherP0);  // Creates a new feather with the
                                               // specified information
    /**
	 * @brief Deletes the feather at the specified index.
	 * 
	 * @param index The index of the feather to delete.
	 */
    void deleteFeather(int index);             // Deletes the feather at the specified index

  private:
    MaskOutlineValPtr m_mask_outlineP;
    MaskOutlineSuite3 m_maskOutlineSuite;
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
    TextDocument(TextDocumentPtr text_documentP)
        : m_text_documentP(text_documentP), m_textDocumentSuite(TextDocumentSuite1()){};
    ~TextDocument() = default;

    /**
	 * @brief Returns the text of the document.
	 *
	 * @return std::string The text of the document.
	 */
    std::string getText();                      // Returns the text of the document

    /**
     * @brief Sets the text of the document.
     * 
     * @param unicodePS The new text of the document.
     */
    void setText(const std::string &unicodePS); // Sets the text of the document

  private:
    TextDocumentPtr m_text_documentP;
    TextDocumentSuite1 m_textDocumentSuite;
};

/**
 * @class AssetManager
 * @brief Manages assets within an After Effects project.
 *
 * Provides methods to import assets, organize them based on various criteria,
 * replace existing assets with new ones, and find assets based on custom predicates.
 */

class AssetManager
{
  public:
    AssetManager(){};

    /**
     * @brief Imports an asset into the project.
     * 
     * \param filePath
     * \param name
     * \return ItemPtr to the imported asset.
     */
    ItemPtr import(const std::string &filePath, const std::string &name = "");

    // Organizes assets into folders based on type (e.g., footage, audio) or
    // custom criteria, would require ItemCollection to be implemented
   // void organizeAssets(const std::function<bool(const ItemPtr &)> &criteria);

    //** Replaces an existing asset with a new one */
    void replaceAsset(const ItemPtr &oldAsset, const std::string &newFilePath);

    // Finds assets based on a predicate function
    // Will require ItemCollection to be implemented
   // std::vector<ItemPtr> findAssets(const std::function<bool(const ItemPtr &)> &predicate);

  protected:
    static inline AEGP_FootageLayerKey layerkey(const std::string &name)
    {
        AEGP_FootageLayerKey layer_key;
        layer_key.layer_idL = AEGP_LayerID_UNKNOWN;
        layer_key.layer_indexL = AEGP_LayerIndex_MERGED;
        layer_key.layer_draw_style = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS;

        strncpy_s(layer_key.nameAC, name.c_str(), AEGP_FOOTAGE_LAYER_NAME_LEN);
        layer_key.nameAC[AEGP_FOOTAGE_LAYER_NAME_LEN] = '\0'; // Ensure null termination

        return layer_key;
    }

    static inline AEGP_FileSequenceImportOptions sequence()
    {
        AEGP_FileSequenceImportOptions options;
        options.all_in_folderB = TRUE;
        options.force_alphabeticalB = TRUE;
        options.start_frameL = AEGP_ANY_FRAME;
        options.end_frameL = AEGP_ANY_FRAME;
        return options;
    }
};

/**
 * @class KeyFrame
 * @brief Represents a keyframe in After Effects.
 *
 * Allows for the creation and manipulation of keyframes, including setting
 * their time, value, interpolation type, flags, easing, and tangents.
 */
class KeyFrame
{
  public:
    // Using std::variant to accommodate different tangent types.
    using TangentValue = std::variant<std::monostate, double, TwoDVal, ThreeDVal, ColorVal>;
    double time;
    TangentValue value = std::monostate(); // Value of the keyframe

    std::optional<std::pair<AE_KeyInterp, AE_KeyInterp>> interp; // Interpolation for in/out
    std::vector<AE_KeyframeFlag> flags = {};                     // Flags for the keyframe
    std::optional<AE_KeyframeEase> easeIn,
        easeOut;                                         // Ease in/out values (std::tuple<double,double>)
    std::optional<std::pair<TangentValue, TangentValue>> // In/out
        tangents;                                        // Pair of in/out tangents

    KeyFrame(double time) : time(time) {}
    KeyFrame(double time, TangentValue value) : time(time), value(value){};
    KeyFrame &setInterpolation(AE_KeyInterp inInterp, AE_KeyInterp outInterp)
    {
        interp.emplace(std::make_pair(inInterp, outInterp));
        return *this;
    }

    KeyFrame &setEaseIn(double speed, double influence)
    {
        easeIn.emplace(AE_KeyframeEase{speed, influence});
        return *this;
    }

    KeyFrame &setEaseOut(double speed, double influence)
    {
        easeOut.emplace(AE_KeyframeEase{speed, influence});
        return *this;
    }

    KeyFrame &setFlag(AE_KeyframeFlag keyframeFlags)
    {
        flags.push_back(keyframeFlags);
        return *this;
    }

    // Templated method to set tangents with type checking at compile time
    template <typename T> KeyFrame &setTangents(T inTan, T outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(double inTan, double outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(TwoDVal inTan, TwoDVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(ThreeDVal inTan, ThreeDVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setTangents(ColorVal inTan, ColorVal outTan)
    {
        tangents.emplace(std::make_pair(inTan, outTan));
        return *this;
    }

    KeyFrame &setValue(double value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(KeyFrame::TangentValue value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(TwoDVal value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(ThreeDVal value)
    {
        this->value = value;
        return *this;
    }

    KeyFrame &setValue(ColorVal value)
    {
        this->value = value;
        return *this;
    }

    std::string toString() const
    {
        std::ostringstream os;

        // Time
        os << "Time: " << time << "\n";

        // Value
        os << "Value: ";
        std::visit(
            overloaded{[&](double val) { os << val; },
                       [&](const TwoDVal &val) { os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ")"; },
                       [&](const ThreeDVal &val) {
                           os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ")";
                       },
                       [&](const ColorVal &val) {
                           os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ", "
                              << std::get<3>(val) << ")";
                       },
                       [&](std::monostate) { os << "none"; }},
            value);
        os << "\n";

        // Interpolation
        if (interp.has_value())
        {
            os << "Interpolation: In - " << toInterpString(std::get<0>(interp.value())) << ", Out - "
               << toInterpString(std::get<1>(interp.value())) << "\n";
        }

        // Flags
        if (!flags.empty())
        {
            os << "Flags: ";
            for (auto &flag : flags)
            {
                os << toFlagString(flag) << " ";
            }
            os << "\n";
        }

        // Ease In/Out
        if (easeIn.has_value())
        {
            os << "Ease In: Speed - " << std::get<0>(easeIn.value()) << ", Influence - " << std::get<1>(easeIn.value())
               << "\n";
        }
        if (easeOut.has_value())
        {
            os << "Ease Out: Speed - " << std::get<0>(easeOut.value()) << ", Influence - "
               << std::get<1>(easeOut.value()) << "\n";
        }

        // Tangents
        if (tangents.has_value())
        {
            os << "Tangents: In - ";
            std::visit(
                [&os](const auto &val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, double>)
                    {
                        os << val;
                    }
                    else if constexpr (std::is_same_v<T, TwoDVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ")";
                    }
                    else if constexpr (std::is_same_v<T, ThreeDVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ")";
                    }
                    else if constexpr (std::is_same_v<T, ColorVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ", "
                           << std::get<3>(val) << ")";
                    }
                },
                tangents.value().first);

            os << ", Out - ";
            std::visit(
                [&os](const auto &val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, double>)
                    {
                        os << val;
                    }
                    else if constexpr (std::is_same_v<T, TwoDVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ")";
                    }
                    else if constexpr (std::is_same_v<T, ThreeDVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ")";
                    }
                    else if constexpr (std::is_same_v<T, ColorVal>)
                    {
                        os << "(" << std::get<0>(val) << ", " << std::get<1>(val) << ", " << std::get<2>(val) << ", "
                           << std::get<3>(val) << ")";
                    }
                },
                tangents.value().second);
            os << "\n";
        }

        return os.str();
    }

  private:
    std::string toInterpString(AE_KeyInterp interp) const
    {
        switch (interp)
        {
        case AE_KeyInterp::LINEAR:
            return "Linear";
        case AE_KeyInterp::BEZIER:
            return "Bezier";
        case AE_KeyInterp::HOLD:
            return "Hold";
        default:
            return "None";
        }
    }

    std::string toFlagString(AE_KeyframeFlag flag) const
    {
        switch (flag)
        {
        case AE_KeyframeFlag::TEMPORAL_CONTINUOUS:
            return "Temporal Continuous";
        case AE_KeyframeFlag::TEMPORAL_AUTOBEZIER:
            return "Temporal AutoBezier";
        case AE_KeyframeFlag::SPATIAL_CONTINUOUS:
            return "Spatial Continuous";
        case AE_KeyframeFlag::SPATIAL_AUTOBEZIER:
            return "Spatial AutoBezier";
        case AE_KeyframeFlag::ROVING:
            return "Roving";
        default:
            return "None";
        }
    }
};

#endif // MISC_HPP
