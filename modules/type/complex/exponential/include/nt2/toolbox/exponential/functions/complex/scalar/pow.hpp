//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_SCALAR_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_SCALAR_POW_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <complex>
#include <cmath>

// namespace nt2 { namespace ext
// {
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                               , (A0)
//                             , (scalar_< complex_<floating_<A0> > >)
//                               (scalar_< complex_<floating_<A0> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return static_cast<result_type>(std::pow(a0, a1));
//     }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                               , (A0)(A1)
//                               , (scalar_< complex_<floating_<A0> > >)
//                                 (scalar_< floating_<A1> >)
//                             )
//   {
//     typedef A0  result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       result_type ca1 = result_type(a1, Zero<A1>()); 
//       return static_cast<result_type>(std::pow(a0, ca1));
//     }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                               , (A0)(A1)
//                               , (scalar_< floating_<A0> >)
//                                 (scalar_< complex_<floating_<A1> > >)
//                             )
//   {
//     typedef A1 result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       result_type ca0 = result_type(a0, Zero<A0>()); 
//       return static_cast<result_type>(std::pow(ca0, a1));
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                             , (A0)(A1)
//                             , (scalar_< complex_<floating_<A0> > >)
//                               (scalar_< imaginary_<floating_<A1> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       result_type ca1 = result_type(Zero<A1>(), a1); 
//       return static_cast<result_type>(std::pow(a0, ca1));
//      }
//    };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                             , (A0)(A1)
//                             , (scalar_< imaginary_<floating_<A0> > >)
//                               (scalar_< complex_<floating_<A1> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       result_type ca0 = result_type(Zero<A1>(), a0()); 
//       return static_cast<result_type>(std::pow(ca0, a1));
//      }
//    };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                             , (A0)(A1)
//                             , (scalar_< imaginary_<floating_<A0> > >)
//                               (scalar_< floating_<A1> >)
//                             )
//   {
//     typedef meta::as_complex<A1> result_type;
//     NT2_FUNCTOR_CALL(2)
//       {
//         result_type ca1 = result_type(a1, Zero<A1>()); 
//         result_type ca0 = result_type(Zero<A1>(), a0()); 
//         return static_cast<result_type>(std::pow(ca0, ca1));
//       }
//    };
  
//    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
//                             , (A0)(A1)
//                             ,  (scalar_< floating_<A0> >)
//                                (scalar_< imaginary_<floating_<A1> > >)
//                             )
//   {
//     typedef meta::as_complex<A0> result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       result_type ca0 = result_type(a0, Zero<A1>()); 
//       result_type ca1 = result_type(Zero<A1>(), a1()); 
//       return static_cast<result_type>(std::pow(ca0, ca1));
//      }
//    }; 
// } }


#endif
