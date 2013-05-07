//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_SHARING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_SHARING_HPP_INCLUDED

namespace nt2
{
  //============================================================================
  /*!
   * shared_ indicates the current container will reuse existing memory as its
   * data buffer.
   **/
  //============================================================================
  struct shared_;

  //============================================================================
  /*!
   * owned_ indicates the current container will allocates its own memory.
   **/
  //============================================================================
  struct owned_;

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for sharing options
     **/
    //==========================================================================
    struct sharing_ {};
  }


}


#endif
