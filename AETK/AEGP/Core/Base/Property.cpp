#include "AETK/AEGP/Core/Base/Property.hpp"
#include "AETK/AEGP/Core/Base/Misc.hpp"

std::string BaseProperty::getName() const
{
    return StreamSuite6().GetStreamName(m_property, TRUE);
}

void BaseProperty::setName(const std::string &name)
{
    DynamicStreamSuite4().SetStreamName(m_property, name);
}

std::string BaseProperty::matchName() const
{
    return DynamicStreamSuite4().GetMatchname(m_property);
}

void BaseProperty::reOrder(int index)
{
    DynamicStreamSuite4().ReorderStream(m_property, index);
}

std::shared_ptr<BaseProperty>
BaseProperty::getProperty(const std::string &name) const
{
    auto stream = DynamicStreamSuite4().GetNewStreamRefByMatchname(m_property, name);
    return std::make_shared<BaseProperty>(stream);
}

std::shared_ptr<BaseProperty> BaseProperty::getProperty(int index) const
{
    auto stream = DynamicStreamSuite4().GetNewStreamRefByIndex(m_property, index);
	return std::make_shared<BaseProperty>(stream);
}

void BaseProperty::addProperty(const std::string &name) const {
    if (DynamicStreamSuite4().CanAddStream(m_property, name)) {
			DynamicStreamSuite4().AddStream(m_property, name);
    }
}

void BaseProperty::removeProperty(const std::string &name) const {
    auto stream = DynamicStreamSuite4().GetNewStreamRefByMatchname(m_property, name);
    if (stream) {
		DynamicStreamSuite4().DeleteStream(stream);
	}
}

void BaseProperty::removeProperty(int index) const {
    auto stream = DynamicStreamSuite4().GetNewStreamRefByIndex(m_property, index);
    if (stream) {
		DynamicStreamSuite4().DeleteStream(stream);
	}
}

double OneDProperty::getValue(AE_LTimeMode timeMode, double time,
                              bool preExpression) const
{
        AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
            m_property, timeMode, SecondsToTime(time), // convert double to A_Time
                                         preExpression);
        double value = val.val.one_d;
        StreamSuite6().DisposeStreamValue(val);
        return value;
}

void OneDProperty::setValue(double value) {
    AEGP_StreamValue2 val;
	val.val.one_d = value;
	StreamSuite6().SetStreamValue(m_property, val);
}

TwoDVal TwoDProperty::getValue(AE_LTimeMode timeMode, double time,
                               bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
		m_property, timeMode, SecondsToTime(time), // convert double to A_Time
									 preExpression);
        TwoDVal value = toTwoDVal(val.val.two_d);
        StreamSuite6().DisposeStreamValue(val);
        return value;
}

void TwoDProperty::setValue(TwoDVal value) {
    AEGP_StreamValue2 val;
	val.val.two_d = toAEGP_TwoDVal(value);
	StreamSuite6().SetStreamValue(m_property, val);
}

ThreeDVal ThreeDProperty::getValue(AE_LTimeMode timeMode, double time,
                                   bool preExpression) const
{
        AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
            getStream(), timeMode, SecondsToTime(time), preExpression);
        ThreeDVal value = toThreeDVal(val.val.three_d);
        //StreamSuite6().DisposeStreamValue(val);
        return value;
}

void ThreeDProperty::setValue(ThreeDVal value) {
    AEGP_StreamValue2 val;
	val.val.three_d = toAEGP_ThreeDVal(value);
	StreamSuite6().SetStreamValue(m_property, val);
}

ColorVal ColorProperty::getValue(AE_LTimeMode timeMode, double time,
                                 bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
			m_property, timeMode, SecondsToTime(time), preExpression);
		ColorVal value = toColorVal(val.val.color);
		StreamSuite6().DisposeStreamValue(val);
		return value;
}

void ColorProperty::setValue(ColorVal value) {
    AEGP_StreamValue2 val;
	val.val.color = toAEGP_ColorVal(value);
	StreamSuite6().SetStreamValue(m_property, val);
}

std::shared_ptr<Marker> MarkerProperty::getValue(AE_LTimeMode timeMode,
                                                 double time,
                                                 bool preExpression) const
{
        AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
            m_property, timeMode, SecondsToTime(time), preExpression);
        AEGP_MarkerValP markerVal = val.val.markerP;
        MarkerValPtr markerPtr = MarkerSuite3::createPtr(markerVal);
        return std::make_shared<Marker>(markerPtr);
}

int LayerIDProperty::getValue(AE_LTimeMode timeMode, double time,
                              bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
m_property, timeMode, SecondsToTime(time), preExpression);
    int value = val.val.layer_id;
	StreamSuite6().DisposeStreamValue(val);
	return value;
}

int MaskIDProperty::getValue(AE_LTimeMode timeMode, double time,
                             bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
        m_property, timeMode, SecondsToTime(time), preExpression);
    int value = val.val.mask_id;
    StreamSuite6().DisposeStreamValue(val);
    return value;
}

std::shared_ptr<MaskOutline>
MaskOutlineProperty::getValue(AE_LTimeMode timeMode, double time,
                                          bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
		m_property, timeMode, SecondsToTime(time), preExpression);
    AEGP_MaskOutlineValH maskOutlineVal = val.val.mask;
    MaskOutlineValPtr maskOutlinePtr =
        std::make_shared<AEGP_MaskOutlineValH>(maskOutlineVal);
    StreamSuite6().DisposeStreamValue(val);
	return std::make_shared<MaskOutline>(maskOutlinePtr);
}

std::shared_ptr<TextDocument>
TextDocumentProperty::getValue(AE_LTimeMode timeMode, double time,
                               bool preExpression) const
{
    AEGP_StreamValue2 val = StreamSuite6().GetNewStreamValue(
		m_property, timeMode, SecondsToTime(time), preExpression);
	TextDocumentPtr textDocumentVal = std::make_shared<AEGP_TextDocumentH>(val.val.text_documentH);
	StreamSuite6().DisposeStreamValue(val);
	return std::make_shared<TextDocument>(textDocumentVal);
}

int PropertyGroup::getNumProperties() const
{
    return DynamicStreamSuite4().GetNumStreamsInGroup(m_property);
}

std::shared_ptr<BaseProperty>
PropertyGroup::getProperty(const std::string &name) const
{
    auto stream = DynamicStreamSuite4().GetNewStreamRefByMatchname(m_property, name);
	return std::make_shared<BaseProperty>(stream);
}

std::shared_ptr<BaseProperty> PropertyGroup::getProperty(int index) const
{
    auto stream = DynamicStreamSuite4().GetNewStreamRefByIndex(m_property, index);
	return std::make_shared<BaseProperty>(stream);
}

void PropertyGroup::addProperty(const std::string &name) const {
    if (DynamicStreamSuite4().CanAddStream(m_property, name)) {
		DynamicStreamSuite4().AddStream(m_property, name);
	}
}

void PropertyGroup::removeProperty(const std::string &name) const {
    auto stream = DynamicStreamSuite4().GetNewStreamRefByMatchname(m_property, name);
    if (stream) {
		DynamicStreamSuite4().DeleteStream(stream);
	}
}

void PropertyGroup::removeProperty(int index) const {
    auto stream = DynamicStreamSuite4().GetNewStreamRefByIndex(m_property, index);
    if (stream) {
		DynamicStreamSuite4().DeleteStream(stream);
	}
}

