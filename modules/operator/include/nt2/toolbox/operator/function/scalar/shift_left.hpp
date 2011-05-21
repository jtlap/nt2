//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SHIFT_LEFT_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SHIFT_LEFT_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_bits.hpp>

NT2_REGISTER_DISPATCH( tag::shift_left_, tag::cpu_
                     , (A0)(A1)
                     , (real_<A0>)(integer_<A1>)
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call<tag::shift_left_(tag::real_,tag::integer_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      typename meta::as_bits<A0>::type t0 = {a0};
      t0.bits = t0.bits << a1;
      return t0.value;
    }
  };
} }

NT2_REGISTER_DISPATCH( tag::shift_left_ , tag::cpu_
                     , (A0)(A1)
                     , (integer_<A0>)(integer_<A1>)
                     );
                     
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call<tag::shift_left_(tag::integer_,tag::integer_), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>
    {
      static A0 a0; static A1 a1;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,a0 << a1)
      typedef typename nested::type type;
    };

    NT2_FUNCTOR_CALL(2) { return a0 << a1; }
  };
} }

#endif
