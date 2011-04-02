//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ULP_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/include/functions/prev.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ulp_, tag::cpu_,
                     (A0),
                     (arithmetic_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ulp_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return One<A0>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ulp_, tag::cpu_,
                     (A0),
                     (real_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ulp_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,signed>::type int_type;
      if (is_eqz(a0)) return Smallestposval<A0>();
      const A0 x = nt2::abs(a0);
      if (x == Inf<A0>()) return x; //Valmax<A0>()-prev(Valmax<A0>());
      typename meta::as_bits<A0>::type aa = {x},  bb = aa;
      --bb.bits;
      ++aa.bits;
      return nt2::min(x-bb.value, aa.value-x);
      //     const A0 pred = predecessor(x);
      //     return (x == Inf<A0>()) ? pred-predecessor(x) : min(dist(pred, x), dist(x, successor(x)));
    }
  };
} }

#endif
// modified by jt the 26/12/2010
