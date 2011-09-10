//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP

#include <boost/mpl/size_t.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{  
  template<unsigned D, typename T, typename P, typename A>
  struct iliffe_buffer;
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<unsigned D, typename T, typename P, typename A>
  struct dimensions_of< memory::iliffe_buffer<D,T,P,A> > : boost::mpl::size_t<D> 
  {};
} }

#endif
