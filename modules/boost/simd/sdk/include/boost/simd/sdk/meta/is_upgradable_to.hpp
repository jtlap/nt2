//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_IS_UPGRADABLE_TO_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_IS_UPGRADABLE_TO_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace meta
{
  /*!
    @brief is A0 upgradable to A1 ?
  **/
  template<typename A0, typename A1>
  struct  is_upgradable_to
          : boost::is_same< A1
                          , typename dispatch::meta::upgrade<A0>::type
                          >
  {};
} } }

#endif
