//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_EPS_HPP_INCLUDED
#include <boost/simd/include/constants/properties.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/sdk/details/ignore_unused.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>
#include <boost/simd/include/functions/exponent.hpp>
#include <boost/simd/include/functions/abs.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::eps_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return One<A0>();
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::eps_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, signed>::type        int_type;
      const A0 a = boost::simd::abs(a0);
      return seladd(is_invalid(a),
                select(is_less(a, Smallestposval<A0>()),
                     Mindenormal<A0>(),
                     ldexp(One<A0>(), exponent(a)-Nbmantissabits<A0>())
                     ),
                Nan<A0>());
      }
  };
} }


#endif
