/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for SSE2 SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd double
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< double_<T>, tag::sse_ > >))
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_< tag::simd_<tag::double_,tag::sse_> >
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = { _mm_load_pd(a0+a1*meta::cardinal_of<type>::value) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd float
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< float_<T>, tag::sse_ > >))
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_< tag::simd_<tag::float_,tag::sse_> >
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = { _mm_load_ps(a0+a1*meta::cardinal_of<type>::value) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd integers
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< simd_< integer_<T>, tag::sse_ > >))
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_<tag::simd_<tag::integer_,tag::sse_> >
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = { _mm_load_si128(reinterpret_cast<__m128i const*>(a0)+a1) };
      return that;
    }
  };
} }

#include <nt2/sdk/simd/details/impl/sse/sse2/load_offset.hpp>

#endif
