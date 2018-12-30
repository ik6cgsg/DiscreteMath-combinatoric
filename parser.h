#ifndef _PARSER_H__
#define _PARSER_H__
#pragma once

#include "error.h"

std::vector<std::string> ParseLine(std::string & line, error * er);
void Check(std::vector<std::string> & params, error * er);

#endif // _PARSER_H__
