//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_STIRLING_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_STIRLING_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/toolbox/euler/function/scalar/constants.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::stirling_, tag::cpu_,
                          (A0),
                          (arithmetic_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::stirling_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return stirling(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::stirling_, tag::cpu_,
                          (A0),
                          (real_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::stirling_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return Nan<A0>();
      if (a0 > Stirlinglargelim<A0>()) return Inf<A0>();
//       static const boost::array<A0, 3 > stirpoly = {{
//      -2.705194986674176E-003f,
//      3.473255786154910E-003f,
//      8.333331788340907E-002f,
//    }};
      A0 w = rec(a0);
      w = fma(w, polevl(w, stirpol<A0, A0>::sp()), One<A0>());
      A0 y = exp(-a0);
      if(is_eqz(y)) return Inf<A0>();
      if( a0 > Stirlingsplitlim<A0>() )
      { /* Avoid overflow in pow() */
        const A0 v = pow(a0,fma(Half<A0>(),a0,-Quarter<A0>()));
        y *= v;
        y *= v;
      }
      else
      {
        y *= pow( a0, a0 - Half<A0>() );
      }
      y *= Sqrt_2pi<A0>()*w;
      return y;
    }
  private:
    template < class A0, class D> struct stirpol{};
    template < class A0> struct stirpol<A0, float>
    {
      static inline  boost::array<A0, 3> sp()
      {
      static const boost::array<A0, 3 > s =
      {{
        -2.705194986674176E-003f,
        3.473255786154910E-003f,
        8.333331788340907E-002f,
      }};
      return s;
      }
    };
    template < class A0> struct stirpol<A0, double>
    {
      static inline boost::array<A0, 5> sp()
      {
      static const boost::array<A0, 5 > s = {{
        7.87311395793093628397E-4,
        -2.29549961613378126380E-4,
        -2.68132617805781232825E-3,
        3.47222221605458667310E-3,
        8.33333333333482257126E-2,
      }};
      return s;
      }
    };

  };
} }

#endif
// modified by jt the 26/12/2010