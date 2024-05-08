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

double TimeToSeconds(const A_Time &time);

A_Time SecondsToTime(double seconds);

int TimeToFrames(const A_Time &time);

A_Time FramesToTime(int frames);

#endif // UTILITY_HPP