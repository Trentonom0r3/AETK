/*******************************************************************/
/*                                                                 */
/*                      ADOBE CONFIDENTIAL                         */
/*                   _ _ _ _ _ _ _ _ _ _ _ _ _                     */
/*                                                                 */
/* Copyright 2007-2023 Adobe Inc.                                  */
/* All Rights Reserved.                                            */
/*                                                                 */
/* NOTICE:  All information contained herein is, and remains the   */
/* property of Adobe Inc. and its suppliers, if                    */
/* any.  The intellectual and technical concepts contained         */
/* herein are proprietary to Adobe Inc. and its                    */
/* suppliers and may be covered by U.S. and Foreign Patents,       */
/* patents in process, and are protected by trade secret or        */
/* copyright law.  Dissemination of this information or            */
/* reproduction of this material is strictly forbidden unless      */
/* prior written permission is obtained from Adobe Inc.            */
/* Incorporated.                                                   */
/*                                                                 */
/*******************************************************************/

#include "AEConfig.h"
#ifdef AE_OS_WIN
	#include <windows.h>
#endif

#include "entry.h"
#include "AE_GeneralPlug.h"
#include "AE_GeneralPlugPanels.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#ifndef DEBUG
	#define DEBUG
#else
	#error
#endif
#include "SuiteHelper.h"
#include "String_Utils.h"
#include "AE_EffectSuites.h"
#include "PanelatorUI_Plat.h"
#include "PT_Err.h"

typedef enum {
	StrID_NONE,							
	StrID_Name,							
	StrID_Description,
	StrID_GenericError,
	StrID_NUMTYPES
} StrIDType;

// This entry point is exported through the PiPL (.r file)
extern "C" DllExport AEGP_PluginInitFuncPrototype EntryPointFunc;

// SuiteManager.h
#pragma once

#include "AEGP_SuiteHandler.h"

/*
 * File: SuiteManager.h
 * Description: Singleton class managing the After Effects suite handler and plugin ID.
 *
 * Guidelines for Contributors:
 * 1. Singleton Pattern: Recognize that SuiteManager is a singleton and should not be instantiated directly.
 * 2. Suite Handling: Understand how SuiteManager provides access to AE suites.
 * 3. No Alteration: Do not modify this file. It is crucial for the stable operation of the entire plugin.
 */


class SuiteManager {
public:
    // Gets the singleton instance of SuiteManager
    static SuiteManager& GetInstance() {
        static SuiteManager instance;
        return instance;
    }

    // Deleted copy constructor and assignment operator to ensure singleton
    SuiteManager(SuiteManager const&) = delete;
    void operator=(SuiteManager const&) = delete;

    // Method to initialize the suite handler
    void InitializeSuiteHandler(SPBasicSuite* pica_basicP) {
        if (!suitesInitialized) {
            suites = new AEGP_SuiteHandler(pica_basicP);
            suitesInitialized = true;
        }
    }
    SuiteHelper<AEGP_PanelSuite1>& InitializepanelHandler(SPBasicSuite* pica_basicP) {

         panelSuites = new SuiteHelper<AEGP_PanelSuite1>(pica_basicP);

         return *panelSuites;
    }

    // Method to get the suite handler
    AEGP_SuiteHandler& GetSuiteHandler() {
        return *suites;
    }

    // Method to get the suite handler
    SuiteHelper<AEGP_PanelSuite1>& GetPanelSuiteHandler() {
        return *panelSuites;
	}

    // Method to set the plugin ID
    void SetPluginID(AEGP_PluginID* pluginIDPtr) {
        this->pluginIDPtr = pluginIDPtr;
    }

    // Method to get the plugin ID
    AEGP_PluginID* GetPluginID() const {
        return pluginIDPtr;
    }

private:
    SuiteManager() : suites(nullptr), suitesInitialized(false), pluginIDPtr(nullptr) {}

    AEGP_SuiteHandler* suites;
    SuiteHelper<AEGP_PanelSuite1>* panelSuites;
    bool suitesInitialized;
    AEGP_PluginID* pluginIDPtr;
};
