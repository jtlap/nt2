//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_PROPERTY_OF_HPP_INCLUDED
#define NT2_SDK_META_PROPERTY_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::meta::property_of \metafunction
 */

//////////////////////////////////////////////////////////////////////////////
// Types property is defined on fundamental types as a lattice of classes
// mimicking the type structuration in C++
//////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/details/property_of.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // property_of computes the entry point of a given type inside the type
  // property lattice.
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Origin = T, class Enable = void>
  struct  property_of
        : details::property_of< typename meta::strip<T>::type
                              , typename meta::strip<Origin>::type
                              >
  {};
} }

#endif
