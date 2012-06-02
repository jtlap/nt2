//[hello

#include <iostream>
#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>

using namespace nt2;

int main()
{
  table<double> x;
  table<double> y = ones(4,4);

  x = 10.0 * y + 4.0;

  std::cout << x << "\n";
}
//]
