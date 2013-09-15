#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/colon.hpp>

int main()
{
  nt2::table<double> I;

  // Generates 1 3 5 7
  I = nt2::colon(1., 2.,  7.);
  NT2_DISPLAY(I);

  // Generates 0. 0.1 ... 1.
  I = nt2::colon(0., 0.1, 1.);
  NT2_DISPLAY(I);

  nt2::table<int> U;

  // generates 4 ... -4
  U = nt2::colon(4, -2, -4);
  NT2_DISPLAY(U);
}
