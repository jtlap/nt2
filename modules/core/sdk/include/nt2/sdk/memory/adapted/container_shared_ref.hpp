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

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/semantic.hpp>
#include <boost/dispatch/meta/terminal_of_shared.hpp>

namespace nt2 { namespace tag
{
  struct table_;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class T, class S>
  struct  is_container< memory::container_shared_ref<T, S, true> >
        : boost::mpl::true_ {};

  template<class T, class S, bool Own>
  struct  is_container_ref< memory::container_shared_ref<T, S, Own> >
        : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specializations
  //============================================================================
  template<class T, class S, bool Own>
  struct value_of< nt2::memory::container_shared_ref<T, S, Own> >
  {
    typedef T& type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class T, class S, bool Own>
  struct model_of< nt2::memory::container_shared_ref<T, S, Own> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container_shared_ref<X, S, Own> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class T, class S, bool Own, class Origin>
  struct hierarchy_of< nt2::memory::container_shared_ref<T, S, Own>, Origin >
  {
    typedef container_< typename boost::dispatch::meta::property_of<T,Origin>::type
                      , S, Sema
                      >                   type;
  };

  template<class T, class S>
  struct terminal_of_shared< nt2::memory::container<T, S> >
  {
    typedef nt2::memory::container<T, S>                        container;
    typedef nt2::memory::container_shared_ref<T, S, true>       container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal
                                    , boost::proto::term<container_ref>
                                    , 0
                                    >                           basic_expr;
    typedef nt2::container::expression< basic_expr
                                      , container&
                                      >                         type;
    static type make()
    {
      return type(basic_expr::make(container_ref()));
    }
  };
} } }

#endif
