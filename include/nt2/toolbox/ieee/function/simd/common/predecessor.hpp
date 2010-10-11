//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_PREDECESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_PREDECESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/prev.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<predecessor_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : meta::is_integral<A1> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute predecessor(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<predecessor_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>       { typedef A0 type;  };
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>   { typedef A0 type;  };

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1, real_)
    {
      return prev(a0);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)  { return oneplus(a0); }

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2, real_)
    {
      typedef typename meta::as_integer<A0, signed>::type itype; 
      A0 m;
      itype expon;
      const A0 fac =  abs(tofloat(a1)); 
      boost::fusion::tie(m, expon) = fast_frexp(a0);
      expon =  seladd(iseq(m, Mhalf<A0>()), expon, Mone<itype>()); 
      A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
      diff = b_and(sel(iseqz(diff)||iseqz(a0),  Mindenormal<A0>(), diff), isfin(a0));
      return sel(iseq(a0, Inf<A0>()), fac*Valmax<A0>(), a0-fac*diff); 
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return a0-a1; ;
    }
  };
} }

      
#endif
