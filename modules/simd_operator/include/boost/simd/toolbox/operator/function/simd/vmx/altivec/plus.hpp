//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_PLUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_PLUS_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace dispatch
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::plus_, tag::cpu_, (A0)
                            , ((simd_<arithmetic_<A0>,tag::altivec_>))
                              ((simd_<arithmetic_<A0>,tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { vec_add(a0(),a1()) };
      return that;
    }
  };
} }

#endif
