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

#include <boost/mpl/logical.hpp>
#include <nt2/core/settings/forward/alignment.hpp>

/**
 * \file
 * \brief Define nt2::have_compatible_alignments
**/

namespace nt2
{
  template<typename T, typename A>
  struct have_compatible_alignments :
    boost::mpl::and_<
      typename nt2::meta::option<
        typename boost::proto::result_of::value<T>::type::settings_type,
        nt2::tag::alignment_>
      ::type,
      A
    >
  {
  };
}

#endif
