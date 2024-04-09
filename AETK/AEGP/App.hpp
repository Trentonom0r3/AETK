/*****************************************************************/ /**
                                                                     * \file   App.hpp
                                                                     * \brief  The main application class
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/

#ifndef APP_HPP
#define APP_HPP

#include <AETK/AEGP/Core/Core.hpp>

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

    template <typename T> static void Alert(const T &data)
    {
        std::ostringstream stream;

        // Check if T is already a string to avoid unnecessary stream operations
        if constexpr (std::is_same_v<T, std::string>)
        {
            UtilitySuite().reportInfo(data);
        }
        else
        {
            // Try to stream the data into the string stream
            stream << data;
            UtilitySuite().reportInfo(stream.str());
        }
    }

    /**
     * @brief
     * Get the main window (HWND) for AE
     *
     * @return
     * The main window as a void pointer, cast to platform specific type
     */
    static void *GetWindow();
    /**
     * @brief Get the current project file path
     *
     * \return
     * The file path as a string
     */
    static std::string UserPluginPath();

    /**
     * @brief Get the path to the folder containing plugins.
     *
     * \return
     * Folder path as a string
     */
    static std::string AllPluginPath();

    /**
     * @brief Get the path to the AE application
     *
     * \return
     * Application path as a string
     */
    static std::string AppPath();

    /**
     * @brief Get the Color of the Paint Palette
     *
     * @param useForeground
     * - If true, get the foreground color, else get the background color
     *
     * \return
     * ColorVal
     */
    static ColorVal BrushColor(bool useForeground);

    /**
     * @brief Set the color of the Paint Palette
     *
     * @param color
     * The color to set
     * @param useForeground
     * - If true, set the foreground color, else set the background color
     */
    static void SetBrushColor(ColorVal color, bool useForeground);
    // no function available to swap color being used in paint palette
    /**
     * @brief Get the current color of the Character Palette, based on which is
     * in the front.
     *
     * @return
     * ColorVal
     */
    static ColorVal CharColor();

    /**
     * @brief Set the color of the Character Palette
     *
     * @param color
     * The color to set
     * @param useFill
     * - If true, set the fill color, else set the stroke color
     */
    static void CharColor(ColorVal color, bool useFill);
};

#endif /* APP_HPP */
