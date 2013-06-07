//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_IS_UPGRADABLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_IS_UPGRADABLE_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief is A0 upgradable to A1 ?
  **/
  template<typename A0, typename A1>
  struct is_upgradable_to
       : boost::is_same< A1
                       , typename dispatch::meta::upgrade<A0>::type
                       >
  {};

  /*!
    @brief is A0 upgradable ? i.e. isn't (u)int64 or double
  **/
  template<typename A0>
  struct is_upgradable
       : mpl::not_< is_upgradable_to<A0, A0> >
  {
  };

  /*!
    @brief is A0 upgradable with the same SIMD extension ?
  **/
  template<typename A0, typename X = typename meta::extension_of<A0>::type>
  struct is_upgradable_on_ext
       : mpl::and_< is_upgradable<A0>
                  , is_same<X, typename meta::extension_of< typename dispatch::meta::upgrade<A0>::type >::type>
                  >
  {
  };
} } }

#endif
