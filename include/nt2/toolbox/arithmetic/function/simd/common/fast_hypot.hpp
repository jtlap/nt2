//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<fast_hypot_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_hypot(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<fast_hypot_,tag::simd_(tag::arithmetic_,Extension),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 x =  abs(a0);
      A0 y =  abs(a1);
      A0 gtyx = gt(y,x); 
      A0 xx = sel(gtyx,y,x);
      A0 yy = sel(gtyx,x,y);
      A0 r =  xx*sqrt(One<A0>()+sqr(yy/xx));
      return sel(ge(xx*Eps<A0>(), yy), xx, r);     
   }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<fast_hypot_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      return nt2::fast_hypot(tofloat(a0), tofloat(a1));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
