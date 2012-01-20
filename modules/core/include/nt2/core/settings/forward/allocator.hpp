//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_ALLOCATOR_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_ALLOCATOR_HPP_INCLUDED


namespace nt2 
{ 
  //============================================================================
  /*! allocator_<A> defines a custom allocator to be used by the container.
   * 
   * \tparam Allocator Allocator type to be used by current container
   **/
  //============================================================================
  template<class Allocator> 
  struct allocator_ 
  {
    typedef Allocator type;
  }; 

  namespace tag 
  { 
    //==========================================================================
    /*!
     * Option tag for allocator options
     **/
    //==========================================================================
    struct allocator_ {}; 
  }

}

#endif
