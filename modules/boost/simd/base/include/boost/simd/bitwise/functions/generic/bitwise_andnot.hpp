//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_BITWISE_ANDNOT_HPP_INCLUDED

#include <boost/simd/bitwise/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/bitwise_notand.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::bitwise_andnot_
                                      , tag::cpu_
                                      , (A0)(A1)
                                      , ( boost::mpl::bool_
                                          <   sizeof(typename meta::scalar_of<A0>::type)
                                          ==  sizeof(typename meta::scalar_of<A1>::type)
                                          >
                                        )
                                      , (generic_< arithmetic_<A0> >)
                                        (generic_< arithmetic_<A1> >)
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_notand(a1,a0);
    }
  };
} } }

#endif
