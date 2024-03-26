/*****************************************************************//**
 * \file   Property.hpp
 * \brief  
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
class Marker;
class MaskOutline;
class TextDocument;

class BaseProperty
{
  public:
    BaseProperty() : m_property(nullptr) {}
    BaseProperty(StreamRefPtr property) : m_property(property) {}
    virtual ~BaseProperty() = default;

    virtual AE_StreamType getType() const { return AE_StreamType::NONE; }

    std::string getName() const;
    void setName(const std::string &name);
    StreamRefPtr getStream() const { return m_property; }

    std::string matchName() const;

	void reOrder(int index);

    template <typename T> //should really only be used with Properties, not PropertyGroups
    T getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
     
    template <typename T> //should really only be used with Properties, not PropertyGroups
    void setValue(T value);

    virtual std::shared_ptr<BaseProperty> getProperty(const std::string &name) const; //should really only be used with PropertyGroups
    virtual std::shared_ptr<BaseProperty> getProperty(int index) const; //should really only be used with PropertyGroups

    virtual void addProperty(const std::string& name) const; //should really only be used with PropertyGroups

    virtual void removeProperty(const std::string& name) const; //should really only be used with PropertyGroups

    virtual void removeProperty(int index) const; //should really only be used with PropertyGroups

    protected:
    StreamRefPtr m_property;
};

class OneDProperty : public BaseProperty
{
  public:
	OneDProperty() : BaseProperty() {}
	OneDProperty(StreamRefPtr property) : BaseProperty(property) {}
	~OneDProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::OneD; }

    double getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const; // returns the value of the property at the given time
    void setValue(double value); // sets the value of the property

};

class TwoDProperty : public BaseProperty
{
  public:
	TwoDProperty() : BaseProperty() {}
	TwoDProperty(StreamRefPtr property) : BaseProperty(property) {}
	~TwoDProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::TwoD; } // returns the type of the property

	TwoDVal getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const; // returns the value of the property at the given time
    void setValue(TwoDVal value); // sets the value of the property

};

class ThreeDProperty : public BaseProperty
{
  public:
	ThreeDProperty() : BaseProperty() {}
	ThreeDProperty(StreamRefPtr property) : BaseProperty(property) {}
	~ThreeDProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::ThreeD; }

	ThreeDVal getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
	void setValue(ThreeDVal value);

};

class ColorProperty : public BaseProperty
{
  public:
	ColorProperty() : BaseProperty() {}
	ColorProperty(StreamRefPtr property) : BaseProperty(property) {}
	~ColorProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::COLOR; }

	ColorVal getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;
	void setValue(ColorVal value);

};

class MarkerProperty : public BaseProperty
{
  public:
	MarkerProperty() : BaseProperty() {}
	MarkerProperty(StreamRefPtr property) : BaseProperty(property) {}
	~MarkerProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::MARKER; }

	std::shared_ptr<Marker> getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;

};

class LayerIDProperty : public BaseProperty
{
  public:
	LayerIDProperty() : BaseProperty() {}
	LayerIDProperty(StreamRefPtr property) : BaseProperty(property) {}
	~LayerIDProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::LAYER_ID; }

	int getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;

};

class MaskIDProperty : public BaseProperty
{
  public:
	MaskIDProperty() : BaseProperty() {}
	MaskIDProperty(StreamRefPtr property) : BaseProperty(property) {}
	~MaskIDProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::MASK_ID; }

	int getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;

};

class MaskOutlineProperty : public BaseProperty //maskOutlineValPtr
{
  public:
        MaskOutlineProperty() : BaseProperty() {}
    MaskOutlineProperty(StreamRefPtr property) : BaseProperty(property) {}
        ~MaskOutlineProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::MASK; }

	std::shared_ptr<MaskOutline> getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0,
                 bool preExpression = TRUE) const;

};

class TextDocumentProperty : public BaseProperty
{
  public:
	TextDocumentProperty() : BaseProperty() {}
	TextDocumentProperty(StreamRefPtr property) : BaseProperty(property) {}
	~TextDocumentProperty() = default;

	AE_StreamType getType() const override { return AE_StreamType::TEXT_DOCUMENT; }

	std::shared_ptr<TextDocument> getValue(AE_LTimeMode = AE_LTimeMode::CompTime, double time = 0.0, bool preExpression = TRUE) const;

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

        std::shared_ptr<BaseProperty> getProperty(const std::string &name) const override;
        std::shared_ptr<BaseProperty> getProperty(int index) const override;

        template <typename EnumType>
        std::shared_ptr<BaseProperty> getProperty(EnumType index) const;

        void addProperty(const std::string& name) const override;

		void removeProperty(const std::string& name) const override;

		void removeProperty(int index) const override;

};

#endif //PROPERTY_HPP
