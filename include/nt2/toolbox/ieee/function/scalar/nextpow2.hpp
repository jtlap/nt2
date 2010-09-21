//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTPOW2_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEXTPOW2_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/abs.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for nextpow2

  /////////////////////////////////////////////////////////////////////////////
  // Compute nextpow2(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<nextpow2_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename meta::as_integer<A0, signed>::type int_type;
      A0 m;
      int_type p;
      boost::fusion::tie(m, p) = nt2::frexp(nt2::abs(a0));
      return (m == Half<A0>())  ? minusone(p) :  p;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::nextpow2(type(a0));
    }
  };
} }


      
#endif
