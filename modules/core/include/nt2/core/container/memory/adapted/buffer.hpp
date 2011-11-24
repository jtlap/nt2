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
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/memory/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/memory/adapted/pointer.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template<typename T, typename A>
  struct buffer;
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<typename T, typename A>
  struct dimensions_of< memory::buffer<T,A> > : boost::mpl::size_t<1 + dimensions_of<T>::value>
  {};

  //============================================================================
  // dereference_ specialization
  //============================================================================
  template< typename T,  typename A, std::size_t Level>
  struct dereference_<memory::buffer<T,A>&,Level>
  {
    typedef typename add_pointers<T,1-Level>::type&  type;
  };


  //============================================================================
  // dereference_ specialization
  //============================================================================
  template<typename T, typename A, std::size_t Level>
  struct dereference_<memory::buffer<T,A>,Level>
  {
    typedef typename add_pointers<T,1-Level>::type  type;
  };

  template<typename T, typename A, std::size_t Level>
  struct dereference_<memory::buffer<T,A> const&,Level>
  {
    typedef typename add_pointers<T,1-Level>::type const&  type;
  };

  template<typename T, typename A>
  struct dereference_<memory::buffer<T,A>&,1>
  {
    typedef typename memory::buffer<T,A>::reference type;
  };

  template<typename T, typename A>
  struct dereference_<memory::buffer<T,A> const&,1>
  {
    typedef typename memory::buffer<T,A>::const_reference type;
  };

  template<typename T, typename A>
  struct dereference_<memory::buffer<T,A>,1>
  {
    typedef typename memory::buffer<T,A>::value_type type;
  };
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

namespace nt2 { namespace memory
{
  //============================================================================
  // buffer initialize - Part of Buffer Concept
  //============================================================================
  template< typename T,  typename P, typename A
          , typename Sizes, typename Bases
          >
  inline void initialize( buffer<T,A>& v
                          , Sizes const& s, Bases const& b, P const& p
                          )
  {
    BOOST_ASSERT(boost::fusion::size(s) == 1);
    BOOST_ASSERT(boost::fusion::size(b) == 1);
    v.restructure( boost::fusion::at_c<0>(b)
                   ,slice<1>(s,p)
                 );
  }

  //============================================================================
  // buffer resize - Part of Buffer Concept
  //============================================================================
  template< typename T,  typename P, typename A
          , typename Sizes, typename Bases
          >
  inline void resize( buffer<T,A>& v
                      , Sizes const& s, Bases const& b, P const& p
                    )
  {
    BOOST_ASSERT(boost::fusion::size(s) == 1);
    BOOST_ASSERT(boost::fusion::size(b) == 1);
    v.restructure( boost::fusion::at_c<0>(b)
                   ,slice<1>(s,p)
                 );
  }


  //============================================================================
  // buffer share - Part of SharingBuffer Concept
  //============================================================================
  template<   typename T, typename P, typename A
              , typename Sizes, typename Bases
          >
  inline void share( buffer<T,A>& v
                     , Sizes const& s, Bases const& b, P const& p
                   )
  {
    initialize(v,s,b,p);
  }


} }

#endif
