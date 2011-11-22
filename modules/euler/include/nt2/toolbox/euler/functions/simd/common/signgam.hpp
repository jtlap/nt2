//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_SIGNGAM_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_SIGNGAM_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::signgam_, tag::cpu_,
                    (A0)(X),
                    ((simd_<arithmetic_<A0>,X>))
                    )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
     typedef typename meta::as_logical<A0>::type bA0; 
     bA0 leza0 =  is_lez(a0);
     return if_nan_else(b_or(b_or(is_nan(a0),eq(a0,Minf<A0>())),
                             b_and(leza0,is_flint(a0))),
                        selsub(leza0,One<A0>(),if_else_zero(is_odd(floor(a0)), Mtwo<A0>()))
                        );
      }
    
  };
} }

#endif
