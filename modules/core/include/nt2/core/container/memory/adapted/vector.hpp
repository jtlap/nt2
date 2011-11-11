//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Fill out the Buffer concepts for std::vector
//==============================================================================
namespace nt2 { namespace meta
{
  template<typename T, typename A>
  struct  dimensions_of< std::vector<T,A> >
        : boost::mpl::size_t<1 + dimensions_of<T>::value>
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename A>
  struct value_of< std::vector<T,A> > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename A>
  struct model_of< std::vector<T,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle vector of vector
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base;
        typedef typename A::template rebind<base>::other            alloc;
        typedef std::vector<base,alloc>                             type;
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
  // std::vector initialize - Part of Buffer Concept
  //============================================================================
    template< typename T, typename A
            , typename Sizes, typename Bases, typename Padding
            >
  inline void initialize( std::vector<T,A>& v
                        , Sizes const& s, Bases const&, Padding const&
                        )
  {
    //==========================================================================
    // Recursively allocate all level of the current std::vector
    //==========================================================================
    details::build<meta::dimensions_of<std::vector<T,A> >::value>::apply(v,s);
  }
} }

#endif
