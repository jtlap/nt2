#include <vector>
#include <numeric>
#include <iostream>

#include <nt2/sdk/simd/io.hpp>
#include <nt2/sdk/simd/range.hpp>

#include <nt2/sdk/memory/allocate.hpp>
#include <nt2/sdk/memory/allocator.hpp>

#include <boost/range/numeric.hpp>

using namespace std;

int main()
{
  vector<char> tab(48);
  nt2::simd::pack<char> r;

  for(int i=0;i<48;++i) tab[i] = 1;
  r = boost::accumulate(nt2::simd::range(tab), nt2::simd::pack<char>());
  cout << r << "\n";
  cout << boost::accumulate(r,0) << "\n";
}
