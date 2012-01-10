//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DIMENSIONS_OF_HPP_INCLUDED
#define NT2_SDK_META_DIMENSIONS_OF_HPP_INCLUDED

/**
 * \file
 * \brief Define the nt2::meta::dimensions_of \metafunction
**/

#include <boost/mpl/size_t.hpp>

namespace nt2 { namespace meta
{
  /**
   * Computes the number of dimensions storable in a given Buffer type.
  **/
  template< typename Buffer >
  struct  dimensions_of : boost::mpl::size_t<0> {};
} }

#endif
