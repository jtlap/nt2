//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_ALIGNMENT_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ALIGNMENT_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>

namespace nt2 
{ 

  //============================================================================
  /*! Current container memory is allocated using an aligning allocator.
   **/
  //============================================================================
  struct aligned_ {};

  //============================================================================
  /*! Current container memory is allocated using an allocator with no 
   *  alignment garantee.
   **/
  //============================================================================
  struct unaligned_ {};

  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for alignment options
     **/
    //==========================================================================
    struct alignment_ {}; 
  }

  namespace meta
  {
    template<class Default> 
    struct option<aligned_, tag::alignment_, Default>
    {
      typedef aligned_ type;
    };

    template<class Default> 
    struct option<unaligned_, tag::alignment_, Default>
    {
      typedef unaligned_ type;
    };

  } 
}

#endif
