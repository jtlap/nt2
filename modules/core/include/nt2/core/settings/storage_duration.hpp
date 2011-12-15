//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_STORAGE_DURATION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_STORAGE_DURATION_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>

namespace nt2 
{ 
  template<typename T>
  struct storage_duration_;
  //============================================================================
   /*! Default storage duration settings. Current container will use dynamic 
    *  allocation for handling its data.
   **/
  //============================================================================
  struct dynamic_;

  //============================================================================
   /*! Current container will use a stack allocated memory block for handling 
    *  its data
   **/
  //============================================================================
  struct automatic_;


  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for storage_duration options
     **/
    //==========================================================================
    struct storage_duration_ {}; 
  }

  namespace meta
  {

    template<class T, class Default> struct option<storage_duration_<T>
                                          , tag::storage_duration_
                                          , Default>
    {
      typedef T type;
    };
  } 
}

#endif
