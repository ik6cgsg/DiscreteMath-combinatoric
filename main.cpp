#include <cstdio>
#include <iostream>
#include <string>

#include "calc.h"

using namespace std;
using namespace calc;

int main(int argc, char const * argv[])
{
  if (argc > 4)
  {
    ReportError(ERR_ARGNUM, 0);
    return -1;
  }

  // one cmd
  if (argc >= 2 && argc <= 4)
  {
    error er = ERR_OK;
    uint res = Calculate(argc, argv, &er);

    if (er != HELP)   // if help function is running, we have nothing to print
    {
      if (er)
      {
        ReportError(er, res);
        return -1;
      }
      cout << res << endl;
    }
    return 0;
  }

  string line;
  getline(cin, line);

  // process the data line by line
  while (line.c_str() != nullptr)
  {
    error er = ERR_OK;
    uint res = Calculate(line, &er);

    if (er != HELP)    // if help function is running, we have nothing to print
    {
      if (er)
        ReportError(er, res);
      else
        cout << res << endl;
    }
    getline(cin, line);
  }

  return 0;
}
