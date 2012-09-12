//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class T, class S>
  struct is_container< memory::container<T, S> > : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // scalar_of specialization
  //============================================================================
  template<class T,class S>
  struct  scalar_of< nt2::memory::container<T,S> >
  {
    typedef typename nt2::memory::container<T,S>::value_type type;
  };

  template<class T,class S>
  struct  scalar_of< nt2::memory::container<T,S>& >
  {
    typedef typename nt2::memory::container<T,S>::reference type;
  };

  template<class T,class S>
  struct  scalar_of< nt2::memory::container<T,S> const >
  {
    typedef typename nt2::memory::container<T,S>::value_type const type;
  };

  template<class T,class S>
  struct  scalar_of< nt2::memory::container<T,S> const&>
  {
    typedef typename nt2::memory::container<T,S>::const_reference type;
  };

  //============================================================================
  // value_of specialization
  //============================================================================
  template<class T, class S>
  struct value_of< nt2::memory::container<T,S> > { typedef T type; };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class T, class S>
  struct model_of< nt2::memory::container<T,S> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container<X, S> type;
      };
    };
  };

  //============================================================================
  // container hierarchy is given by its semantic_
  //============================================================================
  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::memory::container<T, S>, Origin >
  {
    typedef typename nt2::memory::container<T, S>::semantic_t     semantic_t;
    typedef typename semantic_t::template apply<T,S,Origin>::type type;
  };

  template<class T, class S>
  struct terminal_of< nt2::memory::container<T,S> >
  {
    typedef nt2::container::table<T, S> type;
  };
} } }

#endif
