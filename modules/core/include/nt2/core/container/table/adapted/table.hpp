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
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/dimensions_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2
{
  namespace tag       { struct table_; }
  namespace container { template<class T, class S> struct table; }
}

namespace nt2 { namespace meta
{
  //============================================================================
  // Container of the main nt2 proto domain act as tables
  //============================================================================
  template<> struct container_of<container::domain>
  {
    struct type
    {
      template<class T, class S> struct apply
      {
        typedef container::container<tag::table_, T, S> type;
      };
    };
  };
} }

//==============================================================================
// Fill out the Buffer concepts
//==============================================================================
namespace nt2 { namespace meta
{
  template<class T, class S>
  struct dimensions_of< nt2::container::table<T,S> > 
          : boost::mpl::size_t<container::table<T,S>::extent_type::static_size> 
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

  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::memory::container<tag::table_, T, S>, Origin >
  {
    typedef table_< typename property_of< typename value_of<T>::type
                                        , Origin
                                        >::type
                  , S
                  >                                   type;
  };

  //============================================================================
  // table use container<tag::table_> to do its biddings
  //============================================================================
  template<class T, class S> struct semantic_of< nt2::container::table<T, S> >
  {
    typedef nt2::memory::container<tag::table_,T, S> type;
  };  
} } }

#endif
