#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/pack/io.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <iostream>

#include <nt2/sdk/details/type_id.hpp>

int main()
{
  int array[4] = {1, 2, 3, 4};
    
  boost::simd::pack<float> r;
  boost::simd::pack<int>* v = reinterpret_cast<boost::simd::pack<int>*>(array);

  r = nt2::tofloat(*v);
  std::cout << r << "\n";
  std::cout << (r + r) << "\n";
  float sum = boost::simd::sum(r + r);
  std::cout << sum << "\n";
  
  typedef boost::simd::native<float, boost::simd::tag::sse_> native;
  typedef boost::simd::pack<float> pack;
  
  boost::fusion::vector2<native, native> t = nt2::sincos(evaluate(r));
  std::cout << t << std::endl;
  
  pack s, c;
  c = nt2::sincos(r, s);
  std::cout << s << " " << c << std::endl;

  boost::simd::pack<float> r2;
  r2 = nt2::Ten<boost::simd::pack<float> >();

  r = nt2::tofloat(*v+2)*r2;
  
  // r = nt2::tofloat(*v+2)*nt2::Ten<boost::simd::pack<float> >();
  
  std::cout << r << "\n";
}
