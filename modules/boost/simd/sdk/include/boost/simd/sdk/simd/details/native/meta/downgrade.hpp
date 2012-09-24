//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_DOWNGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_DOWNGRADE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace dispatch { namespace ext
{
  ////////////////////////////////////////////////////////////////////////////
  // Extension Point for downgrade on native<T,Ext>.
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class Ext, class Sign>
  struct downgrade< boost::simd::native<T, Ext>, Sign, typename boost::enable_if_c< !(sizeof(typename meta::primitive_of<T>::type) <= 1) >::type >
  {
    typedef typename
    simd::meta::vector_of< typename dispatch::meta::downgrade<T,Sign>::type
                         , simd::meta::cardinal_of< simd::native<T,Ext> >::value*2
                         >::type type;
  };
} } }

#endif /* BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_DOWNGRADE_HPP_INCLUDED */
