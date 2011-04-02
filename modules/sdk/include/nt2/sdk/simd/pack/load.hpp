/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_LOAD_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for SIMD packs
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd pack
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(A2)(T)(C)(Sema)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< expr_< A2
                                        , domain_< simd::domain<T,C> >
                                        , tag::terminal_
                                        , Sema
                                        >
                                 >
                        ))
                      )

namespace nt2 { namespace ext
{
  template<class T, class C, class Sema, class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_<tag::expr_ < simd::domain<T,C>
                                                    , tag::terminal_
                                                    , Sema
                                                    >
                                        >
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
      type that(a0,a1);
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd pack with suboffset
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(A2)(T)(C)(Sema)(N)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        ((target_< expr_< A2
                                        , domain_< simd::domain<T,C> >
                                        , tag::terminal_
                                        , Sema
                                        >
                                 >
                        ))
                        (mpl_integral_< integer_<N> >)
                      )

namespace nt2 { namespace ext
{
  template<class T, class C, class Sema, class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_<tag::expr_ < simd::domain<T,C>
                                                    , tag::terminal_
                                                    , Sema
                                                    >
                                        >
                          , tag::mpl_integral_<tag::integer_>
                          )
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class A0,class A1,class A2,class A3>
    struct result<This(A0,A1,A2,A3)> : meta::strip<A2>::type {};

    NT2_FUNCTOR_CALL(4)
    {
      typedef typename NT2_RETURN_TYPE(4)::type type;
      type that(a0,a1,a3);
      return that;
    }
  };
} }

#endif
