/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_MEMORY_BUFFER_ADAPTOR_HPP_INCLUDED 
#define NT2_CORE_CONTAINER_MEMORY_BUFFER_ADAPTOR_HPP_INCLUDED 

#include <boost/assert.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/details/buffer_base.hpp>
#include <nt2/sdk/meta/add_pointers.hpp>

namespace nt2 {  namespace memory
{

  template<  class Type,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  class buffer_adaptor;

  //////////////////////////////////////////////////////////////////////////////
  // ADL swap
  //////////////////////////////////////////////////////////////////////////////

  // template<  class Type, class Allocator,
  //            class Sizes ,
  //            class Bases ,
  //            class Padding ,
  //            class Shared
  //         >
  // void swap( buffer_adaptor<std::vector<Type, Allocator>,Sizes, Bases, Padding, Shared >& a
  //          , buffer_adaptor<std::vector<Type, Allocator>,Sizes, Bases, Padding, Shared >& b 
  //          )
  // {
  //   a.swap(b);
  // }
} } 

#endif
