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

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/core/settings/forward/settings.hpp>
#include <nt2/core/settings/forward/index.hpp>
#include <nt2/core/settings/forward/storage_order.hpp>
#include <nt2/core/settings/forward/alignment.hpp>

/**
 * \file
 * \brief Define nt2::make_position
**/

namespace nt2 { namespace meta
{
  template<typename T, typename Seq> struct make_position
  {
    typedef typename meta::strip<T>::type expr_type;
    typedef typename expr_type::index_type index_type;
    typedef typename expr_type::storage_order_type storage_order_type;
    typedef typename expr_type::alignment_type alignment_type;

    typedef position<Seq, index_type, storage_order_type, alignment_type> type;
  };
} }

#endif
