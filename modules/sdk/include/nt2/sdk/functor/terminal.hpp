//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_TERMINAL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_TERMINAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2
{
  //==============================================================================
  // Special functor for handling terminal in expression AST evaluation
  //==============================================================================
  template<class Site> struct functor<tag::terminal_,Site>
  {
    template<class Sig> struct result;

    template<class This, class Value, class State, class Data>
    struct result<This(Value, State, Data)>
    {
      typedef typename
      meta::dispatch_call<tag::terminal_(Value,State,Data),Site>::type  callee;
      typedef typename
      meta::result_of<callee(Value, State, Data)>::type             type;
    };

    template<class Value, class State, class Data> inline
    typename meta::enable_call<tag::terminal_(Value,State,Data),Site>::type
    operator()( Value& v, State& s, Data& d ) const
    {
      typename
      meta::dispatch_call<tag::terminal_(Value,State,Data),Site>::type callee;
      return callee(v,s,d);
    }
  };
}

#endif
