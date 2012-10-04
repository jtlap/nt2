//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_REF_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Container>
  struct  is_container< memory::container_ref<Container> >
        : boost::mpl::true_
  {};

  template<class Container>
  struct  is_container_ref< memory::container_ref<Container> >
        : boost::mpl::true_
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // scalar_of specializations
  //============================================================================
  template<class Container>
  struct  scalar_of< nt2::memory::container_ref<Container> >
        : scalar_of<Container>
  {
  };

  template<class Container>
  struct  scalar_of< nt2::memory::container_ref<Container> const >
        : scalar_of<Container>
  {
  };

  template<class Container>
  struct  scalar_of< nt2::memory::container_ref<Container>& >
        : scalar_of<Container&>
  {
  };

  template<class Container>
  struct  scalar_of< nt2::memory::container_ref<Container> const& >
        : scalar_of<Container const&>
  {
  };

  //============================================================================
  // value_of specializations
  //============================================================================
  template<class Container>
  struct value_of< nt2::memory::container_ref<Container> >
   : value_of<Container>
  {
  };

  template<class Container>
  struct value_of< nt2::memory::container_ref<Container> const >
   : value_of<Container>
  {
  };

  template<class Container>
  struct value_of< nt2::memory::container_ref<Container>& >
   : value_of<Container>
  {
  };

  template<class Container>
  struct value_of< nt2::memory::container_ref<Container> const& >
   : value_of<Container>
  {
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class Container>
  struct model_of< nt2::memory::container_ref<Container> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container_ref<X> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class Container, class Origin>
  struct hierarchy_of< nt2::memory::container_ref<Container>, Origin >
   : hierarchy_of< Container, Origin >
  {
  };
} } }

#endif
