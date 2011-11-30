//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

////////////////////////////////////////////////////////////////////////////////
// store for SIMD types
// TODO : Documentation for simd store
// TODO : Make them work properly with ContiguousRandomAccessIterator
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/memory/details/category.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/error/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::store_, boost::simd::tag::altivec_, (A0)(A1)(A2)
                            , ((simd_< arithmetic_<A0>, boost::simd::tag::altivec_ >))
                              (iterator_< scalar_< arithmetic_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a1,BOOST_SIMD_CONFIG_ALIGNMENT)
     && boost::simd::memory::is_aligned(a1+a2,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to store with a pointer that"
        " is not aligned on the simd vector size.");
      vec_st(a0.data_, a2*sizeof(*a1), a1);
      return a0;
    }
  };
} } }

#endif
#endif
