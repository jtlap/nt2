/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// make for SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>

NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(X)
                      , ((target_< simd_< arithmetic_<A0>, X > >))
                      )

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call< tag::make_ ( tag::target_<tag::simd_<tag::arithmetic_, X> >
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    #define M0(z,n,t)                                                                      \
    simd::native<A0, X> operator()(BOOST_PP_ENUM_PARAMS(n, A0 const& a)) const             \
    {                                                                                      \
      NT2_ALIGNED_TYPE(A0) tmp[n] = {                                                      \
        BOOST_PP_ENUM_PARAMS(n, a)                                                         \
      };                                                                                   \
      return load<simd::native<A0, X> >(&tmp[0], 0);                                       \
    }
    
    NT2_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
  };
} }

#endif
