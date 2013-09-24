#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/colon.hpp>

int main()
{
  nt2::table<double> I;

  // Generates 1 .. 7
  I = nt2::colon(1., 7.);
  NT2_DISPLAY(I);

  // Generates 1.1 .. 7.1
  I = nt2::colon(1.1, 7.5);
  NT2_DISPLAY(I);
}
