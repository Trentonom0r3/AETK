/*****************************************************************/ /**
                                                                     * \file   Effects.hpp
                                                                     * \brief
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef EFFECTS_HPP
#define EFFECTS_HPP

#include <AETK/AEGP/Core/Core.hpp>

class BaseProperty;
class Layer;
/**
 * @brief The Effect class represents an After Effects effect.
 *
 */
class Effect
{
  public:
    Effect() : m_effect(nullptr)
    // m_key(m_effSuite.getInstalledKeyFromLayerEffect(m_effect))
    {
    }
    Effect(EffectRefPtr effect) : m_effect(effect){};

    ~Effect() = default;
    static tk::shared_ptr<Effect> apply(tk::shared_ptr<Layer> layer, const std::string &name);
    std::string name();      // get the name of the effect
    std::string matchName(); // get the match name of the effect
    std::string category();  // get the category of the effect

    tk::shared_ptr<BaseProperty> param(int index);               // get the parameter at the index
    tk::shared_ptr<BaseProperty> param(const std::string &name); // get the parameter by name

    void callGeneric(double time, PF_Cmd cmd, void *extra); // call the generic function of the effect

    tk::shared_ptr<Effect> duplicate(); // duplicate the effect

  private:
    EffectRefPtr m_effect;
    int m_key;
};

#endif // EFFECTS_HPP
