#include <iostream>
#include <boost/simd/memory/new.hpp>
#include <boost/simd/memory/is_aligned.hpp>

using boost::simd::is_aligned;

int main()
{
  char* ptr = new char[17];
  std::cout << is_aligned( ptr ) << "\n";
}
