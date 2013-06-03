//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_ADD_SETTINGS_HPP_INCLUDED
#define NT2_SDK_META_ADD_SETTINGS_HPP_INCLUDED

#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/domain.hpp>
#include <nt2/core/settings/forward/settings.hpp>
#include <boost/proto/expr.hpp>

namespace nt2 { namespace meta
{
  template<class T, class S>
  struct add_settings
  {
    typedef nt2::settings type(T, S);
  };

  template<class T, class S>
  struct add_settings<T&, S>
  {
    typedef typename add_settings<T, S>::type& type;
  };

  template<class T, class S>
  struct add_settings<T const, S>
  {
    typedef typename add_settings<T, S>::type const type;
  };

  template<class T, class S, class S2>
  struct add_settings< memory::container<T, S>, S2 >
  {
    typedef memory::container<T, typename add_settings<S, S2>::type> type;
  };

  template<class T, class S, class S2>
  struct add_settings< memory::container_ref<T, S>, S2 >
  {
    typedef memory::container_ref<T, typename add_settings<S, S2>::type> type;
  };

  template<class T, class S, bool Own, class S2>
  struct add_settings< memory::container_shared_ref<T, S, Own>, S2 >
  {
    typedef memory::container_shared_ref<T, typename add_settings<S, S2>::type, Own> type;
  };

  template<class T, class S>
  struct add_settings< boost::proto::basic_expr<boost::proto::tag::terminal, boost::proto::term<T>, 0l>, S >
  {
    typedef boost::proto::basic_expr<boost::proto::tag::terminal, boost::proto::term<typename add_settings<T, S>::type>, 0l> type;
  };

  template<class Expr, class Semantic, class S>
  struct add_settings< nt2::container::expression<Expr, Semantic>, S >
  {
    typedef nt2::container::expression<typename add_settings<Expr, S>::type, typename add_settings<Semantic, S>::type> type;
  };

  template<class T, class S, class S2>
  struct add_settings< container::table_view<T, S>, S2 >
  {
    typedef container::table_view<T, typename add_settings<S, S2>::type> type;
  };

  template<class T, class S, class S2>
  struct add_settings< container::table_shared_view<T, S>, S2 >
  {
    typedef container::table_shared_view<T, typename add_settings<S, S2>::type> type;
  };

  template<class T, class S, class S2>
  struct add_settings< container::table<T, S>, S2 >
  {
    typedef container::table<T, typename add_settings<S, S2>::type> type;
  };
} }

#endif
