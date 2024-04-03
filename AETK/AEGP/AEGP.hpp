/*****************************************************************//**
 * \file   AEGP.hpp
 * \brief  Include all AEGP headers
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/
#pragma once

#ifndef AEGP_HPP
#define AEGP_HPP

#define SDK_VERSION 2023

// General Imports
#include "AETK/AEGP/Core/Base/AEGeneral.hpp" //Wrapper around all AEGP Suite headers
#include "AETK/AEGP/Core/Base/SuiteManager.hpp" // Wrapper for AEGP_SuiteHandler and AEGP_PluginID
#include "AETK/AEGP/Core/Base/Collection.hpp" // Wrapper for Collections of Items (not using collection suites)
#include "AETK/AEGP/Core/Base/ItemCollection.hpp" // Wrapper for AEGP_ItemH, uses Layer.hpp, Comp.hpp, Footage.hpp, Folder.hpp
#include "AETK/AEGP/Core/Base/LayerCollection.hpp" // Wrapper for AEGP_LayerH, uses Layer.hpp
#include "AETK/AEGP/Core/Base/Property.hpp" // Wrapper for AEGP_PropertyH, uses AEGP_Value, AEGP_StreamRefH
#include "AETK/AEGP/Core/Base/Misc.hpp" // Wrapper for AEGP_PropertyGroupH, uses Property.hpp
//Mid-Level Wrapper imports
#include "AETK/AEGP/Core/Project.hpp" // Wrapper for AEGP_ProjectH
#include "AETK/AEGP/Core/App.hpp" //Wrapper for misc AEGP funcs related to application.
#include "AETK/AEGP/Core/Effects.hpp" //Wrapper for AEGP_EffectRefH, uses Properties.hpp
#include "AETK/AEGP/Core/Items.hpp" //Wrapper for AEGP_ItemH, uses Layer.hpp, Comp.hpp, Footage.hpp, Folder.hpp
#include "AETK/AEGP/Core/Layer.hpp" //Wrapper for AEGP_CompH, uses Layer.hpp
#include "AETK/AEGP/Core/Mask.hpp" //Wrapper for AEGP_CompH, uses Layer.hpp

//Memory Related Imports
#include "AETK/AEGP/Memory/AEAllocator.hpp" //custom allocator for AEGP to use with any STL containers
#include "AETK/AEGP/Memory/AEMemory.hpp" //pre-defined "AE::Memory" namespace for AEGP containers. "AE::vector" etc.

//Exception Imports
#include "AETK/AEGP/Exception/Exception.hpp" //Custom Exception class for AEGP
#include "AETK/AEGP/Exception/Logging.hpp" //Logging utility for AEGP

//Utility Imports
#include "AETK/AEGP/Util/Context.hpp" //Scoped Context Managers for AEGP Calls
#include "AETK/AEGP/Util/Task.hpp" // Threading utility for calling and executing AEGP with multiple threads.
#include "AETK/AEGP/Util/Image.hpp" // Image utility for AEGP

//Template Imports -Ommitted until further testing
#include "AETK/AEGP/Template/Plugin.hpp" //Template class for designing plugins

#endif // !AEGP_HPP

