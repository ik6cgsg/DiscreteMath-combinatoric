#include "parser.h"

using namespace std;

static bool s_digits(string & line)
{
  return line.find_first_not_of("0123456789") == string::npos;
} // End of 's_digits' function

static bool s_empty(string & line)
{
  return line.find_first_not_of(" \t\r\n") == string::npos;
} // End of 's_empty' function

static uint s_checkFunc(string & func, error * er)
{
  if (func == "U" || func == "u" ||
      func == "A" || func == "a" ||
      func == "C" || func == "c" ||
      func == "S" || func == "s")
    return 2;
  else if (func == "P" || func == "p" ||
           func == "B" || func == "b")
    return 1;
  else if (func == "Q" || func == "q" ||
           func == "H" || func == "h")
    return 0;
  else
    *er = ERR_FUNC;

  return 0;
} // End of 's_checkFunc' function

vector<string> ParseLine(string & line, error * er)
{
  vector<string> res;

  while (!s_empty(line))
  {
    auto off = line.find_first_not_of(" \t\r\n");
    line.erase(line.begin(), line.begin() + off);
    off = line.find_first_of(" \t\r\n");

    string param = line.substr(0, off);
    line.erase(line.begin(), line.begin() + off);
    res.push_back(param);
  }

  return res;
} // End of 'ParseLine' function

void Check(std::vector<std::string> & params, error * er)
{
  /* empty line -> help */
  if (params.size() == 0)
    return;

  uint numOfParams = s_checkFunc(params[0], er);
  string max = "4294967295";

  if (*er)
    return;

  if (params.size() - 1 != numOfParams)
  {
    *er = ERR_ARGNUM;
    return;
  }

  for (uint i = 1; i <= numOfParams; i++)
  {
    if (params[i].size() > 1 && params[i][0] == '-')
    {
      *er = ERR_SIGNED;
      return;
    }
    if (!s_digits(params[i]))
    {
      *er = ERR_LETTER;
      return;
    }
    if (params[i].size() > max.size() || params[i].size() == max.size() && params[i].compare(max) > 0)
    {
      *er = ERR_OVERFLOW;
      return;
    }
  }
} // End of 'Check' function
