/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_UPGRADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_UPGRADE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>

////////////////////////////////////////////////////////////////////////////
// Extension Point for upgrade on native<T,Ext>.
// Prevent from upgrading native<float,altivec_> to native<double,altivec_>
// which is not supported.
////////////////////////////////////////////////////////////////////////////

namespace boost { namespace dispatch { namespace meta
{

  template<class T, class Ext, class Sign>
  struct upgrade< typename boost::simd::native<T, Ext>, Sign >
  {
    typedef typename dispatch::meta::upgrade<T,Sign>::type uT;
    typedef typename
    boost::mpl::if_< typename
                     simd::meta::is_vectorizable<uT,Ext>::type
                   , typename simd::native<uT,Ext>
                   , typename simd::native< T,Ext>
                   >::type type;
  };

} } }

#endif /* BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_UPGRADE_HPP_INCLUDED */
