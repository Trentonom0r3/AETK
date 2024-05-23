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

void Marker::setFlag(MarkerFlag flagType, bool valueB)
{
    MarkerSuite().setMarkerFlag(m_markerP, flagType, valueB);
}

bool Marker::getFlag(MarkerFlag flagType)
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
    return MarkerSuite().getMarkerDuration(m_markerP).toSeconds();
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
    MaskOutlineSuite().setMaskOutlineVertexInfo(m_mask_outlineP, which_pointL, vertexP.toAEGP());
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
    MaskOutlineSuite().setMaskOutlineFeatherInfo(m_mask_outlineP, which_featherL, featherP.toAEGP());
}

int MaskOutline::createFeather(MaskFeather featherP0)
{
    return MaskOutlineSuite().createMaskOutlineFeather(m_mask_outlineP, featherP0.toAEGP());
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

std::variant<OneD, TwoD, ThreeD, Color> StreamValue2::value()
{
    auto streamType = StreamSuite().GetStreamType(makeStreamRefPtr(get().streamH, false));
    OneD one_d;
    TwoD two_d;
    ThreeD three_d;
    Color color;

    switch (streamType)
    {
    case StreamType::OneD:
        one_d = get().val.one_d;
		return one_d;
    case StreamType::TwoD:
    case StreamType::TwoD_SPATIAL: {
        two_d = std::make_tuple(get().val.two_d.x, get().val.two_d.y);
        return two_d;

    }
    case StreamType::ThreeD:
    case StreamType::ThreeD_SPATIAL: {
        three_d = std::make_tuple(get().val.three_d.x, get().val.three_d.y, get().val.three_d.z);
        return three_d;
    }
    case StreamType::COLOR: {
        color = std::make_tuple(get().val.color.redF, get().val.color.greenF,
                                    get().val.color.blueF, get().val.color.alphaF);
        return color;
    }
    default:
        return 0;
    }
}

AEGP_StreamValue2 &StreamValue2::streamFromValue(StreamRefPtr streamref, std::variant<OneD, TwoD, ThreeD, Color> value)
{
    AEGP_StreamValue2 val{};
    //val.streamH = *streamref;
    auto type = StreamSuite().GetStreamType(streamref);
    switch (type)
    {
    case StreamType::OneD:
        val.val.one_d = std::get<double>(value);
        break;
    case StreamType::TwoD: // std::tuple<double, double>
    case StreamType::TwoD_SPATIAL:
        val.val.two_d.x = std::get<0>(std::get<TwoD>(value));
        val.val.two_d.y = std::get<1>(std::get<TwoD>(value));
        break;
    case StreamType::ThreeD: // std::tuple<double, double, double>
    case StreamType::ThreeD_SPATIAL:
        val.val.three_d.x = std::get<0>(std::get<ThreeD>(value));
        val.val.three_d.y = std::get<1>(std::get<ThreeD>(value));
        val.val.three_d.z = std::get<2>(std::get<ThreeD>(value));
        break;
    case StreamType::COLOR: // std::tuple<double, double, double, double>
        val.val.color.redF = std::get<0>(std::get<Color>(value));
        val.val.color.greenF = std::get<1>(std::get<Color>(value));
        val.val.color.blueF = std::get<2>(std::get<Color>(value));
        val.val.color.alphaF = std::get<3>(std::get<Color>(value));
        break;
    default:
        break;
    }
    return val;
}
