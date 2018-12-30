#ifndef _CALC_H__
#define _CALC_H__
#pragma once

#include "error.h"

namespace calc
{
  namespace comb
  {
    uint mul(uint a, uint b, error * er);
    uint add(uint a, uint b, error * er);

    uint getU(uint m, uint n, error * er);
    uint getA(uint m, uint n, error * er);
    uint getP(uint n, error * er);
    uint getC(uint m, uint n, error * er);
    uint getS(uint m, uint n, error * er);
    uint getB(uint n, error * er);
  }

  uint Calculate(std::string & line, error * er);
  uint Calculate(int argc, char const * argv[], error * er);
} // end of 'calc' namespace

#endif // _CALC_H__
