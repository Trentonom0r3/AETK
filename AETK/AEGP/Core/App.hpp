/*****************************************************************//**
 * \file   App.hpp
 * \brief  A class to interact with the After Effects application
 * Provides utility functions to interact with the application, such as
 * Alerting the user, getting the main window, getting the current project
 * or application path, and getting or setting the color of the paint or
 * text palette.
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#pragma once

#ifndef APP_HPP
#define APP_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

namespace AE
{

class App
{
  public:
    App() = default;
    virtual ~App() = default;

    /**
     * @brief
     * Alert the user with a message
     *
     * @param data
     * The message to display
     */
    void Alert(std::any data) const
    {
        try
        {
            if (data.has_value())
            {
                UtilitySuite6().reportInfo(std::any_cast<std::string>(data));
            }
        }
        catch (const std::bad_any_cast &e)
        {
            throw e;
        }
        catch (const AEException &e)
        {
            throw AEException(e);
        }
    }

    /**
     * @brief
     * Get the main window (HWND) for AE
     *
     * @return
     * The main window as a void pointer, cast to platform specific type
     */
    void *GetWindow() const
    {
        try
        {
            void *window = UtilitySuite6().getMainHWND();
            return window;
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Get the current project file path
     *
     * \return
     * The file path as a string
     */
    std::string UserPluginPath()
    {
        try
        {
            return UtilitySuite6().getPluginPath(
                AE_PluginPathType::USER_PLUGIN);
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Get the path to the folder containing plugins.
     *
     * \return
     * Folder path as a string
     */
    std::string AllPluginPath()
    {
        try
        {
            return UtilitySuite6().getPluginPath(
                AE_PluginPathType::ALLUSER_PLUGIN);
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Get the path to the AE application
     *
     * \return
     * Application path as a string
     */
    std::string AppPath()
    {
        try
        {
            return UtilitySuite6().getPluginPath(AE_PluginPathType::APP);
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Get the Color of the Paint Palette
     *
     * @param useForeground
     * - If true, get the foreground color, else get the background color
     *
     * \return
     * ColorVal
     */
    ColorVal BrushColor(bool useForeground)
    {
        try
        {
            if (useForeground)
            {
                return UtilitySuite6().getPaintPalForeColor();
            }
            else
            {
                return UtilitySuite6().getPaintPalBackColor();
            }
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Set the color of the Paint Palette
     *
     * @param color
     * The color to set
     * @param useForeground
     * - If true, set the foreground color, else set the background color
     */
    void SetBrushColor(ColorVal color, bool useForeground)
    {
        try
        {
            if (useForeground)
            {
                UtilitySuite6().setPaintPalForeColor(color);
            }
            else
            {
                UtilitySuite6().setPaintPalBackColor(color);
            }
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }
    // no function abailable to swap color being used in paint palette
    /**
     * @brief Get the current color of the Character Palette, based on which is
     * in the front.
     *
     * @return
     * ColorVal
     */
    ColorVal CharColor()
    {
        try
        {
            if (UtilitySuite6().charPalIsFillColorUIFrontmost())
            {
                return std::get<1>(UtilitySuite6().getCharPalFillColor());
            }
            else
            {
                return std::get<1>(UtilitySuite6().getCharPalStrokeColor());
            }
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }

    /**
     * @brief Set the color of the Character Palette
     *
     * @param color
     * The color to set
     * @param useFill
     * - If true, set the fill color, else set the stroke color
     */
    void CharColor(ColorVal color, bool useFill)
    {
        try
        {
            if (useFill)
            {
                UtilitySuite6().setCharPalFillColor(color);
            }
            else
            {
                UtilitySuite6().setCharPalStrokeColor(color);
            }
        }
        catch (const AEException &e)
        {
            throw e;
        }
    }
};

} // namespace AE

#endif // APP_HPP
