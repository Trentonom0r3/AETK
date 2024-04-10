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

#include <AETK/AEGP/Core/Core.hpp>


#include <AETK/AEGP/Util/Keyframe.hpp>
#include <cmath>  // For std::abs
#include <limits> // Include this at the top of your file

class BaseProperty
{
  public:
    BaseProperty() : m_property(nullptr){};
    BaseProperty(StreamRefPtr property) : m_property(std::move(property)){};
    virtual ~BaseProperty() = default;

    virtual StreamType getType() const { return StreamType::NONE; }

    std::string getName() const;
    void setName(const std::string &name);
    StreamRefPtr getStream() const { return m_property; }
   std::shared_ptr<BaseProperty> duplicate();
    std::string matchName() const;

    void reOrder(int index);

    template <typename T> // should really only be used with Properties, not
                          // PropertyGroups
    T getValue(LTimeMode = LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;

    template <typename T> // should really only be used with Properties, not
                          // PropertyGroups
    void setValue(T value);

    virtual std::shared_ptr<BaseProperty>
    getProperty(const std::string &name) const; // should really only be used with PropertyGroups
    virtual std::shared_ptr<BaseProperty>
    getPropertyByIndex(int index) const; // should really only be used with PropertyGroups

    virtual void addProperty(const std::string &name) const; // should really only be used with PropertyGroups

    virtual void removeProperty(const std::string &name) const; // should really only be used with PropertyGroups

    virtual void removeProperty(int index) const; // should really only be used with PropertyGroups

    int numKeys();

    KeyFrame getKeyframe(int index);

    inline tk::vector<KeyFrame> getKeyframes();

    inline KeyFrame getNearestKeyframe(double time);

    inline void addKey(const KeyFrame &keyframe);

    inline void addKeys(const tk::vector<KeyFrame> &keyframes);

  protected:
    inline void setKeyFlags(AEGP_KeyframeIndex keyIndex, tk::vector<KeyframeFlag> flags);

    inline void setKeyInterpolation(AEGP_KeyframeIndex keyIndex, KeyInterp inInterp, KeyInterp outInterp);

    inline void setKeyTemporalEase(AEGP_KeyframeIndex keyIndex, A_long dimension, KeyframeEase inEase,
                                   KeyframeEase outEase);

    inline void setKeySpatialTangents(AEGP_KeyframeIndex keyIndex, AEGP_StreamValue2 inTan, AEGP_StreamValue2 outTan);

    inline AEGP_StreamValue2 convertToAEValue(const KeyFrame::TangentValue &value);

    KeyFrame::TangentValue convertToTangentValue(AEGP_StreamValue2 value);

    StreamRefPtr m_property;
};

class PropertyGroup : public BaseProperty
{
  public:
    PropertyGroup() : BaseProperty() {}
    PropertyGroup(StreamRefPtr property) : BaseProperty(property) {}
    ~PropertyGroup() = default;

    StreamType getType() const override { return StreamType::NONE; } // may need to change this

    int getNumProperties() const;

   std::shared_ptr<BaseProperty> getProperty(const std::string &name) const override;
   std::shared_ptr<BaseProperty> getPropertyByIndex(int index) const override;

    template <typename EnumType>std::shared_ptr<BaseProperty> getProperty(EnumType index) const;

    void addProperty(const std::string &name) const override;

    void removeProperty(const std::string &name) const override;

    void removeProperty(int index) const override;
};

class OneDProperty : public BaseProperty
{
  public:
    OneDProperty() : BaseProperty() {}
    OneDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~OneDProperty() = default;

    StreamType getType() const override { return StreamType::OneD; }

    double getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0,
                    bool preExpression = TRUE) const; // returns the value of the property at the given time
    void setValue(double value);                      // sets the value of the property
};

class TwoDProperty : public BaseProperty
{
  public:
    TwoDProperty() : BaseProperty() {}
    TwoDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~TwoDProperty() = default;

    StreamType getType() const override { return StreamType::TwoD; } // returns the type of the property

    TwoDVal getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0,
                     bool preExpression = TRUE) const; // returns the value of the property at the given time
    void setValue(TwoDVal value);                      // sets the value of the property
};

class ThreeDProperty : public BaseProperty
{
  public:
    ThreeDProperty() : BaseProperty() {}
    ThreeDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~ThreeDProperty() = default;

    StreamType getType() const override { return StreamType::ThreeD; }

    ThreeDVal getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
    void setValue(ThreeDVal value);
};

class ColorProperty : public BaseProperty
{
  public:
    ColorProperty() : BaseProperty() {}
    ColorProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~ColorProperty() = default;

    StreamType getType() const override { return StreamType::COLOR; }

    ColorVal getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
    void setValue(ColorVal value);
};

class MarkerProperty : public BaseProperty
{
  public:
    MarkerProperty() : BaseProperty() {}
    MarkerProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MarkerProperty() = default;

    StreamType getType() const override { return StreamType::MARKER; }

   std::shared_ptr<Marker> getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0,
                                    bool preExpression = TRUE) const;

   std::shared_ptr<Marker> addMarker(double time);
};

class LayerIDProperty : public BaseProperty
{
  public:
    LayerIDProperty() : BaseProperty() {}
    LayerIDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~LayerIDProperty() = default;

    StreamType getType() const override { return StreamType::LAYER_ID; }

    int getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
};

class MaskIDProperty : public BaseProperty
{
  public:
    MaskIDProperty() : BaseProperty() {}
    MaskIDProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MaskIDProperty() = default;

    StreamType getType() const override { return StreamType::MASK_ID; }

    int getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
};

class MaskOutlineProperty : public BaseProperty // maskOutlineValPtr
{
  public:
    MaskOutlineProperty() : BaseProperty() {}
    MaskOutlineProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~MaskOutlineProperty() = default;

    StreamType getType() const override { return StreamType::MASK; }

   std::shared_ptr<MaskOutline> getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0,
                                         bool preExpression = TRUE) const;
};

class TextDocumentProperty : public BaseProperty
{
  public:
    TextDocumentProperty() : BaseProperty() {}
    TextDocumentProperty(StreamRefPtr property) : BaseProperty(property) {}
    ~TextDocumentProperty() = default;

    StreamType getType() const override { return StreamType::TEXT_DOCUMENT; }

   std::shared_ptr<TextDocument> getValue(LTimeMode timeMode = LTimeMode::CompTime, double time = 0.0,
                                          bool preExpression = TRUE) const;
};

#endif // PROPERTY_HPP
