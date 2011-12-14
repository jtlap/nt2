//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/hypot.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/is_inf.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/logical_or.hpp>
#include <boost/simd/include/functions/exponent.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/include/functions/any.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::hypot_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_floating<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::hypot(tofloat(a0), tofloat(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hypot_, tag::cpu_,
                              (A0)(X),
                              ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    template < class T, class I = typename dispatch::meta::as_integer<T, signed>::type>
    struct hypot_ctnts {};

    template <class I, class CAT>
    struct hypot_ctnts<simd::native<float, CAT>, I>
    {
      typedef I  int_type;
      static inline int_type C1(){ return boost::simd::integral_constant<int_type, 50>();};
      static inline int_type C2(){ return boost::simd::integral_constant<int_type, 60>();};
      static inline int_type MC1(){ return boost::simd::integral_constant<int_type, -50>();};
      static inline int_type MC2(){ return boost::simd::integral_constant<int_type, -60>();};
      static inline int_type C3(){ return boost::simd::integral_constant<int_type, 0x00800000>();};
      static inline int_type M1(){ return boost::simd::integral_constant<int_type, 0xfffff000>();};
    };

    template <class I, class CAT>
    struct hypot_ctnts<simd::native<double, CAT>, I>
    {
      typedef I  int_type;
      static inline int_type C1(){ return boost::simd::integral_constant<int_type, 500>();};
      static inline int_type C2(){ return boost::simd::integral_constant<int_type, 600>();};
      static inline int_type MC1(){ return boost::simd::integral_constant<int_type, -500>();};
      static inline int_type MC2(){ return boost::simd::integral_constant<int_type, -600>();};
      static inline int_type C3(){ return boost::simd::integral_constant<int_type, 0x0010000000000000ll>();}
      static inline int_type M1(){ return boost::simd::integral_constant<int_type, 0xffffffff00000000ll>();};
    };

    typedef typename dispatch::meta::as_floating<A0>::type result_type; 

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0; 
      typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::as_logical<int_type>::type bint_type; 
      typedef hypot_ctnts<A0, int_type> cts;
      A0 x =  boost::simd::abs(a0);
      A0 y =  boost::simd::abs(a1);
      bA0 tinf = is_inf(x+y);
      A0 a =  boost::simd::max(x, y);
      A0 b =  boost::simd::min(x, y);
      int_type ea =   exponent(a);
      int_type eb  =  exponent(b);
      bint_type te1 = gt(ea,cts::C1());
      bint_type te2 = lt(eb,cts::MC1());
      bool te3 = boost::simd::any(logical_or(te1, te2));
      int_type e = Zero<int_type>();
      if (te3)
      {
        e = select(te1, cts::MC2(), e);
        e = select(te2, cts::C1(),  e);
        a =  ldexp(a, e);
        b =  ldexp(b, e);
      }
      A0 w = a-b;
      bA0 test =  gt(w,b);
      A0 t1 = a& cts::M1();
      A0 t2 = a-t1;
      A0 w1_2  = (t1*t1-(b*(-b)-t2*(a+t1)));
      A0 y1 = b& cts::M1();
      A0 y2 = b - y1;
      t1 = bitwise_cast<A0>(bitwise_cast<int_type>(a)+cts::C3()) ;
      t2 = (a+a) - t1;
      A0 w2_2  = (t1*y1-(w*(-w)-(t1*y2+t2*b)));
      w =  select(test, w1_2, w2_2);
      w = boost::simd::sqrt(w);
      if (te3) w = ldexp(w, -e);
      return select(tinf, Inf<A0>(), w);
    }
  };
} } }

#endif
