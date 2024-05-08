#include <AETK/AEGP/Util/Factories.hpp>
#include <AETK/AEGP/Util/Masks.hpp>

tk::shared_ptr<BaseProperty> Mask::getProperty(MaskStream property)
{
    auto stream = StreamSuite().GetNewMaskStream(m_mask, property);
    return PropertyFactory::CreateProperty(stream);
}

tk::shared_ptr<Mask> Mask::getMask(LayerPtr layer, A_long maskIndex)
{
    auto maskref = MaskSuite().getLayerMaskByIndex(layer, maskIndex); 
	return tk::make_shared<Mask>(maskref);
}

bool Mask::invert()
{
return MaskSuite().getMaskInvert(m_mask);
}

void Mask::setInvert(bool invert) {
MaskSuite().setMaskInvert(m_mask, invert);
}

MaskMode Mask::mode()
{
return MaskSuite().getMaskMode(m_mask);
}

void Mask::setMode(MaskMode mode) {
MaskSuite().setMaskMode(m_mask, mode);
}

tk::shared_ptr<MaskOutlineProperty> Mask::outline()
{
    auto property = getProperty(MaskStream::OUTLINE);
    return std::static_pointer_cast<MaskOutlineProperty>(property);
}

MaskMBlur Mask::motionBlurState()
{
    return MaskSuite().getMaskMotionBlurState(m_mask);
}

tk::shared_ptr<OneDProperty> Mask::opacity()
{
    auto property = getProperty(MaskStream::OPACITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

void Mask::setMotionBlurState(MaskMBlur blurState) {}

tk::shared_ptr<TwoDProperty> Mask::feather()
{
    auto property = getProperty(MaskStream::FEATHER);
    return std::static_pointer_cast<TwoDProperty>(property);
}

tk::shared_ptr<OneDProperty> Mask::expansion()
{
    auto property = getProperty(MaskStream::EXPANSION);
    return std::static_pointer_cast<OneDProperty>(property);
}

MaskFeatherFalloff Mask::featherFalloff()
{
    return MaskSuite().getMaskFeatherFalloff(m_mask);
}

void Mask::setFeatherFalloff(MaskFeatherFalloff featherFalloff)
{
    MaskSuite().setMaskFeatherFalloff(m_mask, featherFalloff);
}

AEGP_MaskIDVal Mask::id()
{
    return MaskSuite().getMaskID(m_mask);
}

ColorVal Mask::color()
{
    return MaskSuite().getMaskColor(m_mask);
}

void Mask::setColor(ColorVal color)
{
    MaskSuite().setMaskColor(m_mask, color);
}

bool Mask::lockState()
{
    return MaskSuite().getMaskLockState(m_mask);
}

void Mask::setLockState(bool lock)
{
    MaskSuite().setMaskLockState(m_mask, lock);
}

bool Mask::isRotoBezier()
{
    return MaskSuite().getMaskIsRotoBezier(m_mask);
}

void Mask::setIsRotoBezier(bool isRotoBezier)
{
    MaskSuite().setMaskIsRotoBezier(m_mask, isRotoBezier);
}
