#include "AETK/AEGP/Layers.hpp"
#include "AETK/AEGP/Util/Effects.hpp"
#include "AETK/AEGP/Util/Factories.hpp"
#include "AETK/AEGP/Util/Masks.hpp"
#include "AETK/AEGP/Util/Properties.hpp"

tk::shared_ptr<BaseProperty> Layer::getProperty(LayerStream stream)
{
    auto property = StreamSuite().GetNewLayerStream(m_layer, stream);
    return PropertyFactory::CreateProperty(property);
}

tk::shared_ptr<ThreeDProperty> Layer::Position()
{
    auto property = getProperty(LayerStream::POSITION);
    return std::static_pointer_cast<ThreeDProperty>(property);
}

tk::shared_ptr<ThreeDProperty> Layer::Scale()
{
    auto property = getProperty(LayerStream::SCALE);
    return std::static_pointer_cast<ThreeDProperty>(property);
}

tk::shared_ptr<ThreeDProperty> Layer::Rotation()
{
    auto property = getProperty(LayerStream::ROTATION);
    return std::static_pointer_cast<ThreeDProperty>(property);
}

tk::shared_ptr<ThreeDProperty> Layer::AnchorPoint()
{
    auto property = getProperty(LayerStream::ANCHORPOINT);
    return std::static_pointer_cast<ThreeDProperty>(property);
}

tk::shared_ptr<OneDProperty> Layer::Opacity()
{
    auto property = getProperty(LayerStream::OPACITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> Layer::RotationX()
{
    auto property = getProperty(LayerStream::ROTATE_X);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> Layer::RotationY()
{
    auto property = getProperty(LayerStream::ROTATE_Y);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> Layer::RotationZ()
{
    auto property = getProperty(LayerStream::ROTATE_Z);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<TextDocumentProperty> Layer::Text()
{
    auto property = getProperty(LayerStream::TEXT);
    return std::static_pointer_cast<TextDocumentProperty>(property);
}

tk::shared_ptr<MarkerProperty> Layer::Marker()
{
    auto property = getProperty(LayerStream::MARKER);
    return std::static_pointer_cast<MarkerProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::AcceptsShadows()
{
    auto property = getProperty(LayerStream::ACCEPTS_SHADOWS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::AcceptsLights()
{
    auto property = getProperty(LayerStream::ACCEPTS_LIGHTS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::AmbientCoeff()
{
    auto property = getProperty(LayerStream::AMBIENT_COEFF);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::DiffuseCoeff()
{
    auto property = getProperty(LayerStream::DIFFUSE_COEFF);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::SpecularIntensity()
{
    auto property = getProperty(LayerStream::SPECULAR_INTENSITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::SpecularShininess()
{
    auto property = getProperty(LayerStream::SPECULAR_SHININESS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::CastsShadows()
{
    auto property = getProperty(LayerStream::CASTS_SHADOWS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::LightTransmission()
{
    auto property = getProperty(LayerStream::LIGHT_TRANSMISSION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::Metal()
{
    auto property = getProperty(LayerStream::METAL);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ReflectionIntensity()
{
    auto property = getProperty(LayerStream::REFLECTION_INTENSITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ReflectionSharpness()
{
    auto property = getProperty(LayerStream::REFLECTION_SHARPNESS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ReflectionRolloff()
{
    auto property = getProperty(LayerStream::REFLECTION_ROLLOFF);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::TransparencyCoeff()
{
    auto property = getProperty(LayerStream::TRANSPARENCY_COEFF);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::TransparencyRolloff()
{
    auto property = getProperty(LayerStream::TRANSPARENCY_ROLLOFF);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::IndexOfRefraction()
{
    auto property = getProperty(LayerStream::INDEX_OF_REFRACTION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ExtrusionBevelStyle()
{
    auto property = getProperty(LayerStream::EXTRUSION_BEVEL_STYLE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ExtrusionBevelDirection()
{
    auto property = getProperty(LayerStream::EXTRUSION_BEVEL_DIRECTION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ExtrusionBevelDepth()
{
    auto property = getProperty(LayerStream::EXTRUSION_BEVEL_DEPTH);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ExtrusionHoleBevelDepth()
{
    auto property = getProperty(LayerStream::EXTRUSION_HOLE_BEVEL_DEPTH);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::ExtrusionDepth()
{
    auto property = getProperty(LayerStream::EXTRUSION_DEPTH);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::PlaneCurvature()
{
    auto property = getProperty(LayerStream::PLANE_CURVATURE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> AVLayer::PlaneSubdivision()
{
    auto property = getProperty(LayerStream::PLANE_SUBDIVISION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<Layer> Layer::activeLayer()
{
    try
    {
    auto layerptr = LayerSuite().GetActiveLayer();
    return LayerFactory::createLayer(layerptr);
    }
    catch (const AEException& e)
    {
		throw e;
	}
}

std::string Layer::getName()
{
    std::string type = std::get<0>(LayerSuite().GetLayerName(m_layer));
    return type;
}

std::string Layer::getMatchName()
{
    std::string type = std::get<1>(LayerSuite().GetLayerName(m_layer));
    return type;
}

void Layer::setName(const std::string &name)
{
    LayerSuite().SetLayerName(m_layer, name);
}

int Layer::getIndex()
{
    return LayerSuite().GetLayerIndex(m_layer);
}

void Layer::setIndex(int index)
{
    LayerSuite().ReorderLayer(m_layer, index);
}

tk::shared_ptr<Item> Layer::sourceItem()
{
    auto item = LayerSuite().GetLayerSourceItem(m_layer);
    return ItemFactory::createItem(item);
}

tk::shared_ptr<CompItem> Layer::parentComp()
{
    auto comp = LayerSuite().GetLayerParentComp(m_layer);
    return std::make_shared<CompItem>(comp);
}

LayerQual Layer::getQuality()
{
    return LayerSuite().GetLayerQuality(m_layer);
}

void Layer::setQuality(LayerQual quality)
{
    LayerSuite().SetLayerQuality(m_layer, quality);
}

bool Layer::isLayerVideoOn()
{
    return LayerSuite().IsLayerVideoReallyOn(m_layer);
}

bool Layer::isLayerAudioOn()
{
    return LayerSuite().IsLayerAudioReallyOn(m_layer);
}

double Layer::currentTime()
{
    return LayerSuite().GetLayerCurrentTime(m_layer, LTimeMode::CompTime).toSeconds();
}

double Layer::duration()
{
    return LayerSuite().GetLayerDuration(m_layer, LTimeMode::CompTime).toSeconds();
}

double Layer::offset()
{
    return LayerSuite().GetLayerOffset(m_layer).toSeconds();
}

void Layer::setOffset(double offset)
{
    LayerSuite().SetLayerOffset(m_layer, SecondsToTime(offset));
}

double Layer::inPoint()
{
    auto inPoint = LayerSuite().GetLayerInPoint(m_layer, LTimeMode::CompTime);
    return inPoint.toSeconds();
}

void Layer::setInPoint(double inPoint)
{
    LayerSuite().SetLayerInPointAndDuration(m_layer, LTimeMode::CompTime, SecondsToTime(inPoint),
                                            LayerSuite().GetLayerDuration(m_layer, LTimeMode::CompTime));
}

double Layer::stretch()
{
    return RATIO2FLOAT(LayerSuite().GetLayerStretch(m_layer));
}

void Layer::setStretch(double stretch) {}

// TODO Implement Tis
bool Layer::isFlagSet(LayerFlag flag)
{
    return false;
}
// TODO Implement Tis
void Layer::setFlag(LayerFlag flag, bool value) {}

bool Layer::is3DLayer()
{
    return LayerSuite().IsLayer3D(m_layer);
}

bool Layer::is2DLayer()
{
    return LayerSuite().IsLayer2D(m_layer);
}

bool Layer::VideoActive()
{
    // TODO return LayerSuite().IsVideoActive(m_layer);   IMPLEMENT LATER
    return false;
}

tk::shared_ptr<Layer> Layer::parentLayer()
{
    auto layer = LayerSuite().GetLayerParent(m_layer);
    return LayerFactory::createLayer(layer);
}

void Layer::setParentLayer(tk::shared_ptr<Layer> parentLayer)
{
    LayerSuite().SetLayerParent(m_layer, parentLayer->getLayer());
}

tk::shared_ptr<Layer> Layer::duplicate()
{
    auto layer = LayerSuite().DuplicateLayer(m_layer);
    return LayerFactory::createLayer(layer);
}

void Layer::Delete()
{
    LayerSuite().DeleteLayer(m_layer);
}

LayerSamplingQual Layer::getSamplingQuality()
{
    return LayerSuite().GetLayerSamplingQuality(m_layer);
}

void Layer::setSamplingQuality(LayerSamplingQual quality)
{
    LayerSuite().SetLayerSamplingQuality(m_layer, quality);
}

int Layer::numEffects()
{
    return EffectSuite().getLayerNumEffects(m_layer);
}

tk::shared_ptr<OneDProperty> CameraLayer::Zoom()
{
    auto property = getProperty(LayerStream::ZOOM);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::DepthOfField()
{
    auto property = getProperty(LayerStream::DEPTH_OF_FIELD);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::FocusDistance()
{
    auto property = getProperty(LayerStream::FOCUS_DISTANCE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::Aperture()
{
    auto property = getProperty(LayerStream::APERTURE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::BlurLevel()
{
    auto property = getProperty(LayerStream::BLUR_LEVEL);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisShape()
{
    auto property = getProperty(LayerStream::IRIS_SHAPE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisRotation()
{
    auto property = getProperty(LayerStream::IRIS_ROTATION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisRoundness()
{
    auto property = getProperty(LayerStream::IRIS_ROUNDNESS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisAspectRatio()
{
    auto property = getProperty(LayerStream::IRIS_ASPECT_RATIO);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisDiffractionFringe()
{
    auto property = getProperty(LayerStream::IRIS_DIFFRACTION_FRINGE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisHighlightGain()
{
    auto property = getProperty(LayerStream::IRIS_HIGHLIGHT_GAIN);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisHighlightThreshold()
{
    auto property = getProperty(LayerStream::IRIS_HIGHLIGHT_THRESHOLD);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> CameraLayer::IrisHighlightSaturation()
{
    auto property = getProperty(LayerStream::IRIS_HIGHLIGHT_SATURATION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::Intensity()
{
    auto property = getProperty(LayerStream::INTENSITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::ConeAngle()
{
    auto property = getProperty(LayerStream::CONE_ANGLE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::ConeFeather()
{
    auto property = getProperty(LayerStream::CONE_FEATHER);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::ShadowDarkness()
{
    auto property = getProperty(LayerStream::SHADOW_DARKNESS);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::ShadowDiffusion()
{
    auto property = getProperty(LayerStream::SHADOW_DIFFUSION);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::LightFalloffType()
{
    auto property = getProperty(LayerStream::LIGHT_FALLOFF_TYPE);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::LightFalloffStart()
{
    auto property = getProperty(LayerStream::LIGHT_FALLOFF_START);
    return std::static_pointer_cast<OneDProperty>(property);
}

tk::shared_ptr<OneDProperty> LightLayer::LightFalloffDistance()
{
    auto property = getProperty(LayerStream::LIGHT_FALLOFF_DISTANCE);
    return std::static_pointer_cast<OneDProperty>(property);
}
