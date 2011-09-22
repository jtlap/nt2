//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_COMPOSITE_BUFFER_HPP

#include <boost/mpl/size_t.hpp>
#include <nt2/core/container/meta/reference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template< typename Buffer > struct composite_buffer;
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<typename B>
  struct  dimensions_of< memory::composite_buffer<B> >
        : dimensions_of< B >
  {};

  //============================================================================
  // dereference_ specialization
  //============================================================================
  template<typename B, std::size_t Level>
  struct dereference_<memory::composite_buffer<B>&,Level>
  {
    struct local
    {
      template<class T> struct apply
      {
        typedef typename dereference_<T&,Level>::type type;
      };
    };

    typedef typename boost::mpl::
            transform < typename memory::composite_buffer<B>::data_type
                      , local
                      >::type                                               type;
  };

  template<typename B, std::size_t Level>
  struct dereference_<memory::composite_buffer<B> const&,Level>
  {
    struct local
    {
      template<class T> struct apply
      {
        typedef typename dereference_<T const&,Level>::type type;
      };
    };

    typedef typename boost::mpl::
            transform < typename memory::composite_buffer<B>::data_type
                      , local
                      >::type                                               type;
  };
} }

namespace nt2 { namespace memory
{
  //============================================================================
  // composite_buffer initialize - Part of Buffer Concept
  //============================================================================
  template<typename B, typename Sizes, typename Bases,typename Padding>
  inline void initialize( composite_buffer<B>& v
                        , Sizes const& s, Bases const& b, Padding const& p
                        )
  {
    v.initialize(s,b,p);
  }

  //============================================================================
  // composite_buffer share - Part of SharingBuffer Concept
  //============================================================================
  template< typename B
          , typename Sizes, typename Bases
          , typename Padding, typename Target
          >
  inline void share( composite_buffer<B>& v
                   , Sizes const& s, Bases const& b, Padding const& p
                   , Target const& t
                   )
  {
    v.initialize(s,b,p,t);
  }
} }

#endif
