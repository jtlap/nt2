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
#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/begin.hpp>
#include <iostream>
#include <nt2/sdk/meta/type_id.hpp>

int main()
{
  int array[4] = {1, 2, 3, 4};
    
  boost::simd::pack<float, 4> r;
  boost::simd::pack<int, 4>* v = reinterpret_cast<boost::simd::pack<int, 4>*>(array);

  // testing element-wise operations, reductions, display
  r = nt2::tofloat(*v);
  std::cout << r << "\n";
  std::cout << (r + r) << "\n";
  float sum = boost::simd::sum(r + r);
  std::cout << sum << "\n";
  
  typedef boost::simd::native<float, boost::simd::tag::sse_> native;
  typedef boost::simd::pack<float, 4> pack;
  typedef boost::simd::pack<int, 4> packi;
  
  // testing functions which return a tuple (compile but doesn't do the right thing)
  boost::fusion::vector2<native, native> t = nt2::sincos(evaluate(r));
  std::cout << t << std::endl;
  
  // testing variant that modifies its argument
  pack s, c;
  c = nt2::sincos(r, s);
  std::cout << s << " " << c << std::endl;

  // testing constants
  pack r2;
  r2 = nt2::Ten<pack>();
  r = nt2::tofloat(*v+2)*nt2::Ten<pack>();
  std::cout << r2 << "\n";
  std::cout << r << "\n";

   // testing load, store, splat and make
   packi p;
   p = boost::simd::load<packi>(&array[0], 0);
   std::cout << p << "\n";
   p = p+1;
   boost::simd::store(p, &array[0], 0);
   std::cout << "{ " << array[0] << ", " << array[1] << ", " << array[2] << ", " << array[3] << " }\n";
  
   p = boost::simd::splat<packi>(0);
   std::cout << p << "\n";
  
   p = boost::simd::make<packi>(1, 2, 3, 4);
   std::cout << p << "\n";
  
   // testing cardinal
   std::cout << boost::simd::meta::cardinal_of<pack>::value << "\n";

   // Testing iterators for native mode
   packi p_it = boost::simd::make<packi>(1, 2, 3, 4);
   packi::iterator it = p_it.begin();
   packi::const_iterator it_ = p_it.begin();
   packi::iterator it__ = p_it.end();
   packi::const_iterator it___ = p_it.end();
   for(;it!=it__;++it) std::cout << *it << " " ;
   std::cout << "\n";
   for(;it_!=it___;++it_) std::cout << *it_ << " " ;
   std::cout << "\n";
   std::cout << "is_empty : " << p_it.empty() << "\n";
   std::cout << "size     : " << p_it.size() << "\n";
   // Testing Fusion interface
   std::cout << boost::fusion::deref(boost::fusion::begin(p_it)) << "\n";
   packi copy = p_it;
   std::cout << copy << std::endl;

   // Testing iterators for emulate mode
//   typedef boost::simd::pack<int,8> emulate;
//   emulate p_emu = boost::simd::make<emulate>(1, 2, 3, 4, 5, 6, 7, 8);
//   emulate::iterator ite = p_emu.begin();
//   emulate::const_iterator ite_ = p_emu.begin();
//   emulate::iterator ite__ = p_emu.end();
//   emulate::const_iterator ite___ = p_emu.end();
//   for(;ite!=ite__;++ite) std::cout << *ite << " " ;
//   std::cout << "\n";
//   for(;ite_!=ite___;++ite_) std::cout << *ite_ << " " ;
//   std::cout << "\n";
//   std::cout << "is_empty : " << p_emu.empty() << "\n";
//   std::cout << "size     : " << p_emu.size() << "\n";

}
