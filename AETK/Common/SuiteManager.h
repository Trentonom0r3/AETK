/**
 * \file
 *SuiteManager.hpp
 * \brief
 *Singleton
 *class
 *managing
 *the After
 *Effects
 *suite
 *handler
 *and plugin
 *ID.
 *
 * \author
 *tjerf
 * \date
 *March 2024
 *********************************************************************/

#pragma once
#include "AEConfig.h"
#ifdef AE_OS_WIN
#include <Windows.h>
#endif
#include "entry.h"
// AE Headers
#include "Headers/A.h"
#include "Headers/AE_GeneralPlug.h"
#include "Headers/AE_Macros.h"
#include "Util/Param_Utils.h"
#include "Util/String_Utils.h"

#include "Headers/AE_Macros.h"
#include "Util/AEGP_SuiteHandler.h"

/*
 * File: SuiteManager.h
 * Description: Singleton class managing the After Effects suite handler and
 * plugin ID.
 *
 * Guidelines for Contributors:
 * 1. Singleton Pattern: Recognize that SuiteManager is a singleton and should
 * not be instantiated directly.
 * 2. Suite Handling: Understand how SuiteManager provides access to AE suites.
 * 3. No Alteration: Do not modify this file. It is crucial for the stable
 * operation of the entire plugin.
 */

/**
 * @class SuiteManager
 * @brief Singleton class managing the After Effects suite handler and plugin
 * ID.
 *
 * The SuiteManager class is responsible for managing the After Effects suite
 * handler and plugin ID. It follows the Singleton pattern to ensure that only
 * one instance of the class can exist. The class provides methods to initialize
 * the suite handler, get the suite handler, set the plugin ID, and get the
 * plugin ID.
 */
class SuiteManager
{
  public:
    /**
     * @brief Gets the singleton instance of SuiteManager.
     *
     * This method returns the singleton instance of the SuiteManager class.
     *
     * @return SuiteManager& The reference to the singleton instance of
     * SuiteManager.
     */
    static SuiteManager &GetInstance()
    {
        static SuiteManager instance;
        return instance;
    }

    // Deleted copy constructor and assignment operator to ensure singleton
    SuiteManager(SuiteManager const &) = delete;
    void operator=(SuiteManager const &) = delete;

    /**
     * @brief Initializes the suite handler.
     *
     * This method initializes the suite handler with the provided SPBasicSuite
     * pointer. It should be called before accessing any AE suites.
     *
     * @param pica_basicP The SPBasicSuite pointer.
     */
    void InitializeSuiteHandler(SPBasicSuite *pica_basicP)
    {
        if (!suitesInitialized)
        {
            suites = new AEGP_SuiteHandler(pica_basicP);
            suitesInitialized = true;
        }
    }

    /**
     * @brief Gets the suite handler.
     *
     * This method returns a reference to the suite handler.
     *
     * @return AEGP_SuiteHandler& The reference to the suite handler.
     */
    AEGP_SuiteHandler &GetSuiteHandler() { return *suites; }

    /**
     * @brief Sets the plugin ID.
     *
     * This method sets the plugin ID with the provided AEGP_PluginID pointer.
     *
     * @param pluginIDPtr The AEGP_PluginID pointer.
     */
    void SetPluginID(AEGP_PluginID *pluginIDPtr) { this->pluginIDPtr = pluginIDPtr; }

    /**
     * @brief Gets the plugin ID.
     *
     * This method returns a constant pointer to the plugin ID.
     *
     * @return const AEGP_PluginID* The constant pointer to the plugin ID.
     */
    AEGP_PluginID *GetPluginID() const { return pluginIDPtr; }

  private:
    /**
     * @brief Default constructor.
     *
     * The default constructor is private to prevent direct instantiation of the
     * SuiteManager class.
     */
    SuiteManager() : suites(nullptr), suitesInitialized(false), pluginIDPtr(nullptr) {}

    AEGP_SuiteHandler *suites;  /**< Pointer to the suite handler. */
    bool suitesInitialized;     /**< Flag indicating if the suite handler has been
                                   initialized. */
    AEGP_PluginID *pluginIDPtr; /**< Pointer to the plugin ID. */
};