//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_DEFINITELY_LESS_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_DEFINITELY_LESS_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>

#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_finite.hpp>

#include <nt2/include/functions/successor.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::definitely_less_, tag::cpu_,
                                 (A0)(A1)(A2),
                                 (arithmetic_<A0>)(arithmetic_<A1>)(arithmetic_<A2>)
                                )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::definitely_less_(tag::arithmetic_,tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> :
      boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
        return a0 < a1-a2;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::definitely_less_, tag::cpu_,
                                 (A0)(A1)(A2),
                                 (real_<A0>)(real_<A1>)(real_<A2>)
                                )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::definitely_less_(tag::real_,tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> :
      boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      if (isfin(a0) && a1 == Inf<A1>()) return true;
      if (isfin(a1) && a0 == Minf<A0>()) return true;
      if (isnan(a0) || isnan(a1)) return false;
      return  a0 < successor(a1,-a2);
    }
  };
} }

#endif
// modified by jt the 26/12/2010