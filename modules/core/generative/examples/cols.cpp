#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/cols.hpp>

int main()
{
  nt2::table<double> I;

  // Creates a @c 4x4 column indices matrix with base index -1.
  I = nt2::cols(4,4,-1.);
  NT2_DISPLAY(I);

  // Create a 2-by-3 column indices matrix with base index 3.
  I = nt2::cols(2,3,3.);
  NT2_DISPLAY(I);

  // Create a 1-by-3 column indices vector with base index 0.
  I = nt2::cols( nt2::of_size(1,3), 0. );
  NT2_DISPLAY(I);

  // Create a 3-by-3 column indices matrix  with base index -1
  // whose elements are 32-bit
  nt2::table<int> U;
  U = nt2::cols( 3, -1 );
  NT2_DISPLAY(U);
}
