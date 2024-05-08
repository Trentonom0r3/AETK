#include "AETK/AEGP/Util/Properties.hpp"
#include "AETK/AEGP/Util/Factories.hpp"

std::string BaseProperty::getName() const
{
    try
    {
        return StreamSuite().GetStreamName(m_property, TRUE);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

void BaseProperty::setName(const std::string &name)
{

    DynamicStreamSuite().SetStreamName(m_property, name);
}

std::shared_ptr<BaseProperty> BaseProperty::duplicate()
{

    auto newStream = DynamicStreamSuite().DuplicateStream(m_property);
    auto stream = DynamicStreamSuite().GetNewStreamRefByIndex(m_property, newStream);
    return PropertyFactory::CreateProperty(stream);
}

std::string BaseProperty::matchName() const
{
    try
    {
        return DynamicStreamSuite().GetMatchname(m_property);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

void BaseProperty::reOrder(int index)
{
    DynamicStreamSuite().ReorderStream(m_property, index);
}

std::shared_ptr<BaseProperty> BaseProperty::getProperty(const std::string &name) const
{

    auto stream = DynamicStreamSuite().GetNewStreamRefByMatchname(m_property, name);
    return PropertyFactory::CreateProperty(stream);
}

std::shared_ptr<BaseProperty> BaseProperty::getPropertyByIndex(int index) const
{

    auto stream = DynamicStreamSuite().GetNewStreamRefByIndex(m_property, index);
    return PropertyFactory::CreateProperty(stream);
}

void BaseProperty::addProperty(const std::string &name) const
{

    if (DynamicStreamSuite().CanAddStream(m_property, name))
    {
        DynamicStreamSuite().AddStream(m_property, name);
    }
}

void BaseProperty::removeProperty(const std::string &name) const
{

    auto stream = DynamicStreamSuite().GetNewStreamRefByMatchname(m_property, name);
    if (stream)
    {
        DynamicStreamSuite().DeleteStream(stream);
    }
}

void BaseProperty::removeProperty(int index) const
{

    auto stream = DynamicStreamSuite().GetNewStreamRefByIndex(m_property, index);
    if (stream)
    {
        DynamicStreamSuite().DeleteStream(stream);
    }
}

int BaseProperty::numKeys()
{
    int numKeys = KeyframeSuite().GetStreamNumKFs(m_property);
    return numKeys;
}

KeyFrame BaseProperty::getKeyframe(int index) // Gets the Key at the given index.
{
    auto keyNum = KeyframeSuite().GetStreamNumKFs(m_property);
    if (index >= keyNum)
    {
        throw std::out_of_range("Keyframe index out of range");
    }
    auto keyIndex = index;
    auto time = KeyframeSuite().GetKeyframeTime(m_property, keyIndex, LTimeMode::CompTime).toSeconds();
    auto value = KeyframeSuite().GetNewKeyframeValue(m_property, keyIndex);
    auto flags = KeyframeSuite().GetKeyframeFlags(m_property, keyIndex);
    auto interp = KeyframeSuite().GetKeyframeInterpolation(m_property, keyIndex);
    auto inInterp = std::get<0>(interp);
    auto outInterp = std::get<1>(interp);
    auto tangents = KeyframeSuite().GetNewKeyframeSpatialTangents(m_property, keyIndex);
    auto inTan = std::get<0>(tangents);
    auto outTan = std::get<1>(tangents);
    auto ease = KeyframeSuite().GetKeyframeTemporalEase(m_property, keyIndex, 0);
    auto inEase = std::get<0>(ease);
    auto outEase = std::get<1>(ease);
    KeyFrame config(time);
    config.setValue(convertToTangentValue(*value));
    config.setFlag(flags);
    config.interp = std::make_pair(inInterp, outInterp);
    config.easeIn = inEase;
    config.easeOut = outEase;
    config.tangents = std::make_pair(convertToTangentValue(*inTan), convertToTangentValue(*outTan));

    return config;
}

inline tk::vector<KeyFrame> BaseProperty::getKeyframes() // Gets all the keys
{
    auto keyNum = KeyframeSuite().GetStreamNumKFs(m_property);
    tk::vector<KeyFrame> keyframes;
    for (int i = 0; i < keyNum; i++)
    {
        keyframes.push_back(getKeyframe(i));
    }
    return keyframes;
}

inline KeyFrame BaseProperty::getNearestKeyframe(double time) // Gets the nearest key
{
    double nearestTimeDifference = 1e308; // Set to a large number
    int nearestKeyIndex = -1;

    int keyNum = KeyframeSuite().GetStreamNumKFs(m_property);
    for (int i = 0; i < keyNum; i++)
    {
        auto keyTime = KeyframeSuite().GetKeyframeTime(m_property, i, LTimeMode::CompTime).toSeconds();
        double timeDifference = std::abs(keyTime - time);

        if (timeDifference < nearestTimeDifference)
        {
            nearestTimeDifference = timeDifference;
            nearestKeyIndex = i;
        }
    }

    if (nearestKeyIndex != -1) // A nearest keyframe was found
    {
        return getKeyframe(nearestKeyIndex);
    }
    else
    {
        throw std::runtime_error("No keyframes available.");
    }
}

inline void BaseProperty::addKey(const KeyFrame &keyframe) // Adds Keyframe to the property
{
    auto akH = KeyframeSuite().StartAddKeyframes(m_property);
    auto keyIndex = KeyframeSuite().AddKeyframes(akH, LTimeMode::CompTime, SecondsToTime(keyframe.time));
    KeyframeSuite().SetAddKeyframe(akH, keyIndex, makeStreamValue2Ptr(convertToAEValue(keyframe.value)));
    //converttoAEValue(keyframe.value) make this accept streamrefptr as well (for binding)
    //makeStreaValue2otr take streamRefptr as arg, then std::variant, then return streamValue2Ptr

    setKeyFlags(keyIndex, keyframe.flags);
    // Check if interpolation is specified and apply it
    if (keyframe.interp.has_value())
    {
        auto [inInterp, outInterp] = keyframe.interp.value();
        setKeyInterpolation(keyIndex, inInterp, outInterp);
    }

    // Apply ease in/out if specified
    if (keyframe.easeIn.has_value())
    {
        auto inEase = keyframe.easeIn.value();
        if (keyframe.easeOut.has_value())
        {
            auto outEase = keyframe.easeOut.value();
            setKeyTemporalEase(keyIndex, 0, inEase, outEase);
        }
        else
        {
            setKeyTemporalEase(keyIndex, 0, inEase, inEase);
        }
    }

    if (keyframe.tangents.has_value())
    {
        auto [inTan, outTan] = keyframe.tangents.value();
        setKeySpatialTangents(keyIndex, convertToAEValue(inTan), convertToAEValue(outTan));
    }
    KeyframeSuite().EndAddKeyframes(akH);
};

inline void BaseProperty::addKeys(const tk::vector<KeyFrame> &keyframes) // Adds multiple keyframes to the property
{
    auto akH = KeyframeSuite().StartAddKeyframes(m_property);
    for (const auto &keyframe : keyframes)
    {
        auto keyIndex = KeyframeSuite().AddKeyframes(akH, LTimeMode::CompTime, SecondsToTime(keyframe.time));
        KeyframeSuite().SetAddKeyframe(akH, keyIndex, makeStreamValue2Ptr(convertToAEValue(keyframe.value)));
        setKeyFlags(keyIndex, keyframe.flags);

        // Check if interpolation is specified and apply it
        if (keyframe.interp.has_value())
        {
            auto [inInterp, outInterp] = keyframe.interp.value();
            setKeyInterpolation(keyIndex, inInterp, outInterp);
        }

        // Apply ease in/out if specified
        if (keyframe.easeIn.has_value())
        {
            auto inEase = keyframe.easeIn.value();
            if (keyframe.easeOut.has_value())
            {
                auto outEase = keyframe.easeOut.value();
                setKeyTemporalEase(keyIndex, 0, inEase, outEase);
            }
            else
            {
                setKeyTemporalEase(keyIndex, 0, inEase, inEase);
            }
        }

        if (keyframe.tangents.has_value())
        {
            auto [inTan, outTan] = keyframe.tangents.value();
            setKeySpatialTangents(keyIndex, convertToAEValue(inTan), convertToAEValue(outTan));
        }
    }
    KeyframeSuite().EndAddKeyframes(akH);
}

inline void BaseProperty::setKeyFlags(AEGP_KeyframeIndex keyIndex, tk::vector<KeyframeFlag> flags)
{
    for (auto flag : flags)
    {
        KeyframeSuite().SetKeyframeFlag(m_property, keyIndex, flag, true);
    }
}

inline void BaseProperty::setKeyInterpolation(AEGP_KeyframeIndex keyIndex, KeyInterp inInterp, KeyInterp outInterp)
{
    KeyframeSuite().SetKeyframeInterpolation(m_property, keyIndex, inInterp, outInterp);
}

inline void BaseProperty::setKeyTemporalEase(AEGP_KeyframeIndex keyIndex, A_long dimension, KeyframeEase inEase,
                                             KeyframeEase outEase)
{
    KeyframeSuite().SetKeyframeTemporalEase(
        m_property, keyIndex, KeyframeSuite().GetStreamTemporalDimensionality(m_property), inEase, outEase);
}

inline void BaseProperty::setKeySpatialTangents(AEGP_KeyframeIndex keyIndex, AEGP_StreamValue2 inTan,
                                                AEGP_StreamValue2 outTan)
{
    KeyframeSuite().SetKeyframeSpatialTangents(m_property, keyIndex, makeStreamValue2Ptr(inTan),
                                               makeStreamValue2Ptr(outTan));
}

inline AEGP_StreamValue2 BaseProperty::convertToAEValue(const KeyFrame::TangentValue &value)
{
    AEGP_StreamValue2 aeValue;
    aeValue.streamH = *m_property;
    std::visit(overloaded{
                   [&](double val) { aeValue.val.one_d = val; }, [&](TwoDVal val) { aeValue.val.two_d = val.toAEGP(); },
                   [&](ThreeDVal val) { aeValue.val.three_d = val.toAEGP(); },
                   [&](ColorVal val) { aeValue.val.color = val.toAEGP(); },
                   [&](std::monostate) {} // Do nothing for std::monostate
               },
               value);

    return aeValue;
}

KeyFrame::TangentValue BaseProperty::convertToTangentValue(AEGP_StreamValue2 value)
{
    switch (StreamSuite().GetStreamType(m_property))
    {
    case StreamType::OneD:
        return value.val.one_d;
    case StreamType::TwoD:
    case StreamType::TwoD_SPATIAL:
        return TwoDVal(value.val.two_d);
    case StreamType::ThreeD:
    case StreamType::ThreeD_SPATIAL:
        return ThreeDVal(value.val.three_d);
    case StreamType::COLOR:
        return ColorVal(value.val.color);
    default:
        return std::monostate();
    }
}

double OneDProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    double value = val->get().val.one_d;
    return value;
}

void OneDProperty::setValue(double value)
{

    AEGP_StreamValue2 val;
    val.val.one_d = value;
    StreamSuite().SetStreamValue(m_property, makeStreamValue2Ptr(val));
}

TwoDVal TwoDProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    TwoDVal value(val->get().val.two_d);
    return value;
}

void TwoDProperty::setValue(TwoDVal value)
{
    AEGP_StreamValue2 val;
    val.val.two_d = value.toAEGP();
    StreamSuite().SetStreamValue(m_property, makeStreamValue2Ptr(val));
}

ThreeDVal ThreeDProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    ThreeDVal value(val->get().val.three_d);
    return value;
}

void ThreeDProperty::setValue(ThreeDVal value)
{
    AEGP_StreamValue2 val;
    val.val.three_d = value.toAEGP();
    StreamSuite().SetStreamValue(m_property, makeStreamValue2Ptr(val));
}

ColorVal ColorProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{

    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    ColorVal value(val->get().val.color);
    return value;
}

void ColorProperty::setValue(ColorVal value)
{
    AEGP_StreamValue2 val;
    val.val.color = value.toAEGP();
    StreamSuite().SetStreamValue(m_property, makeStreamValue2Ptr(val));
}

std::shared_ptr<Marker> MarkerProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    return std::make_shared<Marker>(makeMarkerValPtr(val->get().val.markerP));
}

std::shared_ptr<Marker> MarkerProperty::addMarker(double time)
{
    auto idx = KeyframeSuite().InsertKeyframe(m_property, LTimeMode::CompTime, SecondsToTime(time));
    MarkerValPtr mrk = MarkerSuite().getNewMarker();
    AEGP_StreamValue2 val;
    val.streamH = *m_property;
    val.val.markerP = *mrk;
    KeyframeSuite().SetKeyframeValue(m_property, idx, makeStreamValue2Ptr(val));
    return std::make_shared<Marker>(mrk);
}

int LayerIDProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    int value = val->get().val.layer_id;
    return value;
}

int MaskIDProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    int value = val->get().val.mask_id;
    return value;
}

std::shared_ptr<MaskOutline> MaskOutlineProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);
    return std::make_shared<MaskOutline>(makeMaskOutlineValPtr(val->get().val.mask));
}

std::shared_ptr<TextDocument> TextDocumentProperty::getValue(LTimeMode timeMode, double time, bool preExpression) const
{
    StreamValue2Ptr val = StreamSuite().GetNewStreamValue(m_property, timeMode, SecondsToTime(time), preExpression);

    return std::make_shared<TextDocument>(makeTextDocumentPtr(val->get().val.text_documentH));
}

int PropertyGroup::getNumProperties() const
{
    return DynamicStreamSuite().GetNumStreamsInGroup(m_property);
}

std::shared_ptr<BaseProperty> PropertyGroup::getProperty(const std::string &name) const
{
    auto stream = DynamicStreamSuite().GetNewStreamRefByMatchname(m_property, name);
    return PropertyFactory::CreateProperty(stream);
}

std::shared_ptr<BaseProperty> PropertyGroup::getPropertyByIndex(int index) const
{
    try
    {
        auto stream = DynamicStreamSuite().GetNewStreamRefByIndex(m_property, index);
        return PropertyFactory::CreateProperty(stream);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

void PropertyGroup::addProperty(const std::string &name) const
{
    if (DynamicStreamSuite().CanAddStream(m_property, name))
    {
        DynamicStreamSuite().AddStream(m_property, name);
    }
}

void PropertyGroup::removeProperty(const std::string &name) const
{
    auto stream = DynamicStreamSuite().GetNewStreamRefByMatchname(m_property, name);
    if (stream)
    {
        DynamicStreamSuite().DeleteStream(stream);
    }
}

void PropertyGroup::removeProperty(int index) const
{
    auto stream = DynamicStreamSuite().GetNewStreamRefByIndex(m_property, index);
    if (stream)
    {
        DynamicStreamSuite().DeleteStream(stream);
    }
}
