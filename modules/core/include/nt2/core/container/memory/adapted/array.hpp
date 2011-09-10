//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP

#include <boost/mpl/size_t.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace boost
{  
  template<class T, std::size_t N> class array;
}

//==============================================================================
// Fill out the Buffer concepts for boost::array
//==============================================================================
namespace nt2 { namespace meta
{
  template<class T, std::size_t N>
  struct  dimensions_of< boost::array<T,N> > 
        : boost::mpl::size_t<1 + dimensions_of<T>::value> 
  {};
} }

#endif
