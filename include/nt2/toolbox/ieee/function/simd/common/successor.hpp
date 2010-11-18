//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
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
#include <nt2/include/functions/next.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<successor_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)> : meta::is_integral<A1> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute successor(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<successor_,tag::simd_(tag::arithmetic_,Extension),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>: meta::strip<A0>{};
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>: meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return next(a0);
    }

    NT2_FUNCTOR_CALL(2)
    {
      return a0==Inf<A0>() ? a0 : bitfloating(bitinteger(a0)+a1);
//       typedef typename meta::as_integer<A0, signed>::type itype; 
//       A0 m;
//       itype expon;
//       const A0 fac =  abs(tofloat(a1)); 
//       boost::fusion::tie(m, expon) = fast_frexp(a0);
//       expon =  seladd(iseq(m, Mhalf<A0>()), expon, Mone<itype>()); 
//       A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
//       diff = b_and(sel(iseqz(diff)||iseqz(a0),  Mindenormal<A0>(), diff), isfin(a0));
//       return sel(iseq(a0, Minf<A0>()), fac*Valmin<A0>(), a0+fac*diff); 
    }

  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<successor_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>: meta::strip<A0>{};
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>: meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1){ return oneplus(a0); }
    NT2_FUNCTOR_CALL(2){ return a0+a1;       }
  };

} }

#endif
/// Revised by jt the 15/11/2010
/// No restore -- hand modifications
