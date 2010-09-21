//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED

#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/abs.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for round2even

  /////////////////////////////////////////////////////////////////////////////
  // Compute round2even(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<round2even_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef A0 type;
    };

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
       const type v = abs(a0);
       const type t2n = Two2nmb<type>();
       volatile type d0 = (v+t2n);
       volatile type d = (d0-t2n);
       d = (v < t2n)?d:v;
       return b_xor(d, nt2::bitofsign(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return a0;
    }
  };
} }


      
#endif
