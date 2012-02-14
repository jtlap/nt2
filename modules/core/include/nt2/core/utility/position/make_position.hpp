//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_POSITION_MAKE_POSITION_HPP_INCLUDED
#define NT2_CORE_UTILITY_POSITION_MAKE_POSITION_HPP_INCLUDED

#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/alignment.hpp>

/**
 * \file
 * \brief Define nt2::make_position
**/

namespace nt2 { namespace meta
{
  template<typename A, typename Seq> struct make_position
  {
    typedef typename nt2::meta::settings_of<A>::type settings_type;
    typedef typename nt2::meta::option<settings_type, nt2::tag::index_>::type index_type;
    typedef typename nt2::meta::option<settings_type, nt2::tag::storage_order_>::type storage_order_type;
    typedef typename nt2::meta::option<settings_type, nt2::tag::alignment_>::type alignment_type;

    typedef position<Seq, index_type, storage_order_type, alignment_type> type;
  };
} }

#endif
