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

#include <AETK/AEGP/Core/Core.hpp>
#include <AETK/AEGP/Util/Properties.hpp>


class Effect;
class Mask;
class Item;
class CompItem;

class Layer : public PropertyGroup
{
  public:
    Layer(LayerPtr layer) : m_layer(layer), PropertyGroup(DynamicStreamSuite().GetNewStreamRefForLayer(layer)) {}

    virtual ~Layer() = default;

    virtual ObjectType getObjectType() const { return ObjectType::NONE; }

    static tk::shared_ptr<Layer> activeLayer();

    LayerPtr getLayer() const { return m_layer; }
    void setLayer(LayerPtr layer) { m_layer = layer; }

    std::string getName();
    std::string getMatchName();
    void setName(const std::string &name);

    int getIndex();
    void setIndex(int index);

    tk::shared_ptr<Item> sourceItem();

    tk::shared_ptr<CompItem> parentComp();

    LayerQual getQuality();
    void setQuality(LayerQual quality);

    bool isLayerVideoOn();
    bool isLayerAudioOn();

    double currentTime(); // in frames
    double duration();    // in frames, use int for frame number

    double offset();
    void setOffset(double offset);

    double inPoint();
    void setInPoint(double inPoint);

    double stretch();
    void setStretch(double stretch);

    bool isFlagSet(LayerFlag flag);
    void setFlag(LayerFlag flag, bool value);

    bool is3DLayer();
    bool is2DLayer();
    bool VideoActive(); // video running

    tk::shared_ptr<Layer> parentLayer();
    void setParentLayer(std::shared_ptr<Layer> parentLayer);

    tk::shared_ptr<Layer> duplicate();
    void Delete();

    LayerSamplingQual getSamplingQuality();
    void setSamplingQuality(LayerSamplingQual quality);

    int numEffects();
    // Properties
    tk::shared_ptr<BaseProperty> getProperty(LayerStream stream);

    // Property ShortCuts
    tk::shared_ptr<ThreeDProperty> AnchorPoint();
    tk::shared_ptr<ThreeDProperty> Position();
    tk::shared_ptr<ThreeDProperty> Rotation();
    tk::shared_ptr<MarkerProperty> Marker();
    tk::shared_ptr<ThreeDProperty> Scale();
    tk::shared_ptr<OneDProperty> Opacity();
    tk::shared_ptr<OneDProperty> RotationX();
    tk::shared_ptr<OneDProperty> RotationY();
    tk::shared_ptr<OneDProperty> RotationZ();
    tk::shared_ptr<TextDocumentProperty> Text();

  protected:
    LayerPtr m_layer;
};

class AVLayer : public Layer
{
  public:
    AVLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~AVLayer() = default;

    ObjectType getObjectType() const override { return ObjectType::AV; }

    tk::shared_ptr<OneDProperty> AcceptsShadows();
    tk::shared_ptr<OneDProperty> AcceptsLights();
    tk::shared_ptr<OneDProperty> AmbientCoeff();
    tk::shared_ptr<OneDProperty> DiffuseCoeff();
    tk::shared_ptr<OneDProperty> SpecularIntensity();
    tk::shared_ptr<OneDProperty> SpecularShininess();
    tk::shared_ptr<OneDProperty> CastsShadows();
    tk::shared_ptr<OneDProperty> LightTransmission();
    tk::shared_ptr<OneDProperty> Metal();
    tk::shared_ptr<OneDProperty> ReflectionIntensity();
    tk::shared_ptr<OneDProperty> ReflectionSharpness();
    tk::shared_ptr<OneDProperty> ReflectionRolloff();
    tk::shared_ptr<OneDProperty> TransparencyCoeff();
    tk::shared_ptr<OneDProperty> TransparencyRolloff();
    tk::shared_ptr<OneDProperty> IndexOfRefraction();
    tk::shared_ptr<OneDProperty> ExtrusionBevelStyle();
    tk::shared_ptr<OneDProperty> ExtrusionBevelDirection();
    tk::shared_ptr<OneDProperty> ExtrusionBevelDepth();
    tk::shared_ptr<OneDProperty> ExtrusionHoleBevelDepth();
    tk::shared_ptr<OneDProperty> ExtrusionDepth();
    tk::shared_ptr<OneDProperty> PlaneCurvature();
    tk::shared_ptr<OneDProperty> PlaneSubdivision();
};

class CameraLayer : public Layer
{
  public:
    CameraLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~CameraLayer() = default;

    ObjectType getObjectType() const override { return ObjectType::CAMERA; }

    tk::shared_ptr<OneDProperty> Zoom();
    tk::shared_ptr<OneDProperty> DepthOfField();
    tk::shared_ptr<OneDProperty> FocusDistance();
    tk::shared_ptr<OneDProperty> Aperture();
    tk::shared_ptr<OneDProperty> BlurLevel();
    tk::shared_ptr<OneDProperty> IrisShape();
    tk::shared_ptr<OneDProperty> IrisRotation();
    tk::shared_ptr<OneDProperty> IrisRoundness();
    tk::shared_ptr<OneDProperty> IrisAspectRatio();
    tk::shared_ptr<OneDProperty> IrisDiffractionFringe();
    tk::shared_ptr<OneDProperty> IrisHighlightGain();
    tk::shared_ptr<OneDProperty> IrisHighlightThreshold();
    tk::shared_ptr<OneDProperty> IrisHighlightSaturation();
};

class LightLayer : public Layer
{
  public:
    LightLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~LightLayer() = default;

    ObjectType getObjectType() const override { return ObjectType::LIGHT; }

    ColorProperty Color();
    tk::shared_ptr<OneDProperty> Intensity();
    tk::shared_ptr<OneDProperty> ConeAngle();
    tk::shared_ptr<OneDProperty> ConeFeather();
    tk::shared_ptr<OneDProperty> ShadowDarkness();
    tk::shared_ptr<OneDProperty> ShadowDiffusion();
    tk::shared_ptr<OneDProperty> LightFalloffType();
    tk::shared_ptr<OneDProperty> LightFalloffStart();
    tk::shared_ptr<OneDProperty> LightFalloffDistance();
};

class TextLayer : public Layer
{
  public:
    TextLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~TextLayer() = default;

    ObjectType getObjectType() const override { return ObjectType::TEXT; }
};

class VectorLayer : public Layer
{
  public:
    VectorLayer(LayerPtr layer) : Layer(layer) {}

    virtual ~VectorLayer() = default;

    ObjectType getObjectType() const override { return ObjectType::VECTOR; }
};

#endif // LAYER_HPP
