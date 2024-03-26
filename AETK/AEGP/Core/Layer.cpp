#include "AETK/AEGP/Core/Layer.hpp"
#include "AETK/AEGP/Core/Items.hpp"
#include "AETK/AEGP/Core/Effects.hpp"

std::shared_ptr<BaseProperty> AE::Layer::getProperty(AE_LayerStream stream)
{
    auto property = m_streamSuite.GetNewLayerStream(m_layer, stream);
    AE_StreamGroupingType groupType =
        m_dynamicStreamSuite.GetStreamGroupingType(property);

    // Check if the stream represents a group and handle accordingly
    if (groupType == AE_StreamGroupingType::INDEXED_GROUP ||
        groupType == AE_StreamGroupingType::NAMED_GROUP)
    {
        return std::make_shared<PropertyGroup>(property);
    }
    else if (groupType == AE_StreamGroupingType::LEAF)
    {
        // Proceed with the original logic for individual properties
        AE_StreamType streamType = m_streamSuite.GetStreamType(property);
        switch (streamType)
        {
        case AE_StreamType::OneD:
            return std::make_shared<OneDProperty>(property);
        case AE_StreamType::TwoD:
        case AE_StreamType::TwoD_SPATIAL:
            return std::make_shared<TwoDProperty>(property);
        case AE_StreamType::ThreeD:
        case AE_StreamType::ThreeD_SPATIAL:
            return std::make_shared<ThreeDProperty>(property);
        case AE_StreamType::COLOR:
            return std::make_shared<ColorProperty>(property);
        case AE_StreamType::MARKER:
            return std::make_shared<MarkerProperty>(property);
        case AE_StreamType::LAYER_ID:
            return std::make_shared<LayerIDProperty>(property);
        case AE_StreamType::MASK_ID:
            return std::make_shared<MaskIDProperty>(property);
        case AE_StreamType::MASK:
            return std::make_shared<MaskOutlineProperty>(property);
        case AE_StreamType::TEXT_DOCUMENT:
            return std::make_shared<TextDocumentProperty>(property);
        // Add additional cases as necessary for other property types
        default:
            return std::make_shared<BaseProperty>(
                property); // Fallback for unrecognized or generic properties
        }
    }
    return nullptr;
}

std::shared_ptr < ThreeDProperty > AE::Layer::Position()
{
	auto property = getProperty(AE_LayerStream::POSITION);
	return std::static_pointer_cast<ThreeDProperty>(property);
}

std::shared_ptr<ThreeDProperty> AE::Layer::Scale()
{
    auto property = getProperty(AE_LayerStream::SCALE);
	return std::static_pointer_cast<ThreeDProperty>(property);
}

std::shared_ptr<ThreeDProperty> AE::Layer::Rotation()
{
    auto property = getProperty(AE_LayerStream::ROTATION);
	return std::static_pointer_cast<ThreeDProperty>(property);
}

std::shared_ptr<ThreeDProperty> AE::Layer::AnchorPoint()
{
    auto property = getProperty(AE_LayerStream::ANCHORPOINT);
	return std::static_pointer_cast<ThreeDProperty>(property);
}

 std::shared_ptr<OneDProperty> AE::Layer::Opacity()
{
     auto property = getProperty(AE_LayerStream::OPACITY);
	return std::static_pointer_cast<OneDProperty>(property);
}

 std::shared_ptr<OneDProperty> AE::Layer::RotationX()
{
	auto property = getProperty(AE_LayerStream::ROTATE_X);
	return std::static_pointer_cast<OneDProperty>(property);
}

 std::shared_ptr<OneDProperty> AE::Layer::RotationY()
{
	auto property = getProperty(AE_LayerStream::ROTATE_Y);
	return std::static_pointer_cast<OneDProperty>(property);
}

 std::shared_ptr<OneDProperty> AE::Layer::RotationZ()
{
	auto property = getProperty(AE_LayerStream::ROTATE_Z);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<MarkerProperty> AE::Layer::Marker()
{
	auto property = getProperty(AE_LayerStream::MARKER);
	return std::static_pointer_cast<MarkerProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::AcceptsShadows()
{
	auto property = getProperty(AE_LayerStream::ACCEPTS_SHADOWS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::AcceptsLights()
{
    auto property = getProperty(AE_LayerStream::ACCEPTS_LIGHTS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::AmbientCoeff()
{
    auto property = getProperty(AE_LayerStream::AMBIENT_COEFF);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::DiffuseCoeff()
{
    auto property = getProperty(AE_LayerStream::DIFFUSE_COEFF);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::SpecularIntensity()
{
    auto property = getProperty(AE_LayerStream::SPECULAR_INTENSITY);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::SpecularShininess()
{
    auto property = getProperty(AE_LayerStream::SPECULAR_SHININESS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::CastsShadows()
{
    auto property = getProperty(AE_LayerStream::CASTS_SHADOWS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::LightTransmission()
{
    auto property = getProperty(AE_LayerStream::LIGHT_TRANSMISSION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::Metal()
{
    auto property = getProperty(AE_LayerStream::METAL);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ReflectionIntensity()
{
    auto property = getProperty(AE_LayerStream::REFLECTION_INTENSITY);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ReflectionSharpness()
{
    auto property = getProperty(AE_LayerStream::REFLECTION_SHARPNESS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ReflectionRolloff()
{
    auto property = getProperty(AE_LayerStream::REFLECTION_ROLLOFF);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::TransparencyCoeff()
{
    auto property = getProperty(AE_LayerStream::TRANSPARENCY_COEFF);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::TransparencyRolloff()
{
    auto property = getProperty(AE_LayerStream::TRANSPARENCY_ROLLOFF);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::IndexOfRefraction()
{
    auto property = getProperty(AE_LayerStream::INDEX_OF_REFRACTION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ExtrusionBevelStyle()
{
    auto property = getProperty(AE_LayerStream::EXTRUSION_BEVEL_STYLE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ExtrusionBevelDirection()
{
    auto property = getProperty(AE_LayerStream::EXTRUSION_BEVEL_DIRECTION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ExtrusionBevelDepth()
{
    auto property = getProperty(AE_LayerStream::EXTRUSION_BEVEL_DEPTH);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ExtrusionHoleBevelDepth()
{
    auto property = getProperty(AE_LayerStream::EXTRUSION_HOLE_BEVEL_DEPTH);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::ExtrusionDepth()
{
    auto property = getProperty(AE_LayerStream::EXTRUSION_DEPTH);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::PlaneCurvature()
{
    auto property = getProperty(AE_LayerStream::PLANE_CURVATURE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::AVLayer::PlaneSubdivision()
{
    auto property = getProperty(AE_LayerStream::PLANE_SUBDIVISION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<AE::Layer> AE::Layer::activeLayer()
{
    auto layerptr = LayerSuite9().GetActiveLayer();
    return LayerFactory::createLayer(layerptr);
}

std::string AE::Layer::getName()
{
    std::string type = std::get<0>(m_layerSuite.GetLayerName(m_layer));
    return type;
}

std::string AE::Layer::getMatchName()
{
    std::string type = std::get<1>(m_layerSuite.GetLayerName(m_layer));
	return type;
}

void AE::Layer::setName(const std::string &name) {
    m_layerSuite.SetLayerName(m_layer, name);
}

int AE::Layer::getIndex() 
{
    return m_layerSuite.GetLayerIndex(m_layer);
}

void AE::Layer::setIndex(int index) {
    m_layerSuite.ReorderLayer(m_layer, index);
}

std::shared_ptr<AE::Item> AE::Layer::sourceItem() 
{
    auto item = m_layerSuite.GetLayerSourceItem(m_layer);
	return ItemFactory::createItem(item);
}

std::shared_ptr<AE::CompItem> AE::Layer::parentComp() 
{
	auto comp = m_layerSuite.GetLayerParentComp(m_layer);
    return std::make_shared<AE::CompItem>(comp);
}

AE_LayerQual AE::Layer::getQuality() 
{
    return m_layerSuite.GetLayerQuality(m_layer);
}

void AE::Layer::setQuality(AE_LayerQual quality) {
    m_layerSuite.SetLayerQuality(m_layer, quality);
}

bool AE::Layer::isLayerVideoOn() 
{
    return m_layerSuite.IsLayerVideoReallyOn(m_layer);
}

bool AE::Layer::isLayerAudioOn() 
{
    return m_layerSuite.IsLayerAudioReallyOn(m_layer);
}

double AE::Layer::currentTime() 
{
    return TimeToSeconds(m_layerSuite.GetLayerCurrentTime(m_layer, AE_LTimeMode::CompTime));
}

double AE::Layer::duration() 
{
    return TimeToSeconds(
        m_layerSuite.GetLayerDuration(m_layer, AE_LTimeMode::CompTime));
}

double AE::Layer::offset()
{
    return TimeToSeconds(m_layerSuite.GetLayerOffset(m_layer));
}

void AE::Layer::setOffset(double offset) {
	m_layerSuite.SetLayerOffset(m_layer, SecondsToTime(offset));
}

double AE::Layer::stretch()
{
    return RATIO2FLOAT(m_layerSuite.GetLayerStretch(m_layer));
}

void AE::Layer::setStretch(double stretch) {
}

// TODO Implement Tis
bool AE::Layer::isFlagSet(AE_LayerFlag flag) 
{
    return false;
}
// TODO Implement Tis
void AE::Layer::setFlag(AE_LayerFlag flag, bool value) {}

bool AE::Layer::is3DLayer() 
{
    return m_layerSuite.IsLayer3D(m_layer);
}

bool AE::Layer::is2DLayer() 
{
    return m_layerSuite.IsLayer2D(m_layer);
}

bool AE::Layer::VideoActive() 
{
    // TODO return m_layerSuite.IsVideoActive(m_layer);   IMPLEMENT LATER
    return false;
}

std::shared_ptr<AE::Layer> AE::Layer::parentLayer()  {
    auto layer = m_layerSuite.GetLayerParent(m_layer);
    return LayerFactory::createLayer(layer);
}

void AE::Layer::setParentLayer(std::shared_ptr<AE::Layer> parentLayer) {
    m_layerSuite.SetLayerParent(m_layer, parentLayer->getLayer());
}

std::shared_ptr<AE::Layer> AE::Layer::duplicate() {
    auto layer = m_layerSuite.DuplicateLayer(m_layer);
	return LayerFactory::createLayer(layer);
}

void AE::Layer::Delete() {
    m_layerSuite.DeleteLayer(m_layer);
}

AE_LayerSamplingQual AE::Layer::getSamplingQuality() 
{
    return m_layerSuite.GetLayerSamplingQuality(m_layer);
}

void AE::Layer::setSamplingQuality(AE_LayerSamplingQual quality) {
    m_layerSuite.SetLayerSamplingQuality(m_layer, quality);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::Zoom()
{
    auto property = getProperty(AE_LayerStream::ZOOM);
    return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::DepthOfField()
{
    auto property = getProperty(AE_LayerStream::DEPTH_OF_FIELD);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::FocusDistance()
{
    auto property = getProperty(AE_LayerStream::FOCUS_DISTANCE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::Aperture()
{
    auto property = getProperty(AE_LayerStream::APERTURE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::BlurLevel()
{
    auto property = getProperty(AE_LayerStream::BLUR_LEVEL);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisShape()
{
    auto property = getProperty(AE_LayerStream::IRIS_SHAPE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisRotation()
{
    auto property = getProperty(AE_LayerStream::IRIS_ROTATION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisRoundness()
{
    auto property = getProperty(AE_LayerStream::IRIS_ROUNDNESS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisAspectRatio()
{
    auto property = getProperty(AE_LayerStream::IRIS_ASPECT_RATIO);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisDiffractionFringe()
{
    auto property = getProperty(AE_LayerStream::IRIS_DIFFRACTION_FRINGE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisHighlightGain()
{
    auto property = getProperty(AE_LayerStream::IRIS_HIGHLIGHT_GAIN);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisHighlightThreshold() {
    auto property = getProperty(AE_LayerStream::IRIS_HIGHLIGHT_THRESHOLD);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::CameraLayer::IrisHighlightSaturation()
{
    auto property = getProperty(AE_LayerStream::IRIS_HIGHLIGHT_SATURATION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::Intensity()
{
    auto property = getProperty(AE_LayerStream::INTENSITY);
    return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::ConeAngle()
{
    auto property = getProperty(AE_LayerStream::CONE_ANGLE);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::ConeFeather()
{
    auto property = getProperty(AE_LayerStream::CONE_FEATHER);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::ShadowDarkness()
{
    auto property = getProperty(AE_LayerStream::SHADOW_DARKNESS);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::ShadowDiffusion()
{
	auto property = getProperty(AE_LayerStream::SHADOW_DIFFUSION);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::LightFalloffType()
{
    auto property = getProperty(AE_LayerStream::LIGHT_FALLOFF_TYPE);
    return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::LightFalloffStart()
{
    auto property = getProperty(AE_LayerStream::LIGHT_FALLOFF_START);
	return std::static_pointer_cast<OneDProperty>(property);
}

std::shared_ptr<OneDProperty> AE::LightLayer::LightFalloffDistance()
{
    auto property = getProperty(AE_LayerStream::LIGHT_FALLOFF_DISTANCE);
	return std::static_pointer_cast<OneDProperty>(property);
}
