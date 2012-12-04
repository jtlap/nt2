//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ISQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_ISQRT_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/isqrt.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>
#include <boost/simd/include/functions/scalar/sqrt.hpp>
#include <boost/simd/include/functions/scalar/toint.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::isqrt_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename  dispatch::meta::as_integer<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return itrunc(boost::simd::sqrt(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::isqrt_, tag::cpu_
                            , (A0)
                            , (scalar_< uint_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return static_cast<A0>(boost::simd::sqrt(result_type(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::isqrt_, tag::cpu_
                            , (A0)
                            , (scalar_< int_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return (is_ltz(a0)) ?  Zero<A0>() : static_cast<A0>(boost::simd::sqrt(result_type(a0)));
    }
  };
} } }


#endif
