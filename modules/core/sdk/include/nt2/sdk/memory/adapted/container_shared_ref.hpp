//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_ADAPTED_CONTAINER_SHARED_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_ADAPTED_CONTAINER_SHARED_REF_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/make_shared.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Container, bool Own>
  struct  is_container< memory::container_shared_ref<Container, Own> >
        : boost::mpl::true_ {};

  template<class Container, bool Own>
  struct  is_container_ref< memory::container_shared_ref<Container, Own> >
        : boost::mpl::true_ {};

} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // scalar_of specializations
  //============================================================================
  template<class Container, bool Own>
  struct  scalar_of< nt2::memory::container_shared_ref<Container, Own> >
        : scalar_of<Container>
  {
  };

  template<class Container, bool Own>
  struct  scalar_of< nt2::memory::container_shared_ref<Container, Own> const >
        : scalar_of<Container>
  {
  };

  template<class Container, bool Own>
  struct  scalar_of< nt2::memory::container_shared_ref<Container, Own>& >
        : scalar_of<Container&>
  {
  };

  template<class Container, bool Own>
  struct  scalar_of< nt2::memory::container_shared_ref<Container, Own> const& >
        : scalar_of<Container const&>
  {
  };

  //============================================================================
  // value_of specializations
  //============================================================================
  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> const >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own>& >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> const& >
   : value_of<Container>
  {
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class Container, bool Own>
  struct model_of< nt2::memory::container_shared_ref<Container, Own> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container_shared_ref<X, Own> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class Container, bool Own, class Origin>
  struct hierarchy_of< nt2::memory::container_shared_ref<Container, Own>, Origin >
   : hierarchy_of< Container, Origin >
  {
  };

  template<class T, class S>
  struct terminal_of_shared< nt2::memory::container<T, S> >
  {
    typedef nt2::memory::container<T, S>                        container;
    typedef nt2::memory::container_shared_ref<container, true>  container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0
                                    >                           basic_expr;
    typedef nt2::container::expression< basic_expr
                                      , container
                                      , boost::proto::is_proto_expr
                                      >                         type;
    static type make()
    {
      return type(basic_expr::make(container_ref(boost::make_shared<container>())));
    }
  };
} } }

#endif
