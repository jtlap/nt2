//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_DEFINITELY_GREATER_HPP_INCLUDED

#include <nt2/include/functions/is_ord.hpp>
#include <nt2/include/functions/successor.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::definitely_greater_, tag::cpu_,
                                    (A0)(A1)(A2),
                                    (integer_<A0>)(integer_<A1>)(integer_<A2>)
                                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::definitely_greater_(tag::integer_,tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; };

    NT2_FUNCTOR_CALL(3)
    {
      return (a0 > a1+a2);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::definitely_greater_, tag::cpu_,
                                    (A0)(A1)(A2),
                                    (real_<A0>)(real_<A1>)(integer_<A2>)
                                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::definitely_greater_(tag::real_,tag::real_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> {typedef bool type; };

    NT2_FUNCTOR_CALL(3)
    {
      return b_and(
               is_ord(a0, a1),
               (a0 >  successor(a1, a2))
               );
    }
  };
} }

#endif
// modified by jt the 26/12/2010
