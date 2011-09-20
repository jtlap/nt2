//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_HPP

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <nt2/sdk/meta/remove_pointers.hpp>
#include <nt2/core/container/meta/reference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Fill out the Buffer concepts for boost::array
//==============================================================================
namespace nt2 { namespace meta
{
  //============================================================================
  // dimensions_of specialization
  //============================================================================
  template<typename T>
  struct  dimensions_of< T* > 
        : boost::mpl::size_t<1 + dimensions_of<T>::value> 
  {};  

  //============================================================================
  // reference_ specialization
  //============================================================================ 
  template<typename T, std::size_t Level> 
  struct dereference_<T*&,Level>
  {
    typedef typename meta::remove_pointers<T*,Level>::type& type;
  };  
  
  template<typename T, std::size_t Level> 
  struct dereference_<T* const&,Level>
  {
    typedef typename meta::remove_pointers<T*,Level>::type const& type;
  };
} }

namespace nt2 { namespace memory
{
  //============================================================================
  // T* initialize - Part of Buffer Concept
  //============================================================================
  template<typename T, typename Sizes, typename Bases, typename Padding>
  inline void initialize( T*& , Sizes const&, Bases const&, Padding const& ) {}
} }

#endif
