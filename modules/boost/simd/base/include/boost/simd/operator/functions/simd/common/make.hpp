//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAKE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAKE_HPP_INCLUDED

#include <boost/simd/operator/functions/make.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, tag::cpu_
                                   , (A0)(X)
                                   , ((target_< simd_< unspecified_<A0>, X > >))
                                   )
  {
    typedef typename A0::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    #define M0(z,n,t)                                                                              \
    inline result_type                                                                             \
    operator()(BOOST_PP_ENUM_PARAMS(n, stype const& a)) const                                      \
    {                                                                                              \
      BOOST_SIMD_ALIGNED_TYPE(stype) tmp[n] = { BOOST_PP_ENUM_PARAMS(n, a) };                      \
      return aligned_load<result_type>(&tmp[0], 0);                                                \
    }                                                                                              \
    /**/

    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::make_, tag::cpu_
                                      , (A0)(X)
                                      , (mpl::equal_to
                                              < mpl::sizeof_<A0>
                                              , mpl::sizeof_<typename A0::type>
                                              >
                                        )
                                      , ((target_< simd_< logical_<A0>, X > >))
                                      )
  {
    typedef typename A0::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;
    typedef typename dispatch::meta::as_integer<result_type, unsigned>::type iresult_type;
    typedef typename meta::scalar_of<iresult_type>::type istype;

    #define M1(z,n,t) bitwise_cast<istype>(genmask(a##n))

    #define M0(z,n,t)                                                                              \
    BOOST_FORCEINLINE result_type                                                                  \
    operator()(BOOST_PP_ENUM_PARAMS(n, stype const& a)) const                                      \
    {                                                                                              \
      return bitwise_cast<result_type>(make<iresult_type>(BOOST_PP_ENUM(n, M1, ~)));               \
    }                                                                                              \
    /**/

    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
    #undef M1
  };
} } }

#endif
