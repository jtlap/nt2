//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <boost/fusion/tuple.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/is_eqz.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<successor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::is_integral<A1> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute successor(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<successor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>: meta::strip<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1, real_)
    {
      return next(a0); 
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, real_)
    {
      typedef typename meta::as_integer<A0, signed>::type itype;
      if (iseq(a0, Minf<A0>())) return a1*Valmin<A0>();
      if (iseqz(a0))            return a1*Mindenormal<A0>();    
      A0 m;
      itype expon;
      boost::fusion::tie(m, expon) = fast_frexp(a0);
      if(iseq(m, Mhalf<A0>())) --expon; 
      A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
      return diff ? a1*Mindenormal<A0>():a0+a1*diff; 
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)  { return oneplus(a0); }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)  { return a0+a1;       }
   };
} }


      
#endif
