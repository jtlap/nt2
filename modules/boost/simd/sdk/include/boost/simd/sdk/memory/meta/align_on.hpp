/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_META_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_META_ALIGN_ON_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>

namespace boost { namespace simd {  namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Compute an aligned value of an integral constant on a power of 2 boundary.
  // Documentation: align_on_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t V, std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_on_c
       : boost::mpl::integral_c< std::size_t
                               , (V+N-1) & ~(N-1)
                               >
  {
    //==========================================================================
    /*
     * Alignment done on a non-power of two boundary
     */    
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (meta::is_power_of_2_c<N>::value)
    , BOOST_SIMD_INVALID_ALIGNMENT_VALUE
    , (boost::mpl::int_<N>)
    );  
  };

  //////////////////////////////////////////////////////////////////////////////
  // Compute an aligned value of an Integral Constant on a power of 2 boundary.
  // Documentation: align_on.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class V, class N = boost::mpl::size_t<BOOST_SIMD_CONFIG_ALIGNMENT> >
  struct align_on
       : boost::mpl::integral_c< typename V::value_type,
                                 typename V::value_type(align_on_c<std::size_t(V::value), std::size_t(N::value)>::value)
                               >
  {};
} } }

#endif
