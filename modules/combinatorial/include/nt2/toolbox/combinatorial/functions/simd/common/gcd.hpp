//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_GCD_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_GCD_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_else_nan.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/sdk/simd/logical.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0; 
      A0 a = a0, b = a1;
      bA0 t= is_nez(b);
      while (nt2::any(t))
      {
        A0 r = if_else_zero(t, rem(a, b));
        a = b; 
        b = r;
        t =  is_nez(b); 
      }
      return a;
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcd_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type    bA0; 
      bA0 ints = logical_and(is_flint(a1), is_flint(a0)); 
      A0 a =  if_else_zero(ints, a0); 
      A0 b =  if_else_zero(ints, a1); 
      bA0 t= is_nez(b);
      while (nt2::any(t))
      {
        A0 r = if_zero_else(t, rem(a, b));
        a = b;
        b = r;
        t = is_nez(b);
      }
      return if_else_nan(ints, a);
    }
  };
} }

#endif
