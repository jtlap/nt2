//[hello

#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>

using namespace nt2;

int main()
{
  table<double> x;
  table<double> y = ones(4,4);

  x = 40.0 * y + 2.0;

  std::cout << x << "\n";
}
//]
