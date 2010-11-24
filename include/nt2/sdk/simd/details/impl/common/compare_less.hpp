/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_COMPARE_LESS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_COMPARE_LESS_HPP_INCLUDED

#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call< simd::is_less_,tag::simd_(tag::arithmetic_,tag::sse_)
              , fundamental_  , Info
              >
        : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(2)
    {
      for(std::size_t i=0;i<meta::cardinal_of<A0>::value;++i)
      {
        if (a0[i] < a1[i])  return true;
        if (a1[i] < a0[i])  return false;
      }
      return false;
    }
  };
} }

#endif
