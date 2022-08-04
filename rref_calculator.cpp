// This driver file tests the code in "rref_calc.h"

#include <iostream>
#include <iomanip>
#include "rref_calc.h"

int main()
{
  int M[3][4] = { {  1, 2, 3,  4 },
                  {  5, 6, 7, 8 },
                  { 9, 10, 11,  12 } };
  std::cout << "RREF(M) = " << "\n";

  rref_form(M);

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 4; ++j)
    std::cout << M[i][j] << '\t';
    std::cout << "\n";
  }

  system ("PAUSE>NUL");

  return 0;
}
