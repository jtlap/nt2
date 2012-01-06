//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <nt2/sdk/meta/as_sequence.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template< typename Type
          , std::ptrdiff_t B
          , typename A = boost::simd::memory::allocator<Type> >
  struct buffer;
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template< typename T, std::ptrdiff_t B, typename A>
  struct value_of< nt2::memory::buffer<T,B,A> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, std::ptrdiff_t B, typename A>
  struct model_of< nt2::memory::buffer<T,B,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::memory::
                buffer<X,B,typename A::template rebind<X>::other>  type;
      };
    };
  };
} } }

#endif
