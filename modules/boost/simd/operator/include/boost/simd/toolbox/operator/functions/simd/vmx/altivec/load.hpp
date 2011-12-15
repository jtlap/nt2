//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, boost::simd::tag::altivec_
                            , (A0)(A1)(A2)
                            , (iterator_< scalar_< arithmetic_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_<simd_<arithmetic_<A2>,boost::simd::tag::altivec_> >))
                            )
  {

    typedef typename A2::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::memory::is_aligned(a0+a1,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        " is not aligned on the simd vector size.");
      result_type that = { vec_ld(a1*sizeof(*a0),a0) };
      return that;
    }
  };
} } }

#include <boost/simd/toolbox/operator/functions/simd/vmx/altivec/impl/load_offset.hpp>

#endif
#endif
