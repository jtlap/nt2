//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_BUFFER_HPP_INCLUDED
#define NT2_CORE_SETTINGS_BUFFER_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>

namespace nt2 
{ 
  template <typename T>
  struct buffer_;

  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for buffer options
     **/
    //==========================================================================
    struct buffer_ {}; 
  }

  namespace meta
  {
    template<class T, class Default> struct option<buffer_<T>, tag::buffer_, Default>
    {
      typedef T type;
    };
  } 
}

#endif
