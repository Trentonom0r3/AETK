#include <AETK/AEGP/Layers.hpp>
#include <AETK/AEGP/Util/Effects.hpp>
#include <AETK/AEGP/Util/Properties.hpp>

tk::shared_ptr<Effect> Effect::apply(tk::shared_ptr<Layer> layer, const std::string &matchName)
{
    try
    {

        AEGP_InstalledEffectKey currentKey = 0; // Assuming 0 is a valid initial key or indicates 'start'.
        A_long numEffects = EffectSuite().getNumInstalledEffects();

        for (A_long i = 0; i < numEffects; ++i)
        {
            std::string currentMatchName = EffectSuite().getEffectMatchName(currentKey);
            if (currentMatchName == matchName)
            {
                // Match found, apply effect.
                EffectRefPtr effectRef = EffectSuite().applyEffect(layer->getLayer(), currentKey);

                return tk::make_shared<Effect>(effectRef);
            }
            currentKey = EffectSuite().getNextInstalledEffect(currentKey);
        }

        return nullptr;
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

std::string Effect::name()
{
    try
    {
        return EffectSuite().getEffectName(m_key);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

std::string Effect::matchName()
{
    return EffectSuite().getEffectMatchName(m_key);
}

std::string Effect::category()
{
    return EffectSuite().getEffectCategory(m_key);
}

tk::shared_ptr<BaseProperty> Effect::param(int index)
{
    auto stream = StreamSuite().GetNewEffectStreamByIndex(m_effect, index);

    return tk::make_shared<BaseProperty>(stream);
}

tk::shared_ptr<BaseProperty> Effect::param(const std::string &name)
{
    for (int i = 0; i < StreamSuite().GetEffectNumParamStreams(m_effect); ++i)
    {
        std::string currentName =
            StreamSuite().GetStreamName(StreamSuite().GetNewEffectStreamByIndex(m_effect, i), true);
        if (currentName == name)
        {
            auto stream = StreamSuite().GetNewEffectStreamByIndex(m_effect, i);
            return tk::make_shared<BaseProperty>(stream);
        }
    }
    return nullptr;
}

void Effect::callGeneric(double time, PF_Cmd cmd, void *extra) {}

tk::shared_ptr<Effect> Effect::duplicate()
{
    EffectRefPtr effectRef = EffectSuite().duplicateEffect(m_effect);
    return tk::make_shared<Effect>(effectRef);
}
