/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// store for SIMD types
// TODO : Documentation for simd store
// TODO : Make them work properly with ContiguousRandomAccessIterator
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over store for arithmetic SIMD types
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::store_
                      , tag::cpu_
                      , (A0)(A1)(A2)
                      , ((simd_< arithmetic_<A0>, tag::altivec_ >))
                        (iterator_< arithmetic_<A1> >)
                        (integer_<A2>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::store_ ( tag::simd_<tag::arithmetic_,tag::altivec_>
                            , tag::iterator_<tag::arithmetic_>
                            , tag::integer_
                            )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(3)
    {
      vec_st(a0.data_, a2*16, a1);
      return a0;
    }
  };
} }

#endif
