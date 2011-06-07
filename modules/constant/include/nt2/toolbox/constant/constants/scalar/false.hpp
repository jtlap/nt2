//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_REGISTER_DISPATCH(tag::false_ ,tag::cpu_,(A0),(target_< fundamental_<A0> >))

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::false_(tag::target_<tag::fundamental_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return splat<typename A0::type>(false);
    }
  };
} }

#endif
