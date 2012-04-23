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
    // Markee for 'lower' option
    struct lower_ {};

    // Markee for in place option
    struct in_place_ {};

    // Markee for [] option
    struct empty_t {};
  }

  meta::as_<details::lower_>    const lower_    = {};
  meta::as_<details::in_place_> const in_place_ = {};
  meta::as_<details::empty_t>   const empty_    = {};
}

#endif
