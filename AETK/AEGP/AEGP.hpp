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
#include "AETK/AEGP/Core/Base/Import.hpp" // Utility Wrappers for importing files
#include "AETK/AEGP/Core/Base/Item.hpp" // Wrapper for AEGP_ItemH
#include "AETK/AEGP/Core/Base/Layer.hpp" // Wrapper for AEGP_LayerH
#include "AETK/AEGP/Core/Base/Properties.hpp" // Base Wrapper for AEGP_StreamRefH
#include "AETK/AEGP/Core/Base/SuiteManager.hpp" // Wrapper for AEGP_SuiteHandler and AEGP_PluginID
#include "AETK/AEGP/Core/Base/Collection.hpp" // Wrapper for Collections of Items (not using collection suites)

//Mid-Level Wrapper imports
#include "AETK/AEGP/Core/Project.hpp" // Wrapper for AEGP_ProjectH
#include "AETK/AEGP/Core/App.hpp" //Wrapper for misc AEGP funcs related to application.
#include "AETK/AEGP/Core/Comp.hpp" //Wrapper for AEGP_CompH (Derived from AEGP_ItemH)
#include "AETK/AEGP/Core/Effects.hpp" //Wrapper for AEGP_EffectRefH, uses Properties.hpp

//Memory Related Imports
#include "AETK/AEGP/Memory/AEAllocator.hpp" //custom allocator for AEGP to use with any STL containers
#include "AETK/AEGP/Memory/AEMemory.hpp" //pre-defined "AE::Memory" namespace for AEGP containers. "AE::vector" etc.

//Exception Imports
#include "AETK/AEGP/Exception/Exception.hpp" //Custom Exception class for AEGP

//Utility Imports
#include "AETK/AEGP/Util/Context.hpp" //Scoped Context Managers for AEGP Calls
#include "AETK/AEGP/Util/Task.hpp" // Threading utility for calling and executing AEGP with multiple threads.
#include "AETK/AEGP/Util/Image.hpp" // Image utility for AEGP

//Template Imports
#include "AETK/AEGP/Template/Plugin.hpp" //Template class for designing plugins

#endif // !AEGP_HPP

