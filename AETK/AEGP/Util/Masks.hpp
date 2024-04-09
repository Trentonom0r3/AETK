/*****************************************************************/ /**
                                                                     * \file   Masks.hpp
                                                                     * \brief
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef MASKS_HPP
#define MASKS_HPP

#include <AETK/AEGP/Core/Core.hpp>
#include <AETK/AEGP/Util/Properties.hpp>



class Mask : public PropertyGroup
{
  public:
    Mask(MaskRefPtr maskRef) : m_mask(maskRef) {}
    ~Mask() = default;

    static tk::shared_ptr<Mask> getMask(LayerPtr layer, A_long maskIndex);

    bool invert();
    void setInvert(bool invert);

    MaskMode mode();
    void setMode(MaskMode mode);

    MaskMBlur motionBlurState();
    void setMotionBlurState(MaskMBlur blurState);

    MaskFeatherFalloff featherFalloff();
    void setFeatherFalloff(MaskFeatherFalloff featherFalloff);

    AEGP_MaskIDVal id();

    ColorVal color();
    void setColor(ColorVal color);

    bool lockState();
    void setLockState(bool lock);

    bool isRotoBezier();
    void setIsRotoBezier(bool isRotoBezier);

    tk::shared_ptr<BaseProperty> getProperty(MaskStream property);

    tk::shared_ptr<MaskOutlineProperty> outline();
    tk::shared_ptr<OneDProperty> opacity();
    tk::shared_ptr<TwoDProperty> feather();
    tk::shared_ptr<OneDProperty> expansion();

  private:
    MaskRefPtr m_mask;
};

#endif /* MASKS_HPP */
