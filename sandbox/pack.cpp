#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/pack/io.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <iostream>

#include <nt2/sdk/details/type_id.hpp>

int main()
{
  int array[4] = {1, 2, 3, 4};
    
  boost::simd::pack<float> r;
  boost::simd::pack<int>* v = reinterpret_cast<boost::simd::pack<int>*>(array);

  // testing element-wise operations, reductions, display
  r = nt2::tofloat(*v);
  std::cout << r << "\n";
  std::cout << (r + r) << "\n";
  float sum = boost::simd::sum(r + r);
  std::cout << sum << "\n";
  
  typedef boost::simd::native<float, boost::simd::tag::sse_> native;
  typedef boost::simd::pack<float> pack;
  
  // testing functions which return a tuple (compile but doesn't do the right thing)
  boost::fusion::vector2<native, native> t = nt2::sincos(evaluate(r));
  std::cout << t << std::endl;
  
  // testing variant that modifies its argument
  pack s, c;
  c = nt2::sincos(r, s);
  std::cout << s << " " << c << std::endl;

  // testing constants
  boost::simd::pack<float> r2;
  r2 = nt2::Ten<boost::simd::pack<float> >();  
  r = nt2::tofloat(*v+2)*nt2::Ten<boost::simd::pack<float> >();
  std::cout << r << "\n";
  
  // testing load, store, splat and make
  boost::simd::pack<int> p;
  p = boost::simd::load< boost::simd::pack<int> >(&array[0], 0);
  std::cout << p << "\n";
  p = p+1;
  boost::simd::store(p, &array[0], 0);
  std::cout << "{ " << array[0] << ", " << array[1] << ", " << array[2] << ", " << array[3] << " }\n";
  
  p = boost::simd::splat< boost::simd::pack<int> >(0.);
  std::cout << p << "\n";
  
  p = boost::simd::make< boost::simd::pack<int> >(1, 2, 3, 4);
  std::cout << p << "\n";
  
  // testing cardinal
  std::cout << boost::simd::meta::cardinal_of<pack>::value << "\n";
}
