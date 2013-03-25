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
#include <nt2/sdk/memory/category.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace nt2 { namespace meta
{
  /// INTERNAL ONLY memory::container models Container
  template<typename T, typename S, typename Sema>
  struct is_container< memory::container<T, S, Sema> > : boost::mpl::true_ {};

  /// INTERNAL ONLY Option of a container use its settings and semantic
  template<typename T, typename S, typename Sema, typename Tag>
  struct  option<memory::container<T, S, Sema> , Tag>
        : option<S, Tag, Sema>
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  /// INTERNAL ONLY value_of for container
  template<typename T, typename S, typename Sema>
  struct value_of< nt2::memory::container<T,S,Sema> > { typedef T type; };

  template<typename T,typename S, typename Sema>
  struct value_of< nt2::memory::container<T,S,Sema>& >
  {
    typedef typename nt2::memory::container<T,S,Sema>::reference type;
  };

  template<typename T,typename S, typename Sema>
  struct value_of< nt2::memory::container<T,S,Sema> const&>
  {
    typedef typename nt2::memory::container<T,S,Sema>::const_reference type;
  };

  /// INTERNAL ONLY model_of for container
  template<typename T, typename S, typename Sema>
  struct model_of< nt2::memory::container<T,S,Sema> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef nt2::memory::container<X,S,Sema> type;
      };
    };
  };

  /// INTERNAL ONLY hierarchy_of for container
  template<typename T, typename S, typename Sema, typename Origin>
  struct hierarchy_of< nt2::memory::container<T,S,Sema>, Origin >
  {
    typedef container_< typename boost::dispatch::meta::property_of<T,Origin>::type
                      , S, Sema
                      >                   type;
  };

  /// INTERNAL ONLY container builds a terminal from its semantic
  template<typename T, typename S, typename Sema>
  struct  terminal_of< nt2::memory::container<T,S,Sema> >
        : Sema::template terminal_of<T,S>
  {};
} } }

#endif
