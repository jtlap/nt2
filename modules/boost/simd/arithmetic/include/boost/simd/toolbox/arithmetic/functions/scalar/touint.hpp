//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TOUINT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_TOUINT_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/touint.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/oneplus.hpp>
#include <boost/simd/include/functions/is_ngt.hpp>
#include <boost/simd/include/functions/scalar/is_lez.hpp>
#include <boost/simd/include/functions/scalar/is_gez.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touint_, tag::cpu_ , (A0)
                            , (scalar_< integer_<A0> >)
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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touint_, tag::cpu_
                            , (A0)
                            , ((scalar_<signed_<A0> > ))
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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::touint_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, unsigned> ::type result_type;
    typedef typename dispatch::meta::as_integer<A0>::type si_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_lez(a0)) return Zero<result_type>();
      if (is_ngt(a0,tofloat(Valmax<si_type>())))
        return bitwise_cast<result_type>(toint(a0));
      else
        return bitwise_cast<result_type>(toint(a0-tofloat(Valmax<si_type>())))+oneplus(bitwise_cast<result_type>(Valmax<si_type>()));

    }
  };
} } }

#endif
