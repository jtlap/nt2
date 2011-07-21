//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_IMPL_DIVIDES_INT8_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_IMPL_DIVIDES_INT8_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // a/b use a bit preserving algorithm from vecLib by Apple
  //////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::divides_, tag::cpu_, (A0)(A1)
                            , ((simd_<ints8_<A0>,tag::altivec_>))
                              ((simd_<ints8_<A1>,tag::altivec_>)) )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
    }
  };
} } }

#endif
