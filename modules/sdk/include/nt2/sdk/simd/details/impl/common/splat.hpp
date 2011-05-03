/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatches over splat_
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::splat_, tag::cpu_, (A0)(A1)(X)
                      , (unspecified_<A0>)
                        ((target_< simd_< unspecified_<A1>, X > >))
                      )
namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::splat_ ( tag::unspecified_
                            , tag::target_<tag::simd_<tag::unspecified_, X> >
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A1>::type {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A1>::type sA1;
      
      NT2_ALIGNED_TYPE(sA1) tmp[meta::cardinal_of<A1>::value];
      for(int i = 0; i != meta::cardinal_of<A1>::value; ++i)
        tmp[i] = a0;
      
      return load<A1>(&tmp[0], 0);
    }
  };
} }

#endif
