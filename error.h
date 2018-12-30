#ifndef _ERROR_H__
#define _ERROR_H__
#pragma once

#include <iostream>
#include <string>
#include <vector>

using uint = unsigned int;

enum error
{
  ERR_OK,
  ERR_OVERFLOW,
  ERR_MUL_OVERFLOW,
  ERR_SUM_OVERFLOW,
  ERR_ARGNUM,
  ERR_FUNC,
  ERR_LETTER,
  ERR_SIGNED,
  /* additional field for help function */
  HELP
};

void ReportError( error er, uint func );

#endif //_ERROR_H__
