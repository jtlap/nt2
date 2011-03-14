#include <iostream>
#include <numeric>
#define BOOST_PROTO_STRICT_RESULT_OF

#include <nt2/sdk/simd/pack.hpp>
#include <nt2/sdk/simd/begin.hpp>
#include <nt2/sdk/simd/end.hpp>
#include <nt2/include/timing.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/constant/dsl/digits.hpp>
#include <nt2/sdk/constant/dsl/boolean.hpp>

using namespace std;

int main()
{
  static volatile float r,vr;

  std::cout << nt2::splat< nt2::simd::pack<float> >( 1.234 ) << std::endl;
  std::cout << nt2::splat< nt2::simd::pack<float,8> >( 1.234 ) << std::endl;

	nt2::memory::buffer<float, nt2::memory::allocator<float> > b(0,4096);
	for(int i=0;i<4096;++i) b[i] = 1;
	
	nt2::tic();
	for(int i=0;i<100000;++i) r = std::accumulate(b.begin(),b.end(),0.f);
	double d = nt2::toc();
	std::cout << r << std::endl;
	
	nt2::tic();
	for(int i=0;i<100000;++i)
	{
	  nt2::simd::pack<float> zz(nt2::zero_),itr;
	  itr = std::accumulate( nt2::simd::begin(b),nt2::simd::end(b),zz);
    vr = std::accumulate( itr.begin(),itr.end(),0.f);
	 }
	double vd = nt2::toc();
  std::cout << vr << std::endl;
  std::cout << d/vd << std::endl;

  nt2::simd::pack<float> yyy;
  yyy = nt2::load< nt2::simd::pack<float> >(&b[0],0);
  b[1] = 10;
  nt2::simd::pack<float> www;
  www = nt2::load< nt2::simd::pack<float>, 1 >(&b[0],0);
  std::cout << yyy << " "<< www << "\n";

  nt2::simd::pack<float> xxx =
  nt2::splat< nt2::simd::pack<float> >( 1.234 );

  nt2::store( xxx, &b[0], 0);
  std::cout << b[0] << b[1] << b[2] << b[3] << "\n";

  nt2::store( xxx, &b[0], 10);
  std::cout << b[40] << b[41] << b[42] << b[43] << "\n";


}
