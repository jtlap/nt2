//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_STORAGE_ORDER_OF_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_STORAGE_ORDER_OF_HPP_INCLUDED

/**
 * \file
 * \brief Define the nt2::meta::storage_order_of \metafunction
**/

#include <boost/mpl/size_t.hpp>
#include <nt2/core/settings/storage_order.hpp>


namespace nt2 { namespace meta
{
  /**
   * Gives the storage order of the Buffer type.
  **/
  template< typename Buffer >
  struct  storage_order_of : nt2::C_order_ {};

} }

#endif
