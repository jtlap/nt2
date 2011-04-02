//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXPX2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_EXPX2_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/floor.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expx2_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::expx2_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return expx2(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expx2_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::expx2_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (is_inf(a0)) return Inf<A0>();
      A0 x =  nt2::abs(a0);
      /* Represent x as an exact multiple of 1/32 plus a residual.  */
      A0 m = Expx2c1<A0>() * floor(Expx2c2<A0>() * x + Half<A0>());
      x -= m;
      /* x**2 = m**2 + 2mf + f**2 */
      A0 u = sqr(m);
      A0 u1 = Two<A0>() * m * x  +  sqr(x);
      if ((u+u1) > Maxlog<A0>()) return Inf<A0>();
      /* u is exact, u1 is small.  */
      return exp(u) * exp(u1);
    }
  };
} }

#endif
// modified by jt the 26/12/201

