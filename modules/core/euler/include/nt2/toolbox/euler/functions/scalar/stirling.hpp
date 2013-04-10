//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_STIRLING_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_STIRLING_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/stirling.hpp>
#include <nt2/include/functions/scalar/pow.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/exp.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
#include <nt2/toolbox/euler/constants/stirlinglargelim.hpp>
#include <nt2/toolbox/euler/constants/stirlingsplitlim.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2pi.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::stirling_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::stirling(result_type(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::stirling_, tag::cpu_,
           (A0),
           (scalar_< floating_<A0> >)
           )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (nt2::is_nan(a0)) return nt2::Nan<A0>();
      if (a0 > nt2::Stirlinglargelim<A0>()) return nt2::Inf<A0>();
      A0 w = nt2::rec(a0);
      w = fma(w, polevl(w, stirpol<A0, A0>::sp()), nt2::One<A0>());
      A0 y = nt2::exp(-a0);
      if(nt2::is_eqz(y)) return nt2::Inf<A0>();
      if( a0 > nt2::Stirlingsplitlim<A0>() )
        { /* Avoid overflow in pow() */
          const A0 v = nt2::pow(a0,nt2::fma(Half<A0>(),a0,-nt2::Quarter<A0>()));
          y *= v;
          y *= v;
        }
      else
        {
          y *= nt2::pow( a0, a0 - nt2::Half<A0>() );
        }
      y *= nt2::Sqrt_2pi<A0>()*w;
      return y;
    }
  private:
    template < class AA0, class D> struct stirpol{};
    template < class AA0> struct stirpol<AA0, float>
    {
      static inline  boost::array<AA0, 3> sp()
      {
        static const boost::array<AA0, 3 > s =
          {{
              -2.705194986674176E-003f,
              3.473255786154910E-003f,
              8.333331788340907E-002f,
            }};
        return s;
      }
    };
    template < class AA0> struct stirpol<AA0, double>
    {
      static inline boost::array<AA0, 5> sp()
      {
        static const boost::array<AA0, 5 > s = {{
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
