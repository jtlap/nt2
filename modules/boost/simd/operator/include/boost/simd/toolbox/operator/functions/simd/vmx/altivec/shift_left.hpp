//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_LEFT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// operator binary shift left
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_left_, boost::simd::tag::altivec_, (A0)(A1)
                            , ((simd_<integer_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<integer_<A1>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)  
    { 
      typedef typename boost::dispatch::meta::as_unsigned<A1>::type type;
      type shift = simd::native_cast<type>(a1);
      A0 that  = { vec_sl(a0(), shift()) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_left_, boost::simd::tag::altivec_, (A0)(A1)
                            , ((simd_<single_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<ints32_<A1>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2) 
   { 
     typedef typename boost::dispatch::meta::as_unsigned<A1>::type type;
     type shift = simd::native_cast<type>(a1);
     type value = simd::native_cast<type>(a0);
     A0 that  = simd::native_cast<A0>( vec_sl(value(), shift()) ); 
     return that;  
   }
  };
} } }

#endif
#endif
