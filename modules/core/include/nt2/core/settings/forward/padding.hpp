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

namespace nt2
{
  //============================================================================
  /*!
   * Specify a padding strategy will be used.
   **/
  //============================================================================
  template<class Strategy> struct padding_
  {
    typedef Strategy type;
  };

  //============================================================================
  /*!
   * Specify a padding strategy which doesn't pad anything
   **/
  //============================================================================
  struct no_padding_  {};

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for padding options
     **/
    //==========================================================================
    struct padding_ {};
  }
}


#endif
