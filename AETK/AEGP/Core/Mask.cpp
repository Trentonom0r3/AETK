#include "Mask.hpp"

std::shared_ptr<BaseProperty> AE::Mask::getProperty(AE_MaskStream property)
{
    auto stream = m_streamSuite.GetNewMaskStream(m_mask, property);
    AE_StreamGroupingType groupType =
        m_dynamicSuite.GetStreamGroupingType(stream);

    // Check if the stream represents a group and handle accordingly
    if (groupType == AE_StreamGroupingType::INDEXED_GROUP ||
        groupType == AE_StreamGroupingType::NAMED_GROUP)
    {
        return std::make_shared<PropertyGroup>(stream);
    }
    else if (groupType == AE_StreamGroupingType::LEAF)
    {
        // Proceed with the original logic for individual properties
        AE_StreamType streamType = m_streamSuite.GetStreamType(stream);
        switch (streamType)
        {
        case AE_StreamType::OneD:
            return std::make_shared<OneDProperty>(stream);
        case AE_StreamType::TwoD:
        case AE_StreamType::TwoD_SPATIAL:
            return std::make_shared<TwoDProperty>(stream);
        case AE_StreamType::ThreeD:
        case AE_StreamType::ThreeD_SPATIAL:
            return std::make_shared<ThreeDProperty>(stream);
        case AE_StreamType::COLOR:
            return std::make_shared<ColorProperty>(stream);
        case AE_StreamType::MARKER:
            return std::make_shared<MarkerProperty>(stream);
        case AE_StreamType::LAYER_ID:
            return std::make_shared<LayerIDProperty>(stream);
        case AE_StreamType::MASK_ID:
            return std::make_shared<MaskIDProperty>(stream);
        case AE_StreamType::MASK:
            return std::make_shared<MaskOutlineProperty>(stream);
        case AE_StreamType::TEXT_DOCUMENT:
            return std::make_shared<TextDocumentProperty>(stream);
        // Add additional cases as necessary for other property types
        default:
            return std::make_shared<BaseProperty>(
                stream); // Fallback for unrecognized or generic properties
        }
    }
    return nullptr;
}

std::shared_ptr<AE::Mask> AE::Mask::getMask(LayerPtr layer, A_long maskIndex)
{
    return std::shared_ptr<Mask>();
}

bool AE::Mask::invert()
{
return false;
}

void AE::Mask::setInvert(bool invert) {}

void AE::Mask::setMode(AE_MaskMode mode) {}

std::shared_ptr<MaskOutlineProperty> AE::Mask::outline()
{
    auto property = getProperty(AE_MaskStream::OUTLINE);
    return std::static_pointer_cast<MaskOutlineProperty>(property);
}

AE_MaskMBlur AE::Mask::motionBlurState()
{
    return AE_MaskMBlur();
}

std::shared_ptr<OneDProperty> AE::Mask::opacity()
{
    auto property = getProperty(AE_MaskStream::OPACITY);
return std::static_pointer_cast<OneDProperty>(property);
}

void AE::Mask::setMotionBlurState(AE_MaskMBlur blurState) {}

std::shared_ptr<TwoDProperty> AE::Mask::feather()
{
	auto property = getProperty(AE_MaskStream::FEATHER);
return std::static_pointer_cast<TwoDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::Mask::expansion()
{
    auto property = getProperty(AE_MaskStream::EXPANSION);
return std::static_pointer_cast<OneDProperty>(property);
}

AE_MaskFeatherFalloff AE::Mask::featherFalloff()
{
    return m_maskSuite.getMaskFeatherFalloff(m_mask);
}

void AE::Mask::setFeatherFalloff(AE_MaskFeatherFalloff featherFalloff) {
    m_maskSuite.setMaskFeatherFalloff(m_mask, featherFalloff);
}

AEGP_MaskIDVal AE::Mask::id()
{
    return m_maskSuite.getMaskID(m_mask);
}

ColorVal AE::Mask::color()
{
    return m_maskSuite.getMaskColor(m_mask);
}

void AE::Mask::setColor(ColorVal color) {
    m_maskSuite.setMaskColor(m_mask, color);
}

bool AE::Mask::lockState()
{
    return m_maskSuite.getMaskLockState(m_mask);
}

void AE::Mask::setLockState(bool lock) {
	m_maskSuite.setMaskLockState(m_mask, lock);
}

bool AE::Mask::isRotoBezier()
{
    return m_maskSuite.getMaskIsRotoBezier(m_mask);
}

void AE::Mask::setIsRotoBezier(bool isRotoBezier) {
    m_maskSuite.setMaskIsRotoBezier(m_mask, isRotoBezier);
}


