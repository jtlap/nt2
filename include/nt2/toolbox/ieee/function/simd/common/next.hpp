//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXT_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXT_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_finite.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for next

  /////////////////////////////////////////////////////////////////////////////
  // Compute next(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<next_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,    real_)
    {
      typedef typename meta::as_integer<A0, signed>::type itype; 
      A0 m;
      itype expon;
      boost::fusion::tie(m, expon) = fast_frexp(a0);
      expon =  seladd(is_equal(m, Mhalf<A0>()), expon, Mone<itype>()); 
      A0 diff =  fast_ldexp(One<A0>(), expon-Nbdigits<A0>());
      diff = b_and(sel(is_eqz(diff)||is_eqz(a0),  Mindenormal<A0>(), diff), is_finite(a0));
//       std::cout << "diff  "<< diff << std::endl;
//       std::cout << "a0    "<< a0   << std::endl;  
      return sel(is_equal(a0, Minf<A0>()), Valmin<A0>(), a0+diff); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,    arithmetic_)
    {
      return a0+One<A0>(); 
    }
  };
} }

      
#endif
