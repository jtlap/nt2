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

#include <nt2/core/settings/forward/padding.hpp>
#include <nt2/core/settings/option.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*! global_padding_ with alignment value
   *  return padding_strategy of global_ with the alignment value
   **/
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< global_padding_<N>, tag::global_padding_, Default >
  {
    typedef global_padding_<N> type;
  };

  //============================================================================
  /*! lead_padding_ with alignment value
   *  return padding_strategy of lead_ with the alignment value
   **/
  //============================================================================
  template<class Default, std::ptrdiff_t N>
  struct  option< lead_padding_<N>, tag::lead_padding_, Default >
  {
    typedef lead_padding_<N> type;
  };

  //============================================================================
  /*!
   * no_padding_ option
   **/
  //============================================================================
  template<class Default>
  struct  option< no_padding_, tag::lead_padding_, Default >
  {
    typedef lead_padding_<1> type;
  };

  template<class Default>
  struct  option< no_padding_, tag::global_padding_, Default >
  {
    typedef global_padding_<1> type;
  };
} }

#endif
