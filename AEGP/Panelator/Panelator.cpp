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

#include <new>
#include "Panelator.h"

template <>
const A_char* SuiteTraits<AEGP_PanelSuite1>::i_name = kAEGPPanelSuite;
template <>
const int32_t SuiteTraits<AEGP_PanelSuite1>::i_version = kAEGPPanelSuiteVersion1;

class Panelator
{
public:
	SPBasicSuite					*i_pica_basicP;
	AEGP_PluginID					i_pluginID;
	
	AEGP_SuiteHandler&				i_sp = SuiteManager::GetInstance().GetSuiteHandler();
	AEGP_Command					i_command;
	SuiteHelper<AEGP_PanelSuite1>	i_ps;
	const A_u_char*					i_match_nameZ;
	A_char*							i_panel_nameZ;
	
	/// STATIC BINDERS
	static SPAPI A_Err
	S_CommandHook(
		AEGP_GlobalRefcon	plugin_refconP,			/* >> */
		AEGP_CommandRefcon	refconP,				/* >> */
		AEGP_Command		command,				/* >> */
		AEGP_HookPriority	hook_priority,			/* >> currently always AEGP_HP_BeforeAE */
		A_Boolean			already_handledB,		/* >> */
		A_Boolean			*handledPB)		/* << whether you handled */
	{
		PT_XTE_START {
			reinterpret_cast<Panelator*>(refconP)->CommandHook(command, hook_priority, already_handledB, handledPB);
		} PT_XTE_CATCH_RETURN_ERR;
	}
	
	static A_Err
	S_UpdateMenuHook(
		AEGP_GlobalRefcon		plugin_refconP,		/* >> */
		AEGP_UpdateMenuRefcon	refconP,			/* >> */
		AEGP_WindowType			active_window)		/* >> */
	{
		PT_XTE_START {
			reinterpret_cast<Panelator*>(plugin_refconP)->UpdateMenuHook(active_window);
		} PT_XTE_CATCH_RETURN_ERR;
	}
																		 
	static A_Err
	S_CreatePanelHook(							
		AEGP_GlobalRefcon		plugin_refconP,			
		AEGP_CreatePanelRefcon	refconP,
		AEGP_PlatformViewRef	container,
		AEGP_PanelH				panelH,
		AEGP_PanelFunctions1*	outFunctionTable,
		AEGP_PanelRefcon*		outRefcon)
	{
		PT_XTE_START {
			 reinterpret_cast<Panelator*>(plugin_refconP)->CreatePanelHook(container, panelH, outFunctionTable, outRefcon);
		} PT_XTE_CATCH_RETURN_ERR;
	}
	 
	Panelator(
		SPBasicSuite* pica_basicP,
		AEGP_PluginID	pluginID,
		A_u_char* name,
		AEGP_Command command):
			i_pluginID(pluginID),
			i_ps(pica_basicP),
			i_match_nameZ(name),
		    i_panel_nameZ(reinterpret_cast<A_char*>(name)),
			i_command(command)
	{
		PT_ETX(i_sp.CommandSuite1()->AEGP_GetUniqueCommand(&i_command));

		PT_ETX(i_sp.CommandSuite1()->AEGP_InsertMenuCommand(i_command, i_panel_nameZ, AEGP_Menu_WINDOW, AEGP_MENU_INSERT_SORTED));
		 
		PT_ETX(i_sp.RegisterSuite5()->AEGP_RegisterCommandHook(i_pluginID,
																AEGP_HP_BeforeAE,
																i_command,
																&Panelator::S_CommandHook,
																(AEGP_CommandRefcon)(this)));
		PT_ETX(i_sp.RegisterSuite5()->AEGP_RegisterUpdateMenuHook(i_pluginID,
																&Panelator::S_UpdateMenuHook,
																NULL));
		
		PT_ETX(i_ps->AEGP_RegisterCreatePanelHook(i_pluginID, i_match_nameZ,
													&Panelator::S_CreatePanelHook,
													(AEGP_CreatePanelRefcon)this,
													true));
	 }
																		 
	 void CommandHook(
		AEGP_Command		command,				/* >> */
		AEGP_HookPriority	hook_priority,			/* >> currently always AEGP_HP_BeforeAE */
		A_Boolean			already_handledB,		/* >> */
		A_Boolean			*handledPB)				/* << whether you handled */
	{
		if(command == i_command){
			PT_ETX(i_ps->AEGP_ToggleVisibility(i_match_nameZ));
		}
	}
																							
	void UpdateMenuHook(
		AEGP_WindowType			active_window)		/* >> */
	{
		PT_ETX(i_sp.CommandSuite1()->AEGP_EnableCommand(i_command));

		A_Boolean	out_thumb_is_shownB = FALSE, out_panel_is_frontmostB = FALSE;
		
		PT_ETX(i_ps->AEGP_IsShown(i_match_nameZ, &out_thumb_is_shownB, &out_panel_is_frontmostB));
		PT_ETX(i_sp.CommandSuite1()->AEGP_CheckMarkMenuCommand(i_command, out_thumb_is_shownB && out_panel_is_frontmostB));
	}
																													   
	void CreatePanelHook(							
		AEGP_PlatformViewRef container,
		AEGP_PanelH		panelH,
		AEGP_PanelFunctions1* outFunctionTable,
		AEGP_PanelRefcon*		outRefcon)
	{
		*outRefcon = reinterpret_cast<AEGP_PanelRefcon>(new PanelatorUI_Plat(i_pica_basicP, panelH, container, outFunctionTable));
	}
};


#include <map>

// Global container to hold multiple Panelator instances
std::map<AEGP_PluginID, Panelator*> g_panelatorInstances;

A_Err EntryPointFunc(
    struct SPBasicSuite *pica_basicP,
    A_long major_versionL,
    A_long minor_versionL,
    AEGP_PluginID aegp_plugin_id,
    AEGP_GlobalRefcon *global_refconP)
{

	//initialize interpreter on the messagequeue thread
	// In EntryPointFunc
	SuiteManager::GetInstance().InitializeSuiteHandler(pica_basicP);
	AEGP_SuiteHandler& suites = SuiteManager::GetInstance().GetSuiteHandler();

	SuiteManager::GetInstance().InitializepanelHandler(pica_basicP);
	SuiteHelper<AEGP_PanelSuite1>& panelSuites = SuiteManager::GetInstance().GetPanelSuiteHandler();

	PT_XTE_START{
		// Create a Panelator instance for the first plugin ID
		A_u_char * panel_nameZ = reinterpret_cast<A_u_char*>("Panelator");
		AEGP_Command command = 629L;
		AEGP_PluginID aegp_plugin_id = 0;
		Panelator * panelator1 = new Panelator(pica_basicP, aegp_plugin_id, panel_nameZ, command);
        g_panelatorInstances[aegp_plugin_id] = panelator1;

        // Assuming you have another plugin ID
		A_u_char * panel_nameZ2 = reinterpret_cast<A_u_char*>("Panelator2");
		AEGP_Command command2 = 630L;
		AEGP_PluginID aegp_plugin_id2 = 1;
		Panelator* panelator2 = new Panelator(pica_basicP, aegp_plugin_id2, panel_nameZ2, command2);
        g_panelatorInstances[aegp_plugin_id] = panelator2;

        // You can set the global refcon to the first instance or manage differently
        *global_refconP = (AEGP_GlobalRefcon) panelator1;
    }
    PT_XTE_CATCH_RETURN_ERR;
}
