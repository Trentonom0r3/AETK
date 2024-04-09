/*****************************************************************/ /**
                                                                     * \file   Utility.hpp
                                                                     * \brief  A collection of utility functions
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "AETK//Common/Common.hpp"
#include "AETK/AEGP/Core/Enums.hpp"

template <class... Ts> struct overloaded : Ts...
{
    using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

inline bool isValidItemType(ItemType type, ItemPtr item) {
    AEGP_ItemType typeH;
    SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemType(*item, &typeH);
    return type == static_cast<ItemType>(typeH);
}


inline bool isValidLayerType(ObjectType type, LayerPtr layer) {
    AEGP_ObjectType typeH;
	SuiteManager::GetInstance().GetSuiteHandler().LayerSuite8()->AEGP_GetLayerObjectType(*layer, &typeH);
	return type == static_cast<ObjectType>(typeH);
}

#endif // UTILITY_HPP