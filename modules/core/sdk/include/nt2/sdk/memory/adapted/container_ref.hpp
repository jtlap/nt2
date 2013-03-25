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
#include <nt2/sdk/memory/category.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/add_settings.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/forward/semantic.hpp>

namespace nt2 { namespace tag
{
  struct table_;
} }

namespace nt2 { namespace meta
{
  template<class T, class S>
  struct  is_container_ref< memory::container_ref<T, S> >
        : boost::mpl::true_
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specializations
  //============================================================================
  template<class T, class S>
  struct value_of< nt2::memory::container_ref<T, S> >
  {
    typedef T& type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class T, class S>
  struct model_of< nt2::memory::container_ref<T, S> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container_ref<X, S> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::memory::container_ref<T, S>, Origin >
  {
    typedef container_< typename boost::dispatch::meta::property_of<T,Origin>::type
                      , S, Sema
                      >                   type;
  };

  /// INTERNAL ONLY container builds a terminal from its semantic
  template<typename T, typename S, typename Sema>
  struct  terminal_of< nt2::memory::container_ref<T,S,Sema> >
        : Sema::template terminal_of<T,S>
  {};
} } }

#endif
