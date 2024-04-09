#include <AETK/AEGP/Core/Suites.hpp>
#include <AETK/AEGP/Core/Types.hpp>
#include <AETK/AEGP/Util/Factories.hpp>

Marker Marker::createMarker()
{
    auto marker = MarkerSuite().getNewMarker();
    return Marker(marker);
}

Marker Marker::duplicateMarker()
{
    auto marker = MarkerSuite().duplicateMarker(m_markerP);
    return Marker(marker);
}

void Marker::setFlag(AEGP_MarkerFlagType flagType, bool valueB)
{
    MarkerSuite().setMarkerFlag(m_markerP, flagType, valueB);
}

bool Marker::getFlag(AEGP_MarkerFlagType flagType)
{
    return MarkerSuite().getMarkerFlag(m_markerP, flagType);
}

std::string Marker::getString(MarkerStringType strType)
{
    return MarkerSuite().getMarkerString(m_markerP, strType);
}

void Marker::setString(MarkerStringType strType, const std::string &unicodeP)
{
    MarkerSuite().setMarkerString(m_markerP, strType, unicodeP);
}

int Marker::countCuePointParams()
{
    return MarkerSuite().countCuePointParams(m_markerP);
}

std::tuple<std::string, std::string> Marker::getIndCuePointParam(int param_indexL)
{
    return MarkerSuite().getIndCuePointParam(m_markerP, param_indexL);
}

void Marker::setIndCuePointParam(int param_indexL, const std::string &unicodeKeyP, const std::string &unicodeValueP)
{
    MarkerSuite().setIndCuePointParam(m_markerP, param_indexL, unicodeKeyP, unicodeValueP);
}

void Marker::insertCuePointParam(int param_indexL)
{
    MarkerSuite().insertCuePointParam(m_markerP, param_indexL);
}

void Marker::deleteIndCuePointParam(int param_indexL)
{
    MarkerSuite().deleteIndCuePointParam(m_markerP, param_indexL);
}

void Marker::setDuration(double durationD)
{
    MarkerSuite().setMarkerDuration(m_markerP, SecondsToTime(durationD));
}

double Marker::getDuration()
{
    return TimeToSeconds(MarkerSuite().getMarkerDuration(m_markerP));
}

void Marker::setLabel(int value)
{
    MarkerSuite().setMarkerLabel(m_markerP, value);
}

int Marker::getLabel()
{
    return MarkerSuite().getMarkerLabel(m_markerP);
}

bool MaskOutline::isOpen()
{
    return MaskOutlineSuite().isMaskOutlineOpen(m_mask_outlineP);
}

void MaskOutline::setOpen(bool openB)
{
    MaskOutlineSuite().setMaskOutlineOpen(m_mask_outlineP, openB);
}

int MaskOutline::numSegments()
{
    return MaskOutlineSuite().getMaskOutlineNumSegments(m_mask_outlineP);
}

MaskVertex MaskOutline::getVertexInfo(int which_pointL)
{
    auto vertex = MaskOutlineSuite().getMaskOutlineVertexInfo(m_mask_outlineP, which_pointL);
    return MaskVertex(vertex);
}

void MaskOutline::setVertexInfo(int which_pointL, MaskVertex vertexP)
{
    MaskOutlineSuite().setMaskOutlineVertexInfo(m_mask_outlineP, which_pointL, vertexP.ToAEGPMaskVertex());
}

void MaskOutline::createVertex(int insert_position)
{
    MaskOutlineSuite().createVertex(m_mask_outlineP, insert_position);
}

void MaskOutline::deleteVertex(int index)
{
    MaskOutlineSuite().deleteVertex(m_mask_outlineP, index);
}

int MaskOutline::numFeathers()
{
    return MaskOutlineSuite().getMaskOutlineNumFeathers(m_mask_outlineP);
}

MaskFeather MaskOutline::getFeatherInfo(int which_featherL)
{
    auto feather = MaskOutlineSuite().getMaskOutlineFeatherInfo(m_mask_outlineP, which_featherL);
    return MaskFeather(feather);
}

void MaskOutline::setFeatherInfo(int which_featherL, MaskFeather featherP)
{
    MaskOutlineSuite().setMaskOutlineFeatherInfo(m_mask_outlineP, which_featherL, featherP.ToAEGPMaskFeather());
}

int MaskOutline::createFeather(MaskFeather featherP0)
{
    return MaskOutlineSuite().createMaskOutlineFeather(m_mask_outlineP, featherP0.ToAEGPMaskFeather());
}

void MaskOutline::deleteFeather(int index)
{
    MaskOutlineSuite().deleteMaskOutlineFeather(m_mask_outlineP, index);
}

std::string TextDocument::getText()
{
    return TextDocumentSuite().getNewText(m_text_documentP);
}

void TextDocument::setText(const std::string &unicodePS)
{
    TextDocumentSuite().setText(m_text_documentP, unicodePS);
}
