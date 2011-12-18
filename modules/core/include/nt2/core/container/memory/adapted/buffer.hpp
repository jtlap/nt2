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
#include <nt2/core/container/meta/dimensions_of.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename T, typename A = boost::simd::memory::allocator<T> >
  struct buffer;
} }

namespace nt2 { namespace meta
{
  //==============================================================================
  // buffer dimension is 1
  //==============================================================================
  template<typename T, typename A>
  struct  dimensions_of< memory::buffer<T,A> > : boost::mpl::size_t<1> {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template< typename T, typename A> struct value_of< nt2::memory::buffer<T,A> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename A> struct model_of< nt2::memory::buffer<T,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::memory::
                buffer<X,typename A::template rebind<X>::other>  type;
      };
    };
  };
} } }

#endif
