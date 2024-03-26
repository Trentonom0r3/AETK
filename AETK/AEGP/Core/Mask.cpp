#include "Mask.hpp"

std::shared_ptr<BaseProperty> AE::Mask::getProperty(AE_MaskStream property)
{
    auto stream = m_streamSuite.GetNewMaskStream(m_mask, property);
    return std::make_shared<BaseProperty>(stream);
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
    auto stream = m_streamSuite.GetNewMaskStream(m_mask, AE_MaskStream::OUTLINE);
    return std::make_shared<MaskOutlineProperty>(stream);
}

AE_MaskMBlur AE::Mask::motionBlurState()
{
    return AE_MaskMBlur();
}

std::shared_ptr<OneDProperty> AE::Mask::opacity()
{
    auto stream = m_streamSuite.GetNewMaskStream(m_mask, AE_MaskStream::OPACITY);
	return std::make_shared<OneDProperty>(stream);
}

void AE::Mask::setMotionBlurState(AE_MaskMBlur blurState) {}

std::shared_ptr<TwoDProperty> AE::Mask::feather()
{
	auto stream = m_streamSuite.GetNewMaskStream(m_mask, AE_MaskStream::FEATHER);
	return std::make_shared<TwoDProperty>(stream);
}

std::shared_ptr<OneDProperty> AE::Mask::expansion()
{
    auto stream = m_streamSuite.GetNewMaskStream(m_mask, AE_MaskStream::EXPANSION);
	return std::make_shared<OneDProperty>(stream);
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


