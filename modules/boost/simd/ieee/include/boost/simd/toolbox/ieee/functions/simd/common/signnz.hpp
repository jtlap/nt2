//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SIGNNZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SIGNNZ_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/signnz.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/signmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<integer_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return genmask(is_ltz(a0))-genmask(is_gez(a0)); // here True is -1 False 0 !
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<unsigned_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0&)const
    {
      return One<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::signnz_, tag::cpu_,
                         (A0)(X),
                         ((simd_<floating_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      #ifndef BOOST_SIMD_NO_NANS
      return if_else(is_nan(a0), a0, b_or(One<A0>(), b_and(Signmask<A0>(), a0)));
      #else
      return b_or(One<A0>(), b_and(Signmask<A0>(), a0));
      #endif
      ;
    }
  };
} } }
#endif
