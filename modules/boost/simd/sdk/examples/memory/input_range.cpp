#include <boost/simd/memory/input_range.hpp>
#include <boost/range/algorithm/copy.hpp>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
  using boost::simd::pack;
  using boost::simd::input_range;

  std::vector<float> data(16);

  for(std::size_t i=0;i<data.size();++i)
    data[i]  = 1 + i;

  boost::copy( input_range<4>(data), std::ostream_iterator< pack<float,4> >(std::cout, " "));
  std::cout << std::endl;
}
