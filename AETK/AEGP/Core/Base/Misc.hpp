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
 * @brief A class Representing a Marker in After Effects.
 */
class Marker
{
  public:
    Marker() = default;
    Marker(MarkerValPtr markerP)
        : m_markerP(markerP), m_markerSuite(MarkerSuite3()){};
    ~Marker() = default;

    static Marker createMarker(); // Creates a new marker
    Marker duplicateMarker(); // Duplicates the marker
    void setFlag(AEGP_MarkerFlagType flagType, bool valueB); // Sets the value of the specified flag
    bool getFlag(AEGP_MarkerFlagType flagType); // Returns the value of the specified flag
    std::string getString(AE_MarkerStringType strType); // Returns the string value of the specified type
    void setString(AE_MarkerStringType strType, const std::string &unicodeP,
                   A_long lengthL); // Sets the string value of the specified type
    int countCuePointParams(); // Returns the number of cue point parameters
    std::tuple<std::string, std::string> getIndCuePointParam(int param_indexL); // Returns the key and value of the specified cue point parameter
    void setIndCuePointParam(int param_indexL, const std::string &unicodeKeyP,
                             A_long key_lengthL,
                             const std::string &unicodeValueP,
                             A_long value_lengthL); // Sets the key and value of the specified cue point parameter
    void insertCuePointParam(int param_indexL); // Inserts a new cue point parameter
    void deleteIndCuePointParam(int param_indexL); // Deletes the specified cue point parameter
    void setDuration(double durationD); // Sets the duration of the marker
    double getDuration(); // Returns the duration of the marker
    void setLabel(int value); // Sets the label of the marker
    int getLabel(); // Returns the label of the marker

  private:
    MarkerValPtr m_markerP;
    MarkerSuite3 m_markerSuite;
};

/**
 * @brief A class representing a Mask Outline in After Effects.
 * 
 */
class MaskOutline
{
  public:
    MaskOutline() = default;
    MaskOutline(MaskOutlineValPtr mask_outlineP)
        : m_mask_outlineP(mask_outlineP),
          m_maskOutlineSuite(MaskOutlineSuite3()){};
    ~MaskOutline() = default;

    bool isOpen(); // Returns true if the mask is open, false if it is closed
    void setOpen(bool openB); // Sets the mask to open or closed
    int numSegments(); // Returns the number of segments in the mask
    MaskVertex getVertexInfo(int which_pointL); // Returns the vertex information for the specified point
    void setVertexInfo(int which_pointL, MaskVertex vertexP); // Sets the vertex information for the specified point
    void createVertex(int insert_position); // Creates a new vertex at the specified position
    void deleteVertex(int index); // Deletes the vertex at the specified index
    int numFeathers(); // Returns the number of feathers in the mask
    FeatherInfo getFeatherInfo(int which_featherL); // Returns the feather information for the specified feather
    void setFeatherInfo(int which_featherL, FeatherInfo featherP); // Sets the feather information for the specified feather
    int createFeather( FeatherInfo featherP0); // Creates a new feather with the specified information
    void deleteFeather(int index); // Deletes the feather at the specified index

  private:
    MaskOutlineValPtr m_mask_outlineP;
    MaskOutlineSuite3 m_maskOutlineSuite;
};

class TextDocument
{
  public:
    TextDocument(TextDocumentPtr text_documentP)
	  : m_text_documentP(text_documentP),
		m_textDocumentSuite(TextDocumentSuite1()){};
  ~TextDocument() = default;

  std::string getText(); // Returns the text of the document
  void setText(const std::string &unicodePS); // Sets the text of the document

  private:
  TextDocumentPtr m_text_documentP;
  TextDocumentSuite1 m_textDocumentSuite;

};

class AssetManager
{
public:
  AssetManager(){};
  // Imports an asset into the project, returning a handle to the imported asset
  ItemPtr import(const std::string &filePath, const std::string &name = "");

  // Organizes assets into folders based on type (e.g., footage, audio) or
  // custom criteria, would require ItemCollection to be implemented
  void organizeAssets(const std::function<bool(const ItemPtr &)> &criteria);

  // Replaces an existing asset with a new one
  void replaceAsset(const ItemPtr &oldAsset, const std::string &newFilePath);

  // Finds assets based on a predicate function
  // Will require ItemCollection to be implemented
  std::vector<ItemPtr>
  findAssets(const std::function<bool(const ItemPtr &)> &predicate);

protected:
  static inline AEGP_FootageLayerKey layerkey(const std::string &name)
  {
      AEGP_FootageLayerKey layer_key;
      layer_key.layer_idL = AEGP_LayerID_UNKNOWN;
      layer_key.layer_indexL = AEGP_LayerIndex_MERGED;
      layer_key.layer_draw_style = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS;

      strncpy_s(layer_key.nameAC, name.c_str(), AEGP_FOOTAGE_LAYER_NAME_LEN);
      layer_key.nameAC[AEGP_FOOTAGE_LAYER_NAME_LEN] =
          '\0'; // Ensure null termination

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

#endif // MISC_HPP
