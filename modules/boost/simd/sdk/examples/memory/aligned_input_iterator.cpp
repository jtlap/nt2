#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/memory/aligned_input_iterator.hpp>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
  using boost::simd::pack;
  using boost::simd::allocator;
  using boost::simd::aligned_input_end;
  using boost::simd::aligned_input_begin;
  using boost::simd::aligned_input_iterator;

  std::vector<float, allocator<float> > data(16);

  for(std::size_t i=0;i<data.size();++i)
    data[i]  = 1 + i;

  aligned_input_iterator<float,4> vb = aligned_input_begin<4>(data.begin());
  aligned_input_iterator<float,4> ve = aligned_input_end<4>(data.end());

  std::copy(vb, ve, std::ostream_iterator< pack<float,4> >(std::cout, " "));
  std::cout << std::endl;
}
