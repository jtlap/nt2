//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/core/container/meta/model_of.hpp>
#include <nt2/core/container/meta/value_of.hpp>
#include <nt2/core/container/meta/reference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace boost { template<class T, std::size_t N> class array; }

//==============================================================================
// Fill out the Buffer concepts for boost::array
//==============================================================================
namespace nt2 { namespace meta
{
  //============================================================================
  // dimensions_of specialization
  //============================================================================
  template<typename T, std::size_t N>
  struct  dimensions_of< boost::array<T,N> >
        : boost::mpl::size_t<1 + dimensions_of<T>::value>
  {};

  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, std::size_t N>
  struct value_of< boost::array<T,N> > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, std::size_t N>
  struct model_of< boost::array<T,N> >
  {
    typedef struct make
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle array of array
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base;
        typedef boost::array<base,N>                                type;
      };
    } type;
  };
} }

namespace nt2 { namespace memory
{
  //============================================================================
  // boost::array initialize - Part of Buffer Concept
  //============================================================================
  template< typename T, std::size_t N
          , typename Sizes, typename Bases, typename Padding
          >
  inline void initialize( boost::array<T,N>&
                        , Sizes const&, Bases const&, Padding const&
                        )
  {}
} }

#endif
