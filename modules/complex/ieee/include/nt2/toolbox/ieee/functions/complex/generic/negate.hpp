//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_COMPLEX_GENERIC_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_COMPLEX_GENERIC_NEGATE_HPP_INCLUDED
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::negate_, tag::cpu_,
                             (A0)(A1),
                             (generic_<complex_ < arithmetic_<A0> > >)
                             (generic_< arithmetic_<A1> >)
                             )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        A0 tmp = if_else_zero(is_nez(a1), a0);
        tmp = if_else(is_ltz(a1), -a0, tmp);
        return if_else(is_nan(a1), Nan<result_type>(), tmp); 
      }
  };
  
} } 
#endif
