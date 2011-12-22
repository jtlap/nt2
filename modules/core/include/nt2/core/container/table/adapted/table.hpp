//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_ADAPTED_TABLE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_ADAPTED_TABLE_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/storage_order_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace container
{
  template<class Type, class Settings> struct table;
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<class T, class S>
  struct dimensions_of< nt2::container::table<T,S> > 
          : boost::mpl::size_t<container::table<T,S>::container_type::extent_type::static_size> 
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<class T, class S> struct value_of< nt2::container::table<T,S> >
  {
    typedef T type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename S> struct model_of< nt2::container::table<T,S> >
  {
    struct type
    {
      template<class X>
      struct apply { typedef nt2::container::table<X,S> type; };
    };
  };
} } }

#endif
