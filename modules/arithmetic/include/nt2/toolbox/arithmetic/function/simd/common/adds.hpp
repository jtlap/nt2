//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_ADDS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_ADDS_HPP_INCLUDED
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/select.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<real_<A0>,X>))
                          ((simd_<real_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::add(a0, a1);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<uint_<A0>,X>))
                          ((simd_<uint_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0pa1 = a0+a1;
      return b_or(a0pa1, lt(a0pa1, a0)); 
     //      return sel(lt(a0pa1, nt2::max(a0, a1)), Valmax<A0>(), a0pa1); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::adds_, tag::cpu_,
                          (A0)(X),
                          ((simd_<int_<A0>,X>))
                          ((simd_<int_<A0>,X>))
                         )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 gtza0 = is_gtz(a0);
      A0 gtza1 = is_gtz(a1);
      A0 a0pa1 = a0+a1;
      A0 test1 = b_and(gtza0, b_and(gtza1, (lt(a0pa1, nt2::max(a0, a1))))); 
      A0 test2 = b_andnot(b_andnot(b_or(is_gtz(a0pa1),gt(a0pa1, nt2::min(a0, a1))),gtza0),gtza1);
      return sel(test1,Valmax<A0>(),sel(test2,Valmin<A0>(),a0pa1)); 
    }
  };
} }
#endif
