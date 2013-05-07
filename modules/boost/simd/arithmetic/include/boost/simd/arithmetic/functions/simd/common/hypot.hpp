//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/hypot.hpp>
#include <boost/simd/include/functions/simd/tofloat.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/is_inf.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/exponent.hpp>
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/sqrt.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

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
      typedef typename dispatch::meta::as_integer<result_type>::type itype;
      result_type r =  boost::simd::abs(a0);
      result_type i =  boost::simd::abs(a1);
      itype e =  exponent(boost::simd::max(i, r));
      return  if_else( logical_or(logical_and(is_nan(a0), is_inf(a1)),
                                  logical_and(is_nan(a1), is_inf(a0))),
                       Inf<result_type>(),
                       ldexp(sqrt(sqr(ldexp(r, -e))+sqr(ldexp(i, -e))), e)
                       );
    }
  };
} } }

#endif
