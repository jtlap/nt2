//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SQRS_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SQRS_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/sqrs.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/functions/simd/abss.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/sqrtvalmax.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <iostream>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sqrs_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< int_<A0>, X >))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      typedef typename dispatch::meta::upgrade<utype>::type uutype;
      std::cout << "icitte" << std::endl;
      return if_else(gt(abss(a0), boost::simd::Sqrtvalmax<result_type>()),
                     boost::simd::Valmax<result_type>(), bitwise_cast<A0>(sqr(bitwise_cast<utype>(a0))));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sqrs_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< uint_<A0>, X>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(gt(abss(a0), boost::simd::Sqrtvalmax<result_type>()),
                     boost::simd::Valmax<result_type>(), sqr(a0));
    }
  };

} } }

#endif
