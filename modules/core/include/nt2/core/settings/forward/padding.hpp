//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_PADDING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_PADDING_HPP_INCLUDED

#include <boost/mpl/int.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>

namespace nt2
{
  //============================================================================
  /*!
   * Specify a global padding strategy will be used.
   **/
  //============================================================================
  template<std::ptrdiff_t Value = 1>
  struct global_padding_ : boost::mpl::int_<Value> {};

  //============================================================================
  /*!
   * Specify a lead dimension padding strategy will be used.
   **/
  //============================================================================
  template<std::ptrdiff_t Value = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct lead_padding_  : boost::mpl::int_<Value> {};

  //============================================================================
  /*!
   * Specify that current container doesn't pad its memory.
   **/
  //============================================================================
  struct no_padding_ {};

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for padding options
     **/
    //==========================================================================
    struct global_padding_  {};
    struct lead_padding_    {};
  }
}


#endif
