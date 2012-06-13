//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_SIMD_COMMON_MULTIPLIES_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEX_SIMD_COMMON_MULTIPLIES_HPP_INCLUDED
#include <nt2/toolbox/operator/functions/multiplies.hpp>
#include <nt2/include/functions/multiplies.hpp>
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
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

// namespace nt2 { namespace ext
// {
//   //These  versions are erroneous
//   // complex/complex
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(X)
//                                      , ((simd_< complex_< arithmetic_<A0> >, X>))
//                                      ((simd_< complex_< arithmetic_<A0> >, X >))
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//       {
//         typedef typename meta::as_real<A0>::type rA0;
//         typedef typename meta::as_logical<rA0>::type lA0; 
//         rA0 a0a1r = nt2::real(a0) * nt2::real(a1);
//         rA0 a0a1i = nt2::imag(a0) * nt2::imag(a1);
//         rA0 x = a0a1r - a0a1i; 
//         rA0 y = (nt2::real(a0) + nt2::imag(a0)) * (nt2::real(a1) + nt2::imag(a1)) - a0a1r - a0a1i; 
//         result_type r = result_type(x, y); 
//         if (nt2::any(logical_or(is_invalid(x), is_invalid(y))))
//           {
//             lA0 test = is_real(a0); 
//             r = if_else(test, nt2::multiplies(nt2::real(a0), a1), r);
//             test = logical_andnot(is_imag(a0), test); 
//             r = if_else(test, nt2::multiplies(pure(a0), a1), r);
//             test = logical_andnot(is_real(a1), test); 
//             r = if_else(test, nt2::multiplies(a0, nt2::real(a1)), r);
//             test = logical_andnot(is_imag(a1), test); 
//             r = if_else(test, nt2::multiplies(a0, pure(a1)), r);
//           }
//         return r;
//       }
//   };
  
//   // complex/real
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< arithmetic_<A0>, X >))
//                                        ((simd_< complex_< arithmetic_<A1> >, X >))
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         result_type r = result_type(if_zero_else(is_imag(a1), a0*nt2::real(a1)),
//                                     if_zero_else(is_real(a1), a0*nt2::imag(a1)));
//         typedef typename meta::as_logical<A0>::type ltype;
//         ltype z = is_eqz(a1); 
//         if (nt2::any(z))
//           r = if_else(z, result_type(a0*nt2::real(a1)), r);
//         return r;    
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< complex_< arithmetic_<A0> >, X >))
//                                      ((simd_< arithmetic_<A1>, X >))
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         result_type r = result_type(if_zero_else(is_imag(a0), nt2::real(a0)*a1),
//                                     if_zero_else(is_real(a0), nt2::imag(a0)*a1));
//         typedef typename meta::as_logical<A1>::type ltype;
//         ltype z = is_eqz(a0); 
//         if (nt2::any(z))
//           r = if_else(z, result_type(a1*nt2::real(a0)), r);
//         return r; 
//       }
//   };
  
//   // complex/imaginary
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< imaginary_< arithmetic_<A0> >, X >))
//                                      ((simd_< complex_< arithmetic_<A1> >, X >))
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         result_type r = result_type(if_zero_else(is_real(a1), -nt2::imag(a0)*nt2::imag(a1)),
//                                     if_zero_else(is_imag(a1),nt2::imag(a0)*nt2::real(a1))); 
//         typedef typename meta::as_real<A1>::type rtype;
//         typedef typename meta::as_logical<rtype>::type ltype;
//         ltype z = is_eqz(a1); 
//         if(nt2::any(z))
//           r = if_else(z, result_type(nt2::real(a1), nt2::imag(a0)*nt2::imag(a1)), r);
//         return r; 
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< complex_< arithmetic_<A0> >, X >))
//                                      ((simd_< imaginary_< arithmetic_<A1> >, X >))
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         result_type r = result_type(if_zero_else(is_imag(a0),-nt2::imag(a0)*nt2::imag(a1)),
//                                     if_zero_else(is_imag(a1),nt2::real(a0)*nt2::imag(a1))); 
//         typedef typename meta::as_real<A1>::type rtype;
//         typedef typename meta::as_logical<rtype>::type ltype;
//         ltype z = is_eqz(a0); 
//         if(nt2::any(z))
//           {
//             result_type tmp = result_type(nt2::real(a0), multiplies(nt2::imag(a0), nt2::imag(a1))); 
//             r = if_else(z, tmp, r);
//           }
//         return r; 
//       }
//   };
  
//   // imaginary/real
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< arithmetic_<A0>, X >))
//                                      ((simd_< imaginary_< arithmetic_<A1> >, X >))
//                                      )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return bitwise_cast<result_type>(a0*nt2::imag(a1));
//       }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< imaginary_< arithmetic_<A0> >, X >))
//                                      ((simd_< arithmetic_<A1>, X >))
//                                      )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return bitwise_cast<result_type>(nt2::imag(a0)*a1);
//       }
//   };
  
//   // imaginary/imaginary
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_, (A0)(A1)(X)
//                                      , ((simd_< imaginary_< arithmetic_<A0> >, X >))
//                                      ((simd_< imaginary_< arithmetic_<A1> >, X >))
//                                      )
//   {
//     typedef typename meta::as_real<A0>::type result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         return -(nt2::imag(a0) * nt2::imag(a1));
//       }
//   };
  
// } }

#endif
