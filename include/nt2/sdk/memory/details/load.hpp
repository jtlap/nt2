/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_LOAD_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ without offset
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        (target_< fundamental_<T> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_<tag::fundamental_>
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
      A0 that = a0;
      std::advance(that,a1);
      return *that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ with offset
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::load_
                      , tag::cpu_
                      , (A0)(A1)(T)(N)
                      , (iterator_<fundamental_<A0> >)
                        (fundamental_<A1>)
                        (target_< fundamental_<T> >)
                        (mpl_integral_< integer_<N> >)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::load_( tag::iterator_<tag::fundamental_>
                          , tag::fundamental_
                          , tag::target_<tag::fundamental_>
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
      A0 that = a0;
      std::advance(that,a1+A3::value);
      return *that;
    }
  };
} }

#endif
