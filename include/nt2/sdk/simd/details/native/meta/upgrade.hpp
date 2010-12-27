/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_META_UPGRADE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_META_UPGRADE_HPP_INCLUDED

#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/simd/meta/is_vectorizable.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // SIMD types upgrade as their scalar counterpart
  //////////////////////////////////////////////////////////////////////////////
  template<class T,std::size_t Size, class Sign, class H,class X>
  struct  upgrade<T,Size,Sign, meta::simd_<H,X> >
  {
    typedef typename meta::upgrade<typename T::value_type>::type base;
    typedef typename
    boost::mpl::if_< meta::is_vectorizable<base,X>
                   , typename T::template cast<base>::type
                   , T                   
                   >::type type;
  };
} }

#endif


