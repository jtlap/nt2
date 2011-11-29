//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
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
  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct iliffe_buffer;
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct dimensions_of< memory::iliffe_buffer<D,T,DB,IB,SO,P,A> > : boost::mpl::size_t<D>
  {};

  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct storage_order_of< memory::iliffe_buffer<D,T,DB,IB,SO,P,A> >
  {
    typedef SO type;
  };

  //============================================================================
  // dereference_ specialization
  //============================================================================
  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A, std::size_t Level>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A>&,Level>
  {
    typedef typename add_pointers<T,D-Level>::type&  type;
  };


  //============================================================================
  // dereference_ specialization
  //============================================================================
  template<std::size_t D, typename T, typename DB, typename IB, typename SO,typename P, typename A, std::size_t Level>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A>,Level>
  {
    typedef typename add_pointers<T,D-Level>::type  type;
  };

  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A, std::size_t Level>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A> const&,Level>
  {
    typedef typename add_pointers<T,D-Level>::type const&  type;
  };

  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A>&,D>
  {
    typedef typename memory::iliffe_buffer<D,T,DB,IB,SO,P,A>::reference type;
  };

  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A> const&,D>
  {
    typedef typename memory::iliffe_buffer<D,T,DB,IB,SO,P,A>::const_reference type;
  };

  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct dereference_<memory::iliffe_buffer<D,T,DB,IB,SO,P,A>,D>
  {
    typedef typename memory::iliffe_buffer<D,T,DB,IB,SO,P,A>::value_type type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct value_of< nt2::memory::iliffe_buffer<D,T,DB,IB,SO,P,A> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A>
  struct model_of< nt2::memory::iliffe_buffer<D,T,DB,IB,SO,P,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename A::template rebind<X>::other alloc;
        typedef nt2::memory::iliffe_buffer<D,X,DB,IB,SO,P,alloc>    type;
      };
    };
  };
} } }

namespace nt2 { namespace memory
{
  //============================================================================
  // iliffe_buffer initialize - Part of Buffer Concept
  //============================================================================
  template< std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A
          , typename Sizes, typename Bases
          >
  inline void initialize( iliffe_buffer<D,T,DB,IB,SO,P,A>& v
                        , Sizes const& s, Bases const& b, P const& p
                        )
  {
    v.initialize(s,b,p);
  }

  template< std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A
          , typename Sizes, typename Bases
          >
  inline void initialize( iliffe_buffer<D,T,DB,IB,SO,P,A>& v
                          , Sizes const& s, Bases const& b, P const& p, T* const& d
                        )
  {
     v.initialize(s,b,p,d);
  }

  //============================================================================
  // iliffe_buffer resize - Part of Buffer Concept
  //============================================================================
  template< std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A
          , typename Sizes, typename Bases
          >
  inline void resize( iliffe_buffer<D,T,DB,IB,SO,P,A>& v
                    , Sizes const& s, Bases const& b, P const& p
                    )
  {
    v.resize(s,b,p);
  }

  //============================================================================
  // iliffe_buffer share - Part of SharingBuffer Concept
  //============================================================================
  template< std::size_t D, typename T, typename DB, typename IB, typename SO, typename P, typename A
          , typename Sizes, typename Bases, typename Target
          >
  inline void share( iliffe_buffer<D,T,DB,IB,SO,P,A>& v
                   , Sizes const& s, Bases const& b, P const& p
                   , Target const& t
                   )
  {
    v.initialize(s,b,p,t);
  }

} }

#endif
