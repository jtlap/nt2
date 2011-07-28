//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SIMD_COMMON_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#include <nt2/include/functions/is_nan.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_with_equal_nans_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return b_or(eq(a0,a1), b_and(nt2::is_nan(a0), nt2::is_nan(a1)));
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is integer_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::is_equal_with_equal_nans_, tag::cpu_,
			     (A0)(X),
			     ((simd_<integer_<A0>,X>))
			     ((simd_<integer_<A0>,X>))
			     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return eq(a0,a1);
    }
  };
} }

#endif
