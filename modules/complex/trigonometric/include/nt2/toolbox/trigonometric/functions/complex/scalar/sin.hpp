//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_SIN_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SCALAR_SIN_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/sin.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <complex>
#include <cmath>
/* csin (x + I * y) = sin (x) * cosh (y)  + I * (cos (x) * sinh (y)) */
namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sin_, tag::cpu_, (A0)
//                             , (scalar_< complex_< arithmetic_<A0> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       return std::sin(a0); 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sin_, tag::cpu_, (A0)
//                             , (scalar_< imaginary_< arithmetic_<A0> > >)
//                             )
//   {
//     typedef typename meta::as_real<A0>::type rA0;
//     typedef typename meta::as_complex<rA0>::type result_type; 
//     NT2_FUNCTOR_CALL(1)
//     {
//       return result_type(nt2::sinh(imag(a0))); 
//     }
//   };
  
} }

#endif
