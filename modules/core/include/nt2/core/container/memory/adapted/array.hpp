//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP_INCLUDED

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/storage_order_of.hpp>

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

  template<class T, std::size_t N>
  struct storage_order_of< boost::array<T,N> > 
  {
    typedef C_order_  type;
  };


} }

namespace nt2 { namespace memory
{
  //============================================================================
  // boost::array initialize - Part of Buffer Concept
  //============================================================================
  template< typename T, std::size_t N
          , typename Sizes, typename Bases, typename Padding
          >
  inline void initialize( boost::array<T,N>&
                        , Sizes const&, Bases const&, Padding const&
                        )
  {}
} }

#endif
