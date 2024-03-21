/*****************************************************************/ /**
                                                                     * \file
                                                                     *AELayer.hpp
                                                                     * \brief
                                                                     *Layer
                                                                     *class for
                                                                     *After
                                                                     *Effects
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef AELAYER_HPP
#define AELAYER_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"
//#include <Item.hpp>
//#include <Comp.hpp>
namespace AE
{
class Item;
class CompItem;
/**
 * \class Layer
 * \brief Represents a layer in After Effects.
 *
 * This class provides functionality to manipulate and retrieve information
 * about a layer in After Effects.
 */
class Layer
{
  public:
    /**
     * \brief Default constructor for Layer class.
     */
    Layer(){};

    /**
     * \brief Virtual destructor for Layer class.
     */
    virtual ~Layer() = default;

    /**
     * \brief Constructor for Layer class that takes a LayerPtr as input.
     * \param layer A pointer to a Layer object.
     */
    Layer(LayerPtr layer) : m_layer(layer){};

    /**
     * \brief Get the underlying LayerPtr object.
     * \return LayerPtr A pointer to the underlying Layer object.
     */
    LayerPtr getLayer() { return m_layer; }

    /**
     * \brief Set the underlying LayerPtr object.
     * \param layer A pointer to a Layer object.
     */
    void setLayer(LayerPtr layer) { m_layer = layer; }

    /**
     * \brief Get the active layer.
     * \return Layer The active layer.
     */
    static Layer activeLayer();

    /**
     * \brief Get the index of the layer.
     * \return int The index of the layer.
     */
    int index() const;

    /**
     * \brief Reorder the layer to a new index.
     * \param newIndex The new index for the layer.
     */
    void reOrder(int newIndex);

    /**
     * \brief Get the source item of the layer.
     * \return std::shared_ptr<Item> A shared pointer to the source item of the
     * layer.
     */
    std::shared_ptr<Item> source() const;

    /**
     * \brief Get the source ID of the layer.
     * \return int The source ID of the layer.
     */
    int sourceID() const;

    /**
     * \brief Get the parent composition of the layer.
     * \return CompItem The parent composition of the layer.
     */
    CompItem parentComp() const;

    /**
     * \brief Get the name of the layer.
     * \return std::string The name of the layer.
     */
    std::string name() const;

    /**
     * \brief Get the name of the source of the layer.
     * \return std::string The name of the source of the layer.
     */
    std::string sourceName() const;

    /**
     * \brief Get the quality of the layer.
     * \return AE_LayerQual The quality of the layer.
     */
    AE_LayerQual quality() const;

    /**
     * \brief Set the quality of the layer.
     * \param quality The quality of the layer.
     */
    void setQuality(AE_LayerQual quality);

    /**
     * \brief Check if video is active for the layer.
     * \return bool True if video is active, false otherwise.
     */
    bool videoActive() const;

    /**
     * \brief Check if audio is active for the layer.
     * \return bool True if audio is active, false otherwise.
     */
    bool audioActive() const;

    /**
     * \brief Check if effects are active for the layer.
     * \return bool True if effects are active, false otherwise.
     */
    bool effectsActive() const;

    /**
     * \brief Check if motion blur is active for the layer.
     * \return bool True if motion blur is active, false otherwise.
     */
    bool motionBlur() const;

    /**
     * \brief Check if frame blending is active for the layer.
     * \return bool True if frame blending is active, false otherwise.
     */
    bool frameBlending() const;

    /**
     * \brief Check if the layer is locked.
     * \return bool True if the layer is locked, false otherwise.
     */
    bool locked() const;

    /**
     * \brief Check if the layer is shy.
     * \return bool True if the layer is shy, false otherwise.
     */
    bool shy() const;

    /**
     * \brief Check if the layer is collapsed.
     * \return bool True if the layer is collapsed, false otherwise.
     */
    bool collapsed() const;

    /**
     * \brief Check if auto-orientation is active for the layer.
     * \return bool True if auto-orientation is active, false otherwise.
     */
    bool autoOrient() const;

    /**
     * \brief Check if the layer is an adjustment layer.
     * \return bool True if the layer is an adjustment layer, false otherwise.
     */
    bool adjustmentLayer() const;

    /**
     * \brief Check if time remapping is active for the layer.
     * \return bool True if time remapping is active, false otherwise.
     */
    bool timeRemap() const;

    /**
     * \brief Check if the layer is in 3D mode.
     * \return bool True if the layer is in 3D mode, false otherwise.
     */
    bool is3D() const;

    /**
     * \brief Check if the layer is set to look at the camera.
     * \return bool True if the layer is set to look at the camera, false
     * otherwise.
     */
    bool lookAtCamera() const;

    /**
     * \brief Check if the layer is set to look at the point of interest.
     * \return bool True if the layer is set to look at the point of interest,
     * false otherwise.
     */
    bool lookAtPOI() const;

    /**
     * \brief Check if the layer is soloed.
     * \return bool True if the layer is soloed, false otherwise.
     */
    bool solo() const;

    /**
     * \brief Check if the layer's markers are locked.
     * \return bool True if the layer's markers are locked, false otherwise.
     */
    bool markersLocked() const;

    /**
     * \brief Check if the layer is a null layer.
     * \return bool True if the layer is a null layer, false otherwise.
     */
    bool nullLayer() const;

    /**
     * \brief Check if locked masks are hidden for the layer.
     * \return bool True if locked masks are hidden, false otherwise.
     */
    bool hideLockedMask() const;

    /**
     * \brief Check if the layer is a guide layer.
     * \return bool True if the layer is a guide layer, false otherwise.
     */
    bool guideLayer() const;

    /**
     * \brief Check if the layer is set to render separately.
     * \return bool True if the layer is set to render separately, false
     * otherwise.
     */
    bool renderSeparately() const;

    /**
     * \brief Check if the layer is an environment layer.
     * \return bool True if the layer is an environment layer, false otherwise.
     */
    bool environmentLayer() const;

    /**
     * \brief Set the video active state for the layer.
     * \param active The video active state.
     */
    void setVideoActive(bool active);

    /**
     * \brief Set the audio active state for the layer.
     * \param active The audio active state.
     */
    void setAudioActive(bool active);

    /**
     * \brief Set the effects active state for the layer.
     * \param active The effects active state.
     */
    void setEffectsActive(bool active);

    /**
     * \brief Set the motion blur state for the layer.
     * \param active The motion blur state.
     */
    void setMotionBlur(bool active);

    /**
     * \brief Set the frame blending state for the layer.
     * \param active The frame blending state.
     */
    void setFrameBlending(bool active);

    /**
     * \brief Set the locked state for the layer.
     * \param active The locked state.
     */
    void setLocked(bool active);

    /**
     * \brief Set the shy state for the layer.
     * \param active The shy state.
     */
    void setShy(bool active);

    /**
     * \brief Set the collapsed state for the layer.
     * \param active The collapsed state.
     */
    void setCollapsed(bool active);

    /**
     * \brief Set the auto-orientation state for the layer.
     * \param active The auto-orientation state.
     */
    void setAutoOrient(bool active);

    /**
     * \brief Set the adjustment layer state for the layer.
     * \param active The adjustment layer state.
     */
    void setAdjustmentLayer(bool active);

    /**
     * \brief Set the time remap state for the layer.
     * \param active The time remap state.
     */
    void setTimeRemap(bool active);

    /**
     * \brief Set the 3D state for the layer.
     * \param active The 3D state.
     */
    void setIs3D(bool active);

    /**
     * \brief Set the look at camera state for the layer.
     * \param active The look at camera state.
     */
    void setLookAtCamera(bool active);

    /**
     * \brief Set the look at point of interest state for the layer.
     * \param active The look at point of interest state.
     */
    void setLookAtPOI(bool active);

    /**
     * \brief Set the solo state for the layer.
     * \param active The solo state.
     */
    void setSolo(bool active);

    /**
     * \brief Set the markers locked state for the layer.
     * \param active The markers locked state.
     */
    void setMarkersLocked(bool active);

    /**
     * \brief Set the null layer state for the layer.
     * \param active The null layer state.
     */
    void setNullLayer(bool active);

    /**
     * \brief Set the hide locked mask state for the layer.
     * \param active The hide locked mask state.
     */
    void setHideLockedMask(bool active);

    /**
     * \brief Set the guide layer state for the layer.
     * \param active The guide layer state.
     */
    void setGuideLayer(bool active);

    /**
     * \brief Set the render separately state for the layer.
     * \param active The render separately state.
     */
    void setRenderSeparately(bool active);

    /**
     * \brief Set the environment layer state for the layer.
     * \param active The environment layer state.
     */
    void setEnvironmentLayer(bool active);

    /**
     * \brief Check if video is on for the layer.
     * \return bool True if video is on, false otherwise.
     */
    bool isVideoOn() const;

    /**
     * \brief Check if audio is on for the layer.
     * \return bool True if audio is on, false otherwise.
     */
    bool isAudioOn() const;

    /**
     * \brief Get the time of the layer.
     * \return double The time of the layer.
     */
    double time() const;

    /**
     * \brief Get the in point of the layer.
     * \return double The in point of the layer.
     */
    double inPoint() const;

    /**
     * \brief Get the duration of the layer.
     * \return double The duration of the layer.
     */
    double duration() const;

    /**
     * \brief Set the in point and duration of the layer.
     * \param inPoint The in point of the layer.
     * \param duration The duration of the layer.
     */
    void setInPointAndDuration(double inPoint, double duration);

    /**
     * \brief Get the offset of the layer.
     * \return double The offset of the layer.
     */
    double offset() const;

    /**
     * \brief Set the offset of the layer.
     * \param offset The offset of the layer.
     */
    void setOffset(double offset);

    /**
     * \brief Get the stretch of the layer.
     * \return double The stretch of the layer.
     */
    double stretch() const;

    /**
     * \brief Set the stretch of the layer.
     * \param stretch The stretch of the layer.
     */
    void setStretch(double stretch);

    /**
     * \brief Delete the layer.
     */
    void Delete();

    /**
     * \brief Duplicate the layer.
     * \return Layer A duplicate of the layer.
     */
    Layer duplicate();

    /**
     * \brief Get the sampling quality of the layer.
     * \return AE_LayerSamplingQual The sampling quality of the layer.
     */
    AE_LayerSamplingQual samplingQuality() const;

    /**
     * \brief Set the sampling quality of the layer.
     * \param quality The sampling quality of the layer.
     */
    void setSamplingQuality(AE_LayerSamplingQual quality);

  private:
    LayerPtr m_layer;
};
} // namespace AE

#endif // AELAYER_HPP