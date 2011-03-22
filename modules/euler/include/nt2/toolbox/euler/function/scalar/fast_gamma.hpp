//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_FAST_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_FAST_GAMMA_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/stirling.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/is_eqz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_gamma_, tag::cpu_,
                            (A0),
                            (arithmetic_<A0>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_gamma_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return fast_gamma(type(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_gamma_, tag::cpu_,
                            (A0),
                            (real_<A0>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_gamma_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      static boost::array<A0, 7> P = {{
        1.60119522476751861407E-4,
        1.19135147006586384913E-3,
        1.04213797561761569935E-2,
        4.76367800457137231464E-2,
        2.07448227648435975150E-1,
        4.94214826801497100753E-1,
        9.99999999999999996796E-1
      }};
      static boost::array<A0, 8>  Q = {{
        -2.31581873324120129819E-5,
        5.39605580493303397842E-4,
        -4.45641913851797240494E-3,
        1.18139785222060435552E-2,
        3.58236398605498653373E-2,
        -2.34591795718243348568E-1,
        7.14304917030273074085E-2,
        1.00000000000000000320E0
        }};
      A0 x = a0, p, z;
      int32_t sgngam = 1;
      if( is_nan(x) || (x == Minf<A0>()) ) return Nan<A0>();
      if (x == Inf<A0>()) return x;
      A0 q = nt2::abs(x);
      if( q > 33.0 )
      {
        if( is_ltz(x))
          {
            if (((p = floor(q)) == q)) return Nan<A0>();
            int32_t i = (int32_t)p;
            if( is_even(i) ) sgngam = -1;
            z = q - p;
            if( z > Half<A0>() )
            {
              p += One<A0>();
              z = q - p;
            }
            z = q*sinpi(z);
            if( is_eqz(z) ) return Nan<A0>()*sgngam;
            z = nt2::abs(z);
            z = Pi<A0>()/(z * stirling(q) );
          }
        else
          {
            z = stirling(x);
          }
        return( sgngam * z );
      }

      z = One<A0>();
      while( x >= Three<A0>() )
      {
        x -= One<A0>();
        z *= x;
      }

      while( is_ltz(x) )
      {
        if( x > -1.E-9 )
          {
           return z / ((One<A0>() + Euler<A0>() * x) * x);
          }
        z /= x;
        x += One<A0>();
      }

      while( x < Two<A0>() )
      {
        if( is_eqz(x)) return Nan<A0>();
        if( x < 1.e-9 )
          {
            return z / ((One<A0>() + Euler<A0>() * x) * x);
          }
        z /= x;
        x +=  One<A0>();
      }

      if( x == Two<A0>() ) return(z);

      x -= Two<A0>();
      p = polevl(x,P);
      q = polevl(x,Q);
      return z*p/q;
    }
  };
} }

#endif
// modified by jt the 26/12/2010