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
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename T, typename A = memory::allocator<T> >
  struct buffer;

  //============================================================================
  // Buffer have size
  //============================================================================
  template<std::size_t N, typename T, typename A>
  typename buffer<T,A>::size_type size( buffer<T,A> const& b )
  {
    return (N == 1u) ? b.size() : 1u;
  }
  
  // template<std::size_t N, typename T, typename A>
  // typename buffer<T,A>::difference_type lower( buffer<T,A> const& b )
  // {
  //   return (N == 1u) ? b.lower() : 1u;
  // }
  
  // template<std::size_t N, typename T, typename A>
  // typename buffer<T,A>::difference_type upper( buffer<T,A> const& b )
  // {
  //   return (N == 1u) ? b.upper() : 1u;
  // }
  
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
} }

namespace nt2 { namespace meta
{
  //==============================================================================
  // buffer dimension is 1
  //==============================================================================
  template<typename T, typename A>
  struct  dimensions_of< memory::buffer<T,A> > : boost::mpl::size_t<1>
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
