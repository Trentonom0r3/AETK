/*****************************************************************//**
 * \file   AEffect.hpp
 * \brief  AEffect class declaration
 * 
 * \author tjerf
 * \date   March 2024
 *********************************************************************/

#ifndef AEFFECT_HPP
#define AEFFECT_HPP

#include "Headers/AE_Effect.h"
#include <vector>

class Param
{
    static Param color(double r, double g, double b);

};

class ParamConfig
{
    void setParam(Param param);
    void registerParams();

  private:
    std::vector<Param> params;
};

#endif // AEFFECT_HPP
