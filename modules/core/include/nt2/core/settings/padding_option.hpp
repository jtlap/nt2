//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_PADDING_OPTION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_PADDING_OPTION_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/padding_option.hpp>
namespace nt2 
{ 
  //============================================================================
  /*! Specify that current container doesn't pad its memory. 
   *  Equivalent to padding_(none_).
   **/
  //============================================================================
  struct no_padding_;

  //============================================================================
  /*! Specify a global padding strategy will be used. 
   *  Equivalent to padding_(global_). 
   *  The padding value will have to be specified at runtime using 
   *  the appropriate container constructor.
   **/
  //============================================================================
  struct global_padding_;

  //============================================================================
  /*! Specify a lead dimension padding strategy will be used. 
   *  Equivalent to padding_(lead_). 
   *  The padding value will have to be specified at runtime using 
   *  the appropriate container constructor.
   **/
  //============================================================================
  struct lead_padding_;

  //============================================================================
  /*! Specify a global padding strategy will be used. 
   *  The padding value can either be specified at runtime 
   *  (see nt2::global_padding_) or using nt2::with_
   **/
  //============================================================================
  struct global_;

  //============================================================================
  /*! Specify a lead dimension padding strategy will be used. 
   *  The padding value can either be specified at runtime 
   *  (see nt2::lead_padding_) or using nt2::with_
   **/
  //============================================================================
  struct lead_;


  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for padding options
     **/
    //==========================================================================
    struct padding_ {}; 
  }

  namespace meta
  {
    template<class Default> 
    struct option<none_, tag::padding_, Default>
    {
      typedef no_padding_ type;
    };

    template<class Default> 
    struct option<global_, tag::padding_, Default>
    {
      typedef global_padding_ type;
    };

    template<class Default> 
    struct option<lead_, tag::padding_, Default>
    {
      typedef lead_padding_ type;
    };

    // template<std::size_t N, class Default> 
    // struct option<global_, N, tag::padding_, Default>
    // {
    //   typedef global_padding_ type;
    // };

    // template<std::size_t N, class Default> 
    // struct option<lead_, N, tag::padding_, Default>
    // {
    //   typedef lead_padding_ type;
    // };

  } 
}

#endif
