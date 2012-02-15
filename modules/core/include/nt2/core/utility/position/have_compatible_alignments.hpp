//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_HAVE_COMPATIBLE_ALIGNMENTS_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_HAVE_COMPATIBLE_ALIGNMENTS_HPP_INCLUDED

#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/core/settings/forward/settings.hpp>
#include <nt2/core/settings/forward/alignment.hpp>

namespace nt2
{
  template<typename A1, typename A2>
  struct have_compatible_alignments : boost::mpl::false_
  {
  };

  template<>
  struct have_compatible_alignments<nt2::aligned_, nt2::aligned_> : boost::mpl::true_
  {
  };
}

#endif
