//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DOMAIN_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <boost/proto/domain.hpp>

#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2 { namespace container
{
  template<class T, class Enable = void>
  struct proto_value
    : boost::dispatch::meta::as_ref<T>
  {
  };

  template<class T, class Enable = void>
  struct proto_value_impl
   : boost::dispatch::meta::strip<T>
  {
  };

  template<class T>
  struct proto_value_impl<T, typename boost::enable_if< boost::is_same<typename boost::proto::tag_of<T>::type, boost::proto::tag::terminal> >::type>
    : boost::add_reference<T>
  {
  };

  template<class T>
  struct proto_value<T, typename boost::enable_if< boost::proto::is_expr<T> >::type>
   : proto_value_impl<T>
  {
  };

  struct  domain
        : boost::proto::domain< container::generator_transform<domain>
                              , container::grammar
                              >
  {
    template<class T>
    struct as_child : boost::proto::callable
    {
      typedef typename proto_value<T>::type result_type;
      BOOST_FORCEINLINE result_type
      operator()(T& t) const
      {
        return result_type(t);
      }
    };
  };
} }

#endif
