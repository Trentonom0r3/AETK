/*****************************************************************/ /**
                                                                     * \file
                                                                     *Properties.hpp
                                                                     * \brief
                                                                     *Property
                                                                     *classes
                                                                     *for After
                                                                     *Effects
                                                                     *properties
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/
#pragma once

#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

namespace AE
{
// forward declare property classes
class PropertyBase;
class PropertyGroup;
class OneDProperty;
class TwoDProperty;
class ThreeDProperty;
class ColorProperty;
class MarkerProperty;
class LayerIDProperty;
class MaskIDProperty;
class MaskProperty;
class TextDocumentProperty;

class PropertyBase
{
  protected:
    StreamRefPtr streamRef; // Reference to the AE property stream
    AE_StreamType valueType;

  public:
    PropertyBase(StreamRefPtr stream, AE_StreamType valType)
        : streamRef(stream), valueType(valType)
    {
    }

    virtual ~PropertyBase() = default;

    std::string getName() const;
    std::string getUnits() const;
    bool canAddProperty(const std::string &name) const;
    bool isLegal() const;
    bool isTimeVarying() const;
    bool isHidden() const;
    bool isElided() const;
    std::shared_ptr<PropertyGroup> getParentGroup() const;

    std::string getMatchName() const;
    void setName(const std::string &name);
    void reorder(int newIndex);
    void deleteProperty();
    // Accessor for the property's value type
    AE_StreamType getValueType() const { return valueType; }
};

class PropertyGroup : public PropertyBase
{
  public:
    PropertyGroup(StreamRefPtr stream,
                  AE_StreamType valType = AE_StreamType::NONE)
        : PropertyBase(stream, valType)
    {
    }

    virtual ~PropertyGroup() = default;

    // Common functionality for all property groups
    virtual int getNumProperties() const = 0;
    virtual std::shared_ptr<PropertyBase> getProperty(int index) const = 0;
    virtual std::shared_ptr<PropertyBase>
    getProperty(const std::string &name) const = 0;

    template <typename EnumType>
    std::shared_ptr<PropertyBase> getProperty(EnumType name) const;

    virtual std::shared_ptr<PropertyBase>
    addProperty(const std::string &name) = 0;

    template <typename EnumType>
    std::shared_ptr<PropertyBase> addProperty(EnumType name);

    virtual void removeProperty(const std::string &name) = 0;
    virtual void removeProperty(int index) = 0;

    template <typename EnumType> void removeProperty(EnumType name);
};

class OneDProperty : public PropertyBase
{
  public:
    OneDProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::OneD)
    {
    }

    virtual ~OneDProperty() = default;

    double getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(double value, AE_LTimeMode timeMode, double time = 0.0);
};

class TwoDProperty : public PropertyBase
{
  public:
    TwoDProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::TwoD)
    {
    }

    virtual ~TwoDProperty() = default;

    AEGP_TwoDVal getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(AEGP_TwoDVal value, AE_LTimeMode timeMode, double time = 0.0);
};

class ThreeDProperty : public PropertyBase
{
  public:
    ThreeDProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::ThreeD)
    {
    }

    virtual ~ThreeDProperty() = default;

    AEGP_ThreeDVal getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(AEGP_ThreeDVal value, AE_LTimeMode timeMode,
                  double time = 0.0);
};

class ColorProperty : public PropertyBase
{
  public:
    ColorProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::COLOR)
    {
    }

    virtual ~ColorProperty() = default;

    AEGP_ColorVal getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(AEGP_ColorVal value, AE_LTimeMode timeMode,
                  double time = 0.0);
};

class MarkerProperty : public PropertyBase
{
  public:
    MarkerProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::MARKER)
    {
    }

    virtual ~MarkerProperty() = default;

    MarkerValPtr getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(MarkerValPtr value, AE_LTimeMode timeMode, double time = 0.0);
};

class LayerIDProperty : public PropertyBase
{
  public:
    LayerIDProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::LAYER_ID)
    {
    }

    virtual ~LayerIDProperty() = default;

    A_long getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(A_long value, AE_LTimeMode timeMode, double time = 0.0);
};

class MaskIDProperty : public PropertyBase
{
  public:
    MaskIDProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::MASK_ID)
    {
    }

    virtual ~MaskIDProperty() = default;

    A_long getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(A_long value, AE_LTimeMode timeMode, double time = 0.0);
};

class MaskProperty : public PropertyBase
{
  public:
    MaskProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::MASK)
    {
    }

    virtual ~MaskProperty() = default;

    MaskOutlineValPtr getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(MaskOutlineValPtr value, AE_LTimeMode timeMode,
                  double time = 0.0);
};

class TextDocumentProperty : public PropertyBase
{
  public:
    TextDocumentProperty(StreamRefPtr stream)
        : PropertyBase(stream, AE_StreamType::TEXT_DOCUMENT)
    {
    }

    virtual ~TextDocumentProperty() = default;

    TextDocumentPtr getValue(AE_LTimeMode timeMode, double time = 0.0) const;
    void setValue(TextDocumentPtr value, AE_LTimeMode timeMode,
                  double time = 0.0);
};

} // namespace AE

#endif // PROPERTIES_HPP
