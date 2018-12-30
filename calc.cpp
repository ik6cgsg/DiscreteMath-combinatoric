#include <sstream>

#include "calc.h"
#include "parser.h"

using namespace std;

uint s_help(error * er)
{
  setlocale(LC_ALL, "Russian");

  cout << "Предусмотрены следующие команды:" << endl << "H|h - Получение справки" << endl;
  cout << "Q|q - Завершение работы" << endl << "U|u - Число размещений U(m,n)" << endl;
  cout << "A|a - Число размещений без повторений A(m,n)" << endl << "P|p - Число перестановок P(n)" << endl;
  cout << "C|c - Число сочетаний C(m,n)" << endl << "S|s - Число Стирлинга второго рода S(m,n)" << endl;
  cout << "B|b - Число Белла B(n)" << endl;
  cout << "Синтаксис: <команда>[ <пробел><параметр1>[<пробел><параметр2>]]" << endl;

  *er = HELP;
  return -1;
} // End of 's_help' function

uint s_func(vector<string> & params, error * er)
{
  string func;

  if (params.size() != 0)  // if == 0, then line is empy -> help
    func = params[0];

  uint param1, param2;
  stringstream sts;

  if (params.size() >= 2)
  {
    sts << params[1];
    sts >> param1;
  }
  if (params.size() == 3)
  {
    sts.clear();
    sts << params[2];
    sts >> param2;
  }

  if (func == "U" || func == "u")
    return calc::comb::getU(param1, param2, er);
  if (func == "A" || func == "a")
    return calc::comb::getA(param1, param2, er);
  if (func == "C" || func == "c")
    return calc::comb::getC(param1, param2, er);
  if (func == "S" || func == "s")
    return calc::comb::getS(param1, param2, er);
  if (func == "P" || func == "p")
    return calc::comb::getP(param1, er);
  if (func == "B" || func == "b")
    return calc::comb::getB(param1, er);
  if (func == "Q" || func == "q")
    exit(0);

  return s_help(er);
} // End of 's_func' function

uint calc::Calculate(string & line, error * er)
{
  line.push_back('\n');
  vector<string> params = ParseLine(line, er);
  Check(params, er);

  if (*er)
    return 0;

  return s_func(params, er);
} // End of 'calc::Calculate' function

uint calc::Calculate(int argc, char const * argv[], error * er)
{
  vector<string> params;

  for (int i = 1; i < argc; i++)
  {
    string param = argv[i];
    params.push_back(param);
  }
  Check(params, er);

  if (*er)
    return -1;

  return s_func(params, er);
} // End of 'calc::Calculate' function

uint calc::comb::mul(uint a, uint b, error * er)
{
  if (b != 0 && UINT32_MAX / b < a)
  {
    *er = ERR_MUL_OVERFLOW;
    return -1;
  }

  return a * b;
} // End of 'calc::comb::mul' function

uint calc::comb::add(uint a, uint b, error * er)
{
  uint max = a > b ? a : b, res = a + b;

  if (res < max)
    *er = ERR_SUM_OVERFLOW;

  return res;
} // End of 'calc::comb::add' function

uint calc::comb::getU(uint m, uint n, error * er)
{
  uint res = 1;
  uint tmp = m;

  while (n)
  {
    if (n & 1)
      res = mul(res, tmp, er);
    if (n > 1)
      tmp = mul(tmp, tmp, er);
    n >>= 1;

    if (*er)
      return -1;
  }

  return res;
} // End of 'calc::comb::getU' function

uint calc::comb::getA(uint m, uint n, error * er)
{
  if (n > m)
    return 0;

  if (n == 0)
    return 1;

  if (n == 1)
    return m;

  uint res = 1;

  for (uint i = m - n + 1; i <= m; i++)
  {
    res = mul(res, i, er);
    if (*er)
      return -2;
  }

  return res;
} // End of 'calc::comb::getA' function

uint calc::comb::getP(uint n, error * er)
{
  uint res = 1;

  for (uint i = 2; i <= n; i++)
  {
    res = mul(res, i, er);
    if (*er)
      return -3;
  }

  return res;
} // End of 'calc::comb::getP' function

uint calc::comb::getC(uint m, uint n, error * er)
{
  if (n > m)
    return 0;
  if (n == 1 || m == n + 1)
    return m;
  if (n == m)
    return 1;
  if (n > m - n)
    n = m - n;

  vector<uint> A;

  /* initializing */
  for (uint i = 0; i <= n; i++)
    A.push_back(1);

  for (uint i = 1; i <= m - n; i++)
    for (uint j = 1; j <= n; j++)
    {
      A[j] = add(A[j], A[j - 1], er);
      if (*er)
        return -4;
    }

  return A[n];
} // End of 'calc::comb::getC' function

uint calc::comb::getS(uint m, uint n, error * er)
{
  if (m == n)
    return 1;
  if (m > 0 && n == 0)
    return 0;
  if (n > m)
    return 0;
  if (n == 1)
    return 1;

  vector<uint> D;

  /* initializing */
  for (uint i = 0; i < n; i++)
    D.push_back(1);

  for (uint i = 0; i < m - n; i++)
    for (uint j = 1; j < n; j++)
    {
      D[j] = add(D[j - 1], mul((j + 1), D[j], er), er);
      if (*er)
        return -5;
    }

  return D[n - 1];
} // End of 'calc::comb::getS' function

uint calc::comb::getB(uint n, error * er)
{
  if (n == 0)
    return 1;

  vector<uint> A;

  /* initializing */
  for (uint i = 0; i < n; i++)
    A.push_back(1);

  for (uint i = 1; i < n; i++)
  {
    uint t = A[0];
    A[0] = A[i - 1];
    for (uint j = 1; j <= i; j++)
    {
      uint s = A[j];
      A[j] = add(A[j - 1], t, er);

      if (*er)
        return -6;

      t = s;
    }
  }

  return A[n - 1];
} // End of 'calc::comb::getB' function
