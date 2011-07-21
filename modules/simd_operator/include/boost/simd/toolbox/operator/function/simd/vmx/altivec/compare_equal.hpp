//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_COMPARE_EQUAL_HPP_INCLUDED

namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::compare_equal_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::altivec_>))
                              ((simd_<arithmetic_<A0>,tag::altivec_>))
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2) { return vec_all_eq(a0(),a1()); }
  };
} } }

#endif
