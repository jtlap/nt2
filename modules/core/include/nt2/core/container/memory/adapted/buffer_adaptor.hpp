//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_ADAPTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_ADAPTOR_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/storage_order_of.hpp>
#include <nt2/core/container/memory/buffer_adaptor.hpp>

//==============================================================================
// Fill out the Buffer concepts for std::vector
//==============================================================================
namespace nt2 { namespace meta
{
  template<  class Type,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  struct  dimensions_of< memory::buffer_adaptor<Type, Sizes, Bases, Padding, Shared > >
        : boost::mpl::size_t<1>
  {};


} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================

  template<  class Type,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  struct value_of< nt2::memory::buffer_adaptor<Type, Sizes, Bases, Padding, Shared> > : value_of<Type>
  {};

  // ============================================================================
  // model_of specialization
  // ============================================================================

  template<  class Type,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  struct model_of< nt2::memory::buffer_adaptor<Type, Sizes, Bases, Padding, Shared> >
  {};


  template<  class Type, class Allocator,
             class Sizes ,
             class Bases ,
             class Padding ,
             class Shared
          >
  struct model_of< nt2::memory::buffer_adaptor<std::vector<Type, Allocator>, Sizes, Bases, Padding, Shared> >
  {
    struct type
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle vector of vector
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<Type>::type,X>::type base;
        typedef typename Allocator::template rebind<base>::other       alloc;
        typedef nt2::memory::buffer_adaptor<std::vector<base,alloc>, Sizes, Bases, Padding, Shared >  type;
      };
    };
  };

} } }

namespace nt2 { namespace details
{
  template<std::size_t Dims> struct build
  {
    template<typename T, typename A, typename Sizes>
    static inline void apply( std::vector<T,A>& v, Sizes const& s)
    {
      v.resize(boost::fusion::at_c<Dims-1>(s));
      inner_apply(v,s,boost::mpl::size_t<Dims>());
    }

    template<typename T, typename A, typename Sizes, typename N> static inline
    void inner_apply( std::vector<T,A>& v, Sizes const& s, N)
    {
      for(std::size_t i=0;i<boost::fusion::at_c<Dims-1>(s);++i)
        build<Dims-1>::apply(v[i],s);
    }

    template<typename T, typename A, typename Sizes> static inline
    void inner_apply( std::vector<T,A>&, Sizes const&, boost::mpl::size_t<1> const&)
    {}
  };
} }

namespace nt2 { namespace memory
{

  //============================================================================
  // std::vector resize - Part of Buffer Concept
  //============================================================================

  template< typename Type, typename Allocator
            , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void resize( nt2::memory::buffer_adaptor<std::vector<Type, Allocator>, Sizes, Bases, Padding, Shared>& b
                      , Sizes const& s
                      )
  {
    b.resize(boost::fusion::at_c<0>(s));
  }


  //============================================================================
  // std::vector rebase - Part of Buffer Concept
  //============================================================================

    template< typename Type, typename Allocator
              , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void rebase( nt2::memory::buffer_adaptor<std::vector<Type, Allocator>, Sizes, Bases, Padding, Shared>& b 
                      , Bases const& bs
                      )
  {
    b.rebase(bs);
  }


  //============================================================================
  // std::vector restructure - Part of Buffer Concept
  //============================================================================

  template< typename Type, typename Allocator
            , typename Sizes, typename Bases, typename Padding, typename Shared
            >
  inline void restructure( nt2::memory::buffer_adaptor<std::vector<Type, Allocator>, Sizes, Bases, Padding, Shared>& b
                           , Sizes const& sz, Bases const& bs
                           )
  {
    b.restructure(bs,sz);
  }

} }

#endif
