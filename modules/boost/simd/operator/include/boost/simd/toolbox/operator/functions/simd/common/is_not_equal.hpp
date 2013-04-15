//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/is_not_equal.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::is_not_equal_
                                      , boost::simd::tag::cpu_
                                      , (A0)(X)
                                      , (mpl::equal_to< boost::simd::meta::cardinal_of<A0>
                                                      , boost::simd::meta::cardinal_of<typename A0::type>
                                                      >
                                        )
                                      , ((simd_<logical_<A0>,X>))
                                        ((simd_<logical_<A0>,X>))
                                      )
  {
    typedef A0                                                result_type;
    typedef typename meta::as_arithmetic<A0>::type            base_t;
    typedef typename dispatch::meta::as_integer<base_t>::type cast_t;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return bitwise_cast<A0> ( neq( bitwise_cast<cast_t>(a0)
                                   , bitwise_cast<cast_t>(a1)
                                   )
                              );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_not_equal_, tag::cpu_,
                                    (A0)(A1)(X),
                                    ((simd_<arithmetic_ <A0>,X>))((scalar_<arithmetic_<A1> >))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::is_not_equal(a0, boost::simd::splat<A0>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_not_equal_, tag::cpu_,
                                     (A0)(A1)(X),
                                     ((scalar_<arithmetic_<A0> >))((simd_<arithmetic_<A1>,X>))
                                   )
  {
    typedef A1 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return boost::simd::is_not_equal(boost::simd::splat<A1>(a0), a1);
    }
  };
} } }

#endif
