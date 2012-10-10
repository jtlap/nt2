//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_INTERLEAVING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_INTERLEAVING_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace nt2
{
  //============================================================================
  /*! Current container memory is interleaved
   **/
  //============================================================================
  struct interleaved_ : boost::mpl::false_ {};

  //============================================================================
  /*! Current container memory is deinterleaved, ie use multiple container for
      composite type.
   **/
  //============================================================================
  struct deinterleaved_ : boost::mpl::true_  {};

  namespace tag
  {
    //==========================================================================
    /*!
     * Option tag for interleaving options
     **/
    //==========================================================================
    struct interleaving_ {};
  }


}

#endif
