/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

////////////////////////////////////////////////////////////////////////////////
// Splat over terminal of simd domain using the pack::fill method
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::store_
                      , tag::cpu_
                      , (A0)(A1)(A2)(T)(C)(Sema)
                      , (( expr_< A0
                                , domain_< simd::domain<T,C> >
                                , tag::terminal_
                                , Sema
                                >
                        ))
                        (iterator_< fundamental_<A1> >)
                        (integer_<A2>)
                      )

namespace nt2 { namespace ext
{
  template<class T, class C, class Sema, class Dummy>
  struct  call< tag::store_ ( tag::expr_< simd::domain<T,C>
                                        , tag::terminal_
                                        , Sema
                                        >
                            , tag::iterator_<tag::fundamental_>
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
      A0 that = store(boost::proto::value(a0).value(),a1,a2);
      return that;
    }
  };
} }

#endif
