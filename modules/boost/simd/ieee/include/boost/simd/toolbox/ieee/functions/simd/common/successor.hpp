//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>
#include <boost/simd/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/fast_frexp.hpp>
#include <boost/simd/include/functions/fast_ldexp.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/next.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_ unary
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return  seladd(neq(a0, Valmax<A0>()), a0, One<A0>());
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_ unary
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::next(a0);
    }
  };
} } }



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<integer_<A0>,X>))((simd_<integer_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      using boost::simd::Valmax;
      return boost::simd::seladd( boost::simd::gt(Valmax<A0>()-boost::simd::abs(a1), a0), a0, boost::simd::abs(a1));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      using boost::simd::Inf;
      return select(eq(a0, Inf<A0>()), a0,  bitfloating(bitinteger(a0)+a1));
//       typedef typename dispatch::meta::as_integer<A0, signed>::type itype;
//       A0 m;
//       itype expon;
//       const A0 fac =  boost::simd::abs(tofloat(a1));
//       boost::fusion::tie(m, expon) = fast_frexp(a0);
//       expon =  seladd(iseq(m, Mhalf<A0>()), expon, Mone<itype>());
//       A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
//       diff = b_and(select(iseqz(diff)||iseqz(a0),  Mindenormal<A0>(), diff), isfin(a0));
//       return select(iseq(a0, Minf<A0>()), fac*Valmin<A0>(), a0+fac*diff);
    }
  };
} } }


#endif
