//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_GREATER_EQUAL_HPP_INCLUDED

#include <boost/simd/operator/functions/is_greater_equal.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, tag::cpu_,
                                    (A0)(A1)(X),
                                    ((simd_<arithmetic_ <A0>,X>))((scalar_<arithmetic_<A1> >))
                                   )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::is_greater_equal(a0, boost::simd::splat<A0>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_greater_equal_, tag::cpu_,
                                     (A0)(A1)(X),
                                     ((scalar_<arithmetic_<A0> >))((simd_<arithmetic_<A1>,X>))
                                   )
  {
    typedef typename meta::as_logical<A1>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::is_greater_equal(boost::simd::splat<A1>(a0), a1);
    }
  };
} } }

#endif
