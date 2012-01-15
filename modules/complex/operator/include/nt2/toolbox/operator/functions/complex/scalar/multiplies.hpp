//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_SCALAR_MULTIPLIES_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_SCALAR_MULTIPLIES_HPP_INCLUDED
#include <nt2/toolbox/operator/functions/multiplies.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/pure.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <iostream>

// namespace nt2 { namespace ext
// {
  // complex/complex
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)
//                             , (generic_< complex_< arithmetic_<A0> > >)
//                               (generic_< complex_< arithmetic_<A0> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//       {
//         //        return a0*a1; 
//         typedef typename meta::as_real<A0>::type rA0;
//         std::cout << "icitte" << std::endl; 
//         rA0 a0a1r = real(a0) * real(a1);
//         rA0 a0a1i = imag(a0) * imag(a1);
        
//         rA0 x = a0a1r - a0a1i; 
//         rA0 y = (real(a0) + imag(a0)) * (real(a1) + imag(a1)) - a0a1r - a0a1i;
//         if (is_invalid(x) || is_invalid(y))
//           {
//             if (is_real(a0))
//               return nt2::multiplies(real(a0), a1);
//             if (is_imag(a0))
//               return nt2::multiplies(pure(a0), a1);
//             if (is_real(a1))
//               return nt2::multiplies(a0, real(a1)); 
//             if (is_imag(a1))
//               return nt2::multiplies(a0, pure(a1));
//           }
//         return result_type(x, y);
//       }
//   };
  
//   // complex/real
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< arithmetic_<A0> >)
//                                        (generic_< complex_< arithmetic_<A1> > >)
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         if(is_eqz(a1))
//           return result_type(a0*real(a1));
//         else
//           return result_type(if_zero_else(is_imag(a1), a0*real(a1)),
//                              if_zero_else(is_real(a1), a0*imag(a1)));
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< complex_< arithmetic_<A0> > >)
//                                      (generic_< arithmetic_<A1> >)
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         if(is_eqz(a0))
//           return result_type(a1*real(a0));
//         else
//           return result_type(if_zero_else(is_imag(a0), real(a0)*a1),
//                              if_zero_else(is_real(a0), imag(a0)*a1));
//       }
//   };
  
//   // complex/imaginary
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< imaginary_< arithmetic_<A0> > >)
//                                      (generic_< complex_< arithmetic_<A1> > >)
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         if(is_eqz(a1))
//           return result_type(real(a1), imag(a0)*imag(a1));
//         else
//           return result_type(if_zero_else(is_real(a1), -imag(a0)*imag(a1)),
//                              if_zero_else(is_real(a0),imag(a0)*real(a1))); 
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< complex_< arithmetic_<A0> > >)
//                                      (generic_< imaginary_< arithmetic_<A1> > >)
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         if(is_eqz(a0))
//           return result_type(real(a0), imag(a0)*imag(a1));
//         else
//         return result_type(if_zero_else(is_real(a0),-imag(a0)*imag(a1)),
//                            if_zero_else(is_real(a1),real(a0)*imag(a1))); 
//       }
//   };
  
//   // imaginary/real
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< arithmetic_<A0> >)
//                                      (generic_< imaginary_< arithmetic_<A1> > >)
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return result_type(a0 * imag(a1));
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< imaginary_< arithmetic_<A0> > >)
//                                      (generic_< arithmetic_<A1> >)
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return result_type(imag(a0) * a1);
//       }
//   };
  
//   // imaginary/imaginary
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)
//                                      , (generic_< imaginary_< arithmetic_<A0> > >)
//                                      (generic_< imaginary_< arithmetic_<A1> > >)
//                                      )
//   {
//     typedef typename meta::as_real<A0>::type result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return -(imag(a0) * imag(a1));
//       }
//   };
  
// } }


#endif
