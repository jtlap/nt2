/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// store for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::store_
                      , tag::cpu_
                      , (A0)(A1)(A2)
                      , (fundamental_<A0>)
                        (iterator_< fundamental_<A1> >)
                        (integer_<A2>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::store_ ( tag::fundamental_
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
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };
} }

#endif
