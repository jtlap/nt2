//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_IS_NOT_EQUAL_TO_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_IS_NOT_EQUAL_TO_HPP_INCLUDED

#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/complement.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_not_equal_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::altivec_>))
                              ((simd_<arithmetic_<A0>,tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = nt2::complement(nt2::eq(a0,a1));
      return that;
    }
  };
} }

#endif
