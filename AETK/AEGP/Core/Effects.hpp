/*****************************************************************/ /**
                                                                     * \file
                                                                     *Effects.hpp
                                                                     * \brief  A
                                                                     *header
                                                                     *file for
                                                                     *the
                                                                     *Effects
                                                                     *class
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef EFFECTS_HPP
#define EFFECTS_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

class BaseProperty;
namespace AE
{
//class BaseProperty;
class Layer;
/**
 * @brief The Effect class represents an After Effects effect.
 * 
 */
class Effect
{
  public:
    Effect()
        : m_effect(nullptr), m_effSuite(EffectSuite4())
          //m_key(m_effSuite.getInstalledKeyFromLayerEffect(m_effect))
    {
    }
    Effect(EffectRefPtr effect) : m_effect(effect), m_effSuite(EffectSuite4())
    {
		m_key = m_effSuite.getInstalledKeyFromLayerEffect(m_effect);
    }
    Effect(EffectRefPtr effect, StreamRefPtr stream)
        : m_effect(effect), m_effSuite(EffectSuite4()), m_stream(stream)
    {

    }

    ~Effect() = default;
    static std::shared_ptr<AE::Effect> apply(std::shared_ptr<AE::Layer> layer,
                                         const std::string &name);
    std::string name() ; // get the name of the effect
    std::string matchName() ; // get the match name of the effect
    std::string category() ; // get the category of the effect

    std::shared_ptr<BaseProperty> param(int index) ; // get the parameter at the index
    std::shared_ptr<BaseProperty> param(const std::string &name) ; // get the parameter by name

    void callGeneric(double time, PF_Cmd cmd, void *extra); // call the generic function of the effect

    std::shared_ptr<Effect> duplicate(); // duplicate the effect

  private:
    EffectRefPtr m_effect;
    EffectSuite4 m_effSuite;
    StreamRefPtr m_stream;
    int m_key;
};

} // namespace AE

#endif // EFFECTS_HPP
