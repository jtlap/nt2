#include <boost/simd/sdk/config/is_supported.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << boost::simd::config::is_supported<boost::simd::tag::sse2_>() << "\n";
  std::cout << boost::simd::config::is_supported<boost::simd::tag::sse3_>() << "\n";
  std::cout << boost::simd::config::is_supported<boost::simd::tag::ssse3_>() << "\n";
  std::cout << boost::simd::config::is_supported<boost::simd::tag::sse4a_>() << "\n";
  std::cout << boost::simd::config::is_supported<boost::simd::tag::sse4_1_>() << "\n";
  std::cout << boost::simd::config::is_supported<boost::simd::tag::sse4_2_>() << "\n";
  return 0;
}

