/*****************************************************************/ /**
                                                                     * \file   App.hpp
                                                                     * \brief  The main application class
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/


#include <AETK/AEGP/Core/Core.hpp>
#include <AETK/AEGP/App.hpp>

void *App::GetWindow()
{
    try
    {
        void *window = UtilitySuite().getMainHWND();
        return window;
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

std::string App::UserPluginPath()
{
    try
    {
        return UtilitySuite().getPluginPath(PluginPathType::USER_PLUGIN);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

std::string App::AllPluginPath()
{
    try
    {
        return UtilitySuite().getPluginPath(PluginPathType::ALLUSER_PLUGIN);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

std::string App::AppPath()
{
    try
    {
        return UtilitySuite().getPluginPath(PluginPathType::APP);
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

ColorVal App::BrushColor(bool useForeground)
{
    try
    {
        if (useForeground)
        {
            return UtilitySuite().getPaintPalForeColor();
        }
        else
        {
            return UtilitySuite().getPaintPalBackColor();
        }
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

void App::SetBrushColor(ColorVal color, bool useForeground)
{
    try
    {
        if (useForeground)
        {
            UtilitySuite().setPaintPalForeColor(color);
        }
        else
        {
            UtilitySuite().setPaintPalBackColor(color);
        }
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

ColorVal App::CharColor()
{
    try
    {
        if (UtilitySuite().charPalIsFillColorUIFrontmost())
        {
            return std::get<1>(UtilitySuite().getCharPalFillColor());
        }
        else
        {
            return std::get<1>(UtilitySuite().getCharPalStrokeColor());
        }
    }
    catch (const AEException &e)
    {
        throw e;
    }
}

void App::CharColor(ColorVal color, bool useFill)
{
    try
    {
        if (useFill)
        {
            UtilitySuite().setCharPalFillColor(color);
        }
        else
        {
            UtilitySuite().setCharPalStrokeColor(color);
        }
    }
    catch (const AEException &e)
    {
        throw e;
    }
}