/*****************************************************************/ /**
                                                                     * \file
                                                                     *Property.hpp
                                                                     * \brief
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Misc.hpp"
#include <limits> // Include this at the top of your file
#include <cmath> // For std::abs

class Marker;
class MaskOutline;
class TextDocument;
class BaseProperty
{
  public:
    BaseProperty() : m_property(nullptr){};
    BaseProperty(StreamRefPtr property) : m_property(property){};
    virtual ~BaseProperty() = default;

    virtual AE_StreamType getType() const { return AE_StreamType::NONE; }

    std::string getName() const;
    void setName(const std::string &name);
    StreamRefPtr getStream() const { return m_property; }

    std::string matchName() const;

    void reOrder(int index);

    template <typename T> // should really only be used with Properties, not
                          // PropertyGroups
    T getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0,
               bool preExpression = TRUE) const;

    template <typename T> // should really only be used with Properties, not
                          // PropertyGroups
    void setValue(T value);

    virtual std::shared_ptr<BaseProperty> getProperty(const std::string &name)
        const; // should really only be used with PropertyGroups
    virtual std::shared_ptr<BaseProperty> getProperty(
        int index) const; // should really only be used with PropertyGroups

    virtual void addProperty(const std::string &name)
        const; // should really only be used with PropertyGroups

    virtual void removeProperty(const std::string &name)
        const; // should really only be used with PropertyGroups

    virtual void removeProperty(
        int index) const; // should really only be used with PropertyGroups

    inline int numKeys() const {
        int numKeys = KeyframeSuite5().GetStreamNumKFs(m_property);
        return numKeys;
    }

    KeyFrame getKeyframe(int index) // Gets the Key at the given index.
    {
        auto keyNum = KeyframeSuite5().GetStreamNumKFs(m_property);
        if (index >= keyNum)
        {
            throw std::out_of_range("Keyframe index out of range");
        }
        auto keyIndex = index;
        auto time = TimeToSeconds(KeyframeSuite5().GetKeyframeTime(
            m_property, keyIndex, AE_LTimeMode::CompTime));
        auto value = KeyframeSuite5().GetNewKeyframeValue(m_property, keyIndex);
        auto flags = KeyframeSuite5().GetKeyframeFlags(m_property, keyIndex);
        auto interp =
            KeyframeSuite5().GetKeyframeInterpolation(m_property, keyIndex);
        auto inInterp = std::get<0>(interp);
        auto outInterp = std::get<1>(interp);
        auto tangents = KeyframeSuite5().GetNewKeyframeSpatialTangents(
            m_property, keyIndex);
        auto inTan = std::get<0>(tangents);
        auto outTan = std::get<1>(tangents);
        auto ease =
            KeyframeSuite5().GetKeyframeTemporalEase(m_property, keyIndex, 0);
        auto inEase = std::get<0>(ease);
        auto outEase = std::get<1>(ease);
        KeyFrame config(time);
        config.setValue(convertToTangentValue(value));
        config.setFlag(flags);
        config.interp = std::make_pair(inInterp, outInterp);
		config.easeIn = inEase;
        config.easeOut = outEase;
        config.tangents = std::make_pair(convertToTangentValue(inTan), convertToTangentValue(outTan));

        return config;
    }

    inline std::vector<KeyFrame> getKeyframes() // Gets all the keys
    {
        auto keyNum = KeyframeSuite5().GetStreamNumKFs(m_property);
        std::vector<KeyFrame> keyframes;
        for (int i = 0; i < keyNum; i++)
        {
            keyframes.push_back(getKeyframe(i));
        }
        return keyframes;
    }

    inline KeyFrame getNearestKeyframe(double time) // Gets the nearest key
    {
        double nearestTimeDifference = 1e308; // Set to a large number
        int nearestKeyIndex = -1;

        int keyNum = KeyframeSuite5().GetStreamNumKFs(m_property);
        for (int i = 0; i < keyNum; i++)
        {
            auto keyTime = TimeToSeconds(KeyframeSuite5().GetKeyframeTime(
                m_property, i, AE_LTimeMode::CompTime));
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


    inline void addKey(const KeyFrame &keyframe) // Adds Keyframe to the property
    {
        auto akH = KeyframeSuite5().StartAddKeyframes(m_property);
        auto keyIndex = KeyframeSuite5().AddKeyframes(
            akH, AE_LTimeMode::CompTime, SecondsToTime(keyframe.time));
        KeyframeSuite5().SetAddKeyframe(akH, keyIndex,
                                        convertToAEValue(keyframe.value));
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
            setKeySpatialTangents(keyIndex, convertToAEValue(inTan),
                                  convertToAEValue(outTan));
        }
    };

    inline void addKeys(const std::vector<KeyFrame> &keyframes) // Adds multiple keyframes to the property
    {
        auto akH = KeyframeSuite5().StartAddKeyframes(m_property);
        for (const auto &keyframe : keyframes)
        {
            auto keyIndex = KeyframeSuite5().AddKeyframes(
                akH, AE_LTimeMode::CompTime, SecondsToTime(keyframe.time));
            KeyframeSuite5().SetAddKeyframe(akH, keyIndex,
                                            convertToAEValue(keyframe.value));
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
                setKeySpatialTangents(keyIndex, convertToAEValue(inTan),
                                      convertToAEValue(outTan));
            }
        }
    }

  protected:
    inline void setKeyFlags(AEGP_KeyframeIndex keyIndex,
                            std::vector<AE_KeyframeFlag> flags)
    {
        for (auto flag : flags)
        {
            KeyframeSuite5().SetKeyframeFlag(m_property, keyIndex, flag, true);
        }
    }

    inline void setKeyInterpolation(AEGP_KeyframeIndex keyIndex,
                                    AE_KeyInterp inInterp,
                                    AE_KeyInterp outInterp)
    {
        KeyframeSuite5().SetKeyframeInterpolation(m_property, keyIndex,
                                                  inInterp, outInterp);
    }

    inline void setKeyTemporalEase(AEGP_KeyframeIndex keyIndex,
                                   A_long dimension, AE_KeyframeEase inEase,
                                   AE_KeyframeEase outEase)
    {
        KeyframeSuite5().SetKeyframeTemporalEase(
            m_property, keyIndex,
            KeyframeSuite5().GetStreamTemporalDimensionality(m_property), inEase,
            outEase);
    }

    inline void setKeySpatialTangents(AEGP_KeyframeIndex keyIndex,
                                      AEGP_StreamValue2 inTan,
                                      AEGP_StreamValue2 outTan)
    {
        KeyframeSuite5().SetKeyframeSpatialTangents(m_property, keyIndex, inTan,
                                                    outTan);
    }

    inline AEGP_StreamValue2
    convertToAEValue(const KeyFrame::TangentValue &value)
    {
        AEGP_StreamValue2 aeValue;
        aeValue.streamH = *m_property.get();
        std::visit(overloaded{
                       [&](double val) { aeValue.val.one_d = val; },
                       [&](const TwoDVal &val) {
                           aeValue.val.two_d = toAEGP_TwoDVal(val);
                       },
                       [&](const ThreeDVal &val) {
                           aeValue.val.three_d = toAEGP_ThreeDVal(val);
                       },
                       [&](const ColorVal &val) {
                           aeValue.val.color = toAEGP_ColorVal(val);
                       },
                       [&](std::monostate) {} // Do nothing for std::monostate
                   },
                   value);

        return aeValue;
    }

    KeyFrame::TangentValue convertToTangentValue(AEGP_StreamValue2 value)
    {
        switch (StreamSuite6().GetStreamType(m_property))
        {
        case AE_StreamType::OneD:
            return value.val.one_d;
        case AE_StreamType::TwoD:
        case AE_StreamType::TwoD_SPATIAL:
            return toTwoDVal(value.val.two_d);
        case AE_StreamType::ThreeD:
        case AE_StreamType::ThreeD_SPATIAL:
            return toThreeDVal(value.val.three_d);
        case AE_StreamType::COLOR:
            return toColorVal(value.val.color);
        default:
            return std::monostate();
        }
    }

    StreamRefPtr m_property;
};

class OneDProperty : public BaseProperty
{
  public:
    OneDProperty() : BaseProperty() {}
    OneDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~OneDProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::OneD; }

    double getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                    double time = 0.0, bool preExpression = TRUE)
        const; // returns the value of the property at the given time
    void setValue(double value); // sets the value of the property
};

class TwoDProperty : public BaseProperty
{
  public:
    TwoDProperty() : BaseProperty() {}
    TwoDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~TwoDProperty() = default;

    AE_StreamType getType() const override
    {
        return AE_StreamType::TwoD;
    } // returns the type of the property

    TwoDVal getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                     double time = 0.0, bool preExpression = TRUE)
        const; // returns the value of the property at the given time
    void setValue(TwoDVal value); // sets the value of the property
};

class ThreeDProperty : public BaseProperty
{
  public:
    ThreeDProperty() : BaseProperty() {}
    ThreeDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~ThreeDProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::ThreeD; }

    ThreeDVal getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                       double time = 0.0, bool preExpression = TRUE) const;
    void setValue(ThreeDVal value);
};

class ColorProperty : public BaseProperty
{
  public:
    ColorProperty() : BaseProperty() {}
    ColorProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~ColorProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::COLOR; }

    ColorVal getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                      double time = 0.0, bool preExpression = TRUE) const;
    void setValue(ColorVal value);
};

class MarkerProperty : public BaseProperty
{
  public:
    MarkerProperty() : BaseProperty() {}
    MarkerProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MarkerProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::MARKER; }

    std::shared_ptr<Marker>
    getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime, double time = 0.0,
             bool preExpression = TRUE) const;
};

class LayerIDProperty : public BaseProperty
{
  public:
    LayerIDProperty() : BaseProperty() {}
    LayerIDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~LayerIDProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::LAYER_ID; }

    int getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                 double time = 0.0, bool preExpression = TRUE) const;
};

class MaskIDProperty : public BaseProperty
{
  public:
    MaskIDProperty() : BaseProperty() {}
    MaskIDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MaskIDProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::MASK_ID; }

    int getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime,
                 double time = 0.0, bool preExpression = TRUE) const;
};

class MaskOutlineProperty : public BaseProperty // maskOutlineValPtr
{
  public:
    MaskOutlineProperty() : BaseProperty() {}
    MaskOutlineProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MaskOutlineProperty() = default;

    AE_StreamType getType() const override { return AE_StreamType::MASK; }

    std::shared_ptr<MaskOutline>
    getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime, double time = 0.0,
             bool preExpression = TRUE) const;
};

class TextDocumentProperty : public BaseProperty
{
  public:
    TextDocumentProperty() : BaseProperty() {}
    TextDocumentProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~TextDocumentProperty() = default;

    AE_StreamType getType() const override
    {
        return AE_StreamType::TEXT_DOCUMENT;
    }

    std::shared_ptr<TextDocument>
    getValue(AE_LTimeMode timeMode = AE_LTimeMode::CompTime, double time = 0.0,
             bool preExpression = TRUE) const;
};

class PropertyGroup : public BaseProperty
{
  public:
    PropertyGroup() : BaseProperty() {}
    PropertyGroup(StreamRefPtr property) : BaseProperty(property) {}
    ~PropertyGroup() = default;

    AE_StreamType getType() const override
    {
        return AE_StreamType::NONE;
    } // may need to change this

    int getNumProperties() const;

    std::shared_ptr<BaseProperty>
    getProperty(const std::string &name) const override;
    std::shared_ptr<BaseProperty> getProperty(int index) const override;

    template <typename EnumType>
    std::shared_ptr<BaseProperty> getProperty(EnumType index) const;

    void addProperty(const std::string &name) const override;

    void removeProperty(const std::string &name) const override;

    void removeProperty(int index) const override;
};

#endif // PROPERTY_HPP
