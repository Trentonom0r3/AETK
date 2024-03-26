#include "Effects.hpp"
#include "Layer.hpp"
#include "Base/Property.hpp"

std::shared_ptr<AE::Effect> AE::Effect::apply(std::shared_ptr<AE::Layer> layer,
                                      const std::string &matchName)
{
    AEGP_InstalledEffectKey currentKey =
        0; // Assuming 0 is a valid initial key or indicates 'start'.
    A_long numEffects = EffectSuite4().getNumInstalledEffects();

    for (A_long i = 0; i < numEffects; ++i)
    {
        std::string currentMatchName =
            EffectSuite4().getEffectMatchName(currentKey);
        if (currentMatchName == matchName)
        {
            // Match found, apply effect.
            EffectRefPtr effectRef =
                EffectSuite4().applyEffect(layer->getLayer(), currentKey);
            // Assuming EffectRefPtr can be converted to std::shared_ptr<Effect>
            return std::make_shared<AE::Effect>(effectRef);
        }
        currentKey = EffectSuite4().getNextInstalledEffect(currentKey);
    }

    return nullptr;
}

std::string AE::Effect::name() 
{
    return m_effSuite.getEffectName(m_key);
}

std::string AE::Effect::matchName() 
{
    return m_effSuite.getEffectMatchName(m_key);
}

std::string AE::Effect::category() 
{
    return m_effSuite.getEffectCategory(m_key);
}

std::shared_ptr<BaseProperty> AE::Effect::param(int index) 
{
    auto stream = StreamSuite6().GetNewEffectStreamByIndex(m_effect, index);

    return std::make_shared<BaseProperty>(stream);
}

std::shared_ptr<BaseProperty> AE::Effect::param(const std::string &name) 
{
    for (int i = 0; i < StreamSuite6().GetEffectNumParamStreams(m_effect); ++i)
    {
        std::string currentName = StreamSuite6().GetStreamName(StreamSuite6().GetNewEffectStreamByIndex(m_effect, i), true);
        if (currentName == name)
        {
			auto stream = StreamSuite6().GetNewEffectStreamByIndex(m_effect, i);
			return std::make_shared<BaseProperty>(stream);
		}
	}
    return nullptr;
}

void AE::Effect::callGeneric(double time, PF_Cmd cmd, void *extra) {}

std::shared_ptr<AE::Effect> AE::Effect::duplicate()
{
    EffectRefPtr effectRef = EffectSuite4().duplicateEffect(m_effect);
	return std::make_shared<AE::Effect>(effectRef);
}
