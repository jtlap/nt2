//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/is_nan.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for ulpdist

  /////////////////////////////////////////////////////////////////////////////
  // Compute ulpdist(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<ulpdist_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typedef typename meta::as_integer<A0>::type itype;
      itype e1, e2;
      A0 m1, m2;
      boost::fusion::tie(m1, e1) = nt2::frexp(a0);
      boost::fusion::tie(m2, e2) = nt2::frexp(a1);
      itype expo = -nt2::max(e1, e2);
      //      double e = nt2::abs(nt2::ldexp(a0, expo)-nt2::ldexp(a1, expo));
      A0 e = sel(is_eq(e1, e2), nt2::abs(m1-m2), nt2::abs(nt2::ldexp(a0, expo)-nt2::ldexp(a1, expo))); 
      return sel((isnan(a0)&isnan(a1))|isnan(a0-a1),  Zero<A0>(), e/Eps<A0>());
      //      return abs(tofloat(bitinteger(a0)-bitinteger(a1)));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      return (max(a0, a1)-min(a0,a1));
    }
  };
} }

      
#endif
