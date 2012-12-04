//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIONS_HPP_INCLUDED
#define NT2_OPTIONS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>

namespace nt2
{
  namespace details
  {
    // Markee for in place option
    struct in_place_  {};
    struct meshgrid_  {};
    struct whole_     {};
    struct along_     {};
    struct case0_     {};
    struct case1_     {};
    struct case2_     {};
    struct case3_     {};

  }

  // Lower/upper
  static const char lower_    = 'L';
  static const char upper_    = 'U';

  meta::as_<details::in_place_> const in_place_ = {};
  meta::as_<details::whole_>    const whole_    = {};
  meta::as_<details::meshgrid_> const meshgrid_ = {};
  meta::as_<details::along_>    const along_    = {};
  meta::as_<details::case0_>    const case0_    = {};
  meta::as_<details::case1_>    const case1_    = {};
  meta::as_<details::case2_>    const case2_    = {};
  meta::as_<details::case3_>    const case3_    = {};

}

#endif
