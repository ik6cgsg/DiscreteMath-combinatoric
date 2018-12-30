#include "error.h"

using namespace std;

void ReportError(error er, uint func)
{
  string erstr;

  switch (er)
  {
  case ERR_OVERFLOW:
    erstr = "error: argument is too big";
    break;
  case ERR_MUL_OVERFLOW:
    erstr = "error: mul overflow";
    break;
  case ERR_SUM_OVERFLOW:
    erstr = "error: sum overflow";
    break;
  case ERR_ARGNUM:
    erstr = "error: wrong number of arguments";
    break;
  case ERR_FUNC:
    erstr = "error: this function isn't supported";
    break;
  case ERR_LETTER:
    erstr = "error: letter instead of number";
    break;
  case ERR_SIGNED:
    erstr = "error: signed param(s)";
    break;
  default:
    break;
  }

  switch (func)
  {
  case -1:
    erstr.append(" at U function");
    break;
  case -2:
    erstr.append(" at A function");
    break;
  case -3:
    erstr.append(" at P function");
    break;
  case -4:
    erstr.append(" at C function");
    break;
  case -5:
    erstr.append(" at S function");
    break;
  case -6:
    erstr.append(" at B function");
    break;
  }

  cout << erstr << endl;
} // End of 'ReportError' function
