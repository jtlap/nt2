#include <vector>
#include <iostream>
#include <nt2/sdk/meta/type_id.hpp>

int main()
{
  std::vector<long*> vx;

  std::cout << nt2::type_id<char[21]>() << "\n";
  std::cout << nt2::type_id(3.141592f)  << "\n";
  std::cout << nt2::type_id(vx)         << "\n";
}
