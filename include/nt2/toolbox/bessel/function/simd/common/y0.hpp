//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_Y0_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_Y0_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/j0.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/all.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<arithmetic_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y0_(tag::simd_(tag::arithmetic_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::y0(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<double_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y0_(tag::simd_(tag::double_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::y0_>(), a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::y0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<float_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::y0_(tag::simd_(tag::float_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 x   =  abs(a0);
      A0 lt2 = lt(x, Two<A0>());
      if (all(lt2))
      return branch1(x);
      else
      return select (lt2, branch1(x), branch2(x));
      // as branch1 is quick there is no need for an "else if" case
      // computing only branch2,  this probably due to the double pipeline
    }
  };
} }

#endif
// modified by jt the 05/01/2011
