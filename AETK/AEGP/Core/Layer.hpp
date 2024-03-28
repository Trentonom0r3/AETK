/*****************************************************************/ /**
                                                                     * \file
                                                                     *Layer.hpp
                                                                     * \brief  A
                                                                     *header
                                                                     *file for
                                                                     *the Layer
                                                                     *class
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef LAYER_HPP
#define LAYER_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
#include "AETK/AEGP/Core/Base/Property.hpp"

namespace AE
{
class Effect;
class Mask;
class Item;
class CompItem;

class Layer : public PropertyGroup
{
  public:
    Layer(LayerPtr layer)
        : m_layer(layer), m_layerSuite(LayerSuite9()),
          m_streamSuite(StreamSuite6()),
          m_dynamicStreamSuite(DynamicStreamSuite4()),
          PropertyGroup(DynamicStreamSuite4().GetNewStreamRefForLayer(layer))
    {
    }

    virtual ~Layer() = default;

    virtual AE_ObjectType getObjectType() const {return AE_ObjectType::NONE;}

    static std::shared_ptr<Layer> activeLayer();

    LayerPtr getLayer() const { return m_layer; }
    void setLayer(LayerPtr layer) { m_layer = layer; }

    std::string getName();
    std::string getMatchName();
    void setName(const std::string &name);

    int getIndex();
    void setIndex(int index);

    std::shared_ptr<Item> sourceItem();

    std::shared_ptr<CompItem> parentComp();

    AE_LayerQual getQuality();
    void setQuality(AE_LayerQual quality);

    bool isLayerVideoOn();
    bool isLayerAudioOn();

    double currentTime(); //in frames
    double duration(); //in frames, use int for frame number

    double offset();
    void setOffset(double offset);

    double inPoint();
    void setInPoint(double inPoint);

    double stretch();
    void setStretch(double stretch);

    bool isFlagSet(AE_LayerFlag flag);
    void setFlag(AE_LayerFlag flag, bool value);

    bool is3DLayer();
    bool is2DLayer();
    bool VideoActive(); //video running

    std::shared_ptr<AE::Layer> parentLayer();
    void setParentLayer(std::shared_ptr<AE::Layer> parentLayer);

    std::shared_ptr<AE::Layer> duplicate();
    void Delete();

    AE_LayerSamplingQual getSamplingQuality();
    void setSamplingQuality(AE_LayerSamplingQual quality);

    int numEffects();
    //Properties
    std::shared_ptr<BaseProperty> getProperty(AE_LayerStream stream);

    // Property ShortCuts
    std::shared_ptr<ThreeDProperty> AnchorPoint();
    std::shared_ptr<ThreeDProperty> Position();
    std::shared_ptr<ThreeDProperty> Rotation();
    std::shared_ptr<MarkerProperty> Marker();
    std::shared_ptr<ThreeDProperty> Scale();
    std::shared_ptr<OneDProperty> Opacity();
    std::shared_ptr<OneDProperty> RotationX();
    std::shared_ptr<OneDProperty> RotationY();
    std::shared_ptr<OneDProperty> RotationZ();

  protected:
    LayerPtr m_layer;
    LayerSuite9 m_layerSuite;
    StreamSuite6 m_streamSuite;
    DynamicStreamSuite4 m_dynamicStreamSuite;
};

class AVLayer : public Layer
{
  public:
    AVLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~AVLayer() = default;

    AE_ObjectType getObjectType() const override { return AE_ObjectType::AV; }

    std::shared_ptr<OneDProperty> AcceptsShadows();
    std::shared_ptr<OneDProperty> AcceptsLights();
    std::shared_ptr<OneDProperty> AmbientCoeff();
    std::shared_ptr<OneDProperty> DiffuseCoeff();
    std::shared_ptr<OneDProperty> SpecularIntensity();
    std::shared_ptr<OneDProperty> SpecularShininess();
    std::shared_ptr<OneDProperty> CastsShadows();
    std::shared_ptr<OneDProperty> LightTransmission();
    std::shared_ptr<OneDProperty> Metal();
    std::shared_ptr<OneDProperty> ReflectionIntensity();
    std::shared_ptr<OneDProperty> ReflectionSharpness();
    std::shared_ptr<OneDProperty> ReflectionRolloff();
    std::shared_ptr<OneDProperty> TransparencyCoeff();
    std::shared_ptr<OneDProperty> TransparencyRolloff();
    std::shared_ptr<OneDProperty> IndexOfRefraction();
    std::shared_ptr<OneDProperty> ExtrusionBevelStyle();
    std::shared_ptr<OneDProperty> ExtrusionBevelDirection();
    std::shared_ptr<OneDProperty> ExtrusionBevelDepth();
    std::shared_ptr<OneDProperty> ExtrusionHoleBevelDepth();
    std::shared_ptr<OneDProperty> ExtrusionDepth();
    std::shared_ptr<OneDProperty> PlaneCurvature();
    std::shared_ptr<OneDProperty> PlaneSubdivision();
};

class CameraLayer : public Layer
{
  public:
    CameraLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~CameraLayer() = default;

    AE_ObjectType getObjectType() const override
    {
        return AE_ObjectType::CAMERA;
    }

    std::shared_ptr<OneDProperty> Zoom();
    std::shared_ptr<OneDProperty> DepthOfField();
    std::shared_ptr<OneDProperty> FocusDistance();
    std::shared_ptr<OneDProperty> Aperture();
    std::shared_ptr<OneDProperty> BlurLevel();
    std::shared_ptr<OneDProperty> IrisShape();
    std::shared_ptr<OneDProperty> IrisRotation();
    std::shared_ptr<OneDProperty> IrisRoundness();
    std::shared_ptr<OneDProperty> IrisAspectRatio();
    std::shared_ptr<OneDProperty> IrisDiffractionFringe();
    std::shared_ptr<OneDProperty> IrisHighlightGain();
    std::shared_ptr<OneDProperty> IrisHighlightThreshold();
    std::shared_ptr<OneDProperty> IrisHighlightSaturation();
};

class LightLayer : public Layer
{
  public:
    LightLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~LightLayer() = default;

    AE_ObjectType getObjectType() const override
    {
        return AE_ObjectType::LIGHT;
    }

    ColorProperty Color();
    std::shared_ptr<OneDProperty> Intensity();
    std::shared_ptr<OneDProperty> ConeAngle();
    std::shared_ptr<OneDProperty> ConeFeather();
    std::shared_ptr<OneDProperty> ShadowDarkness();
    std::shared_ptr<OneDProperty> ShadowDiffusion();
    std::shared_ptr<OneDProperty> LightFalloffType();
    std::shared_ptr<OneDProperty> LightFalloffStart();
    std::shared_ptr<OneDProperty> LightFalloffDistance();
};

class TextLayer : public Layer
{
  public:
    TextLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~TextLayer() = default;

    AE_ObjectType getObjectType() const override { return AE_ObjectType::TEXT; }
};

class VectorLayer : public Layer
{
  public:
    VectorLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~VectorLayer() = default;

    AE_ObjectType getObjectType() const override
    {
        return AE_ObjectType::VECTOR;
    }
};

} // namespace AE

class LayerFactory
{
  public:
  inline static std::shared_ptr<AE::Layer> createLayer(LayerPtr layer)
  {
      AE_ObjectType type = LayerSuite9().GetLayerObjectType(layer);
      switch (type)
      {
      case AE_ObjectType::AV:
			return std::make_shared<AE::AVLayer>(layer);
      case AE_ObjectType::CAMERA:
			return std::make_shared<AE::CameraLayer>(layer);
      case AE_ObjectType::LIGHT:
			return std::make_shared<AE::LightLayer>(layer);
      case AE_ObjectType::TEXT:
			return std::make_shared<AE::TextLayer>(layer);
      case AE_ObjectType::VECTOR:
			return std::make_shared<AE::VectorLayer>(layer);
		default:
            return std::make_shared<AE::AVLayer>(layer);
		}
	}
};

#endif // LAYER_HPP
