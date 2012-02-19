//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/core/settings/forward/padding.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*! padding_ with alignment strategy functor
   *  return the padding functor type
   **/
  //============================================================================
  template<class Default, class S>
  struct option< padding_<S>, tag::padding_, Default >
  {
    typedef S type;
  };

  //============================================================================
  /*!
   * no_padding_ option
   * return the identity padding functor
   **/
  //============================================================================
  template<class Default>
  struct option< no_padding_, tag::padding_, Default >
  {
    typedef memory::no_padding type;
  };
} }

#endif
