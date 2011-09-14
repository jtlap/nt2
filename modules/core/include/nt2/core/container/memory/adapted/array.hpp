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

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/core/container/meta/reference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace boost { template<class T, std::size_t N> class array; }

//==============================================================================
// Fill out the Buffer concepts for boost::array
//==============================================================================
namespace nt2 { namespace meta
{
  //============================================================================
  // dimensions_of specialization
  //============================================================================
  template<typename T, std::size_t N>
  struct  dimensions_of< boost::array<T,N> > 
        : boost::mpl::size_t<1 + dimensions_of<T>::value> 
  {};  

  //============================================================================
  // reference_ specialization
  //============================================================================
  template<typename T, std::size_t N, std::size_t Level> 
  struct reference_<boost::array<T,N>,Level>
  {
    typedef typename boost::array<T,N>::value_type  base;
    typedef typename reference_<base,Level-1>::type type;
  };

  template<typename T, std::size_t N> 
  struct reference_<boost::array<T,N>,1UL>
  {
    typedef typename boost::array<T,N>::reference type;
  };

  //============================================================================
  // const_reference_ specialization
  //============================================================================
  template<typename T, std::size_t N, std::size_t Level> 
  struct const_reference_<boost::array<T,N>,Level>
  {
    typedef typename boost::array<T,N>::value_type        base;
    typedef typename const_reference_<base,Level-1>::type type;
  };

  template<typename T, std::size_t N> 
  struct const_reference_<boost::array<T,N>,1UL>
  {
    typedef typename boost::array<T,N>::const_reference type;
  };
} }

namespace nt2 { namespace memory
{
  //============================================================================
  // boost::array initialize - Part of Buffer Concept
  //============================================================================
  template<typename T, std::size_t N, typename Sizes, typename Bases>
  inline void initialize( boost::array<T,N>&, Sizes const&, Bases const&) {}
} }

#endif
