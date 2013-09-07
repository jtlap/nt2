#include <boost/simd/memory/aligned_output_iterator.hpp>
#include <boost/simd/memory/allocator.hpp>
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
  using boost::simd::allocator;
  using boost::simd::aligned_output_end;
  using boost::simd::aligned_output_begin;
  using boost::simd::aligned_output_iterator;

  std::vector<float, allocator<float> > data(16);
  typedef std::vector<float, allocator<float> >::iterator it_t;

  aligned_output_iterator<it_t,4> vb = aligned_output_begin<4>(data.begin());
  aligned_output_iterator<it_t,4> ve = aligned_output_end<4>(data.end());

  std::generate(vb, ve, splatted_iota);

  std::copy(data.begin(), data.end(), std::ostream_iterator<float>(std::cout, " "));
  std::cout << std::endl;
}
