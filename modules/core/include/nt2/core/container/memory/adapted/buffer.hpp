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
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/sdk/meta/add_pointers.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/memory/adapted/pointer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename T, typename A = memory::allocator<T> >
  struct buffer;

  //============================================================================
  // Buffer are dereferencable
  //============================================================================
  template<typename T, typename A, typename Position>
  typename buffer<T,A>::reference
  dereference( buffer<T,A>& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }
  
  template<typename T, typename A, typename Position>
  typename buffer<T,A>::const_reference
  dereference( buffer<T,A> const& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }

  //============================================================================
  // Buffer are rebasable
  //============================================================================
  template<typename T, typename A, class Bases>
  typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
  rebase(buffer<T,A>& b, Bases const& bs)
  {
    BOOST_MPL_ASSERT_MSG
    ( (boost::mpl::size<Bases>::value == 1)
    , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
    , (Bases)
    );

    b.rebase( boost::fusion::at_c<0>(bs));
  }

  //============================================================================
  // Buffer are resizable
  //============================================================================
  template<typename T, typename A, class Sizes>
  typename boost::enable_if< boost::fusion::traits::is_sequence<Sizes> >::type
  resize(buffer<T,A>& b, Sizes const& sz)
  {
    BOOST_MPL_ASSERT_MSG
    ( (boost::mpl::size<Sizes>::value == 1)
    , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
    , (Sizes)
    );
    
    b.resize( boost::fusion::at_c<0>(sz) );
  }

  //============================================================================
  // Buffer are restructurable
  //============================================================================
  template<typename T, typename A, class Bases,class Sizes>
  typename boost::enable_if_c < boost::fusion::traits::is_sequence<Sizes>::value
                                &&
                                boost::fusion::traits::is_sequence<Bases>::value
                              >::type
  restructure(buffer<T,A>& b, Sizes const& sz, Bases const& bs)
  {
    BOOST_MPL_ASSERT_MSG
    ( (boost::mpl::size<Sizes>::value == 1)
    , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
    , (Sizes)
    );

    BOOST_MPL_ASSERT_MSG
    ( (boost::mpl::size<Bases>::value == 1)
    , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
    , (Bases)
    );

    b.restructure(boost::fusion::at_c<0>(sz),boost::fusion::at_c<0>(bs));
  }
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<typename T, typename A>
  struct  dimensions_of< memory::buffer<T,A> >
        : boost::mpl::size_t<1 + dimensions_of<T>::value>
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template< typename T, typename A>
  struct value_of< nt2::memory::buffer<T,A> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename A>
  struct model_of< nt2::memory::buffer<T,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename A::template rebind<X>::other alloc;
        typedef nt2::memory::buffer<X,alloc>    type;
      };
    };
  };
} } }

#endif
