//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINTS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_TOUINTS_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/touints.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/is_gez.hpp>
#include <boost/simd/include/functions/is_greater_equal.hpp>
#include <boost/simd/include/functions/oneplus.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<unsigned_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    #ifdef BOOST_PROTO_STRICT_RESULT_OF
    result_type
    #else
    A0 const&
    #endif
    operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<signed_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_FORCEINLINE
    result_type
    operator()(A0 const& a0) const
    {
      return if_else_zero(is_gez(a0), bitwise_cast<result_type>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touints_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;
    typedef typename dispatch::meta::as_integer<A0>::type si_type;

    BOOST_FORCEINLINE
    result_type
    operator()(A0 const& a0) const
    {
      A0 r = if_else_zero(is_gez(a0), a0);
      return if_else(ge(a0,tofloat(Valmax<si_type>())),
                     bitwise_cast<result_type>(toint(a0-tofloat(Valmax<si_type>())))+oneplus(bitwise_cast<result_type>(Valmax<si_type>())),
                     bitwise_cast<result_type>(toint(r))
        );
    }
  };

} } }

#endif
