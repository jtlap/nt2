#include <boost/simd/memory/input_iterator.hpp>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
  using boost::simd::pack;
  using boost::simd::input_end;
  using boost::simd::input_begin;
  using boost::simd::input_iterator;

  std::vector<float> data(16);
  typedef std::vector<float>::iterator it_t;

  for(std::size_t i=0;i<data.size();++i)
    data[i]  = 1 + i;

  input_iterator<it_t,4> vb = input_begin<4>(data.begin());
  input_iterator<it_t,4> ve = input_end<4>(data.end());

  std::copy(vb, ve, std::ostream_iterator< pack<float,4> >(std::cout, " "));
  std::cout << std::endl;
}
