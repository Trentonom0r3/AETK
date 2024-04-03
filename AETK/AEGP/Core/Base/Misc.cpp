#include "Misc.hpp"

Marker Marker::createMarker(){
    auto marker = MarkerSuite3().getNewMarker();
    return Marker(marker);
}

Marker Marker::duplicateMarker()
{
    auto marker = MarkerSuite3().duplicateMarker(m_markerP);
    return Marker(marker);
}

void Marker::setFlag(AEGP_MarkerFlagType flagType, bool valueB) {
    m_markerSuite.setMarkerFlag(m_markerP, flagType, valueB);
}

bool Marker::getFlag(AEGP_MarkerFlagType flagType)
{
    return m_markerSuite.getMarkerFlag(m_markerP, flagType);
}

std::string Marker::getString(AE_MarkerStringType strType)
{
    return m_markerSuite.getMarkerString(m_markerP, strType);
}

void Marker::setString(AE_MarkerStringType strType, const std::string &unicodeP,
                       A_long lengthL)
{
    	m_markerSuite.setMarkerString(m_markerP, strType, unicodeP.c_str(), lengthL);
}

int Marker::countCuePointParams()
{
    return m_markerSuite.countCuePointParams(m_markerP);
}

std::tuple<std::string, std::string>
Marker::getIndCuePointParam(int param_indexL)
{
    return m_markerSuite.getIndCuePointParam(m_markerP, param_indexL);
}

void Marker::setIndCuePointParam(int param_indexL,
                                 const std::string &unicodeKeyP,
                                 A_long key_lengthL,
                                 const std::string &unicodeValueP,
                                 A_long value_lengthL)
{
    m_markerSuite.setIndCuePointParam(m_markerP, param_indexL, unicodeKeyP,
        									  key_lengthL, unicodeValueP,
        									  value_lengthL);
}

void Marker::insertCuePointParam(int param_indexL) {
    m_markerSuite.insertCuePointParam(m_markerP, param_indexL);
}

void Marker::deleteIndCuePointParam(int param_indexL) {
    m_markerSuite.deleteIndCuePointParam(m_markerP, param_indexL);
}


void Marker::setDuration(double durationD) {
    m_markerSuite.setMarkerDuration(m_markerP, SecondsToTime(durationD));
}

double Marker::getDuration()
{
    return TimeToSeconds(m_markerSuite.getMarkerDuration(m_markerP));
}

void Marker::setLabel(int value) {
    m_markerSuite.setMarkerLabel(m_markerP, value);
}

int Marker::getLabel()
{
    return m_markerSuite.getMarkerLabel(m_markerP);
}

bool MaskOutline::isOpen()
{
    return m_maskOutlineSuite.isMaskOutlineOpen(m_mask_outlineP);
}

void MaskOutline::setOpen(bool openB) {
    m_maskOutlineSuite.setMaskOutlineOpen(m_mask_outlineP, openB);
}

int MaskOutline::numSegments()
{
    return m_maskOutlineSuite.getMaskOutlineNumSegments(m_mask_outlineP);
}

MaskVertex MaskOutline::getVertexInfo(int which_pointL)
{
    auto vertex = m_maskOutlineSuite.getMaskOutlineVertexInfo(m_mask_outlineP, which_pointL);
    return MaskVertex(vertex);
}

void MaskOutline::setVertexInfo(int which_pointL,MaskVertex vertexP) {
    m_maskOutlineSuite.setMaskOutlineVertexInfo(m_mask_outlineP, which_pointL,
                                                vertexP.toPF_PathVertex());
}

void MaskOutline::createVertex(int insert_position) {
    m_maskOutlineSuite.createVertex(m_mask_outlineP, insert_position);
}

void MaskOutline::deleteVertex(int index) {
    m_maskOutlineSuite.deleteVertex(m_mask_outlineP, index);
}

int MaskOutline::numFeathers()
{
    return m_maskOutlineSuite.getMaskOutlineNumFeathers(m_mask_outlineP);
}

FeatherInfo MaskOutline::getFeatherInfo(int which_featherL)
{
    auto feather = m_maskOutlineSuite.getMaskOutlineFeatherInfo(m_mask_outlineP, which_featherL);
    return FeatherInfo(feather);
}

void MaskOutline::setFeatherInfo(int which_featherL,
                                  FeatherInfo featherP)
{
    m_maskOutlineSuite.setMaskOutlineFeatherInfo(m_mask_outlineP, which_featherL,
        												 featherP.toAEGP_MaskFeather());
}

int MaskOutline::createFeather( FeatherInfo featherP0)
{
    return m_maskOutlineSuite.createMaskOutlineFeather(m_mask_outlineP, featherP0.toAEGP_MaskFeather());
}

void MaskOutline::deleteFeather(int index) {
	m_maskOutlineSuite.deleteMaskOutlineFeather(m_mask_outlineP, index);
}

std::string TextDocument::getText()
{
    return m_textDocumentSuite.getNewText(m_text_documentP);
}

void TextDocument::setText(const std::string &unicodePS) {
    m_textDocumentSuite.setText(m_text_documentP, unicodePS);
}

ItemPtr AssetManager::import(const std::string &filePath,
                             const std::string &name)
{
    FootageSuite5 suite;
    ItemPtr item;
    FootagePtr footage;
    /*
    A Few Conditions here:
    1. We need to first see if the filePath has an extension. if not, its a
  folder, and thus a sequence.
  2. If it does have an extension, we pas NULL for sequence options.
    */
    if (filePath.find(".") != std::string::npos)
    {
        // This is a single file
        footage = suite.newFootage(filePath, AssetManager::layerkey(name), NULL,
                                   AE_InterpretationStyle::NO_DIALOG_NO_GUESS);
    }
    else
    {
        // This is a sequence
        footage = suite.newFootage(filePath, AssetManager::layerkey(name),
                                   &AssetManager::sequence(),
                                   AE_InterpretationStyle::NO_DIALOG_NO_GUESS);
    }
    if (footage.get())
    {
        item = suite.addFootageToProject(
            footage, ProjSuite6().GetProjectRootFolder(
                         ProjSuite6().GetProjectByIndex(0)));
    }
    return item;
}

void AssetManager::replaceAsset(const ItemPtr &oldAsset,
                                const std::string &newFilePath)
{
    FootageSuite5 suite;
    ItemPtr newFootage = AssetManager::import(newFilePath, "");
    if (newFootage.get())
    {
        // suite.replaceItemMainFootage(oldAsset, newFootage);
    }
    else
    {
        throw AEException("Failed to import new footage");
    }
}
