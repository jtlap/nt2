//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_BITWISE_XOR_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_BITWISE_XOR_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

NT2_REGISTER_DISPATCH_IF ( tag::bitwise_xor_ , tag::cpu_, (A0)(A1)
                         , (boost::mpl::equal_to< boost::mpl::sizeof_<A0>, boost::mpl::sizeof_<A1> >)
                         , tag::bitwise_xor_(tag::fundamental_, tag::fundamental_)
                         , (fundamental_<A0>)(fundamental_<A1>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitwise_xor_(tag::fundamental_, tag::fundamental_), tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This, class A0, class A1> 
    struct result<This(A0, A1)> : meta::strip<A0>
    {
    };

    NT2_FUNCTOR_CALL(2)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      typename meta::as_bits<A1>::type t1 = {a1};
      t0.bits ^= t1.bits;
      return t0.value;
    }
  };
} }

#endif
