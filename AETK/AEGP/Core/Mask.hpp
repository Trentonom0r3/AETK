/*****************************************************************//**
 * \file   Mask.hpp
 * \brief  
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/
#ifndef MASK_HPP
#define MASK_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Property.hpp"

namespace AE
{
class Mask : public PropertyGroup
{
  public:
    Mask(MaskRefPtr maskRef) : m_mask(maskRef), m_maskSuite(MaskSuite6()), 
        m_streamSuite(StreamSuite6()), m_dynamicSuite(DynamicStreamSuite4())
    {
    }
    ~Mask() = default;

    static std::shared_ptr<Mask> getMask(LayerPtr layer, A_long maskIndex);

    bool invert();
    void setInvert(bool invert);

    AE_MaskMode mode();
    void setMode(AE_MaskMode mode);

    AE_MaskMBlur motionBlurState();
    void setMotionBlurState(AE_MaskMBlur blurState);

    AE_MaskFeatherFalloff featherFalloff();
    void setFeatherFalloff(AE_MaskFeatherFalloff featherFalloff);

    AEGP_MaskIDVal id();

    ColorVal color();
    void setColor(ColorVal color);

    bool lockState();
    void setLockState(bool lock);

    bool isRotoBezier();
    void setIsRotoBezier(bool isRotoBezier);

    std::shared_ptr<BaseProperty> getProperty(AE_MaskStream property);

    std::shared_ptr<MaskOutlineProperty> outline();
    std::shared_ptr<OneDProperty> opacity();
    std::shared_ptr<TwoDProperty> feather();
    std::shared_ptr<OneDProperty> expansion();

    private:
    MaskSuite6 m_maskSuite;
    StreamSuite6 m_streamSuite;
    DynamicStreamSuite4 m_dynamicSuite;
    MaskRefPtr m_mask;
};

} // namespace AE

#endif // MASK_HPP
