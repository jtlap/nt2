#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/fill_pattern.hpp>

int main()
{
  nt2::table<double> I;

  // Creates a @c 4x4 matrix with base replicating 1:3
  I = nt2::fill_pattern(nt2::_(1.,3.),4,4);
  NT2_DISPLAY(I);

  nt2::table<int> C;

  // Create a 5-by-1 vector with base replicating 1:3
  C = nt2::fill_pattern( nt2::_(1,3), nt2::of_size(5,1) );
  NT2_DISPLAY(C);
}
