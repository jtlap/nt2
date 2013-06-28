#include <boost/simd/memory/output_iterator.hpp>
#include <boost/simd/include/functions/enumerate.hpp>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

boost::simd::pack<float,4> splatted_iota()
{
  static int seed = 0;
  return seed++;
}

int main()
{
  using boost::simd::pack;
  using boost::simd::output_end;
  using boost::simd::output_begin;
  using boost::simd::output_iterator;

  std::vector<float> data(16);

  output_iterator<float,4> vb = output_begin<4>(data.begin());
  output_iterator<float,4> ve = output_end<4>(data.end());

  std::generate(vb, ve, splatted_iota);

  std::copy(data.begin(), data.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;
}
