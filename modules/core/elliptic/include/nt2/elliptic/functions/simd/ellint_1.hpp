//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SIMD_ELLINT_1_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SIMD_ELLINT_1_HPP_INCLUDED
#include <nt2/elliptic/functions/ellint_1.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {

      typedef typename meta::scalar_of<result_type>::type scalar_type;
      result_type a = One<result_type>();
      result_type b = nt2::sqrt(oneminus(sqr(a0)));
      result_type c = a0;
      while (nt2::maximum(abs(c)) > Eps<scalar_type>())
      {
        result_type an=average(a, b);
        result_type bn=nt2::sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return if_nan_else(gt(nt2::abs(a0), One<result_type>()),
                         if_else(is_eq(a0, One<result_type>()), Inf<result_type>(), Pio_2<result_type>()/a)
                        );
    }
  };
} }


#endif
// function [K]=%k(m)
//     //K=%k(m)
//     //Calculates Jacobi's complete elliptic integral
//     //of the first kind:
//     //  K = integral from 0 to 1 of
//     //      [(1-t**2)(1-m*t**2)]**(-1/2)
//     //m is allowed to be a vector
//     //Ref :Abramowitz and Stegun page 598
//     //  m :Parameter used in calculating the elliptic
//     //    :integral where 0<m<1.
//     //  K :Value of the elliptic integral from 0 to 1
//     //    :on the real axis.
//     //
//     //!

//     [n1,n2]=size(m);
//     un=ones(n1,n2);
//     a=un;
//     b=sqrt(un-m);
//     c=sqrt(m);
//     while max(abs(c)) > %eps,
//         an=0.5*(a+b);
//         bn=sqrt(a.*b);
//         cn=0.5*(a-b);
//         a=an;
//         b=bn;
//         c=cn;
//     end,
//     K=%pi*un./(2*a);
// endfunction
