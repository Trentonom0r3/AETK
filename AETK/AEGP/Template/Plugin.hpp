/**
 * @file Plugin.hpp
 * @brief Plugin interface template for Adobe After Effects plugin development.
 *
 * This header defines the architecture for a plugin, including commands and
 * their lifecycle management within the plugin. It's designed to be used within
 * the Adobe After Effects SDK environment to create custom plugins.
 *
 * @author tjerf
 * @date March 2024
 */

#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include "AETK/AEGP/Core/Core.hpp"
/**
 * @class Command
 * @brief Abstract base class for creating commands within the plugin.
 *
 * This class defines the structure for commands that can be executed by the
 * plugin. Each command is associated with a specific action or behavior.
 */
class Command
{
  public:
    /**
     * Constructs a Command with a name, menu ID, and insertion order.
     * @param name The name of the command.
     * @param menuID The ID of the menu where the command will be inserted.
     * @param after_item Specifies the order of the command within the menu.
     * Defaults to INSERT_SORTED.
     */
    Command(std::string name, MenuID menuID, int after_item = AEGP_MENU_INSERT_SORTED)
        : m_name(name), m_commandSuite(CommandSuite()), m_command(CommandSuite().getUniqueCommand())
    {
        insertCommand(menuID, after_item);
    }
    /**
     * Virtual destructor for cleanup.
     */
    virtual ~Command() = default;
    /**
     * Executes the command's action. Must be implemented by derived classes.
     * This is where you'll execute the command's action or behavior.
     * You'll do whatever logic you'd like here-- AE related or not.
     */
    virtual void execute() = 0;
    /**
     * Updates the state or appearance of the menu item associated with this
     * command. Must be implemented by derived classes.
     *
     * This is used in the updateMenuHook to update the state of the menu item.
     * Use the helper functions to enable, disable, or check the menu item.
     */
    virtual void updateMenu() = 0;
    /**
     * Retrieves the name of the command.
     * @return The command's name.
     */
    std::string getName() const { return m_name; }
    /**
     * Retrieves the command's unique identifier.
     * @return The command's identifier.
     */
    int getCommand() const { return m_command; }

    // Helper functions for command manipulation.
    inline void insertCommand(MenuID menuID, int after_item = AEGP_MENU_INSERT_SORTED)
    {
        m_commandSuite.insertMenuCommand(m_command, m_name, menuID, after_item);
    }
    inline void setCommandName(std::string name) { m_commandSuite.setMenuCommandName(m_command, name); }
    inline void enableCommand(bool enable)
    {
        if (enable)
        {
            m_commandSuite.enableCommand(m_command);
        }
        else
        {
            m_commandSuite.disableCommand(m_command);
        }
    }

    inline void checkCommand(bool check) { m_commandSuite.checkMarkMenuCommand(m_command, check); }

  private:
    std::string m_name;           ///< The command's name.
    int m_command;                ///< The command's unique identifier.
    CommandSuite m_commandSuite; ///< Suite for command operations provided by AE SDK.
};

/**
 * @class Plugin
 * @brief Represents the plugin, managing its commands and lifecycle.
 *
 * This class serves as the central management point for the plugin, handling
 * initialization, command registration, and event hooks.
 *
 * AE Refcons are ignored, as you can use maps to store data instead.
 */
class Plugin
{
  public:
    inline static Plugin *instance;

    Plugin(struct SPBasicSuite *pica_basicP, /* >> */
           AEGP_PluginID aegp_plugin_id,     /* >> */
           AEGP_GlobalRefcon *global_refconV)
        : m_suiteManager(SuiteManager::GetInstance())
    {

        instance = this;
    }
    /**
     * Virtual destructor for cleanup.
     */
    virtual ~Plugin() { instance = nullptr; }

    // Lifecycle event handlers to be implemented by derived classes.//
    /**
     * @brief onInit Initializes the plugin and its commands.
     * Initializes the plugin and its commands.
     * Here, you will add commands to the plugin's command list, and then use the utility functions
     * to register your command hooks (if any).
     */
    virtual void onInit() = 0;

    /**
     * Called when the plugin is being unloaded.
     * This will automatically clean up commands, its up to you to clean up anything else you need to.
     */
    virtual void onDeath() = 0;

    /**
     * Called when the plugin is idle.
     * This is a good place to do any background processing or updating of the UI.
     * This is also where you would utilize the TaskManager to do background processing.
     */
    virtual void onIdle() = 0;

    /**
     * Adds a command to the plugin's command list.
     * @param command A unique pointer to the Command object.
     */
    inline void addCommand(std::unique_ptr<Command> command) { m_commands.push_back(std::move(command)); }

    template <typename T>
    static A_Err EntryPointFunc(struct SPBasicSuite *pica_basicP,  /* >> */
                                A_long major_versionL,             /* >> */
                                A_long minor_versionL,             /* >> */
                                AEGP_PluginID aegp_plugin_id,      /* >> */
                                AEGP_GlobalRefcon *global_refconV) /* << */
    {
        Plugin *plugin = new T(pica_basicP, aegp_plugin_id, global_refconV);
        plugin->onInit();
        return A_Err_NONE;
    }

    // Static hook methods for Adobe After Effects to invoke.   // Static hook
    // methods for Adobe After Effects to invoke.
    inline static A_Err CommandHook(AEGP_GlobalRefcon global_refcon, AEGP_CommandRefcon command_refcon,
                                    AEGP_Command command, AEGP_HookPriority hook_priority, A_Boolean already_handled,
                                    A_Boolean *handled)
    {
        if (instance)
        {
            for (auto &c : instance->m_commands)
            {
                if (c->getCommand() == command)
                {
                    c->execute();
                    *handled = TRUE;
                    return A_Err_NONE;
                }
            }
            // *handled = false;
        }
        // *handled = false;
        return A_Err_NONE;
    }

    inline static A_Err UpdateMenuHook(AEGP_GlobalRefcon global_refcon, AEGP_UpdateMenuRefcon update_menu_refcon,
                                       AEGP_WindowType active_window)
    {
        if (instance)
        {
            for (auto &c : instance->m_commands)
            {
                c->updateMenu();
            }
        }
        return A_Err_NONE;
    }

    inline static A_Err DeathHook(AEGP_GlobalRefcon global_refcon, AEGP_DeathRefcon death_refcon)
    {
        if (instance)
        {
            instance->onDeath();
        }
        return A_Err_NONE;
    }

    inline static A_Err IdleHook(AEGP_GlobalRefcon global_refcon, AEGP_IdleRefcon idle_refcon, A_long *max_sleepPL)
    {
        if (instance)
        {
            instance->onIdle();
        }
        return A_Err_NONE;
    }

    // Methods to register the static hook methods with the Adobe After Effects
    // SDK.
    inline void registerCommandHook()
    {
        RegisterSuite().registerCommandHook(*m_suiteManager.GetPluginID(), AEGP_Command_ALL, instance->CommandHook,
                                             NULL);
    }

    inline void registerUpdateMenuHook() { RegisterSuite().registerUpdateMenuHook(instance->UpdateMenuHook, NULL); }

    inline void registerDeathHook() { RegisterSuite().registerDeathHook(instance->DeathHook, NULL); }

    inline void registerIdleHook() { RegisterSuite().registerIdleHook(instance->IdleHook, NULL); }

  private:
    SuiteManager &m_suiteManager;
    std::vector<std::unique_ptr<Command>> m_commands; // use std, depending on preprocessor directives, will be either
                                                      // std:: or AE:: (custom allocated and owned by AE)
    inline void clearCommands() { m_commands.clear(); }
};

// Define a macro for setting up the plugin's entry point function.
/**
 * @def DECLARE_ENTRY
 * @param PluginType The type of the plugin to be created.
 * @brief Macro for defining the plugin's entry point function.
 */
#define DECLARE_ENTRY(PluginType, pluginID)                                                                            \
    extern "C" DllExport A_Err EntryPointFunc(struct SPBasicSuite *pica_basicP, A_long major_versionL,                 \
                                              A_long minor_versionL, AEGP_PluginID aegp_plugin_id,                     \
                                              AEGP_GlobalRefcon *global_refconV)                                       \
    {                                                                                                                  \
        pluginID = aegp_plugin_id;                                                                                     \
        SuiteManager::GetInstance().InitializeSuiteHandler(pica_basicP);                                               \
        SuiteManager::GetInstance().SetPluginID(&pluginID);                                                            \
        return Plugin::EntryPointFunc<PluginType>(pica_basicP, major_versionL, minor_versionL, aegp_plugin_id,         \
                                                  global_refconV);                                                     \
    }

#endif /* PLUGIN_HPP */
