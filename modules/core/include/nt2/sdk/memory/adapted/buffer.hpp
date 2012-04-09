//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED
#define NT2_SDK_META_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template< typename T
          , typename Allocator = boost::simd::memory::allocator<T>
          > class buffer;
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename Allocator>
  struct value_of< nt2::memory::buffer<T,Allocator> > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename Allocator>
  struct model_of< nt2::memory::buffer<T,Allocator> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base_t;
        typedef typename Allocator::template rebind<base_t>::other  alloc_t;
        typedef nt2::memory::buffer<base_t,alloc_t>                 type;
      };
    };
  };
} } }

#endif
