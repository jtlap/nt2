//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTIONS_GENERIC_COPYSIGN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTIONS_GENERIC_COPYSIGN_HPP_INCLUDED
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>

namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
//                            (A0),
//                            ((generic_<complex_ < floating_<A0> > >))
//                            ((generic_<complex_ < floating_<A0> > >))      
//                           )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return  result_type(copysign(real(a0), real(a1)),
//                           copysign(imag(a0), imag(a1)));
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
//                            (A0),
//                            ((generic_<imaginary_ < floating_<A0> > >))
//                            ((generic_<imaginary_ < floating_<A0> > >))      
//                           )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return  result_type(copysign(imag(a0), imag(a1)));
//     }
//   };
    
//   NT_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
//                            (A0),
//                            ((generic_<dry_ < floating_<A0> > >))
//                            ((generic_<dry_ < floating_<A0> > >))      
//                           )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL_REPEAT(2)
//     {
//       return  result_type(copysign(real(a0), real(a1)));
//     }
//   };

} } 
#endif
